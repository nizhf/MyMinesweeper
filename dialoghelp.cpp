#include "dialoghelp.h"

DialogHelp::DialogHelp()
{
    layoutHelp = new QGridLayout;
    this->setLayout(layoutHelp);

    tb = new QTextBrowser;
    QFile helpFile(":/text/text/help.txt");
//    std::ifstream helpFile;
//    helpFile.open(":/text/text/help.txt");
//    std::string helpText;
//    helpFile >> helpText;
    helpFile.open(QFile::ReadOnly);
    tb->setText(QString(helpFile.readAll()));
    helpFile.close();
    layoutHelp->addWidget(tb, 0, 0, 1, 1);
}
