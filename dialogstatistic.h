#ifndef DIALOGSTATISTIC_H
#define DIALOGSTATISTIC_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QTabWidget>
#include <QGridLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <statisticdata.h>

class DialogStatistic : public QDialog
{
    Q_OBJECT
public:
    DialogStatistic();
    DialogStatistic(StatisticData *data);
    ~DialogStatistic();
    void initLayout(QTableWidget *table, StatisticData::Difficulty diff);


private:
    StatisticData *data;
    int totalTimeInMsec;
    int totalWin;
    int totalLose;

    QTableWidget *tableEasy, *tableNormal, *tableHard, *tableTotal;
    QGridLayout *layoutMain;
    QTabWidget *tabWidget;

    QPushButton *btnClear, *btnOk;



signals:

public slots:
};

#endif // DIALOGSTATISTIC_H