#ifndef GROUPWIDGETSPORTSMEN_H
#define GROUPWIDGETSPORTSMEN_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class GroupWidgetSportsmen
{

public:
    explicit GroupWidgetSportsmen();
    ~GroupWidgetSportsmen();

    QLabel* sportsmenName;
    QPushButton* sportsmenConfirm;
    QPushButton* sportsmenDelete;

private:

};

#endif // GROUPWIDGETSPORTSMEN_H
