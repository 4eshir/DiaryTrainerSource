#ifndef TIME_H
#define TIME_H

#include <cinttypes>
#include <QString>

class Time
{

public:
    Time();
    Time(QString, QString, QString);
    ~Time();

    QString minutes;
    QString seconds;
    QString sharesSeconds;

    friend bool operator >(Time t1, Time t2);
    friend bool operator <(Time t1, Time t2);
    friend bool operator !=(Time t1, Time t2);
    friend bool operator ==(Time t1, Time t2);

    static Time toTime(QString);
    static QString toQString(Time);
    static float toFloat(Time);

private:
};

#endif // TIME_H
