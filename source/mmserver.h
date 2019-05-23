#ifndef MMSERVER_H
#define MMSERVER_H

#include "packet.h"
#include "mmconnection.h"

#include <QComboBox>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>

class MMServer : public MMConnection
{
    Q_OBJECT
public:
    explicit MMServer(QWidget *parent = 0);
    ~MMServer();

    QTcpServer *ServerObject;

    QHostAddress DefaultHost = QHostAddress::LocalHost;
    QHostAddress CurrentHost;
    int CurrentPort;

    bool isRunning = false;
    bool ServerMadeLastCode = NULL;

    bool Start(QString ip);
    void Stop();

    void PopulateHostnameComboBox(QComboBox *box);
    int RollFirstPlayerToGuess(uint seed);

signals:
    void userConnected();
    void maximumConnectionsReached();

public slots:
    void newConnection();

};

#endif // MMSERVER_H
