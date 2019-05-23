#ifndef LOBBY_H
#define LOBBY_H

#include "code.h"
#include "helpers.h"
#include "mmserver.h"
#include "mmclient.h"
#include "mainwindow.h"
#include "serverconnectiondialog.h"
#include "serverhostnameselectdialog.h"

#include <QApplication>
#include <QMainWindow>
#include <QFile>
#include <QDebug>
#include <QTime>
#include <QCoreApplication>

namespace Ui {
class Lobby;
}

class Lobby : public QMainWindow
{
    Q_OBJECT

public:
    explicit Lobby(QWidget *parent = 0);
    ~Lobby();

    MainWindow *GameWindow;

    MMServer *Server;
    MMClient *Client;

    bool IsInGame = false;

private slots:
    void gameFinished();

    void on_PlayOffline_clicked();
    void on_CreateServer_clicked();
    void on_ConnectToServer_clicked();
    void on_InputSend_clicked();
    void on_ClearOutputButton_clicked();

    void connectionEstablished();
    void userConnected();
    void maximumConnectionsReached();
    void recievedPlayersReady(QString data);
    void recievedChatMessage(QString msg);
    void recievedAttempt(QString data);
    void recievedCode(QString data);
    void recievedPlayerWon(QString data);
    void recievedConnectionDenied();
    void userDisconnected();
    void youDisconnected();
    void wroteToChat(QString msg);

    void selectCode();
    void codeSet(Code *code);
    void attemptMade(Code *code, Response resp);
    void playerFoundCode();

    void errorHandle(QString msg);

    void IPAccepted(QString ip);
    void IPDenied();
    void hostnameSelected(QString ip);

private:
    Ui::Lobby *ui;

    QString youPrefix = withColor(toBold("Du: "), "#c43336");
    QString otherPrefix = withColor(toBold("Motspelare: "), "#db0006");

    void newGameWindow(bool online);
    void startGameWindow(bool online);
    void startNewMatch();

    void serverShouldMakeCode();
    void clientShouldMakeCode();

    QStringList packetParser(QString data);

    void connectConnectionObject(MMConnection *conn);
    void connectServerObject(MMServer *server);
    void connectWindowObject(MainWindow *obj);
    void connectServerConnectDialog(ServerConnectionDialog *dialog);
    void connectHostnameChooseDialog(ServerHostnameSelectDialog *dialog);
    void write(QString msg);
    void writeSeparator();

    void delay(int n);
    uint generateSeed();

    QString toBold(QString string);
    QString withColor(QString string, QString color);

    bool isClient = false;
    bool isConnected = false;
    bool opponentWantsRematch = false;
    bool youWantRematch = false;
};

#endif // LOBBY_H
