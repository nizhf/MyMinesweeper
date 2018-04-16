#include "openingmenu.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OpeningMenu menu;
    menu.show();
    return a.exec();
}
