#include "timedataeditor.h"

#include <QFile>
#include <QString>
#include "time.h"

#include <QDebug>

TimeDataEditor::TimeDataEditor()
{

}

TimeDataEditor::~TimeDataEditor()
{

}

void TimeDataEditor::addNewTime(QString filename, QString style, int distance, Time newTime)
{
    QFile fin("DataSportsmens\\" + filename + ".timedata");
    fin.open(QIODevice::ReadOnly | QIODevice::Text);
    QString temp = "";
    QString allFile = "";
    while (temp != style)
    {
        temp = fin.readLine();
        allFile += temp;
        temp.resize(style.size());
    }
    while (temp != QString::number(distance))
    {
        temp = fin.readLine();
        allFile += temp;
        QString strNumb = "";
        if (temp[0] == '[')
        {
            for (uint16_t i = 1; temp[i] != ']'; ++i)
                strNumb += temp[i];
            temp = strNumb;
        }
    }
    temp = fin.readLine();
    temp.remove(temp.size() - 2, 3);
    if (temp == "{")
        temp += Time::toQString(newTime) + "}\n";
    else
        temp += " " + Time::toQString(newTime) + "}\n";
    allFile += temp;
    while (!fin.atEnd())
        allFile += fin.readLine();
    fin.close();
    QFile file("DataSportsmens\\" + filename + ".timedata");
    QTextStream stream(&file);
    file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);
    stream << allFile << endl;
    stream.flush();
    file.close();
}

void TimeDataEditor::deleteLastTime(QString filename, QString style, int distance)
{
    QFile fin("DataSportsmens\\" + filename + ".timedata");
    fin.open(QIODevice::ReadOnly | QIODevice::Text);
    QString temp = "";
    QString allFile = "";
    while (temp != style)
    {
        temp = fin.readLine();
        allFile += temp;
        temp.resize(style.size());
    }
    while (temp != QString::number(distance))
    {
        temp = fin.readLine();
        allFile += temp;
        QString strNumb = "";
        if (temp[0] == '[')
        {
            for (uint16_t i = 1; temp[i] != ']'; ++i)
                strNumb += temp[i];
            temp = strNumb;
        }
    }
    temp = fin.readLine();
    temp.remove(temp.size() - 1, 2);
    uint16_t i = temp.size() - 1;
    if (TimeDataEditor::checkOnce(temp))
        temp = "{}\n";
    else
    {
        while (temp[i] != ' ')
        {
            temp.remove(temp.size() - 1, 2);
            --i;
        }
        temp.remove(temp.size() - 1, 2);
        temp += "}\n";
    }
    allFile += temp;
    while (!fin.atEnd())
        allFile += fin.readLine();
    fin.close();
    QFile file("DataSportsmens\\" + filename + ".timedata");
    QTextStream stream(&file);
    file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);
    stream << allFile << endl;
    stream.flush();
    file.close();
    qDebug() << temp;
}

bool TimeDataEditor::checkOnce(QString value)
{
    for (uint16_t i = 0; i != value.size(); ++i)
    {
        if (value[i] == ' ')
            return false;
    }
    return true;
}

bool TimeDataEditor::checkNull(QString value)
{
    return value == "{}";
}
