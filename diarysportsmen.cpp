#include "diarysportsmen.h"
#include "timedataparser.h"
#include "timedataeditor.h"
#include "exceptionhandler.h"
#include "time.h"
#include "statisticgraph.h"

#include <QFile>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>

diarySportsmen::diarySportsmen(QWidget *parent) :
    QWidget(parent)
{
    resize(340, 50);
    CreateWidgets();
}

diarySportsmen::diarySportsmen(QString name)
{
    resize(340, 50);
    sportName = name;
    setWindowTitle("Дневник спортсмена \"" + sportName + "\"");
    CreateWidgets();
}

diarySportsmen::~diarySportsmen()
{
}

void diarySportsmen::CreateWidgets()
{
    cbStyle = new QComboBox(this);
    cbStyle->setGeometry(QRect(10, 10, 200, 30));
    confirmStyle = new QPushButton("ОК", this);
    confirmStyle->setGeometry(QRect(250, 10, 80, 30));
    connect(confirmStyle, SIGNAL(clicked()), this, SLOT(actionConfirmStyle()));
    cbStyle->addItem("Выберите стиль...");
    cbStyle->addItem("Вольный");
    cbStyle->addItem("На спине");
    cbStyle->addItem("Брасс");
    cbStyle->addItem("Баттерфляй");
    cbStyle->addItem("Комплекс");
    cbStyle->setCurrentIndex(0);
    connect(cbStyle, SIGNAL(currentIndexChanged(int)), this, SLOT(actionCbStyle()));
    cbStyle->show();
    confirmStyle->show();
}

