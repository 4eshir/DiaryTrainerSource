#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QGroupBox>
#include "standard.h"
#include "diarytrainer.h"
#include "diarysportsmen.h"


namespace mainSpace {
    using cui = const unsigned int;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT



public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QMenu *mnMain;
    QMenu *mnDiaries;
    QAction *showStandards;
    QAction *showCondition;
    QAction *showSportsmenDiary;
    QAction *showTrainerDiary;
    QLabel *label;

    Standard *winStand;
    diaryTrainer *winDT;
    diarySportsmen *winDS;


    std::vector <std::string> analyzeData();
    int checkedId(QGroupBox*, int);
    void CreateMenus(); //создает меню главного окна программы
    void CreateStartPage();
    void SetStyle(QLabel*);

private slots:
    void actionShowStandards();
    void actionShowCondition();
    void actionShowSportsmenDiary();
    void actionShowTrainerDiary();
    void checker(); //проверка на существование заданной дистанции
};

#endif // MAINWINDOW_H
