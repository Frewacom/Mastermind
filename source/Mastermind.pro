#-------------------------------------------------
#
# Project created by QtCreator 2017-09-11T12:13:34
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Mastermind
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    code.cpp \
    response.cpp \
    highscoredialog.cpp \
    lobby.cpp \
    gameoverdialog.cpp \
    mmserver.cpp \
    packet.cpp \
    serverconnectiondialog.cpp \
    helpers.cpp \
    mmconnection.cpp \
    mmclient.cpp \
    customtextdialog.cpp \
    serverhostnameselectdialog.cpp

HEADERS += \
        mainwindow.h \
    code.h \
    response.h \
    highscoredialog.h \
    lobby.h \
    gameoverdialog.h \
    mmserver.h \
    packet.h \
    serverconnectiondialog.h \
    helpers.h \
    mmconnection.h \
    mmclient.h \
    customtextdialog.h \
    serverhostnameselectdialog.h

FORMS += \
        mainwindow.ui \
    highscoredialog.ui \
    lobby.ui \
    gameoverdialog.ui \
    serverconnectiondialog.ui \
    customtextdialog.ui \
    serverhostnameselectdialog.ui

RESOURCES += \
    resources.qrc
