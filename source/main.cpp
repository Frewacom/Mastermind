#include "lobby.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    Lobby lobby;
    lobby.show();

    return a.exec();
}