void diarySportsmen::actionConfirmStyle()
{
    smNewTime = new QSignalMapper;
    smDeleteTime = new QSignalMapper;
    QLabel* lblDist = new QLabel("<font size = 6 face = Georgia><p align = center><b>Дистанция</b></p></font>", this);
    lblDist->setGeometry(QRect(10, 100, 180, 40));
    SetStyle(lblDist, "white", "2", "black");
    lblDist->show();
    QLabel* lblBestTime = new QLabel("<font size = 4 face = Georgia><p align = center><b>Лучшее\r\nвремя</b></p></font>", this);
    lblBestTime->setWordWrap(true);
    lblBestTime->setGeometry(QRect(200, 100, 100, 40));
    SetStyle(lblBestTime, "white", "2", "black");
    lblBestTime->show();
    QLabel* lblCurrTime = new QLabel("<font size = 4 face = Georgia><p align = center><b>Текущее\r\nвремя</b></p></font>", this);
    lblCurrTime->setWordWrap(true);
    lblCurrTime->setGeometry(QRect(310, 100, 100, 40));
    SetStyle(lblCurrTime, "white", "2", "black");
    lblCurrTime->show();
    QLabel* lblEditTime = new QLabel("<font size = 4 face = Georgia><p align = center><b>Введите новое время</b></p></font>", this);
    SetStyle(lblEditTime, "white", "2", "black");
    lblEditTime->setWordWrap(true);
    lblEditTime->setGeometry(QRect(420, 100, 120, 40));
    lblEditTime->show();
    uint16_t sizeOfArrays;
    switch(code)
    {
        case 0:
        {
            ExceptionHandler::exceptionNullStyle(this);
            return;
        }
        case 1:
        {
            sizeOfArrays = 6;
            arrDist = new QLabel* [sizeOfArrays];
            for (uint16_t i = 0; i != sizeOfArrays; ++i)
                arrDist[i] = new QLabel(this);
            arrDist[0]->setText("<font size = 6 face = Georgia>50 вольный</font>");
            arrDist[1]->setText("<font size = 6 face = Georgia>100 вольный</font>");
            arrDist[2]->setText("<font size = 6 face = Georgia>200 вольный</font>");
            arrDist[3]->setText("<font size = 6 face = Georgia>400 вольный</font>");
            arrDist[4]->setText("<font size = 6 face = Georgia>800 вольный</font>");
            arrDist[5]->setText("<font size = 6 face = Georgia>1500 вольный</font>");
            break;
        }
        case 2:
        {
            sizeOfArrays = 3;
            arrDist = new QLabel* [sizeOfArrays];
            for (uint16_t i = 0; i != sizeOfArrays; ++i)
                arrDist[i] = new QLabel(this);
            arrDist[0]->setText("<font size = 6 face = Georgia>50 на спине</font>");
            arrDist[1]->setText("<font size = 6 face = Georgia>100 на спине</font>");
            arrDist[2]->setText("<font size = 6 face = Georgia>200 на спине</font>");
            break;
        }
        case 3:
        {
            sizeOfArrays = 3;
            arrDist = new QLabel* [sizeOfArrays];
            for (uint16_t i = 0; i != sizeOfArrays; ++i)
                arrDist[i] = new QLabel(this);
            arrDist[0]->setText("<font size = 6 face = Georgia>50 брасс</font>");
            arrDist[1]->setText("<font size = 6 face = Georgia>100 брасс</font>");
            arrDist[2]->setText("<font size = 6 face = Georgia>200 брасс</font>");
            break;
        }
        case 4:
        {
            sizeOfArrays = 3;
            arrDist = new QLabel* [sizeOfArrays];
            for (uint16_t i = 0; i != sizeOfArrays; ++i)
                arrDist[i] = new QLabel(this);
            arrDist[0]->setText("<font size = 6 face = Georgia>50 батт</font>");
            arrDist[1]->setText("<font size = 6 face = Georgia>100 батт</font>");
            arrDist[2]->setText("<font size = 6 face = Georgia>200 батт</font>");
            break;
        }
        case 5:
        {
            if (detailedStatistic != NULL)
                detailedStatistic->hide();
            sizeOfArrays = 3;
            arrDist = new QLabel* [sizeOfArrays];
            for (uint16_t i = 0; i != sizeOfArrays; ++i)
                arrDist[i] = new QLabel(this);
            arrDist[0]->setText("<font size = 6 face = Georgia>100 комплекс</font>");
            arrDist[1]->setText("<font size = 6 face = Georgia>200 комплекс</font>");
            arrDist[2]->setText("<font size = 6 face = Georgia>400 комплекс</font>");
            break;
        }


        default: //обработка переключения между 25 и 50 метровыми бассейнами для комплекса
        {
            arrDist[2]->hide();
            arrPrevTime[2]->hide();
            arrCurrTime[2]->hide();
            arrConfirmsTime[2]->hide();
            arrDeleteTime[2]->hide();
            arrEnterTime[6]->hide();
            arrEnterTime[7]->hide();
            arrEnterTime[8]->hide();
            sizeOfArrays = 2;
            arrDist = new QLabel* [sizeOfArrays];
            for (uint16_t i = 0; i != sizeOfArrays; ++i)
                arrDist[i] = new QLabel(this);
            arrDist[0]->setText("<font size = 6 face = Georgia>200 комплекс</font>");
            arrDist[1]->setText("<font size = 6 face = Georgia>400 комплекс</font>");
            break;
        }
    }
    qDebug() << "Complete";
    arrPrevTime.resize(sizeOfArrays);
    arrCurrTime.resize(sizeOfArrays);
    arrConfirmsTime.resize(sizeOfArrays);
    arrDeleteTime.resize(sizeOfArrays);
    arrEnterTime = new QLineEdit* [sizeOfArrays * 3];
    for (uint i = 0; i != sizeOfArrays; ++i)
    {
        arrPrevTime[i] = new QLabel(this);
        arrCurrTime[i] = new QLabel(this);
        arrDeleteTime[i] = new QPushButton("Удалить", this);
        arrEnterTime[3 * i] = new QLineEdit(this);
        arrEnterTime[3 * i + 1] = new QLineEdit(this);
        arrEnterTime[3 * i + 2] = new QLineEdit(this);
        arrConfirmsTime[i] = new QPushButton("OK", this);
        arrEnterTime[3 * i]->setGeometry(QRect(420, 150 + 70 * i, 40, 35));
        arrEnterTime[3 * i]->setPlaceholderText("Мин");
        arrEnterTime[3 * i + 1]->setGeometry(QRect(460, 150 + 70 * i, 40, 35));
        arrEnterTime[3 * i + 1]->setPlaceholderText("Сек");
        arrEnterTime[3 * i + 2]->setGeometry(QRect(500, 150 + 70 * i, 40, 35));
        arrEnterTime[3 * i + 2]->setPlaceholderText("Доли");
        arrConfirmsTime[i]->setGeometry(QRect(550, 150 + 70 * i, 35, 35));
        arrDist[i]->setGeometry(QRect(10, 150 + 70 * i, 180, 35));
        arrPrevTime[i]->setGeometry(QRect(200, 150 + 70 * i, 100, 35));
        arrCurrTime[i]->setGeometry(QRect(310, 150 + 70 * i, 100, 35));
        arrDeleteTime[i]->setGeometry(QRect(310, 185 + 70 * i, 100, 25));
        SetStyle(arrDist[i], "white", "1", "black");
        SetStyle(arrPrevTime[i], "white", "1", "black");
        SetStyle(arrCurrTime[i], "white", "1", "black");
        smNewTime->setMapping(arrConfirmsTime[i], i);
        smDeleteTime->setMapping(arrDeleteTime[i], i);
        connect(arrConfirmsTime[i], SIGNAL(clicked()), smNewTime, SLOT(map()));
        connect(arrDeleteTime[i], SIGNAL(clicked()), smDeleteTime, SLOT(map()));
    }
    connect(smNewTime, SIGNAL(mapped(int)), this, SLOT(actionAddTime(int)));
    connect(smDeleteTime, SIGNAL(mapped(int)), this, SLOT(actionDeleteTime(int)));
    for (uint i = 0; i != sizeOfArrays; ++i)
    {
        arrDist[i]->show();
        arrPrevTime[i]->show();
        arrCurrTime[i]->show();
        arrEnterTime[3 * i]->show();
        arrEnterTime[3 * i + 1]->show();
        arrEnterTime[3 * i + 2]->show();
        arrConfirmsTime[i]->show();
        arrDeleteTime[i]->show();
    }
    this->resize(600, 200 + sizeOfArrays * 70);
    detailedStatistic = new QPushButton("Расширенная статистика", this);
    detailedStatistic->setGeometry(QRect(10, 150 + sizeOfArrays * 70, 580, 40));
    connect(detailedStatistic, SIGNAL(clicked()), SLOT(actionShowDetailedStatistic()));
    detailedStatistic->show();
    this->CreateDiaryWidgets();
    this->cbStyle->hide();
    this->confirmStyle->hide();
    SetTime(chooseStyle, 25);
}

