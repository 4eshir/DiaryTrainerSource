#include "time.h"

#include <QDebug>
#include <cmath>

Time::Time()
{
    this->minutes = "0";
    this->seconds = "00";
    this->sharesSeconds = "00";
}

Time::Time(QString n1, QString n2, QString n3)
{
    this->minutes = n1;
    this->seconds = n2;
    this->sharesSeconds = n3;
}

Time::~Time()
{
}

bool operator >(Time t1, Time t2)
{
    float summaryThis = Time::toFloat(t1);
    float summaryT = Time::toFloat(t2);
    return summaryThis > summaryT;
}

bool operator <(Time t1, Time t2)
{
    return (t2 > t1);
}

bool operator !=(Time t1, Time t2)
{
    return (t2 > t1) || (t1 > t2);
}

bool operator ==(Time t1, Time t2)
{
    return !(t2 > t1) && !(t1 > t2);
}



Time Time::toTime(QString value)
{
    std::string strValue = value.toStdString();
    std::reverse(strValue.begin(), strValue.end());
    value = QString::fromStdString(strValue);
    QString tempSeconds = "";
    QString tempMinutes = "";
    QString tempSharesSeconds = "";
    int i = value.size() - 1;
    while (value[i] != ':')
    {
        tempMinutes += value[i];
        --i;
    }
    --i;
    while (value[i] != '.')
    {
        tempSeconds += value[i];
        --i;
    }
    --i;
    while (i != - 1)
    {
        tempSharesSeconds += value[i];
        --i;
    }
    Time tempTime;
    tempTime.seconds = tempSeconds;
    tempTime.minutes = tempMinutes;
    tempTime.sharesSeconds = tempSharesSeconds;
    return tempTime;

}

QString Time::toQString(Time value)
{
    return value.minutes + ":" + value.seconds + "." + value.sharesSeconds;
}

float Time::toFloat(Time value)
{
    return float(value.minutes.toInt() * 60 + (value.seconds + "." + value.sharesSeconds).toFloat());
}
