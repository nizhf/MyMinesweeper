#include "dialogstatistic.h"

DialogStatistic::DialogStatistic()
{
    setWindowTitle("Statistics");
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    setFixedHeight(510);
    setFixedWidth(400);

    layoutMain = new QGridLayout(this);
    tabWidget = new QTabWidget(this);
    tabWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layoutMain->addWidget(tabWidget, 0, 0, 8, 4);
    tableEasy = new QTableWidget(14, 2);
    tableNormal = new QTableWidget(14, 2);
    tableHard = new QTableWidget(14, 2);
    tableTotal = new QTableWidget(4, 2);
    btnClear = new QPushButton("Clear all");
    btnOk = new QPushButton(tr("OK"));
    tabWidget->addTab(tableTotal, tr("Total"));
    tabWidget->addTab(tableEasy, tr("Easy"));
    tabWidget->addTab(tableNormal, tr("Normal"));
    tabWidget->addTab(tableHard, tr("Hard"));
    layoutMain->addWidget(btnClear, 8, 1, 1, 1);
    layoutMain->addWidget(btnOk, 8, 3, 1, 1);

    connect(btnOk, &QPushButton::clicked, this, &DialogStatistic::reject);
    connect(btnClear, &QPushButton::clicked, this, &DialogStatistic::accept);
}

DialogStatistic::DialogStatistic(StatisticData *data) : DialogStatistic()
{
    this->data = data;

    totalTimeInMsec = 1896;
    totalWin = 15;
    totalLose = 23;

    tableTotal->horizontalHeader()->hide();
    tableTotal->verticalHeader()->hide();
    tableTotal->setFrameShape(QFrame::NoFrame);
    tableTotal->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableTotal->setSelectionMode(QAbstractItemView::NoSelection);
    tableTotal->setFocusPolicy(Qt::NoFocus);
    tableTotal->setShowGrid(false);
    tableTotal->setColumnWidth(0, 185);
    tableTotal->setColumnWidth(1, 185);
    for (int i = 0; i < 4; i++) {
        tableTotal->setRowHeight(i, 30);
    }

    tableTotal->setItem(0, 0, new QTableWidgetItem(tr("Total time: ")));
    int msec, secTemp, sec, minTemp, min, hour;
    msec = data->getTotalTimeInMsec() % 1000;
    secTemp = data->getTotalTimeInMsec() / 1000;
    sec = secTemp % 60;
    minTemp = secTemp / 60;
    min = minTemp % 60;
    hour = min / 60;
    tableTotal->setItem(0, 1, new QTableWidgetItem(tr("%1:%2:%3.%4").arg(hour).arg(min).arg(sec).arg(msec)));
    tableTotal->setItem(1, 0, new QTableWidgetItem(tr("Total games: ")));
    tableTotal->setItem(1, 1, new QTableWidgetItem(tr("%1").arg(data->getTotalWin() + data->getTotalLose())));
    tableTotal->setItem(2, 0, new QTableWidgetItem(tr("Wins: ")));
    tableTotal->setItem(2, 1, new QTableWidgetItem(tr("%1").arg(data->getTotalWin())));
    tableTotal->setItem(3, 0, new QTableWidgetItem(tr("Win Rate: ")));
    if (data->getTotalWin() + data->getTotalLose() == 0) {
        tableTotal->setItem(3, 1, new QTableWidgetItem(tr("0")));
    }
    else {
        tableTotal->setItem(3, 1, new QTableWidgetItem(tr("%1%").arg(100 * data->getTotalWin() / (data->getTotalWin() + data->getTotalLose()))));
    }

    initLayout(tableEasy, StatisticData::Easy);
    initLayout(tableNormal, StatisticData::Normal);
    initLayout(tableHard, StatisticData::Hard);
}

DialogStatistic::~DialogStatistic() {

}

