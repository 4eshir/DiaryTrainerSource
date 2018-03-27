#ifndef DIARYTRAINER_H
#define DIARYTRAINER_H

#include "diarysportsmen.h"
#include "formaddsportsmen.h"
#include "groupwidgetsportsmen.h"
#include "sportsmendata.h"

#include <vector>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QGridLayout>
#include <QSignalMapper>
#include <QRadioButton>
#include <QGroupBox>


class diaryTrainer : public QWidget
{
    Q_OBJECT

public:
    explicit diaryTrainer(QWidget *parent = 0);
    ~diaryTrainer();

    QSignalMapper *smDelete;
    QSignalMapper *smChoose;
    QScrollArea *sportsmensArea;
    QGridLayout *mainLayout;
    diarySportsmen *currentSportsmen;
    std::vector<GroupWidgetSportsmen*> sportsmens;
    std::vector<SportsmenData*> sportsmensTimes;
    QPushButton *addSportsmen;
    QPushButton *updateList;

    QGroupBox* gbSort;
    QRadioButton* rbSortAlphabet;
    QRadioButton* rbSortTime;
    QComboBox* cbStyle;
    QComboBox* cbPool;
    QComboBox* cbDistance = NULL;

    QGroupBox* gbGender;
    QRadioButton* rbMale;
    QRadioButton* rbFemale;

    QString style;
    int pool;
    int distance;

    QString genderFilename = "CommonSportsmensDataMale";

    QString prevListSportsmensMale;
    QString prevListSportsmensFemale;



private:
    void CreateRadioButtons();
    void CreateWidgets();
    void DeleteWidgets(int e);
    void SetStyle(QLabel*);

    QString clearStr(QString);
    void AlphabetSort();
    void TimeSort(QString, int);

    int GetDistanceNumb(QString, int, int);
    void ResortedSportsmenList();

private slots:
    void actionAddSportsmen();
    void actionUpdateList();
    void actionDeleteSportsmen(int i);
    void actionChooseSportsmen(int i);
    void actionAddSort();
    void actionSortTime();
    void actionStartSort();
    void actionChooseMale();
    void actionChooseFemale();
};

#endif // DIARYTRAINER_H
