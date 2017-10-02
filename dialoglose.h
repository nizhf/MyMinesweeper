#ifndef DIALOGLOSE_H
#define DIALOGLOSE_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>

class DialogLose : public QDialog
{
    Q_OBJECT
public:
    explicit DialogLose();
    DialogLose(int left, int right, int doubleClick, int timeInMsec, int mousePath);
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
    QPushButton *btnRestart;

signals:

public slots:
};

#endif // DIALOGLOSE_H