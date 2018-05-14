#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <math.h>
#include "boarddelegate.h"
#include "board.h"
#include "dialogwin.h"
#include "dialoglose.h"
#include "dialoghelp.h"
#include "replay.h"
#include <QGridLayout>
#include <QStackedLayout>
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
#include <QStatusBar>
#include <QDesktopWidget>
#include <dialogstatistic.h>
#include <statisticdata.h>
#include <QFile>
#include <QDomDocument>
#include <QDir>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initData();
    void clearData();
    void statisticUpdate(int d);

    bool getPlayMode() const;
    void setPlayMode(bool playMode);

private:
    QGridLayout *layoutMain;
    QWidget *widgetMain;
    QTableView *boardView;

    QStackedLayout *layoutHeader;

    QWidget *headerPlay;
    QGridLayout *layoutHeaderPlay;
    QLCDNumber *lcdMineLeft;
    QLCDNumber *lcdTimer;
    QPushButton *btnRestart;

    QWidget *headerReplay;
    QGridLayout *layoutHeaderReplay;
    QPushButton *btnLast;
    QPushButton *btnPause;
    QPushButton *btnNext;
    QPushButton *btnOpenFile;
    QPushButton *btnTake;

    QTimer *timer;
    QLabel *statusLabel;

    int timeUsed;
    int countLeftClick;
    int countRightClick;
    int countDoubleClick;
    int mouseX;
    int mouseY;
    double mousePath;
    QTime timeBegin;
    int timeUsedInMsec;

    int difficulty;

    bool playMode;

    StatisticData *statisticData;

    Replay *replay;

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
    void mouseMove(const QPoint pos);
    void timeIncrease();
    void newGame(bool noChange = false);
    void geometryRefresh();
    void viewRefresh();
    void gameWin();
    void gameLose();

};

#endif // MAINWINDOW_H
