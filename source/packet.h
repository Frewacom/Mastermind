#ifndef PACKET_H
#define PACKET_H

#include <QString>
#include <QIODevice>
#include <QDebug>
#include <QDataStream>

struct PacketStruct
{
    // Fyra typer: Ny kod, försök, chatt-meddelande, spelare vann
    int type;
    // Här bör vi också ha med size
    QString data;
};

class Packet
{
public:
    Packet(QString type, QString data);

    PacketStruct *Data = new PacketStruct();

    QString Serialize();
};

#endif // PACKET_H
