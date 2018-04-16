#include "dialoglose.h"

DialogLose::DialogLose() :
    countLeftClick(0), countRightClick(0), countDoubleClick(0), timeInMsec(0), mousePath(0)
{
    this->setWindowTitle("You Lose!");
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    this->setMinimumWidth(250);
    initLayout();
    initData();
}

DialogLose::DialogLose(int left, int right, int doubleClick, int timeInMsec, int mousePath) :
    countLeftClick(left), countRightClick(right), countDoubleClick(doubleClick), timeInMsec(timeInMsec), mousePath(mousePath)
{
    this->setWindowTitle("You Lose!");
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    this->setMinimumWidth(250);
    initLayout();
    initData();
}

void DialogLose::initData() {
    labelLeftClick->setText(tr("Left click: %1").arg(countLeftClick));
    labelRightClick->setText(tr("Right click: %1").arg(countRightClick));
    labelDoubleClick->setText(tr("Double click: %1").arg(countDoubleClick));
    int msec = timeInMsec % 1000;
    int secTemp = timeInMsec / 1000;
    int sec = secTemp % 60;
    int minTemp = secTemp / 60;
    int min = minTemp % 60;
    int hour = min / 60;
    labelTime->setText(tr("Time: %1:%2:%3.%4").arg(hour).arg(min).arg(sec).arg(msec));
}

void DialogLose::initLayout() {
    layoutDialog = new QGridLayout;
    this->setLayout(layoutDialog);
    labelLeftClick = new QLabel(this);
    labelRightClick = new QLabel(this);
    labelDoubleClick = new QLabel(this);
    labelTime = new QLabel(this);
    btnOk = new QPushButton(tr("OK"));
    btnRestart = new QPushButton(tr("Restart"));
    connect(btnOk, &QPushButton::clicked, this, &DialogLose::reject);
    connect(btnRestart, &QPushButton::clicked, this, &DialogLose::accept);
    layoutDialog->addWidget(labelLeftClick, 0, 0, 1, 4);
    layoutDialog->addWidget(labelRightClick, 1, 0, 1, 4);
    layoutDialog->addWidget(labelDoubleClick, 2, 0, 1, 4);
    layoutDialog->addWidget(labelTime, 3, 0, 1, 4);
    layoutDialog->addWidget(btnOk, 4, 2, 1, 1);
    layoutDialog->addWidget(btnRestart, 4, 3, 1, 1);
}
