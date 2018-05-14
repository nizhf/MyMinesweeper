#ifndef OPENINGMENU_H
#define OPENINGMENU_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include "mainwindow.h"
#include "dialoghelp.h"

class OpeningMenu : public QDialog
{
    Q_OBJECT
public:
    OpeningMenu();


private:
    QGridLayout *layoutMain;
    QLabel *labelTitle;
    QPushButton *btnStart;
    QPushButton *btnReplay;
    QPushButton *btnHelp;
    QPushButton *btnExit;

    MainWindow *m_play;
    MainWindow *m_replay;



};

#endif // OPENINGMENU_H