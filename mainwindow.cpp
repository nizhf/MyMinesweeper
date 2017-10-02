#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedHeight(40 * 9 + 100);
    setFixedWidth(40 * 9 + 40);

    ssRestart = tr("#btnRestart {"
                  "border-image: url(:/image/image/restart.png)"
                  "} "
                  "#btnRestart:hover {"
                  "border-image: url(:/image/image/restart_hover.png)"
                  "}"
                  "#btnRestart:pressed {"
                  "border-image: url(:/image/image/restart_press.png)"
                  "}");
    ssWin = tr("#btnRestart {"
              "border-image: url(:/image/image/win.png);"
              "}"
              "#btnRestart:hover {"
              "border-image: url(:/image/image/restart_hover.png);"
              "}"
              "#btnRestart:pressed {"
              "border-image: url(:/image/image/restart_press.png)"
              "}");
    ssLose = tr("#btnRestart {"
               "border-image: url(:/image/image/lose.png);"
               "} "
               "#btnRestart:hover {"
               "border-image: url(:/image/image/restart_hover.png);"
               "}"
               "#btnRestart:pressed {"
               "border-image: url(:/image/image/restart_press.png)"
               "}");

    //layout
    widgetMain = new QWidget(this);
    layoutMain = new QGridLayout;
    widgetMain->setLayout(layoutMain);
    this->setCentralWidget(widgetMain);
    boardView = new QTableView;
    boardView->horizontalHeader()->hide();
    boardView->verticalHeader()->hide();
    layoutMain->addWidget(boardView, 1, 0, 9, 9);
    QPalette palLCD;
    palLCD.setColor(QPalette::Normal, QPalette::WindowText, Qt::red);
    lcdMineLeft = new QLCDNumber(this);
    lcdMineLeft->setFixedSize(QSize(100, 50));
    lcdMineLeft->setPalette(palLCD);
    lcdMineLeft->setSegmentStyle(QLCDNumber::Flat);
    layoutMain->addWidget(lcdMineLeft, 0, 1, 1, 1);
    btnRestart = new QPushButton(this);
    btnRestart->setFixedSize(QSize(50, 50));
    btnRestart->setObjectName(tr("btnRestart"));
    btnRestart->setStyleSheet(ssRestart);
    layoutMain->addWidget(btnRestart, 0, 4, 1, 1);
    lcdTimer = new QLCDNumber(this);
    lcdTimer->display(0);
    lcdTimer->setFixedSize(QSize(100, 50));
    lcdTimer->setPalette(palLCD);
    lcdTimer->setSegmentStyle(QLCDNumber::Flat);
    layoutMain->addWidget(lcdTimer, 0, 7, 1, 1);

    //minesweeper basic codes and view & delegate
    board = new Board(1);
    boardModel = new QStandardItemModel;
    boardDelegate = new BoardDelegate;
    boardView->setModel(boardModel);
    boardView->setItemDelegate(boardDelegate);
    viewRefresh();
    geometryRefresh();
    lcdMineLeft->display(board->getMineLeft());

    //Menu bar
    QMenuBar *menuBar = this->menuBar();
    QMenu *menuStart = menuBar->addMenu("Start");
    QMenu *menuHelp = menuBar->addMenu("Help");
    QAction *actionStart = menuStart->addAction("New Game");
    QMenu *menuDiff = menuStart->addMenu("Difficulty");
    QAction *actionEasy = menuDiff->addAction("Easy (9 x 9, 10 mines)");
    QAction *actionNormal = menuDiff->addAction("Normal (16 x 16, 50 mines)");
    QAction *actionHard = menuDiff->addAction("Hard (30 x 16, 99 mines)");
    menuStart->addSeparator();
    QAction *actionExit = menuStart->addAction("Exit");
    QAction *actionHelp = menuHelp->addAction("Help");

    timer = new QTimer(this);
    timeUsed = 0;
    countLeftClick = 0;
    countRightClick = 0;
    countDoubleClick = 0;
    mousePath = 0;

    //signals and slots
    connect(timer, &QTimer::timeout, this, &MainWindow::timeIncrease);
    connect(actionStart, &QAction::triggered, this, &MainWindow::newGame);
    connect(actionEasy, &QAction::triggered, [=](){
        board->setDifficulty(1);
        board->initBoard();
        viewRefresh();
        geometryRefresh();
    });
    connect(actionNormal, &QAction::triggered, [=](){
        board->setDifficulty(2);
        board->initBoard();
        viewRefresh();
        geometryRefresh();
    });
    connect(actionHard, &QAction::triggered, [=](){
        board->setDifficulty(3);
        board->initBoard();
        viewRefresh();
        geometryRefresh();
    });
    connect(actionExit, &QAction::triggered, this, &MainWindow::close);
    connect(btnRestart, &QPushButton::clicked, this, &MainWindow::newGame);
    connect(boardDelegate, &BoardDelegate::leftClick, this, &MainWindow::leftClick);
    connect(boardDelegate, &BoardDelegate::rightClick, this, &MainWindow::rightClick);
    connect(boardDelegate, &BoardDelegate::doubleClick, this, &MainWindow::doubleClick);
    connect(boardDelegate, &BoardDelegate::leftRightClick, this, &MainWindow::leftRightClick);
}

