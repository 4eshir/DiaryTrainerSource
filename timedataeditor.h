#ifndef TIMEDATAEDITOR_H
#define TIMEDATAEDITOR_H

#include <QString>
#include "time.h"

class TimeDataEditor
{

public:
    TimeDataEditor();
    ~TimeDataEditor();

    static void addNewTime(QString, QString, int, Time);
    static void deleteLastTime(QString, QString, int);

private:
    static bool checkOnce(QString);
    static bool checkNull(QString);

};

#endif // TIMEDATAEDITOR_H
