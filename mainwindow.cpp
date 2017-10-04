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
    boardView->setFocusPolicy(Qt::NoFocus);
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
    difficulty = 1;
    board = new Board(difficulty);
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
    QAction *actionStatistic = menuStart->addAction("Statistics");
    menuStart->addSeparator();
    QAction *actionExit = menuStart->addAction("Exit");
    QAction *actionHelp = menuHelp->addAction("Help");

    timer = new QTimer(this);
    timeUsed = 0;
    countLeftClick = 0;
    countRightClick = 0;
    countDoubleClick = 0;
    mousePath = 0;
    statisticData = new StatisticData;
    initData();

    //signals and slots
    connect(timer, &QTimer::timeout, this, &MainWindow::timeIncrease);
    connect(actionStart, &QAction::triggered, this, &MainWindow::newGame);
    connect(actionEasy, &QAction::triggered, [=](){
        difficulty = 1;
        board->setDifficulty(difficulty);
        board->initBoard();
        geometryRefresh();
        newGame();
    });
    connect(actionNormal, &QAction::triggered, [=](){
        difficulty = 2;
        board->setDifficulty(difficulty);
        board->initBoard();
        geometryRefresh();
        newGame();
    });
    connect(actionHard, &QAction::triggered, [=](){
        difficulty = 3;
        board->setDifficulty(difficulty);
        board->initBoard();        
        geometryRefresh();
        newGame();
    });
    connect(actionStatistic, &QAction::triggered, [=](){
        DialogStatistic dialogStatistic(statisticData);
        int result = dialogStatistic.exec();
        if (result == QDialog::Accepted) {
            clearData();
        }
    });
    connect(actionExit, &QAction::triggered, this, &MainWindow::close);
    connect(actionHelp, &QAction::triggered, [=](){
        QDialog dialogHelp;
        dialogHelp.exec();
    });
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
        gameWin();
    }
    if (statusPrevious != 3 && board->getGameStatus() == 3) {
        gameLose();
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
    int x = index.column();
    int y = index.row();
    int statusPrevious = board->getGameStatus();
    board->doubleClick(x, y);
    viewRefresh();
    countDoubleClick++;
    if (statusPrevious != 2 && board->getGameStatus() == 2) {
        gameWin();
    }
    if (statusPrevious != 3 && board->getGameStatus() == 3) {
        gameLose();
    }
}

