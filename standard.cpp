#include "standard.h"

#include <QJsonArray>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>

#include <vector>
#include <fstream>
#include <string>
#include <QFile>
#include <QDebug>

Standard::Standard(QWidget *parent) :
    QWidget(parent)
{
    CreateWidgets();
}

Standard::~Standard()
{
}

void Standard::CreateWidgets()
{
    QLabel *background = new QLabel(this);
    QImage standBack("images\\standardBack.png");
    background->setGeometry(QRect(0, 0, 510, 575));
    background->setPixmap(QPixmap::fromImage(standBack));
    background->setScaledContents(true);
    background->show();
    msic = new QLabel(this);
    msic->setGeometry(QRect(10, 10, 150, 150));
    QImage msicImg("images\\msic.png");
    msic->setPixmap(QPixmap::fromImage(msicImg));
    msic->setScaledContents(true);
    msic->show();
    msicTime = new QLabel("<font face = Georgia size = 5><p align = center>NO TIME</p></font>", this);
    msicTime->setGeometry(QRect(10, 160, 150, 25));
    msicTime->setStyleSheet("QLabel {"
                                            "background-color: white;"
                                            "border-style: solid;"
                                            "border-width: 1px;"
                                            "border-color: black; "
                                            "}");
    msicTime->show();

    ms = new QLabel(this);
    ms->setGeometry(QRect(180, 10, 150, 150));
    QImage msImg("images\\ms.png");
    ms->setPixmap(QPixmap::fromImage(msImg));
    ms->setScaledContents(true);
    ms->show();
    msTime = new QLabel("<font face = Georgia size = 5><p align = center>NO TIME</p></font>", this);
    msTime->setGeometry(QRect(180, 160, 150, 25));
    msTime->setStyleSheet("QLabel {"
                                            "background-color: white;"
                                            "border-style: solid;"
                                            "border-width: 1px;"
                                            "border-color: black; "
                                            "}");
    msTime->show();

    cms = new QLabel(this);
    cms->setGeometry(QRect(350, 10, 150, 150));
    QImage cmsImg("images\\cms.png");
    cms->setPixmap(QPixmap::fromImage(cmsImg));
    cms->setScaledContents(true);
    cms->show();
    cmsTime = new QLabel("<font face = Georgia size = 5><p align = center>NO TIME</p></font>", this);
    cmsTime->setGeometry(QRect(350, 160, 150, 25));
    cmsTime->setStyleSheet("QLabel {"
                                            "background-color: white;"
                                            "border-style: solid;"
                                            "border-width: 1px;"
                                            "border-color: black; "
                                            "}");
    cmsTime->show();

    //--------------------------------

    a1 = new QLabel(this);
    a1->setGeometry(QRect(10, 200, 150, 150));
    QImage a1Img("images\\a1.png");
    a1->setPixmap(QPixmap::fromImage(a1Img));
    a1->setScaledContents(true);
    a1->show();
    a1Time = new QLabel("<font face = Georgia size = 5><p align = center>NO TIME</p></font>", this);
    a1Time->setGeometry(QRect(10, 350, 150, 25));
    a1Time->setStyleSheet("QLabel {"
                                            "background-color: white;"
                                            "border-style: solid;"
                                            "border-width: 1px;"
                                            "border-color: black; "
                                            "}");
    a1Time->show();

    a2 = new QLabel(this);
    a2->setGeometry(QRect(180, 200, 150, 150));
    QImage a2Img("images\\a2.png");
    a2->setPixmap(QPixmap::fromImage(a2Img));
    a2->setScaledContents(true);
    a2->show();
    a2Time = new QLabel("<font face = Georgia size = 5><p align = center>NO TIME</p></font>", this);
    a2Time->setGeometry(QRect(180, 350, 150, 25));
    a2Time->setStyleSheet("QLabel {"
                                            "background-color: white;"
                                            "border-style: solid;"
                                            "border-width: 1px;"
                                            "border-color: black; "
                                            "}");
    a2Time->show();

    a3 = new QLabel(this);
    a3->setGeometry(QRect(350, 200, 150, 150));
    QImage a3Img("images\\a3.png");
    a3->setPixmap(QPixmap::fromImage(a3Img));
    a3->setScaledContents(true);
    a3->show();
    a3Time = new QLabel("<font face = Georgia size = 5><p align = center>NO TIME</p></font>", this);
    a3Time->setGeometry(QRect(350, 350, 150, 25));
    a3Time->setStyleSheet("QLabel {"
                                            "background-color: white;"
                                            "border-style: solid;"
                                            "border-width: 1px;"
                                            "border-color: black; "
                                            "}");
    a3Time->show();

    //------------------------------------

    j1 = new QLabel(this);
    j1->setGeometry(QRect(10, 390, 150, 150));
    QImage j1Img("images\\j1.png");
    j1->setPixmap(QPixmap::fromImage(j1Img));
    j1->setScaledContents(true);
    j1->show();
    j1Time = new QLabel("<font face = Georgia size = 5><p align = center>NO TIME</p></font>", this);
    j1Time->setGeometry(QRect(10, 540, 150, 25));
    j1Time->setStyleSheet("QLabel {"
                                            "background-color: white;"
                                            "border-style: solid;"
                                            "border-width: 1px;"
                                            "border-color: black; "
                                            "}");
    j1Time->show();

    j2 = new QLabel(this);
    j2->setGeometry(QRect(180, 390, 150, 150));
    QImage j2Img("images\\j2.png");
    j2->setPixmap(QPixmap::fromImage(j2Img));
    j2->setScaledContents(true);
    j2->show();
    j2Time = new QLabel("<font face = Georgia size = 5><p align = center>NO TIME</p></font>", this);
    j2Time->setGeometry(QRect(180, 540, 150, 25));
    j2Time->setStyleSheet("QLabel {"
                                            "background-color: white;"
                                            "border-style: solid;"
                                            "border-width: 1px;"
                                            "border-color: black; "
                                            "}");
    j2Time->show();

    j3 = new QLabel(this);
    j3->setGeometry(QRect(350, 390, 150, 150));
    QImage j3Img("images\\j3.png");
    j3->setPixmap(QPixmap::fromImage(j3Img));
    j3->setScaledContents(true);
    j3->show();
    j3Time = new QLabel("<font face = Georgia size = 5><p align = center>NO TIME</p></font>", this);
    j3Time->setGeometry(QRect(350, 540, 150, 25));
    j3Time->setStyleSheet("QLabel {"
                                            "background-color: white;"
                                            "border-style: solid;"
                                            "border-width: 1px;"
                                            "border-color: black; "
                                            "}");
    j3Time->show();
}


