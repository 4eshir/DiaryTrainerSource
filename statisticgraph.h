#ifndef STATISTICGRAPH_H
#define STATISTICGRAPH_H

#include <QWidget>
#include <QTableWidget>
#include <QLabel>

const uint16_t sizeOfTopValues = 5;

class StatisticGraph : public QWidget
{
    Q_OBJECT

public:
    explicit StatisticGraph();
    StatisticGraph(QString, QString, int);
    ~StatisticGraph();

private:
    std::vector<QTableWidget*> scoreTables;
    std::vector<QLabel**> topValues;
    QLabel** distanceRanges;

    void CreateWidgets(QString, QString, int);
    void CreateGraph(QString, QString, int);

    void SetStyle(QLabel*);

    void FillTable(QTableWidget*, QString, QString, int, int);
    void FillTopResult(QLabel**, QString, QString, int, int);
    int GetDistance(QString, int, int);
    QString deleteSpace(QString str);

    float roundTo(float, int);
};

#endif // STATISTICGRAPH_H
