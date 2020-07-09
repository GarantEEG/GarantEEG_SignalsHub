/**
@file newfilterdialog.h

@brief Объявление класса окна добавления нового фильтра

@author Мустакимов Т.Р.
**/
//----------------------------------------------------------------------------------
#ifndef NEWFILTERDIALOG_H
#define NEWFILTERDIALOG_H
//----------------------------------------------------------------------------------
#include <QDialog>

#include <include/GarantEEG_API_CPP.h>
//----------------------------------------------------------------------------------
namespace Ui
{
    class NewFilterDialog;
}
//----------------------------------------------------------------------------------
//! Класс окна добавления нового фильтра
class NewFilterDialog : public QDialog
{
    Q_OBJECT

public:
	/**
	 * @brief NewFilterDialog Конструктор
	 * @param parent Виджет-родитель
	 */
    explicit NewFilterDialog(QWidget *parent = nullptr);

	/**
	 * @brief ~NewFilterDialog Деструктор
	 */
    ~NewFilterDialog();

	/**
	 * @brief Instance Получить указатель на синглтон объекта диалога добавления фильтра
	 * @return Указатель на диалог
	 */
    static NewFilterDialog *Instance();

	/**
	 * @brief Initialize Функция инициализации
	 */
    void Initialize();

	/**
	 * @brief InitializeAndShow Инициализировать диалог и отобразить
	 * @param eeg Указатель на интерфейс для работы с устройством
	 * @param dialog Указатель на диалог настроек фильтров
	 */
    void InitializeAndShow(GarantEEG::IGarantEEG *eeg, class FiltersDialog *dialog);

	/**
	 * @brief SetEeg Установить указатель на интерфейс для работы с устройством
	 * @param eeg Указатель на интерфейс для работы с устройством
	 */
    void SetEeg(GarantEEG::IGarantEEG *eeg);

private slots:
	/**
	 * @brief on_pb_OK_clicked Нажатие на кнопку ОК
	 */
    void on_pb_OK_clicked();

	/**
	 * @brief on_pb_Cancel_clicked Отмена добавления
	 */
    void on_pb_Cancel_clicked();

private:
	//! Указатель на UI диалога
    Ui::NewFilterDialog *ui;

	//! Указатель на интерфейс для работы с устройством
    GarantEEG::IGarantEEG *m_Eeg = nullptr;

	//! Указатель на диалог настроек фильтров
    class FiltersDialog *m_Dialog = nullptr;
};
//----------------------------------------------------------------------------------
#endif // NEWFILTERDIALOG_H
//----------------------------------------------------------------------------------
