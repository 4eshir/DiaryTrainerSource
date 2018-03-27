#include "mainwindow.h"
#include "standard.h"
#include "diarytrainer.h"
#include "timedataparser.h"
#include "diarysportsmen.h"
#include "timedataeditor.h"
#include "time.h"
#include "exceptionhandler.h"


#include <QString>
#include <QFile>
#include <QMenu>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QRadioButton>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QMenuBar>

#include <QDebug>

using namespace mainSpace;

cui startWidth = 750;
cui startHeight = 500;
cui standardWidth = 600;
cui standardHeight = 600;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    CreateMenus();
    CreateStartPage();
    setWindowTitle("EVSK Swim - PC Edition");
    resize(startWidth, startHeight);
}

MainWindow::~MainWindow()
{
}

void MainWindow::CreateMenus()
{
    mnMain = new QMenu ("Главная");
    showStandards = new QAction("Нормативы", this); //пункт меню с нормативами
    connect(showStandards, SIGNAL(triggered()), this, SLOT(actionShowStandards()));
    mnMain->addAction(showStandards); //добавили экшн в меню
    showCondition = new QAction("Условия присвоения разрядов и званий", this); //пункт меню с условиями
    connect(showCondition, SIGNAL(triggered()), this, SLOT(actionShowCondition()));
    mnMain->addAction(showCondition);
    menuBar()->addMenu(mnMain);
    mnDiaries = new QMenu ("Дневник");
    showSportsmenDiary = new QAction("Дневник спортсмена", this);
    connect(showSportsmenDiary, SIGNAL(triggered()), this, SLOT(actionShowSportsmenDiary()));
    mnDiaries->addAction(showSportsmenDiary);
    showTrainerDiary = new QAction("Дневник тренера", this);
    connect(showTrainerDiary, SIGNAL(triggered()), this, SLOT(actionShowTrainerDiary()));
    mnDiaries->addAction(showTrainerDiary);
    menuBar()->addMenu(mnDiaries);
}

void MainWindow::CreateStartPage()
{
    label = new QLabel("LOL KEK CHEBUREK", this);
    label->setGeometry(QRect(0, 30, startWidth, startHeight));
    QImage startPage("images\\startPage.png");
    label->setPixmap(QPixmap::fromImage(startPage));
    label->setScaledContents(true);
    label->show();
}


QPushButton *confirm;

QGroupBox *boxPool;
QRadioButton *rbPool25;
QRadioButton *rbPool50;

QGroupBox *boxSex;
QRadioButton *rbSexMale;
QRadioButton *rbSexFemale;

QGroupBox *boxStyle;
QRadioButton *rbFreestyle;
QRadioButton *rbBackstroke;
QRadioButton *rbBreakstroke;
QRadioButton *rbButterfly;
QRadioButton *rbMidley;

QGroupBox *boxRange;
QRadioButton *rbRange50;
QRadioButton *rbRange100;
QRadioButton *rbRange200;
QRadioButton *rbRange400;
QRadioButton *rbRange800;
QRadioButton *rbRange1500;

