#ifndef TIMEDATAPARSER_H
#define TIMEDATAPARSER_H

#include "time.h"

#include <QString>

class TimeDataParser
{

public:
    TimeDataParser();
    ~TimeDataParser();

    static Time getBestTime(QString, QString, int); //лучшее время спортсмена на заданной дистанции в заданном бассейне
    static Time getWorstTime(QString, QString, int); //лучшее время спортсмена на заданной дистанции в заданном бассейне
    static Time getLastTime(QString, QString, int); //последнее время спортсмена на заданной дистанции в заданном бассейне
    static std::vector<Time> getAllTime(QString, QString, int); //все записи о времени спорстмена на заданной дистанции в заданном бассейне

private:
    static std::vector<Time> QStringListToStdVectorTime(QStringList);

};

#endif // TIMEDATAPARSER_H
