#ifndef DIARYSPORTSMEN_H
#define DIARYSPORTSMEN_H

#include "diary.h"
#include "exceptionhandler.h"

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QSignalMapper>


class diarySportsmen : public QWidget
{
    Q_OBJECT


public:
    explicit diarySportsmen(QWidget *parent = 0);
    diarySportsmen(QString);
    ~diarySportsmen();

    static QString deleteSpace(QString);

    QLineEdit **arrEnterTime;

private:

    int code = 0;
    QComboBox *cbStyle;
    QPushButton *confirmStyle;
    QLabel **arrDist;
    std::vector <QLabel*> arrPrevTime;
    std::vector <QLabel*> arrCurrTime;
    std::vector<QPushButton*> arrConfirmsTime;
    std::vector<QPushButton*> arrDeleteTime;
    QPushButton *b25;
    QPushButton *b50;
    QPushButton *detailedStatistic = NULL;
    QLabel *welcome;

    QSignalMapper *smNewTime;
    QSignalMapper *smDeleteTime;

    QString sportName;
    QString chooseStyle;
    int pool;

    void CreateWidgets();
    void CreateDiaryWidgets();
    void SetTime(QString, int);
    void SetStyle(QLabel*, QString, QString, QString);

    bool isNumb(QString);



private slots:
    void actionConfirmStyle();
    void actionCbStyle();
    void actionAddTime(int);
    void action25meters();
    void action50meters();
    void actionShowDetailedStatistic();
    void actionDeleteTime(int);

};

#endif // DIARYSPORTSMEN_H
