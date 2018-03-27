#include "timedataparser.h"
#include "time.h"

#include <QFile>
#include <QDebug>

using namespace std;

TimeDataParser::TimeDataParser()
{

}

TimeDataParser::~TimeDataParser()
{

}

Time TimeDataParser::getBestTime(QString filename, QString style, int distance)
{
    vector<Time> allTimes = TimeDataParser::getAllTime(filename, style, distance);
    Time nullTime("59", "59", "99");
    if (allTimes.size() == 0)
    {
        return nullTime;
    }
    Time minimum("59", "59", "99");
    for (uint16_t i = 0; i != allTimes.size(); ++i)
    {
        if (allTimes[i] < minimum)
            minimum = allTimes[i];
    }
    return minimum;
}

Time TimeDataParser::getWorstTime(QString filename, QString style, int distance)
{
    vector<Time> allTimes = TimeDataParser::getAllTime(filename, style, distance);
    Time maximum("0", "00", "00");
    for (uint16_t i = 0; i != allTimes.size(); ++i)
    {
        if (allTimes[i] > maximum)
            maximum = allTimes[i];
    }
    return maximum;
}

std::vector<Time> TimeDataParser::getAllTime(QString filename, QString style, int distance)
{
    QFile fin;
    fin.setFileName("DataSportsmens\\" + filename + ".timedata");
    fin.open(QIODevice::ReadOnly | QIODevice::Text);
    QString temp = "";
    while (temp != style)
    {
        temp = fin.readLine();
        temp.resize(style.size());
    }
    while (temp != QString::number(distance))
    {
        temp = fin.readLine();
        QString strNumb = "";
        if (temp[0] == '[')
        {
            for (uint16_t i = 1; temp[i] != ']'; ++i)
                strNumb += temp[i];
            temp = strNumb;
        }
    }
    std::vector<Time> timeVector;
    temp = fin.readLine();
    fin.close();
    temp.remove(0, 1);
    temp.remove(temp.size() - 2, 3);
    if (temp == "")
    {
        timeVector.resize(0);
        return timeVector;
    }
    QStringList timeList = temp.split(' ');
    timeVector = TimeDataParser::QStringListToStdVectorTime(timeList);
    return timeVector;
}

std::vector<Time> TimeDataParser::QStringListToStdVectorTime(QStringList list)
{
    std::vector<Time> returnVector;
    returnVector.resize(list.size());
    for (uint16_t i = 0; i != returnVector.size(); ++i)
        returnVector[i] = Time::toTime(list[i]);
    return returnVector;
}

Time TimeDataParser::getLastTime(QString filename, QString style, int distance)
{
    Time t("0", "00", "00");
    vector<Time> allTimes = TimeDataParser::getAllTime(filename, style, distance);
    if (allTimes.size() == 0)
        return t;
    return allTimes[allTimes.size() - 1];
}
