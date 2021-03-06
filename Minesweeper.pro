#-------------------------------------------------
#
# Project created by QtCreator 2017-09-28T02:40:23
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Minesweeper
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    boarddelegate.cpp \
    board.cpp \
    dialogwin.cpp \
    dialoglose.cpp \
    dialogstatistic.cpp \
    statisticdata.cpp \
    openingmenu.cpp \
    replay.cpp \
    base64.cpp \
    dialoghelp.cpp

HEADERS  += mainwindow.h \
    boarddelegate.h \
    board.h \
    dialogwin.h \
    dialoglose.h \
    dialogstatistic.h \
    statisticdata.h \
    openingmenu.h \
    replay.h \
    base64.h \
    dialoghelp.h

DISTFILES +=

RESOURCES += \
    resource.qrc

