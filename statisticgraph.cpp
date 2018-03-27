#include "statisticgraph.h"
#include "timedataparser.h"
#include "time.h"

#include <QFile>
#include <QTableWidget>
#include <QDebug>
#include <qmath.h>

StatisticGraph::StatisticGraph()
{

}

StatisticGraph::StatisticGraph(QString filename, QString style, int pool)
{
    setWindowTitle("Статистика спортсмена " + filename);
    CreateWidgets(filename, style, pool);
}

StatisticGraph::~StatisticGraph()
{

}


void StatisticGraph::CreateWidgets(QString filename, QString style, int pool)
{
    int size = 0;
    if (style == "midley")
    {
        if (pool == 25)
        {
            size = 3;
            distanceRanges = new QLabel* [size];
            scoreTables.resize(size);
            topValues.resize(size);
            this->resize(size * 200 + 20, 500);
            //дистанции в статические лейблы
            distanceRanges[0] = new QLabel("<font face = Georgia size = 5><p align = center>100 комплекс</p></font>", this);
            distanceRanges[1] = new QLabel("<font face = Georgia size = 5><p align = center>200 комплекс</p></font>", this);
            distanceRanges[2] = new QLabel("<font face = Georgia size = 5><p align = center>400 комплекс</p></font>", this);

            //------------------------------
            //две таблицы
        }
        else
        {
            size = 2;
            distanceRanges = new QLabel* [size];
            scoreTables.resize(size);
            topValues.resize(size);
            this->resize(size * 200 + 20, 500);
            //дистанции в статические лейблы
            distanceRanges[0] = new QLabel("<font face = Georgia size = 5><p align = center>200 комплекс</p></font>", this);
            distanceRanges[1] = new QLabel("<font face = Georgia size = 5><p align = center>400 комплекс</p></font>", this);

            //------------------------------
            //три таблицы
        }
    }
    else if (style == "freestyle")
    {
        size = 6;
        distanceRanges = new QLabel* [size];
        scoreTables.resize(size);
        topValues.resize(size);
        this->resize(size * 200 + 20, 500);
        //дистанции в статические лейблы
        distanceRanges[0] = new QLabel("<font face = Georgia size = 5><p align = center>50 вольный</p></font>", this);
        distanceRanges[1] = new QLabel("<font face = Georgia size = 5><p align = center>100 вольный</p></font>", this);
        distanceRanges[2] = new QLabel("<font face = Georgia size = 5><p align = center>200 вольный</p></font>", this);
        distanceRanges[3] = new QLabel("<font face = Georgia size = 5><p align = center>400 вольный</p></font>", this);
        distanceRanges[4] = new QLabel("<font face = Georgia size = 5><p align = center>800 вольный</p></font>", this);
        distanceRanges[5] = new QLabel("<font face = Georgia size = 5><p align = center>1500 вольный</p></font>", this);

        //------------------------------
        //шесть таблиц
    }
    else
    {
        size = 3;
        distanceRanges = new QLabel* [size];
        scoreTables.resize(size);
        topValues.resize(size);
        this->resize(size * 200 + 20, 500);
        QString tempStyle;
        if (style == "backstroke")
            tempStyle = "на спине";
        else if (style == "butterfly")
            tempStyle = "баттерфляй ";
        else
            tempStyle = "брасс";
        //дистанции в статические лейблы
        distanceRanges[0] = new QLabel("<font face = Georgia size = 5><p align = center>50 " + tempStyle + "</p></font>", this);
        distanceRanges[1] = new QLabel("<font face = Georgia size = 5><p align = center>100 " + tempStyle + "</p></font>", this);
        distanceRanges[2] = new QLabel("<font face = Georgia size = 5><p align = center>200 " + tempStyle + "</p></font>", this);

        //------------------------------
        //три таблицы
    }

    uint16_t numbOfStat = 4;
    for (uint16_t i = 0; i != size; ++i)
    {
        scoreTables[i] = new QTableWidget(this);
        topValues[i] = new QLabel*[numbOfStat];
        for (uint16_t j = 0; j != numbOfStat; ++j)
        {
            topValues[i][j] = new QLabel(this);
            topValues[i][j]->setGeometry(QRect(15 + 200 * i, 355 + 30 * j, 190, 25));
        }
        scoreTables[i]->setGeometry(QRect(20 + 200 * i, 50, 180, 300));
        FillTable(scoreTables[i], filename, style, GetDistance(style, i, pool), pool);
        FillTopResult(topValues[i], filename, style, GetDistance(style, i, pool), pool);
        distanceRanges[i]->setGeometry(QRect(10 + 200 * i, 10, 200, 30));
        SetStyle(distanceRanges[i]);
    }
}

