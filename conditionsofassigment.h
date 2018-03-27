#ifndef CONDITIONSOFASSIGMENT_H
#define CONDITIONSOFASSIGMENT_H

#include <QWidget>

class ConditionsOfAssigment : public QWidget
{
    Q_OBJECT

public:
    explicit ConditionsOfAssigment(QWidget *parent = 0);
    ~ConditionsOfAssigment();

private:
    void CreateWidgets();

};

#endif // CONDITIONSOFASSIGMENT_H
