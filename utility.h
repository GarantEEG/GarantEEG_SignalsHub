/**
@file utility.h

@brief Объявление класса для общих функци приложения

@author Мустакимов Т.Р.
**/
//----------------------------------------------------------------------------------
#ifndef UTILITY_H
#define UTILITY_H
//----------------------------------------------------------------------------------
#include <QWidget>
#include <QSettings>
//----------------------------------------------------------------------------------
//! Класс утилит
class Utility
{
public:
	/**
	 * @brief Utility Конструктор
	 */
	Utility() {}

	/**
	 * @brief BoolToText Перевод bool в текст
	 * @param value Значение для перевода
	 * @return Текстовое представление
	 */
	static QString BoolToText(const bool &value);

	/**
	 * @brief RawStringToBool Конвертирование сырого текста в bool
	 * @param value Сырой текст для перевода
	 * @return Результат конвертирования
	 */
	static bool RawStringToBool(QString value);

	/**
	 * @brief BringWindowToTop Вывести виджет на 1 план
	 * @param window Виджет для вывода
	 */
	static void BringWindowToTop(QWidget *window);

	/**
	 * @brief CreateDirectoryFromFilePath Создать директорию по пути к файлу
	 * @param filePath Путь к файлу
	 */
	static void CreateDirectoryFromFilePath(QString filePath);

	/**
	 * @brief GetSettingInt Получить целочисленное значение из QSettings
	 * @param settings Сеттинги для работы
	 * @param name Ключ для получения значения
	 * @param defaultValue Значение по умолчанию
	 * @return Результат чтения сеттингов
	 */
    static int GetSettingInt(QSettings &settings, const QString &name, int defaultValue);
};
//----------------------------------------------------------------------------------
#endif // UTILITY_H
//----------------------------------------------------------------------------------
