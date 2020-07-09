/**
@file mainwindow.cpp

@brief Реализация класса основного окна приложения

@author Мустакимов Т.Р.
**/
//----------------------------------------------------------------------------------
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "resource.h"
#include "utility.h"
#include "filtersdialog.h"
#include "newfilterdialog.h"
#include <QTime>
#include <QDebug>
#include <chrono>
//----------------------------------------------------------------------------------
using clockk = std::chrono::system_clock;
using dsec = std::chrono::duration<double>;
using tps = std::chrono::time_point<clockk, dsec>;
//----------------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
//----------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
}
//----------------------------------------------------------------------------------
bool MainWindow::initialize()
{
	m_Eeg = GarantEEG::CreateDevice(GarantEEG::DT_GARANT);

	if (m_Eeg == nullptr)
		return false;

	QSettings settings("Neurotrend", "GarantEeg_SignalsHub");

	restoreGeometry(settings.value("MainWindowGeometry").toByteArray());
	restoreState(settings.value("MainWindowState").toByteArray());
	ui->cb_AutoReconnection->setChecked(Utility::GetSettingInt(settings, "AutoReconnect", 1) != 0);
	ui->le_IP->setText(settings.value("IP", "192.168.127.125").toString());
	ui->sb_Port->setValue(Utility::GetSettingInt(settings, "Port", 12345));

	qRegisterMetaType<GarantEEG::GARANT_EEG_DATA>("GarantEEG::GARANT_EEG_DATA");

	connect(this, &MainWindow::UpdateEegData, this, &MainWindow::OnUpdateEegData);
	connect(this, &MainWindow::EegChangeConnectionState, this, &MainWindow::OnEegChangeConnectionState);

	connect(&m_BatteryTimer, &QTimer::timeout, [this]()
	{
		if (m_Eeg != nullptr && m_Eeg->IsStarted())
			ui->pb_Battery->setValue(m_Eeg->GetBatteryStatus());
	});

	m_BatteryTimer.start(1000);

	lsl::stream_info info("GarantEEG", "EEG", 8/*channels count*/, 500/*rate*/, lsl::cf_float32, "GarantEEG");

	lsl::xml_element channels = info.desc().append_child("channels");

	for (int i = 0; i < 8; i++)
	{
		channels.append_child("channel")
			.append_child_value("label", QString("channel_%1").arg(i).toStdString())
			.append_child_value("type", "EEG")
			.append_child_value("unit", "microvolts");
	}

	info.desc().append_child("acquisition")
		.append_child_value("manufacturer", "Neurotrend");



	lsl::stream_info infoRx("GarantEEG.Resistance", "EEG.Resistance", 10/*channels count*/, 10/*rate*/, lsl::cf_float32, "GarantEEG.Resistance");

	lsl::xml_element channelsRx = infoRx.desc().append_child("channels");

	for (int i = 0; i < 10; i++)
	{
		channelsRx.append_child("channel")
			.append_child_value("label", QString("channel_rx_%1").arg(i).toStdString())
			.append_child_value("type", "EEG.Resistance")
			.append_child_value("unit", "kOhm");
	}

	infoRx.desc().append_child("acquisition")
		.append_child_value("manufacturer", "Neurotrend");



	m_Outlet = new lsl::stream_outlet(info, 8);
	m_OutletRx = new lsl::stream_outlet(infoRx, 10);

	FiltersDialog::Instance()->SetEeg(m_Eeg);

	m_Eeg->SetCallback_OnStartStateChanged(this, [](void *userData, uint state)
	{
		if (userData != nullptr)
			emit ((MainWindow*)userData)->EegChangeConnectionState(state);

		//qDebug() << "StartStateChanged" << state;
	});

	m_Eeg->SetCallback_OnRecordingStateChanged(this, [](void *userData, uint state)
	{
		Q_UNUSED(userData);
		Q_UNUSED(state);
		//qDebug() << "RecordingStateChanged" << state;
	});

	m_Eeg->SetCallback_ReceivedData(this, [](void *userData, const GarantEEG::GARANT_EEG_DATA *eegData)
	{
		//qDebug() << "ReceivedData";

		if (userData != nullptr)
			emit ((MainWindow*)userData)->UpdateEegData(*eegData);
	});

	show();

	return true;
}
//----------------------------------------------------------------------------------
void MainWindow::closeEvent(QCloseEvent *event)
{
	QSettings settings("Neurotrend", "GarantEeg_SignalsHub");

    settings.setValue("MainWindowGeometry", saveGeometry());
    settings.setValue("MainWindowState", saveState());
	settings.setValue("AutoReconnect", (ui->cb_AutoReconnection->isChecked() ? 1 : 0));
    settings.setValue("IP", ui->le_IP->text());
	settings.setValue("Port", ui->sb_Port->value());

    FiltersDialog::Instance()->SaveSettings();

    qApp->closeAllWindows();

    event->accept();
}
//----------------------------------------------------------------------------------
void MainWindow::on_pb_Start_clicked()
{
     if (m_Eeg == nullptr || m_Eeg->IsConnecting() || m_Eeg->IsStarted())
         return;

     ui->sb_Info->showMessage("Trying to connect...");

	 if (m_Eeg->Start(false, 500, qPrintable(ui->le_IP->text()), ui->sb_Port->value()))
     {
         ui->le_IP->setEnabled(false);
		 ui->sb_Port->setEnabled(false);
         ui->pb_Start->setEnabled(false);
         ui->cb_AutoReconnection->setEnabled(false);
     }
}
//----------------------------------------------------------------------------------
void MainWindow::on_pb_Stop_clicked()
{
    if (m_Eeg == nullptr || !m_Eeg->IsStarted())
        return;

    m_Eeg->Stop();

    FiltersDialog::Instance()->hide();
    NewFilterDialog::Instance()->hide();

    ui->le_IP->setEnabled(true);
	ui->sb_Port->setEnabled(true);
    ui->cb_AutoReconnection->setEnabled(true);

    ui->pb_Start->setEnabled(true);
    ui->pb_Stop->setEnabled(false);
	ui->pb_Filters->setEnabled(false);
}
//----------------------------------------------------------------------------------
void MainWindow::on_cb_AutoReconnection_stateChanged(int arg1)
{
    Q_UNUSED(arg1);

    if (m_Eeg != nullptr)
        m_Eeg->SetAutoReconnection(ui->cb_AutoReconnection->isChecked());
}
//----------------------------------------------------------------------------------
void MainWindow::OnEegChangeConnectionState(uint state)
{
    //connected
    if (state == GarantEEG::DCS_NO_ERROR)
    {
        ui->sb_Info->showMessage("Connected!", 5000);

        ui->le_IP->setEnabled(false);
		ui->sb_Port->setEnabled(false);
        ui->cb_AutoReconnection->setEnabled(true);

        ui->pb_Start->setEnabled(false);
        ui->pb_Stop->setEnabled(true);
		ui->pb_Filters->setEnabled(true);

        FiltersDialog::Instance()->UpdateEegFilters();
    }
    //connection errors or end of session
    else if (state <= GarantEEG::DCS_CONNECTION_CLOSED)
    {
        ui->sb_Info->showMessage("Failed to connect", 10000);

        ui->le_IP->setEnabled(true);
		ui->sb_Port->setEnabled(true);
        ui->cb_AutoReconnection->setEnabled(true);

        ui->pb_Start->setEnabled(true);
        ui->pb_Stop->setEnabled(false);
		ui->pb_Filters->setEnabled(false);
    }
}
//----------------------------------------------------------------------------------
void MainWindow::OnUpdateEegData(GarantEEG::GARANT_EEG_DATA eegData)
{
	bool useFilters = FiltersDialog::Instance()->GetUseFilters();

    double packetTime = dsec(clockk::now().time_since_epoch()).count();//eegData.Time / 1000.0;
    //qDebug("packetTime=%.03f, count=%i", packetTime, eegData.DataRecordsCount);

    for (int i = 0; i < eegData.DataRecordsCount; i++)
    {
        std::vector<float> sample;

        for (int j = 0; j < 8; j++)
            sample.push_back(useFilters ? eegData.FilteredChannelsData[i].Value[j] : eegData.RawChannelsData[i].Value[j]);

        m_Outlet->push_sample(sample, packetTime);
        packetTime += 0.002;
    }



    std::vector<float> sampleRx;

	for (int i = 0; i < 8; i++)
		sampleRx.push_back(eegData.ResistanceData.Value[i]);

    sampleRx.push_back(eegData.ResistanceData.Ref);
    sampleRx.push_back(eegData.ResistanceData.Ground);

    m_OutletRx->push_sample(sampleRx, eegData.Time / 1000.0);
}
//----------------------------------------------------------------------------------
void MainWindow::on_pb_Filters_clicked()
{
	Utility::BringWindowToTop(FiltersDialog::Instance());
}
//----------------------------------------------------------------------------------