void MainWindow::actionShowStandards()
{
    label->hide();
    QLabel *lblBackground = new QLabel(this);
    lblBackground->setGeometry(0, 25, startWidth, startHeight);
    QImage bcgImg("images\\background.png");
    lblBackground->setPixmap(QPixmap::fromImage(bcgImg));
    lblBackground->setScaledContents(true);
    lblBackground->show();
    resize(standardWidth, 350);
    QLabel *labelPool = new QLabel("<font size = 7 face = Georgia><p align = center>Бассейн</p></font>", this);
    labelPool->setGeometry(QRect(10, 40, 130, 40));
    QLabel *labelSex = new QLabel("<font size = 7 face = Georgia><p align = center>Пол</p></font>", this);
    labelSex->setGeometry(QRect(150, 40, 120, 40));
    QLabel *labelStyle = new QLabel("<font size = 7 face = Georgia><p align = center>Стиль</p></font>", this);
    labelStyle->setGeometry(QRect(280, 40, 120, 40));
    QLabel *labelRange = new QLabel("<font size = 7 face = Georgia><p align = center>Дистанция</p></font>", this);
    labelRange->setGeometry(QRect(410, 40, 170, 40));//RGBA прозрачность
    labelPool->show();
    SetStyle(labelPool);
    labelSex->show();
    SetStyle(labelSex);
    labelStyle->show();
    SetStyle(labelStyle);
    SetStyle(labelRange);
    labelRange->show();
    QVBoxLayout *vbPool = new QVBoxLayout(this);
    rbPool25 = new QRadioButton("25 м", this);
    rbPool50 = new QRadioButton("50 м", this);
    rbPool25->setGeometry(QRect(10, 90, 130, 20));
    rbPool50->setGeometry(QRect(10, 120, 130, 20));
    vbPool->addWidget(rbPool25);
    vbPool->addWidget(rbPool50);
    boxPool = new QGroupBox(this);
    boxPool->setGeometry(QRect(10, 90, 130, 80));
    boxPool->setLayout(vbPool);
    boxPool->setStyleSheet("QGroupBox {"
                           "background-color: white;"
                           "}");
    boxPool->show();

    QVBoxLayout *vbSex = new QVBoxLayout(this);
    rbSexMale = new QRadioButton("Мужчины", this);
    rbSexFemale = new QRadioButton("Женщины", this);
    rbSexMale->setGeometry(QRect(280, 90, 120, 20));
    rbSexFemale->setGeometry(QRect(280, 120, 120, 20));
    vbSex->addWidget(rbSexMale);
    vbSex->addWidget(rbSexFemale);
    boxSex = new QGroupBox(this);
    boxSex->setGeometry(QRect(150, 90, 120, 80));
    boxSex->setLayout(vbSex);
    boxSex->setStyleSheet("QGroupBox {"
                           "background-color: white;"
                           "}");
    boxSex->show();

    QVBoxLayout *vbStyle = new QVBoxLayout(this);
    rbFreestyle = new QRadioButton("Вольный", this);
    rbBackstroke = new QRadioButton("На спине", this);
    rbBreakstroke = new QRadioButton("Брасс", this);
    rbButterfly = new QRadioButton("Баттерфляй", this);
    rbMidley = new QRadioButton("Комлпекс", this);
    rbFreestyle->setGeometry(QRect(150, 90, 120, 20));
    rbBackstroke->setGeometry(QRect(150, 120, 120, 20));
    rbBreakstroke->setGeometry(QRect(150, 150, 120, 20));
    rbButterfly->setGeometry(QRect(150, 180, 120, 20));
    rbMidley->setGeometry(QRect(150, 220, 120, 20));
    vbStyle->addWidget(rbFreestyle);
    vbStyle->addWidget(rbBackstroke);
    vbStyle->addWidget(rbBreakstroke);
    vbStyle->addWidget(rbButterfly);
    vbStyle->addWidget(rbMidley);
    boxStyle = new QGroupBox(this);
    boxStyle->setGeometry(QRect(280, 90, 120, 170));
    boxStyle->setLayout(vbStyle);
    boxStyle->setStyleSheet("QGroupBox {"
                           "background-color: white;"
                           "}");
    boxStyle->show();

    QVBoxLayout *vbRange = new QVBoxLayout(this);
    rbRange50 = new QRadioButton("50 м", this);
    rbRange100 = new QRadioButton("100 м", this);
    rbRange200 = new QRadioButton("200 м", this);
    rbRange400 = new QRadioButton("400 м", this);
    rbRange800 = new QRadioButton("800 м", this);
    rbRange1500 = new QRadioButton("1500 м", this);
    rbRange50->setGeometry(QRect(150, 90, 170, 20));
    rbRange100->setGeometry(QRect(150, 120, 170, 20));
    rbRange200->setGeometry(QRect(150, 150, 170, 20));
    rbRange400->setGeometry(QRect(150, 180, 170, 20));
    rbRange800->setGeometry(QRect(150, 210, 170, 20));
    rbRange1500->setGeometry(QRect(150, 230, 170, 20));
    vbRange->addWidget(rbRange50);
    vbRange->addWidget(rbRange100);
    vbRange->addWidget(rbRange200);
    vbRange->addWidget(rbRange400);
    vbRange->addWidget(rbRange800);
    vbRange->addWidget(rbRange1500);
    boxRange = new QGroupBox(this);
    boxRange->setGeometry(QRect(410, 90, 170, 180));
    boxRange->setLayout(vbRange);
    boxRange->setStyleSheet("QGroupBox {"
                           "background-color: white;"
                           "}");
    boxRange->show();

    confirm = new QPushButton("Показать нормативы", this);
    confirm->setGeometry(QRect(standardWidth / 2 - 100, 300, 200, 40));
    connect(confirm, SIGNAL(clicked()), this, SLOT(checker()));
    confirm->show();
}



