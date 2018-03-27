#include "diarytrainer.h"
#include "exceptionhandler.h"
#include "timedataparser.h"
#include "diarysportsmen.h"

#include <vector>
#include <QFile>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QRadioButton>

#include <QDebug>

diaryTrainer::diaryTrainer(QWidget *parent) :
    QWidget(parent)
{
    this->resize(450, 760);
    setWindowTitle("Дневник тренера");
    QFile fin("CommonData\\CommonSportsmensDataMale.txt");
    fin.open(QIODevice::ReadOnly | QIODevice::Text);
    prevListSportsmensMale = fin.readAll();
    fin.close();
    fin.setFileName("CommonData\\CommonSportsmensDataFemale.txt");
    fin.open(QIODevice::ReadOnly | QIODevice::Text);
    prevListSportsmensFemale = fin.readAll();
    fin.close();
    CreateRadioButtons();
    CreateWidgets();
}

diaryTrainer::~diaryTrainer()
{
}

void diaryTrainer::CreateRadioButtons()
{
    QLabel* lblGender = new QLabel("<font face = Georgia size = 4>Пол:</font>", this);
    lblGender->setGeometry(QRect(10, 45, 100, 30));
    QLabel* lblSort = new QLabel("<font face = Georgia size = 4>Сортировка:</font>", this);
    lblSort->setGeometry(QRect(10, 85, 100, 30));

    mainLayout = new QGridLayout(this);
    rbSortAlphabet = new QRadioButton("по алфавиту", this);
    rbSortTime = new QRadioButton("по лучшему времени", this);
    rbSortAlphabet->setGeometry(QRect(120, 85, 100, 27));
    rbSortTime->setGeometry(QRect(120, 117, 100, 27));
    QHBoxLayout* hblRadButtonsLabel = new QHBoxLayout(this);
    QVBoxLayout* vblRadioButtons = new QVBoxLayout(this);
    vblRadioButtons->addWidget(rbSortAlphabet);
    vblRadioButtons->addWidget(rbSortTime);
    hblRadButtonsLabel->addWidget(lblSort);
    hblRadButtonsLabel->addLayout(vblRadioButtons);
    hblRadButtonsLabel->setGeometry(QRect(10, 85, 370, 70));
    gbSort = new QGroupBox(this);
    gbSort->setGeometry(QRect(10, 95, 280, 70));
    gbSort->setLayout(hblRadButtonsLabel);
    connect(rbSortAlphabet, SIGNAL(clicked()), SLOT(actionAddSort()));
    connect(rbSortTime, SIGNAL(clicked()), SLOT(actionAddSort()));

    rbMale = new QRadioButton("Мужчины", this);
    rbFemale = new QRadioButton("Женщины", this);
    rbMale->setGeometry(QRect(120, 45, 100, 27));
    rbFemale->setGeometry(QRect(160, 45, 100, 27));
    QHBoxLayout* hblRadioButtons = new QHBoxLayout(this);
    hblRadioButtons->addWidget(lblGender);
    hblRadioButtons->addWidget(rbMale);
    hblRadioButtons->addWidget(rbFemale);
    gbGender = new QGroupBox(this);
    gbGender->setGeometry(QRect(10, 45, 370, 40));
    gbGender->setLayout(hblRadioButtons);
    connect(rbMale, SIGNAL(clicked()), SLOT(actionChooseMale()));
    connect(rbFemale, SIGNAL(clicked()), SLOT(actionChooseFemale()));
    rbMale->setChecked(true);

}

