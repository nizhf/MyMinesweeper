#ifndef DIALOGWIN_H
#define DIALOGWIN_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>

class DialogWin : public QDialog
{
    Q_OBJECT
public:
    DialogWin();
    DialogWin(int left, int right, int doubleClick, int timeInMsec, int mousePath);
    void initData();
    void initLayout();

private:
    int countLeftClick;
    int countRightClick;
    int countDoubleClick;
    int timeInMsec;
    int mousePath;

    QGridLayout *layoutDialog;
    QLabel *labelLeftClick;
    QLabel *labelRightClick;
    QLabel *labelDoubleClick;
    QLabel *labelTime;
    QLabel *labelMousePath;
    QPushButton *btnOk;

};

#endif // DIALOGWIN_H