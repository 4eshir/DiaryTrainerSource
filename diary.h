#ifndef DIARY_H
#define DIARY_H

#include <QWidget>

namespace Ui {
class Diary;
}

class Diary : public QWidget
{
    Q_OBJECT

public:
    explicit Diary(QWidget *parent = 0);
    ~Diary();

private:
    Ui::Diary *ui;
};

#endif // DIARY_H