void diaryTrainer::CreateWidgets()
{

    QFile fin("CommonData\\" + genderFilename + ".txt");
    fin.open(QIODevice::ReadOnly | QIODevice::Text);
    QString temp = fin.readLine();
    int sizeOfVector = temp.toInt();
    updateList = new QPushButton("Обновить список", this);
    updateList->setGeometry(QRect(10, 10, 430, 30));
    connect(updateList, SIGNAL(clicked()), this, SLOT(actionUpdateList()));
    sportsmensArea = new QScrollArea(this);
    smDelete = new QSignalMapper;
    smChoose = new QSignalMapper;
    sportsmensTimes.resize(sizeOfVector * 2);
    sportsmens.resize(sizeOfVector);
    for (uint16_t i = 0; i != sizeOfVector; ++i)
    {
        QString tempName = QString(fin.readLine());
        int tempGender = 0;
        QFile fin("DataSportsmens\\" + diarySportsmen::deleteSpace(tempName) + "25.timedata");
        fin.open(QIODevice::ReadOnly | QIODevice::Text);
        QString tempStr = "";
        tempStr = fin.readLine();
        tempGender = tempStr.remove(tempStr.size() - 1, 2).toInt();
        fin.close();
        sportsmensTimes[2 * i] = new SportsmenData(diarySportsmen::deleteSpace(tempName), 25, tempGender);
        sportsmensTimes[2 * i + 1] = new SportsmenData(diarySportsmen::deleteSpace(tempName), 50, tempGender);
        sportsmens[i] = new GroupWidgetSportsmen();
        sportsmens[i]->sportsmenName = new QLabel("<font face = Georgia size = 5>" + tempName.toUtf8() + "</font>", this);
        sportsmens[i]->sportsmenName->setGeometry(QRect(10, 50 + 40 * i, 250, 30));
        SetStyle(sportsmens[i]->sportsmenName);
        sportsmens[i]->sportsmenConfirm = new QPushButton("Выбрать", this);
        sportsmens[i]->sportsmenConfirm->setGeometry(QRect(220, 50 + 40 * i, 80, 30));
        sportsmens[i]->sportsmenDelete = new QPushButton("Удалить", this);
        sportsmens[i]->sportsmenDelete->setGeometry(QRect(310, 50 + 40 * i, 80, 30));
        mainLayout->addWidget(sportsmens[i]->sportsmenName, i, 0);
        mainLayout->addWidget(sportsmens[i]->sportsmenConfirm, i, 1);
        mainLayout->addWidget(sportsmens[i]->sportsmenDelete, i, 2);
        smDelete->setMapping(sportsmens[i]->sportsmenDelete, i);
        smChoose->setMapping(sportsmens[i]->sportsmenConfirm, i);
        connect(sportsmens[i]->sportsmenDelete, SIGNAL(clicked()), smDelete, SLOT(map()));
        connect(sportsmens[i]->sportsmenConfirm, SIGNAL(clicked()), smChoose, SLOT(map()));
        //Добавление нового спортсмена в вектор

        //-------------------------------------
    }
    connect(smDelete, SIGNAL(mapped(int)), this, SLOT(actionDeleteSportsmen(int)));
    connect(smChoose, SIGNAL(mapped(int)), this, SLOT(actionChooseSportsmen(int)));
    QWidget *wgt = new QWidget(this);
    wgt->setLayout(mainLayout);
    sportsmensArea->setGeometry(QRect(10, 210, 430, 500));
    sportsmensArea->setWidget(wgt);
    sportsmensArea->show();
    addSportsmen = new QPushButton("Добавить спортсмена", this);
    addSportsmen->setGeometry(QRect(10, this->height() - 40, this->geometry().width() - 20, 30));
    connect(addSportsmen, SIGNAL(clicked()), this, SLOT(actionAddSportsmen()));

    cbStyle = new QComboBox(this);
    cbStyle->addItem("Выберите стиль...");
    cbStyle->addItem("Вольный");
    cbStyle->addItem("На спине");
    cbStyle->addItem("Брасс");
    cbStyle->addItem("Баттерфляй");
    cbStyle->addItem("Комплекс");
    cbStyle->setGeometry(QRect(300, 95, 140, 30));
    connect(cbStyle, SIGNAL(currentIndexChanged(int)), this, SLOT(actionSortTime()));

    cbPool = new QComboBox(this);
    cbPool->addItem("Выберите бассейн...");
    cbPool->addItem("25 м");
    cbPool->addItem("50 м");
    cbPool->setGeometry(300, 130, 140, 30);
    connect(cbPool, SIGNAL(currentIndexChanged(int)), this, SLOT(actionSortTime()));



    cbStyle->hide();
    cbPool->hide();

    fin.close();
}