void diarySportsmen::actionCbStyle()
{
    code = cbStyle->currentIndex();
    chooseStyle = cbStyle->itemText(cbStyle->currentIndex());
}

void diarySportsmen::CreateDiaryWidgets()
{
    welcome = new QLabel("<font face = Georgia size = 7><p align = center>" + sportName + "(25 метров)" + "</font>", this);
    welcome->setGeometry(QRect(10, 10, 580, 40));
    welcome->show();
    SetStyle(welcome, "white", "1", "black");
    b25 = new QPushButton ("Бассейн 25 метров", this);
    b50 = new QPushButton ("Бассейн 50 метров", this);
    connect(b25, SIGNAL(clicked()), this, SLOT(action25meters()));
    connect(b50, SIGNAL(clicked()), this, SLOT(action50meters()));
    b25->setGeometry(QRect(10, 60, 250, 30));
    b50->setGeometry(QRect(330, 60, 250, 30));
    b25->show();
    b50->show();
}

void diarySportsmen::SetStyle(QLabel* lbl, QString backgroundColor, QString thickness, QString borderColor)
{
    lbl->setStyleSheet("QLabel {"
                                            "background-color:" + backgroundColor + ";"
                                            "border-style: solid;"
                                            "border-width: " + thickness + "px;"
                                            "border-color: " + borderColor + "; "
                                            "}");
}

QString diarySportsmen::deleteSpace(QString str)
{
    QString result = "";
    uint16_t i = 0;
    qDebug() << str;
    while (str[i] != ' ')
    {
        result.push_back(str[i]);
        ++i;
    }
    ++i;
    while (i != str.size() - 1)
    {
        result.push_back(str[i]);
        ++i;
    }
    return result;
}

