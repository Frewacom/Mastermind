#include "mmclient.h"

MMClient::MMClient(QWidget *parent)
{
    Socket = new QTcpSocket();
}

void MMClient::Connect(QString host, int port)
{
    QHostAddress addr(host);
    Socket->connectToHost(addr, port);
    connectSocketObject(Socket);
}

void MMClient::Disconnect()
{
    DeleteSocket();

    emit youDisconnected();
}

void MMClient::DeleteSocket()
{
    if (Socket != nullptr)
    {
        Socket->close();
        Socket->deleteLater();
    }
}

MMClient::~MMClient()
{

}