void diaryTrainer::DeleteWidgets(int e)
{
    QFile fin("CommonData\\" + genderFilename + ".txt");
    fin.open(QIODevice::ReadOnly | QIODevice::Text);
    QString temp = fin.readLine();
    fin.close();
    int sizeOfVector = temp.toInt();
    for (uint16_t i = 0; i != sizeOfVector + e; ++i)
        for (uint16_t j = 0; j != 3; ++j)
            mainLayout->removeItem(mainLayout->itemAtPosition(i, j));
    for (uint16_t i = 0; i != sizeOfVector + e; ++i)
    {
        delete sportsmens[i]->sportsmenName;
        delete sportsmens[i]->sportsmenConfirm;
        delete sportsmens[i]->sportsmenDelete;
    }
}

void diaryTrainer::actionAddSportsmen()
{
    FormAddSportsmen *formAdd = new FormAddSportsmen(genderFilename);
    formAdd->show();
}

void diaryTrainer::actionUpdateList()
{
    QFile fin("CommonData\\" + genderFilename + ".txt");
    fin.open(QIODevice::ReadOnly | QIODevice::Text);
    QString tempStr = fin.readLine();
    int tempSize = tempStr.remove(tempStr.size() - 1, 2).toInt();
    if (tempSize == 0)
    {
        ExceptionHandler::exceptionNullList(this);
        return;
    }
    for (uint16_t i = 0; i != sportsmens.size(); ++i)
        for (uint16_t j = 0; j != 3; ++j)
            mainLayout->removeItem(mainLayout->itemAtPosition(i, j));
    CreateWidgets();
}



void diaryTrainer::SetStyle(QLabel* lbl)
{
    lbl->setStyleSheet("QLabel {"
                                            "background-color: white;"
                                            "border-style: solid;"
                                            "border-width: 1px;"
                                            "border-color: black; "
                                            "}");
}

void diaryTrainer::actionDeleteSportsmen(int i)
{
    QFile fin("CommonData\\" + genderFilename + ".txt");
    int counter = 0;
    fin.open(QIODevice::ReadOnly | QIODevice::Text);
    QString allFile = "";
    QString tempStr = fin.readLine();
    int tempSize = tempStr.remove(tempStr.size() - 1, 2).toInt();
    while (counter != i)
    {
        allFile += fin.readLine();
        ++counter;
    }
    QString name = fin.readLine(); //пропускаем удаляемую строку
    name.remove(name.size() - 1, 2);
    QStringList nameAndSecondName = name.split(' ');
    while (!fin.atEnd())
        allFile += fin.readLine();
    fin.close();
    fin.open(QIODevice::WriteOnly | QIODevice::Truncate);
    QTextStream stream(&fin);
    stream.setCodec("UTF8");
    stream << tempSize - 1 << "\n" << allFile;
    stream.flush();
    fin.close();
    QString temp = "DataSportsmens\\" + nameAndSecondName.at(0) + nameAndSecondName.at(1) + "25.timedata";
    QFile(temp).remove();
    temp = "DataSportsmens\\" + nameAndSecondName.at(0) + nameAndSecondName.at(1) + "50.timedata";
    QFile(temp).remove();
    for (uint16_t i = 0; i != sportsmens.size(); ++i)
        for (uint16_t j = 0; j != 3; ++j)
            mainLayout->removeItem(mainLayout->itemAtPosition(i, j));
    CreateWidgets();
}

QString diaryTrainer::clearStr(QString str)
{
    QString result = "";
    uint16_t i = 0;
    while (str[i] != '>')
        ++i;
    ++i;
    while (str[i] != '<')
    {
        result.push_back(str[i]);
        ++i;
    }
    return result;
}