void diarySportsmen::SetTime(QString style, int pool)
{
    this->pool = pool;
    welcome->setText("<font face = Georgia size = 7><p align = center>" + sportName + "(" + QString::number(this->pool) + " метров)" + "</font>");
    if (style == "Вольный")
        style = "freestyle";
    else if (style == "На спине")
        style = "backstroke";
    else if (style == "Баттерфляй")
        style = "butterfly";
    else if (style == "Брасс")
        style = "breakstroke";
    else
        style = "midley";
    chooseStyle = style;
    qDebug() << style;
    QString noTimeText = "";
   //-------------------------
    if (style == "midley")
    {
        if (pool == 25)
        {
            noTimeText = Time::toQString(TimeDataParser::getBestTime(deleteSpace(sportName) + QString::number(pool), style, 100));
            if (noTimeText == "59:59.99") noTimeText = "NT";
            arrPrevTime[0]->setText("<font face = Courier New size = 5><b>" + noTimeText + "</b></font>");
            noTimeText = Time::toQString(TimeDataParser::getLastTime(deleteSpace(sportName) + QString::number(pool), style, 100));
            if (noTimeText == "0:00.00") noTimeText = "NT";
            arrCurrTime[0]->setText("<font face = Courier New size = 5><b>" + noTimeText + "</b></font>");
            noTimeText = Time::toQString(TimeDataParser::getBestTime(deleteSpace(sportName) + QString::number(pool), style, 200));
            if (noTimeText == "59:59.99") noTimeText = "NT";
            arrPrevTime[1]->setText("<font face = Courier New size = 5><b>" + noTimeText + "</b></font>");
            noTimeText = Time::toQString(TimeDataParser::getLastTime(deleteSpace(sportName) + QString::number(pool), style, 200));
            if (noTimeText == "0:00.00") noTimeText = "NT";
            arrCurrTime[1]->setText("<font face = Courier New size = 5><b>" + noTimeText + "</b></font>");
            noTimeText = Time::toQString(TimeDataParser::getBestTime(deleteSpace(sportName) + QString::number(pool), style, 400));
            if (noTimeText == "59:59.99") noTimeText = "NT";
            arrPrevTime[2]->setText("<font face = Courier New size = 5><b>" + noTimeText + "</b></font>");
            noTimeText = Time::toQString(TimeDataParser::getLastTime(deleteSpace(sportName) + QString::number(pool), style, 400));
            if (noTimeText == "0:00.00") noTimeText = "NT";
            arrCurrTime[2]->setText("<font face = Courier New size = 5><b>" + noTimeText + "</b></font>");
        }
        else
        {
            noTimeText = Time::toQString(TimeDataParser::getBestTime(deleteSpace(sportName) + QString::number(pool), style, 200));
            if (noTimeText == "59:59.99") noTimeText = "NT";
            arrPrevTime[0]->setText("<font face = Courier New size = 5><b>" + noTimeText + "</b></font>");
            noTimeText = Time::toQString(TimeDataParser::getLastTime(deleteSpace(sportName) + QString::number(pool), style, 200));
            if (noTimeText == "0:00.00") noTimeText = "NT";
            arrCurrTime[0]->setText("<font face = Courier New size = 5><b>" + noTimeText + "</b></font>");
            noTimeText = Time::toQString(TimeDataParser::getBestTime(deleteSpace(sportName) + QString::number(pool), style, 400));
            if (noTimeText == "59:59.99") noTimeText = "NT";
            arrPrevTime[1]->setText("<font face = Courier New size = 5><b>" + noTimeText + "</b></font>");
            noTimeText = Time::toQString(TimeDataParser::getLastTime(deleteSpace(sportName) + QString::number(pool), style, 400));
            if (noTimeText == "0:00.00") noTimeText = "NT";
            arrCurrTime[1]->setText("<font face = Courier New size = 5><b>" + noTimeText + "</b></font>");
        }
    }
    else if (style == "freestyle")
    {
        noTimeText = Time::toQString(TimeDataParser::getBestTime(deleteSpace(sportName) + QString::number(pool), style, 50));
        if (noTimeText == "59:59.99") noTimeText = "NT";
        arrPrevTime[0]->setText("<font face = Courier New size = 5><b>" + noTimeText + "</b></font>");
        noTimeText = Time::toQString(TimeDataParser::getLastTime(deleteSpace(sportName) + QString::number(pool), style, 50));
        if (noTimeText == "0:00.00") noTimeText = "NT";
        arrCurrTime[0]->setText("<font face = Courier New size = 5><b>" + noTimeText + "</b></font>");
        noTimeText = Time::toQString(TimeDataParser::getBestTime(deleteSpace(sportName) + QString::number(pool), style, 100));
        if (noTimeText == "59:59.99") noTimeText = "NT";
        arrPrevTime[1]->setText("<font face = Courier New size = 5><b>" + noTimeText + "</b></font>");
        noTimeText = Time::toQString(TimeDataParser::getLastTime(deleteSpace(sportName) + QString::number(pool), style, 100));
        if (noTimeText == "0:00.00") noTimeText = "NT";
        arrCurrTime[1]->setText("<font face = Courier New size = 5><b>" + noTimeText + "</b></font>");
        noTimeText = Time::toQString(TimeDataParser::getBestTime(deleteSpace(sportName) + QString::number(pool), style, 200));
        if (noTimeText == "59:59.99") noTimeText = "NT";
        arrPrevTime[2]->setText("<font face = Courier New size = 5><b>" + noTimeText + "</b></font>");
        noTimeText = Time::toQString(TimeDataParser::getLastTime(deleteSpace(sportName) + QString::number(pool), style, 200));
        if (noTimeText == "0:00.00") noTimeText = "NT";
        arrCurrTime[2]->setText("<font face = Courier New size = 5><b>" + noTimeText + "</b></font>");
        noTimeText = Time::toQString(TimeDataParser::getBestTime(deleteSpace(sportName) + QString::number(pool), style, 400));
        if (noTimeText == "59:59.99") noTimeText = "NT";
        arrPrevTime[3]->setText("<font face = Courier New size = 5><b>" + noTimeText + "</b></font>");
        noTimeText = Time::toQString(TimeDataParser::getLastTime(deleteSpace(sportName) + QString::number(pool), style, 400));
        if (noTimeText == "0:00.00") noTimeText = "NT";
        arrCurrTime[3]->setText("<font face = Courier New size = 5><b>" + noTimeText + "</b></font>");
        noTimeText = Time::toQString(TimeDataParser::getBestTime(deleteSpace(sportName) + QString::number(pool), style, 800));
        if (noTimeText == "59:59.99") noTimeText = "NT";
        arrPrevTime[4]->setText("<font face = Courier New size = 5><b>" + noTimeText + "</b></font>");
        noTimeText = Time::toQString(TimeDataParser::getLastTime(deleteSpace(sportName) + QString::number(pool), style, 800));
        if (noTimeText == "0:00.00") noTimeText = "NT";
        arrCurrTime[4]->setText("<font face = Courier New size = 5><b>" + noTimeText + "</b></font>");
        noTimeText = Time::toQString(TimeDataParser::getBestTime(deleteSpace(sportName) + QString::number(pool), style, 1500));
        if (noTimeText == "59:59.99") noTimeText = "NT";
        arrPrevTime[5]->setText("<font face = Courier New size = 5><b>" + noTimeText + "</b></font>");
        noTimeText = Time::toQString(TimeDataParser::getLastTime(deleteSpace(sportName) + QString::number(pool), style, 1500));
        if (noTimeText == "0:00.00") noTimeText = "NT";
        arrCurrTime[5]->setText("<font face = Courier New size = 5><b>" + noTimeText + "</b></font>");
    }
    else
    {
        noTimeText = Time::toQString(TimeDataParser::getBestTime(deleteSpace(sportName) + QString::number(pool), style, 50));
        if (noTimeText == "59:59.99") noTimeText = "NT";
        arrPrevTime[0]->setText("<font face = Courier New size = 5><b>" + noTimeText + "</b></font>");
        noTimeText = Time::toQString(TimeDataParser::getLastTime(deleteSpace(sportName) + QString::number(pool), style, 50));
        if (noTimeText == "0:00.00") noTimeText = "NT";
        arrCurrTime[0]->setText("<font face = Courier New size = 5><b>" + noTimeText + "</b></font>");
        noTimeText = Time::toQString(TimeDataParser::getBestTime(deleteSpace(sportName) + QString::number(pool), style, 100));
        if (noTimeText == "59:59.99") noTimeText = "NT";
        arrPrevTime[1]->setText("<font face = Courier New size = 5><b>" + noTimeText + "</b></font>");
        noTimeText = Time::toQString(TimeDataParser::getLastTime(deleteSpace(sportName) + QString::number(pool), style, 100));
        if (noTimeText == "0:00.00") noTimeText = "NT";
        arrCurrTime[1]->setText("<font face = Courier New size = 5><b>" + noTimeText + "</b></font>");
        noTimeText = Time::toQString(TimeDataParser::getBestTime(deleteSpace(sportName) + QString::number(pool), style, 200));
        if (noTimeText == "59:59.99") noTimeText = "NT";
        arrPrevTime[2]->setText("<font face = Courier New size = 5><b>" + noTimeText + "</b></font>");
        noTimeText = Time::toQString(TimeDataParser::getLastTime(deleteSpace(sportName) + QString::number(pool), style, 200));
        if (noTimeText == "0:00.00") noTimeText = "NT";
        arrCurrTime[2]->setText("<font face = Courier New size = 5><b>" + noTimeText + "</b></font>");
    }
}