void DialogStatistic::initLayout(QTableWidget *table, StatisticData::Difficulty diff) {
    int msec, secTemp, sec, minTemp, min, hour;
    table->horizontalHeader()->hide();
    table->verticalHeader()->hide();
    table->setFrameShape(QFrame::NoFrame);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionMode(QAbstractItemView::NoSelection);
    table->setFocusPolicy(Qt::NoFocus);
    table->setShowGrid(false);
    table->setColumnWidth(0, 185);
    table->setColumnWidth(1, 185);
    table->setSpan(8, 0, 1, 2);
    for (int i = 0; i < 14; i++) {
        table->setRowHeight(i, 30);
    }

    table->setItem(0, 0, new QTableWidgetItem(tr("Total time: ")));
    msec = data->getTotalTimeInMsec(diff) % 1000;
    secTemp = data->getTotalTimeInMsec(diff) / 1000;
    sec = secTemp % 60;
    minTemp = secTemp / 60;
    min = minTemp % 60;
    hour = min / 60;
    table->setItem(0, 1, new QTableWidgetItem(tr("%1:%2:%3.%4").arg(hour).arg(min).arg(sec).arg(msec)));
    table->setItem(1, 0, new QTableWidgetItem(tr("Total games: ")));
    table->setItem(1, 1, new QTableWidgetItem(tr("%1").arg(data->getWin(diff) + data->getLose(diff))));
    table->setItem(2, 0, new QTableWidgetItem(tr("Wins: ")));
    table->setItem(2, 1, new QTableWidgetItem(tr("%1").arg(data->getWin(diff))));
    table->setItem(3, 0, new QTableWidgetItem(tr("Win Rate: ")));
    if (data->getWin(diff) + data->getLose(diff) == 0) {
        table->setItem(3, 1, new QTableWidgetItem(tr("0")));
    }
    else {
        table->setItem(3, 1, new QTableWidgetItem(tr("%1%").arg(100 * data->getWin(diff) / (data->getWin(diff) + data->getLose(diff)))));
    }
    table->setItem(4, 0, new QTableWidgetItem(tr("Winning Streak max: ")));
    table->setItem(4, 1, new QTableWidgetItem(tr("%1").arg(data->getMaxWinningStreak(diff))));
    table->setItem(5, 0, new QTableWidgetItem(tr("Losing Streak max: ")));
    table->setItem(5, 1, new QTableWidgetItem(tr("%1").arg(data->getMaxLosingStreak(diff))));
    if (data->getStreakWin(diff)) {
        table->setItem(6, 0, new QTableWidgetItem(tr("Winning Streak now: ")));
    }
    else {
        table->setItem(6, 0, new QTableWidgetItem(tr("Losing Streak now: ")));
    }
    table->setItem(6, 1, new QTableWidgetItem(tr("%1").arg(data->getStreakNow(diff))));
    table->setItem(7, 0, new QTableWidgetItem(tr("No flag: ")));
    table->setItem(7, 1, new QTableWidgetItem(tr("%1").arg(data->getGameNP(diff))));

    table->setItem(8, 0, new QTableWidgetItem(tr("Best 5 games:")));
    for (int i = 0; i < 5; i++) {
        if (data->getMinTimeInMsec(i, diff) == -1) {
            table->setItem(9 + i, 0, new QTableWidgetItem(tr("")));
            table->setItem(9 + i, 1, new QTableWidgetItem(tr("")));
        }
        else {
            table->setItem(9 + i, 0, new QTableWidgetItem(tr("%1/%2/%3").arg(data->getMinTimeYear(i, diff)).arg(data->getMinTimeMonth(i, diff)).arg(data->getMinTimeDay(i, diff))));
            msec = data->getMinTimeInMsec(i, diff) % 1000;
            secTemp = data->getMinTimeInMsec(i, diff) / 1000;
            sec = secTemp % 60;
            minTemp = secTemp / 60;
            min = minTemp % 60;
            hour = min / 60;
            table->setItem(9 + i, 1, new QTableWidgetItem(tr("%1:%2:%3.%4").arg(hour).arg(min).arg(sec).arg(msec)));
        }
    }

}