void diaryTrainer::actionChooseSportsmen(int i)
{
    QString name = sportsmens[i]->sportsmenName->text();
    diarySportsmen *win = new diarySportsmen(clearStr(name));
    win->setWindowTitle(clearStr(name));
    win->show();
}

void diaryTrainer::actionAddSort()
{
    if (sportsmens.size() == 0)
        return;
    if (rbSortTime->isChecked())
    {
        cbStyle->setCurrentIndex(0);
        cbStyle->setCurrentText("Выберите стиль...");
        cbPool->setCurrentIndex(0);
        cbStyle->setCurrentText("Выберите бассейн...");
        cbStyle->show();
        cbPool->show();
    }

    if (rbSortAlphabet->isChecked())
    {
        AlphabetSort();
        cbStyle->hide();
        cbPool->hide();
        if (cbDistance != NULL)
            cbDistance->hide();

    }
}

void diaryTrainer::actionSortTime()
{
    if (cbStyle->currentIndex() != 0 && cbPool->currentIndex() != 0)
    {
        if (cbStyle->currentIndex() == 1)
        {
            cbDistance = new QComboBox(this);
            cbDistance->addItem("Выберите дистанцию...");
            cbDistance->addItem("50 м");
            cbDistance->addItem("100 м");
            cbDistance->addItem("200 м");
            cbDistance->addItem("400 м");
            cbDistance->addItem("800 м");
            cbDistance->addItem("1500 м");
            cbDistance->setGeometry(QRect(300, 165, 140, 30));
            connect(cbDistance, SIGNAL(currentIndexChanged(int)), this, SLOT(actionStartSort()));
            cbDistance->show();
        }
        else if (cbStyle->currentIndex() == 5)
        {
            if (cbPool->currentIndex() == 1)
            {
                cbDistance = new QComboBox(this);
                cbDistance->addItem("Выберите дистанцию...");
                cbDistance->addItem("100 м");
                cbDistance->addItem("200 м");
                cbDistance->addItem("400 м");
                cbDistance->setGeometry(QRect(300, 165, 140, 30));
                connect(cbDistance, SIGNAL(currentIndexChanged(int)), this, SLOT(actionStartSort()));
                cbDistance->show();
            }
            else
            {
                cbDistance = new QComboBox(this);
                cbDistance->addItem("Выберите дистанцию...");
                cbDistance->addItem("200 м");
                cbDistance->addItem("400 м");
                cbDistance->setGeometry(QRect(300, 165, 140, 30));
                connect(cbDistance, SIGNAL(currentIndexChanged(int)), this, SLOT(actionStartSort()));
                cbDistance->show();
            }
        }
        else
        {
            cbDistance = new QComboBox(this);
            cbDistance->addItem("Выберите дистанцию...");
            cbDistance->addItem("50 м");
            cbDistance->addItem("100 м");
            cbDistance->addItem("200 м");
            cbDistance->setGeometry(QRect(300, 165, 140, 30));
            connect(cbDistance, SIGNAL(currentIndexChanged(int)), this, SLOT(actionStartSort()));
            cbDistance->show();
        }
        style = cbStyle->itemText(cbStyle->currentIndex());
        distance = cbDistance->currentIndex();
    }

}