void diarySportsmen::actionAddTime(int i)
{
    if (arrEnterTime[3 * i]->text().toInt() > 59 || arrEnterTime[3 * i]->text().toInt() < 0
            || arrEnterTime[3 * i + 1]->text().toInt() > 59 || arrEnterTime[3 * i + 1]->text().toInt() < 0
            || arrEnterTime[3 * i + 2]->text().toInt() > 99 || arrEnterTime[3 * i + 2]->text().toInt() < 0)
    {
        ExceptionHandler::exceptionIncorrectTimeData(this, i);
        return;
    }
    QString resultTime = "";
    resultTime += arrEnterTime[3 * i]->text() + ":" + arrEnterTime[3 * i + 1]->text() + "." + arrEnterTime[3 * i + 2]->text();
    qDebug() << resultTime;
    if (chooseStyle == "midley")
    {
        if (this->pool == 25)
        {
            switch(i)
            {
                case 0:
                {
                    TimeDataEditor::addNewTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 100, Time::toTime(resultTime));
                    arrCurrTime[i]->setText("<font face = Courier New size = 5><b>" + resultTime + "</b></font>");
                    arrPrevTime[i]->setText("<font face = Courier New size = 5><b>" + Time::toQString(TimeDataParser::getBestTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 100)) + "</b></font>");
                    break;
                }
                case 1:
                {
                    TimeDataEditor::addNewTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 200, Time::toTime(resultTime));
                    arrCurrTime[i]->setText("<font face = Courier New size = 5><b>" + resultTime + "</b></font>");
                    arrPrevTime[i]->setText("<font face = Courier New size = 5><b>" + Time::toQString(TimeDataParser::getBestTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 200)) + "</b></font>");
                    break;
                }
                case 2:
                {
                    TimeDataEditor::addNewTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 400, Time::toTime(resultTime));
                    arrCurrTime[i]->setText("<font face = Courier New size = 5><b>" + resultTime + "</b></font>");
                    arrPrevTime[i]->setText("<font face = Courier New size = 5><b>" + Time::toQString(TimeDataParser::getBestTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 400)) + "</b></font>");
                    break;
                }
            }
        }
        else
        {
            switch(i)
            {
                case 0:
                {
                    TimeDataEditor::addNewTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 200, Time::toTime(resultTime));
                    arrCurrTime[i]->setText("<font face = Courier New size = 5><b>" + resultTime + "</b></font>");
                    arrPrevTime[i]->setText("<font face = Courier New size = 5><b>" + Time::toQString(TimeDataParser::getBestTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 200)) + "</b></font>");
                    break;
                }
                case 1:
                {
                    TimeDataEditor::addNewTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 400, Time::toTime(resultTime));
                    arrCurrTime[i]->setText("<font face = Courier New size = 5><b>" + resultTime + "</b></font>");
                    arrPrevTime[i]->setText("<font face = Courier New size = 5><b>" + Time::toQString(TimeDataParser::getBestTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 400)) + "</b></font>");
                    break;
                }
            }
        }
    }
    else if (chooseStyle == "freestyle")
    {
        switch(i)
        {
            case 0:
            {
                TimeDataEditor::addNewTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 50, Time::toTime(resultTime));
                arrCurrTime[i]->setText("<font face = Courier New size = 5><b>" + resultTime + "</b></font>");
                arrPrevTime[i]->setText("<font face = Courier New size = 5><b>" + Time::toQString(TimeDataParser::getBestTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 50)) + "</b></font>");
                break;
            }
            case 1:
            {
                TimeDataEditor::addNewTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 100, Time::toTime(resultTime));
                arrCurrTime[i]->setText("<font face = Courier New size = 5><b>" + resultTime + "</b></font>");
                arrPrevTime[i]->setText("<font face = Courier New size = 5><b>" + Time::toQString(TimeDataParser::getBestTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 100)) + "</b></font>");
                break;
            }
            case 2:
            {
                TimeDataEditor::addNewTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 200, Time::toTime(resultTime));
                arrCurrTime[i]->setText("<font face = Courier New size = 5><b>" + resultTime + "</b></font>");
                arrPrevTime[i]->setText("<font face = Courier New size = 5><b>" + Time::toQString(TimeDataParser::getBestTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 200)) + "</b></font>");
                break;
            }
            case 3:
            {
                TimeDataEditor::addNewTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 400, Time::toTime(resultTime));
                arrCurrTime[i]->setText("<font face = Courier New size = 5><b>" + resultTime + "</b></font>");
                arrPrevTime[i]->setText("<font face = Courier New size = 5><b>" + Time::toQString(TimeDataParser::getBestTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 400)) + "</b></font>");
                break;
            }
            case 4:
            {
                TimeDataEditor::addNewTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 800, Time::toTime(resultTime));
                arrCurrTime[i]->setText("<font face = Courier New size = 5><b>" + resultTime + "</b></font>");
                arrPrevTime[i]->setText("<font face = Courier New size = 5><b>" + Time::toQString(TimeDataParser::getBestTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 800)) + "</b></font>");
                break;
            }
            case 5:
            {
                TimeDataEditor::addNewTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 1500, Time::toTime(resultTime));
                arrCurrTime[i]->setText("<font face = Courier New size = 5><b>" + resultTime + "</b></font>");
                arrPrevTime[i]->setText("<font face = Courier New size = 5><b>" + Time::toQString(TimeDataParser::getBestTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 1500)) + "</b></font>");
                break;
            }

        }
    }
    else
    {
        switch(i)
        {
            case 0:
            {
                TimeDataEditor::addNewTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 50, Time::toTime(resultTime));
                arrCurrTime[i]->setText("<font face = Courier New size = 5><b>" + resultTime + "</b></font>");
                arrPrevTime[i]->setText("<font face = Courier New size = 5><b>" + Time::toQString(TimeDataParser::getBestTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 50)) + "</b></font>");
                break;
            }
            case 1:
            {
                TimeDataEditor::addNewTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 100, Time::toTime(resultTime));
                arrCurrTime[i]->setText("<font face = Courier New size = 5><b>" + resultTime + "</b></font>");
                arrPrevTime[i]->setText("<font face = Courier New size = 5><b>" + Time::toQString(TimeDataParser::getBestTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 100)) + "</b></font>");
                break;
            }
            case 2:
            {
                TimeDataEditor::addNewTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 200, Time::toTime(resultTime));
                arrCurrTime[i]->setText("<font face = Courier New size = 5><b>" + resultTime + "</b></font>");
                arrPrevTime[i]->setText("<font face = Courier New size = 5><b>" + Time::toQString(TimeDataParser::getBestTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 200)) + "</b></font>");
                break;
            }
        }
    }
    arrEnterTime[3 * i]->clear();
    arrEnterTime[3 * i]->setPlaceholderText("Мин");
    arrEnterTime[3 * i + 1]->clear();
    arrEnterTime[3 * i + 1]->setPlaceholderText("Сек");
    arrEnterTime[3 * i + 2]->clear();
    arrEnterTime[3 * i + 2]->setPlaceholderText("Доли");
}

