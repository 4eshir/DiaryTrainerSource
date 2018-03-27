#ifndef EXCEPTIONHANDLER_H
#define EXCEPTIONHANDLER_H

#include <QMainWindow>
#include "diarysportsmen.h"

class diarySportsmen;

class ExceptionHandler
{

public:
    ExceptionHandler();
    ~ExceptionHandler();

    static void exceptionNoTimeData(QMainWindow*); //на данной дистанции нет ни одного сохраненного времени
    static void exceptionOverflowTimeData(QMainWindow*); //для данной дистанции невозможно добавить новое время (переполнение)
    static void exceptionIncorrectTimeData(class diarySportsmen*, int); //неверный формат времени
    static void exceptionIncorrectTimeRange(QMainWindow*); //указан неверный отрезок времени для статистики (<0 или >365)
    static void exceptionIncorrectDistanceData(QMainWindow*); //указана неверная дистанция для отображения нормативов
    static void exceptionInsufficientDistanceData(QMainWindow*); //недостаточно данных для отображения нормативов (неактивна одна или более из 5 групп радиокнопок)
    static void exceptionEmptyEnter(QWidget*); //невозможно добавить нового спортсмена (отсутствует фамилия или имя)
    static void exceptionNullList(QWidget*); //невозможно обновить список - список пуст
    static void exceptionNullStyle(QWidget*); //не выбран стиль плавания

    static void exceptionNoDetected(QMainWindow*);//общее неизвестное исключение
    static void exceptionNoDetected(QWidget*);//общее неизвестное исключение

private:
};

#endif // EXCEPTIONHANDLER_H
