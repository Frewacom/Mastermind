#include "mmserver.h"

MMServer::MMServer(QWidget *parent)
{
    ServerObject = new QTcpServer();
    connect(ServerObject, SIGNAL(newConnection()), this, SLOT(newConnection()));
}

// Public
bool MMServer::Start(QString ip)
{
    if (ServerObject->listen(QHostAddress(ip), DefaultListenPort))
    {
        CurrentHost = ServerObject->serverAddress();
        CurrentPort = ServerObject->serverPort();

        isRunning = true;
        return true;
    }
    else
    {
        return false;
    }
}

void MMServer::Stop()
{
    ServerObject->close();
    if (Socket != nullptr)
    {
        Socket->close();
        Socket = nullptr;
    }
    isRunning = false;
}

// Helpers
void MMServer::PopulateHostnameComboBox(QComboBox *box)
{
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses())
    {
        if (address.protocol() == QAbstractSocket::IPv4Protocol &&
                address != QHostAddress::LocalHost)
        {
            QString addrString = address.toString();
            box->addItem(addrString);
        }
    }
}

int MMServer::RollFirstPlayerToGuess(uint seed)
{
    int min = 0;
    int max = 1;

    return ((qrand() % ((max + 1) - min)) + min);
}

// SIGNALS and SLOTS
void MMServer::newConnection()
{
    if (Socket == nullptr)
    {
        if (ServerObject->hasPendingConnections())
        {
            Socket = ServerObject->nextPendingConnection();
            connectSocketObject(Socket);

            hasConnection = true;
            emit userConnected();
        }
    }
    else
    {
        WriteToNetwork(Headers::ConnectionDenied);
        emit maximumConnectionsReached();
    }
}

MMServer::~MMServer()
{

}