void diaryTrainer::actionStartSort()
{
    qDebug() << "TIMESORT";
    //сортировка по времени
    QString style = cbStyle->currentText();
    if (style == "Вольный") style = "freestyle";
    else if (style == "На спине") style = "backstroke";
    else if (style == "Брасс") style = "breakstroke";
    else if (style == "Баттерфляй") style = "butterfly";
    else style = "midley";
    int pool = cbPool->currentText().remove(cbPool->currentText().size() - 2, 3).toInt();
    int distance = GetDistanceNumb(style, cbDistance->currentText().remove(cbDistance->currentText().size() - 2, 3).toInt(), pool);
    int extraCoef = 0;
    pool == 25 ? extraCoef = 0 : extraCoef = 1;
    for (uint16_t i = 0; i != sportsmens.size(); ++i)
    {
        for (uint16_t j = 0; j != sportsmens.size() - 1; ++j)
        {
            Time t1;
            Time t2;
            if (style == "freestyle")
            {
                t1 = sportsmensTimes[2 * j + extraCoef]->bestFreestyleTime[distance];
                t2 = sportsmensTimes[2 * j + extraCoef + 2]->bestFreestyleTime[distance];
            }
            else if (style == "backstroke")
            {
                t1 = sportsmensTimes[2 * j + extraCoef]->bestBackstrokeTime[distance];
                t2 = sportsmensTimes[2 * j + extraCoef + 2]->bestBackstrokeTime[distance];
            }
            else if (style == "breakstroke")
            {
                t1 = sportsmensTimes[2 * j + extraCoef]->bestBreakstrokeTime[distance];
                t2 = sportsmensTimes[2 * j + extraCoef + 2]->bestBreakstrokeTime[distance];
            }
            else if (style == "butterfly")
            {
                t1 = sportsmensTimes[2 * j + extraCoef]->bestButterflyTime[distance];
                t2 = sportsmensTimes[2 * j + extraCoef + 2]->bestButterflyTime[distance];
            }
            else
            {
                t1 = sportsmensTimes[2 * j + extraCoef]->bestMidleyTime[distance];
                t2 = sportsmensTimes[2 * j + extraCoef + 2]->bestMidleyTime[distance];
            }
            qDebug() << t1.minutes << t1.seconds;
            qDebug() << t2.minutes << t2.seconds;
            if (t1 > t2)
            {
                SportsmenData* tempTime = sportsmensTimes[2 * j + extraCoef];
                sportsmensTimes[2 * j + extraCoef] = sportsmensTimes[2 * j + extraCoef + 2];
                sportsmensTimes[2 * j + extraCoef + 2] = tempTime;
                qDebug() << "if";
                GroupWidgetSportsmen* temp = sportsmens[j];
                sportsmens[j] = sportsmens[j + 1];
                sportsmens[j + 1] = temp;
                //QRect tempB1 = sportsmens[j]->sportsmenConfirm->geometry();
                //QRect tempB2 = sportsmens[j]->sportsmenDelete->geometry();
                QRect tempB3 = sportsmens[j]->sportsmenName->geometry();
                //sportsmens[j]->sportsmenConfirm->setGeometry(sportsmens[j + 1]->sportsmenConfirm->geometry());
                //sportsmens[j]->sportsmenDelete->setGeometry(sportsmens[j + 1]->sportsmenDelete->geometry());
                sportsmens[j]->sportsmenName->setGeometry(sportsmens[j + 1]->sportsmenName->geometry());
                //sportsmens[j + 1]->sportsmenConfirm->setGeometry(tempB1);
                //sportsmens[j + 1]->sportsmenDelete->setGeometry(tempB2);
                sportsmens[j + 1]->sportsmenName->setGeometry(tempB3);
            }
        }
    }
    ResortedSportsmenList();
}

