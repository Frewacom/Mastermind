#ifndef MMCONNECTION_H
#define MMCONNECTION_H

#include "packet.h"

#include <QObject>
#include <QTcpSocket>
#include <QNetworkInterface>

enum Headers
{
    PlayersReady = 0,
    SetCode = 1,
    SetNickname = 2,
    Attempt = 3,
    ChatMessage = 4,
    PlayerWon = 5,
    ConnectionDenied = 6
};

class MMConnection : public QObject
{
    Q_OBJECT
public:
    explicit MMConnection(QObject *parent = nullptr);

    QTcpSocket *Socket = nullptr;
    int DefaultListenPort = 1337;
    bool hasConnection = false;

    void WriteChat(QString data);
    void WriteToNetwork(Headers header, QString data = "");
    void PlayerSelectCode();

signals:
    void connectionEstablished();
    void recievedPlayersReady(QString data);
    void recievedChatMessage(QString msg);
    void recievedAttempt(QString data);
    void recievedCode(QString data);
    void recievedPlayerWon(QString data);
    void recievedConnectionDenied();
    void selectCode();
    void userDisconnected();
    void youDisconnected();
    void wroteToChat(QString msg);
    void errorHandle(QString error);

public slots:
    void connected();
    void readyRead();
    void disconnected();
    void error(QAbstractSocket::SocketError socketError);

protected:
    void connectSocketObject(QTcpSocket *socket);

};

#endif // MMCONNECTION_H
