#include "openingmenu.h"

OpeningMenu::OpeningMenu()
{
    setFixedHeight(600);
    setFixedWidth(300);

    m_play = new MainWindow();
    m_play->setPlayMode(true);
    m_replay = new MainWindow();
    m_replay->setPlayMode(false);
    m_replay->menuBar()->hide();

    labelTitle = new QLabel("Minesweeper");
    btnStart = new QPushButton("Start");
    btnReplay = new QPushButton("Replay");
    btnHelp = new QPushButton("Help");
    btnExit = new QPushButton("Exit");

    layoutMain = new QGridLayout;
    layoutMain->addWidget(labelTitle, 0, 0, 1, 3, Qt::AlignHCenter);
    layoutMain->addWidget(btnStart, 1, 1, 1, 1, Qt::AlignHCenter);
    layoutMain->addWidget(btnReplay, 2, 1, 1, 1, Qt::AlignHCenter);
    layoutMain->addWidget(btnHelp, 3, 1, 1, 1, Qt::AlignHCenter);
    layoutMain->addWidget(btnExit, 4, 1, 1, 1, Qt::AlignHCenter);
    this->setLayout(layoutMain);



    connect(btnStart, &QPushButton::clicked, m_play, &MainWindow::show);
    connect(btnReplay, &QPushButton::clicked, m_replay, &MainWindow::show);
    connect(btnExit, &QPushButton::clicked, this, &OpeningMenu::close);
}
