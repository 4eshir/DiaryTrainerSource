#include "sportsmendata.h"
#include "timedataparser.h"

#include <QFile>

SportsmenData::SportsmenData()
{

}

SportsmenData::SportsmenData(QString name, int pool, bool gender)
{
    this->name = name;
    this->pool = pool;
    this->gender = gender;
    //FREESTYLE
    this->bestFreestyleTime.resize(6);
    this->bestFreestyleTime[0] = TimeDataParser::getBestTime(name + QString::number(pool), "freestyle", 50);
    this->bestFreestyleTime[1] = TimeDataParser::getBestTime(name + QString::number(pool), "freestyle", 100);
    this->bestFreestyleTime[2] = TimeDataParser::getBestTime(name + QString::number(pool), "freestyle", 200);
    this->bestFreestyleTime[3] = TimeDataParser::getBestTime(name + QString::number(pool), "freestyle", 400);
    this->bestFreestyleTime[4] = TimeDataParser::getBestTime(name + QString::number(pool), "freestyle", 800);
    this->bestFreestyleTime[5] = TimeDataParser::getBestTime(name + QString::number(pool), "freestyle", 1500);
    //---------

    //BACKSTROKE
    this->bestBackstrokeTime.resize(3);
    this->bestBackstrokeTime[0] = TimeDataParser::getBestTime(name + QString::number(pool), "backstroke", 50);
    this->bestBackstrokeTime[1] = TimeDataParser::getBestTime(name + QString::number(pool), "backstroke", 100);
    this->bestBackstrokeTime[2] = TimeDataParser::getBestTime(name + QString::number(pool), "backstroke", 200);
    //----------

    //BREAKSTROKE
    this->bestBreakstrokeTime.resize(3);
    this->bestBreakstrokeTime[0] = TimeDataParser::getBestTime(name + QString::number(pool), "breakstroke", 50);
    this->bestBreakstrokeTime[1] = TimeDataParser::getBestTime(name + QString::number(pool), "breakstroke", 100);
    this->bestBreakstrokeTime[2] = TimeDataParser::getBestTime(name + QString::number(pool), "breakstroke", 200);
    //----------


    //MIDLEY
    if (this->pool == 25)
    {
        this->bestMidleyTime.resize(3);
        this->bestMidleyTime[0] = TimeDataParser::getBestTime(name + QString::number(pool), "midley", 100);
        this->bestMidleyTime[1] = TimeDataParser::getBestTime(name + QString::number(pool), "midley", 200);
        this->bestMidleyTime[2] = TimeDataParser::getBestTime(name + QString::number(pool), "midley", 400);
    }
    else
    {
        this->bestMidleyTime.resize(2);
        this->bestMidleyTime[0] = TimeDataParser::getBestTime(name + QString::number(pool), "midley", 200);
        this->bestMidleyTime[1] = TimeDataParser::getBestTime(name + QString::number(pool), "midley", 400);
    }
    //-------

}

SportsmenData::~SportsmenData()
{

}
