#ifndef DIALOGHELP_H
#define DIALOGHELP_H

#include <QDialog>
#include <QLabel>
#include <QTextBrowser>
#include <QFile>
#include <string>
#include <QGridLayout>

class DialogHelp : public QDialog
{
public:
    DialogHelp();

private:
    QTextBrowser *tb;
    QGridLayout *layoutHelp;
};

#endif // DIALOGHELP_H