void diarySportsmen::actionDeleteTime(int i)
{
    if (chooseStyle == "midley")
    {
        if (this->pool == 25)
        {
            switch(i)
            {
                case 0:
                {
                    TimeDataEditor::deleteLastTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 100);
                    //arrCurrTime[i]->setText("<font face = Courier New size = 5><b>" + resultTime + "</b></font>");
                    arrPrevTime[i]->setText("<font face = Courier New size = 5><b>" + Time::toQString(TimeDataParser::getBestTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 100)) + "</b></font>");
                    break;
                }
                case 1:
                {
                    TimeDataEditor::deleteLastTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 200);
                    //arrCurrTime[i]->setText("<font face = Courier New size = 5><b>" + resultTime + "</b></font>");
                    arrPrevTime[i]->setText("<font face = Courier New size = 5><b>" + Time::toQString(TimeDataParser::getBestTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 200)) + "</b></font>");
                    break;
                }
                case 2:
                {
                    TimeDataEditor::deleteLastTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 400);
                    //arrCurrTime[i]->setText("<font face = Courier New size = 5><b>" + resultTime + "</b></font>");
                    arrPrevTime[i]->setText("<font face = Courier New size = 5><b>" + Time::toQString(TimeDataParser::getBestTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 400)) + "</b></font>");
                    break;
                }
            }
        }
        else
        {
            switch(i)
            {
                case 0:
                {
                    TimeDataEditor::deleteLastTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 200);
                    //arrCurrTime[i]->setText("<font face = Courier New size = 5><b>" + resultTime + "</b></font>");
                    arrPrevTime[i]->setText("<font face = Courier New size = 5><b>" + Time::toQString(TimeDataParser::getBestTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 200)) + "</b></font>");
                    break;
                }
                case 1:
                {
                    TimeDataEditor::deleteLastTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 400);
                    //arrCurrTime[i]->setText("<font face = Courier New size = 5><b>" + resultTime + "</b></font>");
                    arrPrevTime[i]->setText("<font face = Courier New size = 5><b>" + Time::toQString(TimeDataParser::getBestTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 400)) + "</b></font>");
                    break;
                }
            }
        }
    }
    else if (chooseStyle == "freestyle")
    {
        switch(i)
        {
            case 0:
            {
                TimeDataEditor::deleteLastTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 50);
                arrCurrTime[i]->setText("<font face = Courier New size = 5><b>" + Time::toQString(TimeDataParser::getLastTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 50)    ) + "</b></font>");
                arrPrevTime[i]->setText("<font face = Courier New size = 5><b>" + Time::toQString(TimeDataParser::getBestTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 50)) + "</b></font>");
                break;
            }
            case 1:
            {
                TimeDataEditor::deleteLastTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 100);
                //arrCurrTime[i]->setText("<font face = Courier New size = 5><b>" + resultTime + "</b></font>");
                arrPrevTime[i]->setText("<font face = Courier New size = 5><b>" + Time::toQString(TimeDataParser::getBestTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 100)) + "</b></font>");
                break;
            }
            case 2:
            {
                TimeDataEditor::deleteLastTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 200);
                //arrCurrTime[i]->setText("<font face = Courier New size = 5><b>" + resultTime + "</b></font>");
                arrPrevTime[i]->setText("<font face = Courier New size = 5><b>" + Time::toQString(TimeDataParser::getBestTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 200)) + "</b></font>");
                break;
            }
            case 3:
            {
                TimeDataEditor::deleteLastTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 400);
                //arrCurrTime[i]->setText("<font face = Courier New size = 5><b>" + resultTime + "</b></font>");
                arrPrevTime[i]->setText("<font face = Courier New size = 5><b>" + Time::toQString(TimeDataParser::getBestTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 400)) + "</b></font>");
                break;
            }
            case 4:
            {
                TimeDataEditor::deleteLastTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 800);
                //arrCurrTime[i]->setText("<font face = Courier New size = 5><b>" + resultTime + "</b></font>");
                arrPrevTime[i]->setText("<font face = Courier New size = 5><b>" + Time::toQString(TimeDataParser::getBestTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 800)) + "</b></font>");
                break;
            }
            case 5:
            {
                TimeDataEditor::deleteLastTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 1500);
                //arrCurrTime[i]->setText("<font face = Courier New size = 5><b>" + resultTime + "</b></font>");
                arrPrevTime[i]->setText("<font face = Courier New size = 5><b>" + Time::toQString(TimeDataParser::getBestTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 1500)) + "</b></font>");
                break;
            }

        }
    }
    else
    {
        switch(i)
        {
            case 0:
            {
                TimeDataEditor::deleteLastTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 50);
                //arrCurrTime[i]->setText("<font face = Courier New size = 5><b>" + resultTime + "</b></font>");
                arrPrevTime[i]->setText("<font face = Courier New size = 5><b>" + Time::toQString(TimeDataParser::getBestTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 50)) + "</b></font>");
                break;
            }
            case 1:
            {
                TimeDataEditor::deleteLastTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 100);
                //arrCurrTime[i]->setText("<font face = Courier New size = 5><b>" + resultTime + "</b></font>");
                arrPrevTime[i]->setText("<font face = Courier New size = 5><b>" + Time::toQString(TimeDataParser::getBestTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 100)) + "</b></font>");
                break;
            }
            case 2:
            {
                TimeDataEditor::deleteLastTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 200);
                //arrCurrTime[i]->setText("<font face = Courier New size = 5><b>" + TimeDataParser::getLastTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 200) + "</b></font>");
                arrPrevTime[i]->setText("<font face = Courier New size = 5><b>" + Time::toQString(TimeDataParser::getBestTime(deleteSpace(sportName) + QString::number(this->pool), chooseStyle, 200)) + "</b></font>");
                break;
            }
        }
    }
}

