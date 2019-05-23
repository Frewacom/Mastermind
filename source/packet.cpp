#include "packet.h"

Packet::Packet(QString type, QString data)
{
    Data->data = data;

    if (type.toLower() == "chat")
    {
        Data->type = 3;
    }
    else if (type.toLower() == "attempt")
    {
        Data->type = 2;
    }
    else if (type.toLower() == "code")
    {
        Data->type = 1;
    }
    else
    {
        qDebug() << "Incorrect Packet type";
    }
}

QString Packet::Serialize()
{
    QString type = QString::number(Data->type);
    qDebug() << type + Data->data;
    return type + Data->data;
}
