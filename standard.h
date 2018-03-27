#ifndef STANDARD_H
#define STANDARD_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class Standard;
}

class Standard : public QWidget
{
    Q_OBJECT

public:
    explicit Standard(QWidget *parent = 0);
    ~Standard();
    void readStandards(std::vector <std::string> code);

private:
    Ui::Standard *ui;
    QLabel *msic;
    QLabel *ms;
    QLabel *cms;
    QLabel *a1;
    QLabel *a2;
    QLabel *a3;
    QLabel *j1;
    QLabel *j2;
    QLabel *j3;

    QLabel *msicTime;
    QLabel *msTime;
    QLabel *cmsTime;
    QLabel *a1Time;
    QLabel *a2Time;
    QLabel *a3Time;
    QLabel *j1Time;
    QLabel *j2Time;
    QLabel *j3Time;

    QString formatString(const QString& operStr);
    void CreateWidgets();
};

#endif // STANDARD_H
