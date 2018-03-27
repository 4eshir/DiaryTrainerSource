#ifndef FORMADDSPORTSMEN_H
#define FORMADDSPORTSMEN_H

#include "diarytrainer.h"

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>


class FormAddSportsmen : public QWidget
{
    Q_OBJECT

public:
    explicit FormAddSportsmen(QWidget *parent = 0);
    FormAddSportsmen(QString);
    ~FormAddSportsmen();

    QLineEdit *leName;
    QLineEdit *leSecondName;

    QLabel *lName;
    QLabel *lSecondName;

    QPushButton *confirm;

    QString genderFilename = "CommonSportsmensDataMale";

private:
    void CreateWidgets();
    void SetStyle(QLabel*);

private slots:
    void actionConfirmAdd();

};

#endif // FORMADDSPORTSMEN_H
