#include "exceptionhandler.h"

#include <QMessageBox>

ExceptionHandler::ExceptionHandler()
{

}

ExceptionHandler::~ExceptionHandler()
{

}

void ExceptionHandler::exceptionInsufficientDistanceData(QMainWindow *mw)
{
    QMessageBox box;
    box.addButton(QMessageBox::StandardButton::Ok);
    box.setWindowTitle(QString("Ошибка ввода"));
    box.setText(QString("<font face = Georgia size = 3>Недостаточно данных!</font>"));
    box.setGeometry(QRect(mw->geometry().x() + 200, mw->geometry().y() + 160, 150, 30));
    box.exec();
}

void ExceptionHandler::exceptionIncorrectDistanceData(QMainWindow *mw)
{
    QMessageBox box;
    box.addButton(QMessageBox::StandardButton::Ok);
    box.setWindowTitle(QString("Ошибка ввода"));
    box.setText(QString("<font face = Georgia size = 3>Такой дистанции не существует!</font>"));
    box.setGeometry(QRect(mw->geometry().x() + 200, mw->geometry().y() + 160, 150, 30));
    box.exec();
}

void ExceptionHandler::exceptionIncorrectTimeRange(QMainWindow *mw)
{
    QMessageBox box;
    box.addButton(QMessageBox::StandardButton::Ok);
    box.setWindowTitle(QString("Ошибка ввода"));
    box.setText(QString("<font face = Georgia size = 3>Невозможно отобразить статистику за выбранный период времени!</font>"));
    box.setGeometry(QRect(mw->geometry().x() + 200, mw->geometry().y() + 160, 150, 30));
    box.exec();
}

void ExceptionHandler::exceptionIncorrectTimeData(diarySportsmen *wid, int i)
{
    QMessageBox box;
    box.addButton(QMessageBox::StandardButton::Ok);
    box.setWindowTitle(QString("Ошибка ввода"));
    box.setText(QString("<font face = Georgia size = 3>Введено неверное время! Повторите попытку</font>"));
    box.setGeometry(QRect(wid->geometry().x() + 200, wid->geometry().y() + 160, 150, 30));
    wid->arrEnterTime[3 * i]->setText("");
    wid->arrEnterTime[3 * i + 1]->setText("");
    wid->arrEnterTime[3 * i + 2]->setText("");
    wid->arrEnterTime[3 * i]->setPlaceholderText("Мин");
    wid->arrEnterTime[3 * i + 1]->setPlaceholderText("Сек");
    wid->arrEnterTime[3 * i + 2]->setPlaceholderText("Доли");
    box.exec();
}

void ExceptionHandler::exceptionOverflowTimeData(QMainWindow *mw)
{
    QMessageBox box;
    box.addButton(QMessageBox::StandardButton::Ok);
    box.setWindowTitle(QString("Ошибка записи"));
    box.setText(QString("<font face = Georgia size = 3>Невозможно добавить новое время на данной дистанции!</font>"));
    box.setGeometry(QRect(mw->geometry().x() + 200, mw->geometry().y() + 160, 150, 30));
    box.exec();
}

void ExceptionHandler::exceptionNoTimeData(QMainWindow *mw)
{
    QMessageBox box;
    box.addButton(QMessageBox::StandardButton::Ok);
    box.setWindowTitle(QString("Ошибка удаления"));
    box.setText(QString("<font face = Georgia size = 3>Невозможно удалить последнее время на дистанции - не найдено ни одной записи для данной дистанции!</font>"));
    box.setGeometry(QRect(mw->geometry().x() + 200, mw->geometry().y() + 160, 150, 30));
    box.exec();
}

void ExceptionHandler::exceptionNoDetected(QMainWindow *mw)
{
    QMessageBox box;
    box.addButton(QMessageBox::StandardButton::Ok);
    box.setWindowTitle(QString("Неидентифицированное исключение"));
    box.setText(QString("<font face = Georgia size = 3>Неизвестная ошибка! Закройте окно и продолжите работу</font>"));
    box.setGeometry(QRect(mw->geometry().x() + 200, mw->geometry().y() + 160, 150, 30));
    box.exec();
}

void ExceptionHandler::exceptionNullList(QWidget* wid)
{
    QMessageBox box;
    box.addButton(QMessageBox::StandardButton::Ok);
    box.setWindowTitle(QString("Ошибка обновления"));
    box.setText(QString("<font face = Georgia size = 3>Список пуст!</font>"));
    box.setGeometry(QRect(wid->geometry().x() + 200, wid->geometry().y() + 160, 150, 30));
    box.exec();
}

void ExceptionHandler::exceptionEmptyEnter(QWidget* wid)
{
    QMessageBox box;
    box.addButton(QMessageBox::StandardButton::Ok);
    box.setWindowTitle(QString("Ошибка ввода"));
    box.setText(QString("<font face = Georgia size = 3>Некорректное имя и/или фамилия! Повторите попытку</font>"));
    box.setGeometry(QRect(wid->geometry().x() + 200, wid->geometry().y() + 160, 150, 30));
    box.exec();
}

void ExceptionHandler::exceptionNullStyle(QWidget* wid)
{
    QMessageBox box;
    box.addButton(QMessageBox::StandardButton::Ok);
    box.setWindowTitle(QString("Ошибка ввода"));
    box.setText(QString("<font face = Georgia size = 3>Не выбран стиль!</font>"));
    box.setGeometry(QRect(wid->geometry().x() + 200, wid->geometry().y() + 160, 150, 30));
    box.exec();
}