MainWindow::~MainWindow()
{
    delete board;
}

void MainWindow::viewRefresh() {
    boardModel->clear();
    for (int x = 0; x < board->getMaxX(); x++) {
        QList<QStandardItem *> items;
        for (int y = 0; y < board->getMaxY(); y++) {
            QStandardItem *item = new QStandardItem(tr("%1").arg(board->valueAt(x, y)));
            items.append(item);
        }
        boardModel->appendColumn(items);
    }
    for (int i = 0; i < board->getMaxX(); i++) {
        boardView->setColumnWidth(i, 40);
    }
    for (int i = 0; i < board->getMaxY(); i++) {
        boardView->setRowHeight(i, 40);
    }
}

void MainWindow::geometryRefresh() {
    btnRestart->setStyleSheet(ssRestart);
    setFixedHeight(40 * board->getMaxY() + 120);
    setFixedWidth(40 * board->getMaxX() + 20);
    boardView->setFixedSize(QSize(40 * board->getMaxX() + 2, 40 * board->getMaxY() + 2));
    this->move(QApplication::desktop()->width() / 2 - this->width() / 2, QApplication::desktop()->height() / 2 - this->height() / 2);
}

void MainWindow::leftClick(const QModelIndex &index) {
    int x = index.column();
    int y = index.row();
    int statusPrevious = board->getGameStatus();
    board->dig(x, y);
    viewRefresh();
    countLeftClick++;
    if (statusPrevious == 0 && board->getGameStatus() == 1) {
        timer->start(1000);
        timeBegin = QTime::currentTime();
    }
    if (statusPrevious != 2 && board->getGameStatus() == 2) {
        btnRestart->setStyleSheet(ssWin);
        timer->stop();
        timeUsedInMsec = timeBegin.msecsTo(QTime::currentTime());
        DialogWin *dialogWin = new DialogWin(countLeftClick, countRightClick, countDoubleClick, timeUsedInMsec, 0);
        dialogWin->exec();
        delete dialogWin;
    }
    if (statusPrevious != 3 && board->getGameStatus() == 3) {
        btnRestart->setStyleSheet(ssLose);
        timer->stop();
        timeUsedInMsec = timeBegin.msecsTo(QTime::currentTime());
        DialogLose *dialogLose = new DialogLose(countLeftClick, countRightClick, countDoubleClick, timeUsedInMsec, 0);
        int dialogResult = dialogLose->exec();
        if (dialogResult == QDialog::Accepted) {
            newGame(true);
        }
        delete dialogLose;
    }
}

void MainWindow::rightClick(const QModelIndex &index) {
    int x = index.column();
    int y = index.row();
    board->setFlag(x, y);
    viewRefresh();
    countRightClick++;
    lcdMineLeft->display(board->getMineLeft());
}

void MainWindow::doubleClick(const QModelIndex &index) {
//    qDebug() << "double " << index.column() << " " << index.row();
    int x = index.column();
    int y = index.row();
    int statusPrevious = board->getGameStatus();
    board->doubleClick(x, y);
    viewRefresh();
    countDoubleClick++;
    if (statusPrevious != 2 && board->getGameStatus() == 2) {
        btnRestart->setStyleSheet(ssWin);
        timer->stop();
        timeUsedInMsec = timeBegin.msecsTo(QTime::currentTime());
        DialogWin *dialogWin = new DialogWin(countLeftClick, countRightClick, countDoubleClick, timeUsedInMsec, 0);
        dialogWin->exec();
        delete dialogWin;
    }
    if (statusPrevious != 3 && board->getGameStatus() == 3) {
        btnRestart->setStyleSheet(ssLose);
        timer->stop();
        timeUsedInMsec = timeBegin.msecsTo(QTime::currentTime());
        DialogLose *dialogLose = new DialogLose(countLeftClick, countRightClick, countDoubleClick, timeUsedInMsec, 0);
        int dialogResult = dialogLose->exec();
        if (dialogResult == QDialog::Accepted) {
            newGame(true);
        }
        delete dialogLose;
    }
}

void MainWindow::leftRightClick(const QModelIndex &index) {
//    qDebug() << "left right " << index.column() << " " << index.row();
    doubleClick(index);
}

void MainWindow::timeIncrease() {
    timeUsed++;
    lcdTimer->display(timeUsed);
}

void MainWindow::newGame(bool noChange) {
    board->newGame(noChange);
    viewRefresh();
    timer->stop();
    timeUsed = 0;
    timeUsedInMsec = 0;
    if (noChange) {
        timeBegin = QTime::currentTime();
        timer->start(1000);
    }
    countLeftClick = 0;
    countRightClick = 0;
    countDoubleClick = 0;
    lcdTimer->display(timeUsed);
    lcdMineLeft->display(board->getMineLeft());
    btnRestart->setStyleSheet(ssRestart);
}