void MainWindow::checker()
{
    if ((!rbPool25->isChecked() && !rbPool50->isChecked()) || (!rbSexMale->isChecked() && !rbSexFemale->isChecked())
            || (!rbBackstroke->isChecked() && !rbBreakstroke->isChecked() && !rbButterfly->isChecked() && !rbFreestyle->isChecked() && !rbMidley->isChecked())
            || (!rbRange50->isChecked() && !rbRange100->isChecked() && !rbRange200->isChecked() && !rbRange400->isChecked() && !rbRange800->isChecked() && !rbRange1500->isChecked()))
    {
        ExceptionHandler::exceptionInsufficientDistanceData(this);
        return;
    }
    if (((!rbFreestyle->isChecked() && !rbMidley->isChecked()) && (rbRange400->isChecked() || rbRange800->isChecked() || rbRange1500->isChecked()))
            || (rbPool50->isChecked() && rbMidley->isChecked() && (rbRange100->isChecked() || rbRange800->isChecked() || rbRange1500->isChecked()))
            || (rbMidley->isChecked() && (rbRange50->isChecked() || rbRange800->isChecked() || rbRange1500->isChecked())))
    {
        ExceptionHandler::exceptionIncorrectDistanceData(this);
    }
    else
    {
        int x = this->geometry().x();
        int y = this->geometry().y();
        winStand = new Standard();
        winStand->setGeometry(QRect(x + 600, y, 510, 575));
        winStand->setWindowTitle("Нормативы");
        winStand->readStandards(analyzeData());
        winStand->show();
    }
    return;
}

void MainWindow::actionShowCondition()
{

}

void MainWindow::actionShowSportsmenDiary()
{
    winDS = new diarySportsmen();
    winDS->show();
}

void MainWindow::actionShowTrainerDiary()
{
    winDT = new diaryTrainer();
    winDT->show();
}

std::vector <std::string> MainWindow::analyzeData()
{
    std::vector <std::string> result;
    result.resize(4);
    if (rbPool25->isChecked())
        result[0] = "25 метров";
    else
        result[0] = "50 метров";

    if (rbSexMale->isChecked())
        result[1] = "Мужчины";
    else
        result[1] = "Женщины";

    if (rbFreestyle->isChecked())
        result[2] = "вольный\r\n";
    else if (rbBackstroke->isChecked())
        result[2] = "на спине\r\n";
    else if (rbBreakstroke->isChecked())
        result[2] = "брасс\r\n";
    else if (rbButterfly->isChecked())
        result[2] = "баттерфляй\r\n";
    else
        result[2] = "комплекс\r\n";

    if (rbRange50->isChecked())
        result[3] = "50";
    else if (rbRange100->isChecked())
        result[3] = "100";
    else if (rbRange200->isChecked())
        result[3] = "200";
    else if (rbRange400->isChecked())
        result[3] = "400";
    else if (rbRange800->isChecked())
        result[3] = "800";
    else
        result[3] = "1500";
    return result;
}

void MainWindow::SetStyle(QLabel* lbl)
{
    lbl->setStyleSheet("QLabel {"
                                            "background-color: white;"
                                            "border-style: solid;"
                                            "border-width: 1px;"
                                            "border-color: black; "
                                            "}");
}
