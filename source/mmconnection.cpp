#include "mmconnection.h"

MMConnection::MMConnection(QObject *parent) : QObject(parent)
{

}

// Helpers
void MMConnection::connectSocketObject(QTcpSocket *socket)
{
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    //connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(error(QAbstractSocket::SocketError)));
}

// Functions
void MMConnection::WriteChat(QString msg)
{
    if (Socket != nullptr && !msg.isEmpty())
    {
        QString packet = QString::number(Headers::ChatMessage) + msg;
        Socket->write(packet.toUtf8());
        Socket->flush();

        emit wroteToChat(msg);
    }
}

void MMConnection::WriteToNetwork(Headers header, QString data)
{
    if (Socket != nullptr)
    {
        QString packet = QString::number(header) + data;
        Socket->write(packet.toUtf8());
        Socket->flush();
        Socket->waitForBytesWritten();
    }
}

// SLOTS
void MMConnection::connected()
{
    hasConnection = true;
    emit connectionEstablished();
}

void MMConnection::readyRead()
{
    QByteArray arr = Socket->readAll();
    QString buffer = arr.data();

    QStringRef type(&buffer, 0, 1);
    int typeInt = type.toInt();
    qDebug() << "Recieved header: " << typeInt;

    buffer.remove(0,1);
    QString data = buffer;

    if (typeInt == Headers::PlayersReady)
    {
        emit recievedPlayersReady(data);
    }
    else if (typeInt == Headers::SetCode)
    {
        emit recievedCode(data);
    }
    else if (typeInt == Headers::SetNickname)
    {
        //emit recievedOpponentName(data);
    }
    else if (typeInt == Headers::Attempt)
    {
        emit recievedAttempt(data);
    }
    else if (typeInt == Headers::ChatMessage)
    {
        emit recievedChatMessage(data);
    }
    else if (typeInt == Headers::PlayerWon)
    {
        emit recievedPlayerWon(data);
    }
    else if (typeInt == Headers::ConnectionDenied)
    {
        emit recievedConnectionDenied();
    }
}

void MMConnection::disconnected()
{
    Socket->deleteLater();
    Socket = nullptr;

    hasConnection = false;
    emit userDisconnected();
}

void MMConnection::error(QAbstractSocket::SocketError socketError)
{
    if (Socket != nullptr)
    {
        switch (socketError)
        {
            case QAbstractSocket::HostNotFoundError:
                emit errorHandle(QString("IP-addressen du angav kunde inte hittas."));
                break;

            case QAbstractSocket::ConnectionRefusedError:
                emit errorHandle(QString("Anslutningen nekades, är du säker på att du skrev in rätt IP?"));
                break;

            case QAbstractSocket::RemoteHostClosedError:
                disconnected();
                break;

            case QAbstractSocket::SocketTimeoutError:
                emit errorHandle(QString("Motspelaren svarade inte. Avbröt anslutingen"));
                break;

//            case QAbstractSocket::NetworkError:
//                emit errorHandle(QString("Nätverksfel.."));
//                break;
        }
    }
}