void MainWindow::leftRightClick(const QModelIndex &index) {
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

void MainWindow::initData() {
    QDomDocument doc;
    QDomText text;
    QDomElement elementDiff;
    QDomElement element;
    QDomElement minTime;
    QDomElement root;
    QDomProcessingInstruction instruction;
    QFile file("statistic.xml");
    if (!file.exists()) {
        QTextStream stream(&file);
        file.open(QIODevice::WriteOnly);

        instruction = doc.createProcessingInstruction(tr("xml"), tr("version = \'1.0\' encoding=\'UTF-8\'"));
        doc.appendChild(instruction);

        root = doc.createElement("Statistic");
        doc.appendChild(root);

        for (int i = 0; i < 3; i++) {
            switch (i) {
            case 0:
                elementDiff = doc.createElement("Easy");
                break;
            case 1:
                elementDiff = doc.createElement("Normal");
                break;
            case 2:
                elementDiff = doc.createElement("Hard");
                break;
            default:
                elementDiff = doc.createElement("Default");
                break;
            }
            element = doc.createElement("win");
            text = doc.createTextNode("0");
            element.appendChild(text);
            elementDiff.appendChild(element);
            element = doc.createElement("lose");
            text = doc.createTextNode("0");
            element.appendChild(text);
            elementDiff.appendChild(element);
            element = doc.createElement("total_time");
            text = doc.createTextNode("0");
            element.appendChild(text);
            elementDiff.appendChild(element);
            element = doc.createElement("win_streak");
            text = doc.createTextNode("0");
            element.appendChild(text);
            elementDiff.appendChild(element);
            element = doc.createElement("lose_streak");
            text = doc.createTextNode("0");
            element.appendChild(text);
            elementDiff.appendChild(element);
            element = doc.createElement("streak_now");
            text = doc.createTextNode("0");
            element.appendChild(text);
            elementDiff.appendChild(element);
            element = doc.createElement("streak_type");
            text = doc.createTextNode("lose");
            element.appendChild(text);
            elementDiff.appendChild(element);
            element = doc.createElement("NP");
            text = doc.createTextNode("0");
            element.appendChild(text);
            elementDiff.appendChild(element);

            for (int j = 0; j < 5; j++) {
                element = doc.createElement(tr("min_time_%1").arg(j));
                minTime = doc.createElement("time");
                text = doc.createTextNode("-1");
                minTime.appendChild(text);
                element.appendChild(minTime);
                minTime = doc.createElement("year");
                text = doc.createTextNode("-1");
                minTime.appendChild(text);
                element.appendChild(minTime);
                minTime = doc.createElement("month");
                text = doc.createTextNode("-1");
                minTime.appendChild(text);
                element.appendChild(minTime);
                minTime = doc.createElement("day");
                text = doc.createTextNode("-1");
                minTime.appendChild(text);
                element.appendChild(minTime);
                elementDiff.appendChild(element);
            }

            root.appendChild(elementDiff);
        }

        doc.save(stream, 4);
        file.close();
    }

    file.open(QIODevice::ReadOnly);
    doc.setContent(&file);
    file.close();
    root = doc.firstChildElement();
    for (int i = 0; i < 3; i++) {
        StatisticData::Difficulty diff;
        switch (i) {
        case 0:
            diff = StatisticData::Easy;
            elementDiff = root.firstChildElement("Easy");
            break;
        case 1:
            diff = StatisticData::Normal;
            elementDiff = root.firstChildElement("Normal");
            break;
        case 2:
            diff = StatisticData::Hard;
            elementDiff = root.firstChildElement("Hard");
            break;
        default:
            break;
        }

        statisticData->setWin(elementDiff.firstChildElement("win").text().toInt(), diff);
        statisticData->setLose(elementDiff.firstChildElement("lose").text().toInt(), diff);
        statisticData->setTotalTimeInMsec(elementDiff.firstChildElement("total_time").text().toInt(), diff);
        statisticData->setMaxWinningStreak(elementDiff.firstChildElement("win_streak").text().toInt(), diff);
        statisticData->setMaxLosingStreak(elementDiff.firstChildElement("lose_streak").text().toInt(), diff);
        statisticData->setStreakNow(elementDiff.firstChildElement("streak_now").text().toInt(), diff);
        if (elementDiff.firstChildElement("streak_type").text() == "win") {
            statisticData->setStreakWin(true, diff);
        }
        else {
            statisticData->setStreakWin(false, diff);
        }
        statisticData->setGameNP(elementDiff.firstChildElement("NP").text().toInt(), diff);

        for (int j = 0; j < 5; j++) {
            QDomElement gameElement = elementDiff.firstChildElement(tr("min_time_%1").arg(j));
            int gameTime = gameElement.firstChildElement(tr("time")).text().toInt();
            int gameYear = gameElement.firstChildElement(tr("year")).text().toInt();
            int gameMonth = gameElement.firstChildElement(tr("month")).text().toInt();
            int gameDay = gameElement.firstChildElement(tr("day")).text().toInt();
            if (gameTime != -1) {
                statisticData->addMinTimeGame(gameTime, gameDay, gameMonth, gameYear, diff);
            }
        }
    }
}

void MainWindow::statisticUpdate(int d) {
    QDomDocument doc;
    QDomElement root;
    QDomElement elementDiff;
    QDomElement element;
    QDomElement elementMinTime;
    QFile file("statistic.xml");
    QTextStream stream(&file);
    if (!file.exists()) initData();
    file.open(QIODevice::ReadOnly);
    doc.setContent(&file);
    file.close();

    file.open(QIODevice::WriteOnly);
    root = doc.firstChildElement();
    StatisticData::Difficulty diff;
    switch (d) {
    case 1:
        elementDiff = root.firstChildElement("Easy");
        diff = StatisticData::Easy;
        break;
    case 2:
        elementDiff = root.firstChildElement("Normal");
        diff = StatisticData::Normal;
        break;
    case 3:
        elementDiff = root.firstChildElement("Hard");
        diff = StatisticData::Hard;
        break;
    default:
        elementDiff = root.firstChildElement("Default");
        break;
    }
    element = elementDiff.firstChildElement("win");
    element.firstChild().setNodeValue(tr("%1").arg(statisticData->getWin(diff)));

    element = elementDiff.firstChildElement("lose");
    element.firstChild().setNodeValue(tr("%1").arg(statisticData->getLose(diff)));

    element = elementDiff.firstChildElement("total_time");
    element.firstChild().setNodeValue(tr("%1").arg(statisticData->getTotalTimeInMsec(diff)));

    element = elementDiff.firstChildElement("win_streak");
    element.firstChild().setNodeValue(tr("%1").arg(statisticData->getMaxWinningStreak(diff)));

    element = elementDiff.firstChildElement("lose_streak");
    element.firstChild().setNodeValue(tr("%1").arg(statisticData->getMaxLosingStreak(diff)));

    element = elementDiff.firstChildElement("streak_now");
    element.firstChild().setNodeValue(tr("%1").arg(statisticData->getStreakNow(diff)));

    element = elementDiff.firstChildElement("streak_type");
    if (statisticData->getStreakWin(diff)) {
        element.firstChild().setNodeValue(tr("win"));
    }
    else {
        element.firstChild().setNodeValue(tr("lose"));
    }

    element = elementDiff.firstChildElement("NP");
    element.firstChild().setNodeValue(tr("%1").arg(statisticData->getGameNP(diff)));

    for (int i = 0; i < 5; i++) {
        element = elementDiff.firstChildElement(tr("min_time_%1").arg(i));

        elementMinTime = element.firstChildElement("time");
        elementMinTime.firstChild().setNodeValue(tr("%1").arg(statisticData->getMinTimeInMsec(i, diff)));

        elementMinTime = element.firstChildElement("year");
        elementMinTime.firstChild().setNodeValue(tr("%1").arg(statisticData->getMinTimeYear(i, diff)));

        elementMinTime = element.firstChildElement("month");
        elementMinTime.firstChild().setNodeValue(tr("%1").arg(statisticData->getMinTimeMonth(i, diff)));

        elementMinTime = element.firstChildElement("day");
        elementMinTime.firstChild().setNodeValue(tr("%1").arg(statisticData->getMinTimeDay(i, diff)));
    }

    doc.save(stream, 4);
    file.close();
}

void MainWindow::gameWin() {
    btnRestart->setStyleSheet(ssWin);
    timer->stop();
    timeUsedInMsec = timeBegin.msecsTo(QTime::currentTime());
    QDate date = QDate::currentDate();

    DialogWin *dialogWin = new DialogWin(countLeftClick, countRightClick, countDoubleClick, timeUsedInMsec, 0);
    dialogWin->exec();
    delete dialogWin;

    switch (difficulty) {
    case 1:
        statisticData->setWin(statisticData->getWin(StatisticData::Easy) + 1, StatisticData::Easy);
        statisticData->setTotalTimeInMsec(statisticData->getTotalTimeInMsec(StatisticData::Easy) + timeUsedInMsec, StatisticData::Easy);
        if (statisticData->getStreakWin(StatisticData::Easy)) {
            statisticData->setStreakNow(statisticData->getStreakNow(StatisticData::Easy) + 1, StatisticData::Easy);
            if (statisticData->getStreakNow(StatisticData::Easy) > statisticData->getMaxWinningStreak(StatisticData::Easy)) {
                statisticData->setMaxWinningStreak(statisticData->getStreakNow(StatisticData::Easy), StatisticData::Easy);
            }
        }
        else {
            statisticData->setStreakWin(true, StatisticData::Easy);
            statisticData->setStreakNow(1, StatisticData::Easy);
            if (statisticData->getStreakNow(StatisticData::Easy) > statisticData->getMaxWinningStreak(StatisticData::Easy)) {
                statisticData->setMaxWinningStreak(statisticData->getStreakNow(StatisticData::Easy), StatisticData::Easy);
            }
        }
        if (countRightClick == 0) {
            statisticData->setGameNP(statisticData->getGameNP(StatisticData::Easy) + 1, StatisticData::Easy);
        }
        statisticData->addMinTimeGame(timeUsedInMsec, date.day(), date.month(), date.year(), StatisticData::Easy);
        break;
    case 2:
        statisticData->setWin(statisticData->getWin(StatisticData::Normal) + 1, StatisticData::Normal);
        statisticData->setTotalTimeInMsec(statisticData->getTotalTimeInMsec(StatisticData::Normal) + timeUsedInMsec, StatisticData::Normal);
        if (statisticData->getStreakWin(StatisticData::Normal)) {
            statisticData->setStreakNow(statisticData->getStreakNow(StatisticData::Normal) + 1, StatisticData::Normal);
            if (statisticData->getStreakNow(StatisticData::Normal) > statisticData->getMaxWinningStreak(StatisticData::Normal)) {
                statisticData->setMaxWinningStreak(statisticData->getStreakNow(StatisticData::Normal), StatisticData::Normal);
            }
        }
        else {
            statisticData->setStreakWin(true, StatisticData::Normal);
            statisticData->setStreakNow(1, StatisticData::Normal);
            if (statisticData->getStreakNow(StatisticData::Normal) > statisticData->getMaxWinningStreak(StatisticData::Normal)) {
                statisticData->setMaxWinningStreak(statisticData->getStreakNow(StatisticData::Normal), StatisticData::Normal);
            }
        }
        if (countRightClick == 0) {
            statisticData->setGameNP(statisticData->getGameNP(StatisticData::Normal) + 1, StatisticData::Normal);
        }
        statisticData->addMinTimeGame(timeUsedInMsec, date.day(), date.month(), date.year(), StatisticData::Normal);
        break;
    case 3:
        statisticData->setWin(statisticData->getWin(StatisticData::Hard) + 1, StatisticData::Hard);
        statisticData->setTotalTimeInMsec(statisticData->getTotalTimeInMsec(StatisticData::Hard) + timeUsedInMsec, StatisticData::Hard);
        if (statisticData->getStreakWin(StatisticData::Hard)) {
            statisticData->setStreakNow(statisticData->getStreakNow(StatisticData::Hard) + 1, StatisticData::Hard);
            if (statisticData->getStreakNow(StatisticData::Hard) > statisticData->getMaxWinningStreak(StatisticData::Hard)) {
                statisticData->setMaxWinningStreak(statisticData->getStreakNow(StatisticData::Hard), StatisticData::Hard);
            }
        }
        else {
            statisticData->setStreakWin(true, StatisticData::Hard);
            statisticData->setStreakNow(1, StatisticData::Hard);
            if (statisticData->getStreakNow(StatisticData::Hard) > statisticData->getMaxWinningStreak(StatisticData::Hard)) {
                statisticData->setMaxWinningStreak(statisticData->getStreakNow(StatisticData::Hard), StatisticData::Hard);
            }
        }
        if (countRightClick == 0) {
            statisticData->setGameNP(statisticData->getGameNP(StatisticData::Hard) + 1, StatisticData::Hard);
        }
        statisticData->addMinTimeGame(timeUsedInMsec, date.day(), date.month(), date.year(), StatisticData::Hard);
        break;
    default:
        break;
    }

    statisticUpdate(difficulty);
}

void MainWindow::gameLose() {
    btnRestart->setStyleSheet(ssLose);
    timer->stop();
    timeUsedInMsec = timeBegin.msecsTo(QTime::currentTime());

    DialogLose *dialogLose = new DialogLose(countLeftClick, countRightClick, countDoubleClick, timeUsedInMsec, 0);
    int dialogResult = dialogLose->exec();
    if (dialogResult == QDialog::Accepted) {
        newGame(true);
    }
    delete dialogLose;

    switch (difficulty) {
    case 1:
        statisticData->setLose(statisticData->getLose(StatisticData::Easy) + 1, StatisticData::Easy);
        statisticData->setTotalTimeInMsec(statisticData->getTotalTimeInMsec(StatisticData::Easy) + timeUsedInMsec, StatisticData::Easy);
        if (!statisticData->getStreakWin(StatisticData::Easy)) {
            statisticData->setStreakNow(statisticData->getStreakNow(StatisticData::Easy) + 1, StatisticData::Easy);
            if (statisticData->getStreakNow(StatisticData::Easy) > statisticData->getMaxLosingStreak(StatisticData::Easy)) {
                statisticData->setMaxLosingStreak(statisticData->getStreakNow(StatisticData::Easy), StatisticData::Easy);
            }
        }
        else {
            statisticData->setStreakWin(false, StatisticData::Easy);
            statisticData->setStreakNow(1, StatisticData::Easy);
            if (statisticData->getStreakNow(StatisticData::Easy) > statisticData->getMaxLosingStreak(StatisticData::Easy)) {
                statisticData->setMaxLosingStreak(statisticData->getStreakNow(StatisticData::Easy), StatisticData::Easy);
            }
        }
        break;
    case 2:
        statisticData->setLose(statisticData->getLose(StatisticData::Normal) + 1, StatisticData::Normal);
        statisticData->setTotalTimeInMsec(statisticData->getTotalTimeInMsec(StatisticData::Normal) + timeUsedInMsec, StatisticData::Normal);
        if (!statisticData->getStreakWin(StatisticData::Normal)) {
            statisticData->setStreakNow(statisticData->getStreakNow(StatisticData::Normal) + 1, StatisticData::Normal);
            if (statisticData->getStreakNow(StatisticData::Normal) > statisticData->getMaxLosingStreak(StatisticData::Normal)) {
                statisticData->setMaxLosingStreak(statisticData->getStreakNow(StatisticData::Normal), StatisticData::Normal);
            }
        }
        else {
            statisticData->setStreakWin(false, StatisticData::Normal);
            statisticData->setStreakNow(1, StatisticData::Normal);
            if (statisticData->getStreakNow(StatisticData::Normal) > statisticData->getMaxLosingStreak(StatisticData::Normal)) {
                statisticData->setMaxLosingStreak(statisticData->getStreakNow(StatisticData::Normal), StatisticData::Normal);
            }
        }
        break;
    case 3:
        statisticData->setLose(statisticData->getLose(StatisticData::Hard) + 1, StatisticData::Hard);
        statisticData->setTotalTimeInMsec(statisticData->getTotalTimeInMsec(StatisticData::Hard) + timeUsedInMsec, StatisticData::Hard);
        if (!statisticData->getStreakWin(StatisticData::Hard)) {
            statisticData->setStreakNow(statisticData->getStreakNow(StatisticData::Hard) + 1, StatisticData::Hard);
            if (statisticData->getStreakNow(StatisticData::Hard) > statisticData->getMaxLosingStreak(StatisticData::Hard)) {
                statisticData->setMaxLosingStreak(statisticData->getStreakNow(StatisticData::Hard), StatisticData::Hard);
            }
        }
        else {
            statisticData->setStreakWin(false, StatisticData::Hard);
            statisticData->setStreakNow(1, StatisticData::Hard);
            if (statisticData->getStreakNow(StatisticData::Hard) > statisticData->getMaxLosingStreak(StatisticData::Hard)) {
                statisticData->setMaxLosingStreak(statisticData->getStreakNow(StatisticData::Hard), StatisticData::Hard);
            }
        }
        break;
    default:
        break;
    }

    statisticUpdate(difficulty);
}

void MainWindow::clearData() {
    statisticData->clear(StatisticData::Easy);
    statisticData->clear(StatisticData::Normal);
    statisticData->clear(StatisticData::Hard);
    statisticUpdate(1);
    statisticUpdate(2);
    statisticUpdate(3);
}