void diarySportsmen::action25meters()
{
    if (this->chooseStyle == "midley")
    {
        this->code = 5;
        actionConfirmStyle();
    }
    this->pool = 25;
    QString style;
    if (this->chooseStyle == "freestyle")
        style = "Вольный";
    else if (this->chooseStyle == "backstroke")
        style = "На спине";
    else if (this->chooseStyle == "butterfly")
        style = "Баттерфляй ";
    else if (this->chooseStyle == "breakstroke")
        style = "Брасс";
    else
        style = "Комплекс";
    SetTime(style, this->pool);
}

void diarySportsmen::action50meters()
{
    if (this->chooseStyle == "midley" && this->code != 10)
    {
        this->code = 10;
        actionConfirmStyle();
    }
    this->pool = 50;
    QString style;
    if (this->chooseStyle == "freestyle")
        style = "Вольный";
    else if (this->chooseStyle == "backstroke")
        style = "На спине";
    else if (this->chooseStyle == "butterfly")
        style = "Баттерфляй ";
    else if (this->chooseStyle == "breakstroke")
        style = "Брасс";
    else
        style = "Комплекс";
    SetTime(style, this->pool);
}

void diarySportsmen::actionShowDetailedStatistic()
{
    StatisticGraph *win = new StatisticGraph(this->sportName, this->chooseStyle, this->pool);
    win->show();
}

bool diarySportsmen::isNumb(QString value)
{
    bool ok;
    value.toInt(&ok);
    return ok;
}
