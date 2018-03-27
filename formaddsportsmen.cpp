#include "formaddsportsmen.h"
#include "exceptionhandler.h"
#include "diarytrainer.h"

#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QGroupBox>
#include <QHBoxLayout>

#include <QDebug>

FormAddSportsmen::FormAddSportsmen(QWidget *parent) :
    QWidget(parent)
{

}

FormAddSportsmen::FormAddSportsmen(QString genderFilename)
{
    this->resize(400, 180);
    this->genderFilename = genderFilename;
    setWindowTitle("Добавление спортсмена");
    CreateWidgets();
}

FormAddSportsmen::~FormAddSportsmen()
{

}

void FormAddSportsmen::CreateWidgets()
{
    lName = new QLabel("<font size = 4 face = Georgia>Введите имя: </font>", this);
    lSecondName = new QLabel("<font size = 4 face = Georgia>Введите фамилию: </font>", this);
    SetStyle(lName);
    SetStyle(lSecondName);
    lName->setGeometry(QRect(10, 10, 150, 30));
    lSecondName->setGeometry(QRect(10, 50, 150, 30));
    leName = new QLineEdit(this);
    leSecondName = new QLineEdit(this);
    leName->setGeometry(QRect(170, 10, 220, 30));
    leSecondName->setGeometry(QRect(170, 50, 220, 30));
    confirm = new QPushButton("Добавить", this);
    confirm->setGeometry(QRect(10, 140, 380, 30));
    connect(confirm, SIGNAL(clicked()), this, SLOT(actionConfirmAdd()));
    QLabel *lblInfo = new QLabel("<font size = 4 face = Georgia><i>После добавления нового спортсмена нажмите на кнопку \"Обновить список\"</i></font>", this);
    lblInfo->setGeometry(QRect(10, 90, 380, 50));
    lblInfo->setWordWrap(true);
}

void FormAddSportsmen::actionConfirmAdd()
{
    if (leName->text() == "" || leSecondName->text() == "")
    {
        ExceptionHandler::exceptionEmptyEnter(this);
        return;
    }
    QFile fin("CommonData\\" + genderFilename + ".txt");
    fin.open(QIODevice::ReadOnly);
    QString temp = fin.readLine();
    temp.remove(temp.size() - 1, 2);
    int tempSize = temp.toInt();
    tempSize++;
    QString allFile = QString::number(tempSize) + "\n";
    while (!fin.atEnd())
        allFile += fin.readLine();
    fin.close();
    allFile += leName->text() + " " + leSecondName->text() + "\n";
    fin.open(QIODevice::WriteOnly | QIODevice::Truncate);
    QTextStream stream(&fin);
    stream.setCodec(QTextCodec::codecForName("UTF-8"));
    stream << allFile;
    stream.flush();
    fin.close();
    this->close();
    fin.setFileName("DataSportsmens\\" + leName->text() + leSecondName->text() + "25.timedata");
    fin.open(QIODevice::WriteOnly | QIODevice::Text);
    QFile support("CommonData\\Template25.timedata");
    support.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream25(&fin);
    stream25 << support.readAll();
    stream.flush();
    support.close();
    fin.close();
    fin.setFileName("DataSportsmens\\" + leName->text() + leSecondName->text() + "50.timedata");
    fin.open(QIODevice::WriteOnly | QIODevice::Text);
    support.setFileName("CommonData\\Template50.timedata");
    support.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream50(&fin);
    stream50 << support.readAll();
    support.close();
    fin.close();
    delete this;
}


void FormAddSportsmen::SetStyle(QLabel* lbl)
{
    lbl->setStyleSheet("QLabel {"
                                            "background-color: white;"
                                            "border-style: solid;"
                                            "border-width: 1px;"
                                            "border-color: black; "
                                            "}");
}