void Standard::readStandards(std::vector <std::string> code)
{
    QString filename = "";
    QString strIden = "";
    if (code[0] == "25 метров" && code[1] == "Мужчины")
        filename = "Male25.txt";
    if (code[0] == "50 метров" && code[1] == "Мужчины")
        filename = "Male50.txt";
    if (code[0] == "25 метров" && code[1] == "Женщины")
        filename = "Female25.txt";
    if (code[0] == "50 метров" && code[1] == "Женщины")
        filename = "Female50.txt";
    QFile fin("standards\\" + filename);
    fin.open(QIODevice::ReadOnly);
    std::string searchStr = code[3] + " " + code[2];
    QString searchQStr = QString::fromStdString(searchStr);
    qDebug() << searchQStr;
    while (!fin.atEnd() && strIden != searchQStr)
    {
        //qDebug() << strIden;
        strIden = fin.readLine();
    }
    qDebug() << strIden;
    QString tempStr = "";
    tempStr = fin.readLine();
    tempStr = formatString(tempStr);
    qDebug() << tempStr;
    msicTime->setText("<font face = Tahoma size = 5><p align = center><b>" + tempStr + "</b></p></font>");
    tempStr = fin.readLine();
    tempStr = formatString(tempStr);
    msTime->setText("<font face = Tahoma size = 5><p align = center><b>" + tempStr + "</b></p></font>");
    tempStr = fin.readLine();
    tempStr = formatString(tempStr);
    cmsTime->setText("<font face = Tahoma size = 5><p align = center><b>" + tempStr + "</b></p></font>");
    tempStr = fin.readLine();
    tempStr = formatString(tempStr);
    a1Time->setText("<font face = Tahoma size = 5><p align = center><b>" + tempStr + "</b></p></font>");
    tempStr = fin.readLine();
    tempStr = formatString(tempStr);
    a2Time->setText("<font face = Tahoma size = 5><p align = center><b>" + tempStr + "</b></p></font>");
    tempStr = fin.readLine();
    tempStr = formatString(tempStr);
    a3Time->setText("<font face = Tahoma size = 5><p align = center><b>" + tempStr + "</b></p></font>");
    tempStr = fin.readLine();
    tempStr = formatString(tempStr);
    j1Time->setText("<font face = Tahoma size = 5><p align = center><b>" + tempStr + "</b></p></font>");
    tempStr = fin.readLine();
    tempStr = formatString(tempStr);
    j2Time->setText("<font face = Tahoma size = 5><p align = center><b>" + tempStr + "</b></p></font>");
    tempStr = fin.readLine();
    tempStr = formatString(tempStr);
    j3Time->setText("<font face = Tahoma size = 5><p align = center><b>" + tempStr + "</b></p></font>");

    fin.close();
}

QString Standard::formatString(const QString& operStr)
{
    QString result;
    int i = 0;
    while (operStr[i] != '/')
    {
        ++i;
    }
    result.resize(i);
    i = 0;
    while (operStr[i] != '/')
    {
        result[i] = operStr[i];
        ++i;
    }
    return result;
}
