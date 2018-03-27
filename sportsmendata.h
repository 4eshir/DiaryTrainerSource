#ifndef SPORTSMENDATA_H
#define SPORTSMENDATA_H

#include <QString>
#include "time.h"

class SportsmenData
{

public:
    explicit SportsmenData();
    SportsmenData(QString, int, bool);
    ~SportsmenData();

    QString name;
    int gender;
    int pool;
    std::vector<Time> bestFreestyleTime;
    std::vector<Time> bestBackstrokeTime;
    std::vector<Time> bestBreakstrokeTime;
    std::vector<Time> bestButterflyTime;
    std::vector<Time> bestMidleyTime;

private:

};

#endif // SPORTSMENDATA_H
