#include "diary.h"
#include "ui_diary.h"

Diary::Diary(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Diary)
{
    ui->setupUi(this);
}

Diary::~Diary()
{
    delete ui;
}
