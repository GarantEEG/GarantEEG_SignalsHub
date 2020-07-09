/**
@file filtersdialog.h

@brief Объявление класса окна настройки фильтров

@author Мустакимов Т.Р.
**/
//----------------------------------------------------------------------------------
#ifndef FILTERSDIALOG_H
#define FILTERSDIALOG_H
//----------------------------------------------------------------------------------
#include <QDialog>

#include <include/GarantEEG_API_CPP.h>
//----------------------------------------------------------------------------------
namespace Ui
{
    class FiltersDialog;
}
//----------------------------------------------------------------------------------
//! Класс диалога настройки фильтров
class FiltersDialog : public QDialog
{
    Q_OBJECT

public:
	/**
	 * @brief FiltersDialog Конструктор
	 * @param parent Виджет-родитель
	 */
    explicit FiltersDialog(QWidget *parent = nullptr);

	/**
	 * @brief ~FiltersDialog Деструктор
	 */
    ~FiltersDialog();

	/**
	 * @brief SaveSettings Сохранить настройки
	 */
    void SaveSettings();

	/**
	 * @brief Instance Получить указатель на синглтон объекта диалога настройки фильтров
	 * @return Указатель на диалог
	 */
    static FiltersDialog *Instance();

	/**
	 * @brief GetUseFilters Получить состояние использования фильтров
	 * @return true если нужно использовать фильтры, false если нет (галочка не установлена)
	 */
    bool GetUseFilters();

	/**
	 * @brief UpdateEegFilters Обновление фильтров на устройстве
	 */
    void UpdateEegFilters();

	/**
	 * @brief SetEeg Установить указатель на интерфейс для работы с устройством
	 * @param eeg Указатель на интерфейс для работы с устройством
	 */
    void SetEeg(GarantEEG::IGarantEEG *eeg);

	/**
	 * @brief OnAddedFilter Функция добавления фильтра
	 * @param type Тип фильтра (название, строкой)
	 * @param typeId Идентификатор типа фильтра
	 * @param order Порядок фильтра
	 * @param rangeMin Минимальная граница среза
	 * @param rangeMax Максимальная границы среза
	 */
    void OnAddedFilter(const QString &type, int typeId, int order, int rangeMin, int rangeMax);

private slots:
	/**
	 * @brief on_pb_Add_clicked Нажатие на кнопку добавления нового фильтра
	 */
    void on_pb_Add_clicked();

	/**
	 * @brief on_pb_RemoveSelected_clicked Нажатие на кнопку удаления текущего выбранного фильтра
	 */
    void on_pb_RemoveSelected_clicked();

	/**
	 * @brief on_pb_RemoveAll_clicked Нажатие на кнопку удаления всех фильтров
	 */
    void on_pb_RemoveAll_clicked();

private:
	//! Указатель на UI диалога
    Ui::FiltersDialog *ui;

	//! Указатель на интерфейс для работы с устройством
    GarantEEG::IGarantEEG *m_Eeg = nullptr;

	//! Перечисление смещений для получения данных из GUI элементов (юзер дата)
    enum FILTER_VARIABLE_INDEX
    {
		//! Смещение для типа фильтра (название, строкой)
        FVI_TYPE = 0,
		//! Смещение для идентификатора типа фильтра
        FVI_TYPE_ID,
		//! Смещение для порядка фильтра
        FVI_ORDER,
		//! Смещение для нижней границы среза фильтра
        FVI_RANGE_MIN,
		//! Смещение для верхней границы среза фильтра
        FVI_RANGE_MAX
    };
};
//----------------------------------------------------------------------------------
#endif // FILTERSDIALOG_H
//----------------------------------------------------------------------------------
