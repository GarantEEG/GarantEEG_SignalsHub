/**
@file mainwindow.h

@brief Объявление класса основного окна приложения

@author Мустакимов Т.Р.
**/
//----------------------------------------------------------------------------------
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//----------------------------------------------------------------------------------
#include <QMainWindow>
#include <QCloseEvent>
#include <QTimer>

#include <lsl_cpp.h>
#include <include/GarantEEG_API_CPP.h>
//----------------------------------------------------------------------------------
namespace Ui
{
    class MainWindow;
}
//----------------------------------------------------------------------------------
//! Класс основного окна приложения
class MainWindow : public QMainWindow
{
    Q_OBJECT

protected:
	/**
	 * @brief closeEvent Событие закрытия окна приложения
	 * @param event Указатель на событие
	 */
    virtual void closeEvent(QCloseEvent *event) override;

public:
	/**
	 * @brief MainWindow Конструктор
	 * @param parent Виджет-родитель
	 */
    explicit MainWindow(QWidget *parent = nullptr);

	/**
	 * @brief ~MainWindow Деструктор
	 */
    ~MainWindow();

	/**
	 * @brief initialize Инициализация главного окна приложения
	 * @return true если инициализация прошла успешно, false если что-то пошло не так
	 */
	bool initialize();

signals:
	/**
	 * @brief EegChangeConnectionState Сигнал обновления информации о подключении к устройству
	 */
    void EegChangeConnectionState(uint);

	/**
	 * @brief UpdateEegData Сигнал получения нового фрэйма данных с устройства
	 */
    void UpdateEegData(GarantEEG::GARANT_EEG_DATA);

public slots:
	/**
	 * @brief OnEegChangeConnectionState Обновление информации о подключении к устройству
	 * @param state Текущее состояние
	 */
    void OnEegChangeConnectionState(uint state);

	/**
	 * @brief OnUpdateEegData Получение нового фрэймы данных с устройства
	 * @param eegData Фрэйм данных
	 */
    void OnUpdateEegData(GarantEEG::GARANT_EEG_DATA eegData);

private slots:
	/**
	 * @brief on_pb_Start_clicked Нажатие на кнопку запуска
	 */
    void on_pb_Start_clicked();

	/**
	 * @brief on_pb_Stop_clicked Нажатие на кнопку остановки
	 */
    void on_pb_Stop_clicked();

	/**
	 * @brief on_cb_AutoReconnection_stateChanged Изменение состояния галочки автоматического переподключения к устройству при разрыве связи
	 * @param arg1 Новое состояние
	 */
    void on_cb_AutoReconnection_stateChanged(int arg1);

	/**
	 * @brief on_pb_Filters_clicked Нажатие на кнопку настройки фильтров
	 */
	void on_pb_Filters_clicked();

private:
	//! Указатель на UI формы
    Ui::MainWindow *ui;

	//! Указатель на интерфейс для работы с устройством
    GarantEEG::IGarantEEG *m_Eeg = nullptr;

	//! Таймер обновления информации о заряде аккумулятора
    QTimer m_BatteryTimer;

	//! Аутлет данных по каналам
    lsl::stream_outlet *m_Outlet = nullptr;

	//! Аутлет данных по сопротивлению
    lsl::stream_outlet *m_OutletRx = nullptr;
};
//----------------------------------------------------------------------------------
#endif // MAINWINDOW_H
//----------------------------------------------------------------------------------