void diaryTrainer::AlphabetSort()
{
    qDebug() << sportsmens[1]->sportsmenName->text();
    for (uint16_t i = 0; i != sportsmens.size(); ++i)
    {
        qDebug() << "!!!!!!!";
        for (uint16_t j = 0; j < sportsmens.size() - 1; ++j)
        {
            qDebug() << j << j + 1;
            qDebug() << sportsmens[j]->sportsmenName->text() << sportsmens[j + 1]->sportsmenName->text() << (sportsmens[j]->sportsmenName->text() > sportsmens[j + 1]->sportsmenName->text());
            if (sportsmens[j]->sportsmenName->text() > sportsmens[j + 1]->sportsmenName->text())
            {
                SportsmenData* tempTime = sportsmensTimes[2 * j];
                sportsmensTimes[2 * j] = sportsmensTimes[2 * j + 2];
                sportsmensTimes[2 * j + 2] = tempTime;
                tempTime = sportsmensTimes[2 * j + 1];
                sportsmensTimes[2 * j + 1] = sportsmensTimes[2 * j + 3];
                sportsmensTimes[2 * j + 3] = tempTime;
                qDebug() << "if";
                GroupWidgetSportsmen* temp = sportsmens[j];
                sportsmens[j] = sportsmens[j + 1];
                sportsmens[j + 1] = temp;
                //QRect tempB1 = sportsmens[j]->sportsmenConfirm->geometry();
                //QRect tempB2 = sportsmens[j]->sportsmenDelete->geometry();
                QRect tempB3 = sportsmens[j]->sportsmenName->geometry();
                //sportsmens[j]->sportsmenConfirm->setGeometry(sportsmens[j + 1]->sportsmenConfirm->geometry());
                //sportsmens[j]->sportsmenDelete->setGeometry(sportsmens[j + 1]->sportsmenDelete->geometry());
                sportsmens[j]->sportsmenName->setGeometry(sportsmens[j + 1]->sportsmenName->geometry());
                //sportsmens[j + 1]->sportsmenConfirm->setGeometry(tempB1);
                //sportsmens[j + 1]->sportsmenDelete->setGeometry(tempB2);
                sportsmens[j + 1]->sportsmenName->setGeometry(tempB3);
            }
        }
    }
    ResortedSportsmenList();
}

int diaryTrainer::GetDistanceNumb(QString style, int distance, int pool)
{
    if (style == "midley")
    {
        if (pool == 25)
        {
            switch(distance)
            {
                case 100:
                    return 0;
                case 200:
                    return 1;
                case 400:
                    return 2;
            }
        }
        else
        {
            switch(distance)
            {
                case 200:
                    return 0;
                case 400:
                    return 1;
            }
        }
    }
    else if (style == "freestyle")
    {
        switch(distance)
        {
            case 50:
                return 0;
            case 100:
                return 1;
            case 200:
                return 2;
            case 400:
                return 3;
            case 800:
                return 4;
            case 1500:
                return 5;
        }
    }
    else
    {
        switch(distance)
        {
            case 50:
                return 0;
            case 100:
                return 1;
            case 200:
                return 2;
        }
    }
}

void diaryTrainer::actionChooseMale()
{
    rbSortAlphabet->setChecked(false);
    rbSortTime->setChecked(false);
    cbStyle->hide();
    cbPool->hide();
    cbDistance = new QComboBox(this);
    cbDistance->hide();
    genderFilename = "CommonSportsmensDataMale";
    for (uint16_t i = 0; i != sportsmens.size(); ++i)
        for (uint16_t j = 0; j != 3; ++j)
            mainLayout->removeItem(mainLayout->itemAtPosition(i, j));
    CreateWidgets();
}

void diaryTrainer::actionChooseFemale()
{
    rbSortAlphabet->setChecked(false);
    rbSortTime->setChecked(false);
    cbStyle->hide();
    cbPool->hide();
    cbDistance = new QComboBox(this);
    cbDistance->hide();
    genderFilename = "CommonSportsmensDataFemale";
    for (uint16_t i = 0; i != sportsmens.size(); ++i)
        for (uint16_t j = 0; j != 3; ++j)
            mainLayout->removeItem(mainLayout->itemAtPosition(i, j));
    CreateWidgets();
}

void diaryTrainer::ResortedSportsmenList()
{
    QFile fin;
    if (rbMale->isChecked())
        fin.setFileName("CommonData\\CommonSportsmensDataMale.txt");
    else if (rbFemale->isChecked())
        fin.setFileName("CommonData\\CommonSportsmensDataFemale.txt");
    fin.open(QIODevice::ReadOnly | QIODevice::Text);
    QString newList = fin.readLine();
    for (uint16_t i = 0 ; i != sportsmens.size(); ++i)
        newList += clearStr(sportsmens[i]->sportsmenName->text());
    fin.close();
    fin.open(QIODevice::WriteOnly | QIODevice::Truncate);
    QTextStream stream(&fin);
    stream.setCodec("UTF-8");
    stream << newList;
    stream.flush();
    fin.close();
}