void StatisticGraph::FillTable(QTableWidget* table, QString filename, QString style, int distance, int pool)
{
    table->setRowCount(10);
    table->setColumnCount(1);
    QTableWidgetItem* tempItem;
    QStringList lst;
    lst << "Последние 10\nрезультатов";
    table->setHorizontalHeaderLabels(lst);
    std::vector<Time> allTimes = TimeDataParser::getAllTime(deleteSpace(filename) + QString::number(pool), style, distance);
    for (uint16_t i = 0; i != 10; ++i)
    {
        qDebug() << i;
        if (i > allTimes.size() - 1 || i != allTimes.size() - 1)
            tempItem = new QTableWidgetItem("NT");
        else
            tempItem = new QTableWidgetItem(Time::toQString(allTimes[i]));
        table->setItem(i, 0, tempItem);
    }
}

void StatisticGraph::FillTopResult(QLabel** labels, QString filename, QString style, int distance, int pool)
{
    QString tempTime = Time::toQString(TimeDataParser::getBestTime(deleteSpace(filename) + QString::number(pool), style, distance));
    if (tempTime == "59:59.99")
        tempTime = "NT";
    labels[0]->setText("<font face = Tahoma size = 3 color = green><b>Лучшее время: " + tempTime + "</b></font>");
    SetStyle(labels[0]);
    if (tempTime == "NT")
        labels[2]->setText("<font face = Tahoma size = 3 color = green><b>Лучшая скорость: NS</b></font>");
    else
        labels[2]->setText("<font face = Tahoma size = 3 color = green><b>Лучшая скорость: " + QString::number(roundTo(distance / Time::toFloat(TimeDataParser::getBestTime(deleteSpace(filename) + QString::number(pool), style, distance)), 2)) + " м/с</b></font>");
    SetStyle(labels[2]);
    tempTime = Time::toQString(TimeDataParser::getWorstTime(deleteSpace(filename) + QString::number(pool), style, distance));
    qDebug() << tempTime;
    if (tempTime == "0:00.00")
        tempTime = "NT";
    labels[1]->setText("<font face = Tahoma size = 3 color = red><b>Худшее время: " + tempTime + "</b></font>");
    SetStyle(labels[1]);
    if (tempTime == "NT")
        labels[3]->setText("<font face = Tahoma size = 3 color = red><b>Худшая скорость: NS</b></font>");
    else
        labels[3]->setText("<font face = Tahoma size = 3 color = red><b>Худшая скорость: " + QString::number(roundTo(distance / Time::toFloat(TimeDataParser::getBestTime(deleteSpace(filename) + QString::number(pool), style, distance)), 2)) + " м/с</b></font>");
    SetStyle(labels[3]);
}

int StatisticGraph::GetDistance(QString style, int index, int pool)
{
    if (style == "midley")
    {
        if (pool == 25)
        {
            switch(index)
            {
                case 0:
                    return 100;
                case 1:
                    return 200;
                case 2:
                    return 400;
            }
        }
        else
        {
            switch(index)
            {
                case 0:
                    return 200;
                case 1:
                    return 400;
            }
        }
    }
    else if (style == "freestyle")
    {
        switch(index)
        {
            case 0:
                return 50;
            case 1:
                return 100;
            case 2:
                return 200;
            case 3:
                return 400;
            case 4:
                return 800;
            case 5:
                return 1500;
        }
    }
    else
    {
        switch(index)
        {
            case 0:
                return 50;
            case 1:
                return 100;
            case 2:
                return 200;
        }
    }
}

QString StatisticGraph::deleteSpace(QString str)
{
    QString result = "";
    uint16_t i = 0;
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

float StatisticGraph::roundTo(float inpValue, int inpCount)
{
    float outpValue;
    float tempVal;
    tempVal = inpValue * pow(10, inpCount);
    if (float(int(tempVal)) + 0.5 == tempVal)
    {
        if (int(tempVal) % 2==0)
            outpValue = float(qFloor(tempVal)) / pow(10, inpCount);
        else
            outpValue = float(qCeil(tempVal)) / pow(10, inpCount);
    }
    else
    {
        if (float(int(tempVal)) + 0.5 > tempVal)
            outpValue = float(qCeil(tempVal)) / pow(10, inpCount);
        else
            outpValue = float(qFloor(tempVal)) / pow(10, inpCount);
    }
    return outpValue;
}



void StatisticGraph::SetStyle(QLabel* lbl)
{
    lbl->setStyleSheet("QLabel {"
                                            "background-color: white;"
                                            "border-style: solid;"
                                            "border-width: 1px;"
                                            "border-color: black; "
                                            "}");
}
