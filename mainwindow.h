#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "boarddelegate.h"
#include "board.h"
#include "dialogwin.h"
#include "dialoglose.h"
#include <QGridLayout>
#include <QPixmap>
#include <QLabel>
#include <QPushButton>
#include <QLCDNumber>
#include <QTimer>
#include <QTime>
#include <QDebug>
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QTableView>
#include <QDialog>
#include <QModelIndex>
#include <QHeaderView>
#include <QApplication>
#include <QDesktopWidget>
#include <dialogstatistic.h>
#include <statisticdata.h>
#include <QFile>
#include <QDomDocument>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initData();
    void clearData();
    void statisticUpdate(int d);

private:
    QGridLayout *layoutMain;
    QWidget *widgetMain;
    QTableView *boardView;
    QLCDNumber *lcdMineLeft;
    QLCDNumber *lcdTimer;
    QPushButton *btnRestart;
    QTimer *timer;

    int timeUsed;
    int countLeftClick;
    int countRightClick;
    int countDoubleClick;
    int mousePath;
    QTime timeBegin;
    int timeUsedInMsec;

    int difficulty;

    StatisticData *statisticData;

    Board *board;
    QStandardItemModel *boardModel;
    BoardDelegate *boardDelegate;

    QString ssRestart;
    QString ssWin;
    QString ssLose;

public slots:
    void leftClick(const QModelIndex &index);
    void rightClick(const QModelIndex &index);
    void doubleClick(const QModelIndex &index);
    void leftRightClick(const QModelIndex &index);
    void timeIncrease();
    void newGame(bool noChange = false);
    void geometryRefresh();
    void viewRefresh();
    void gameWin();
    void gameLose();

};

#endif // MAINWINDOW_H
