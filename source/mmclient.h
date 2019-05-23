#ifndef MMCLIENT_H
#define MMCLIENT_H

#include "packet.h"
#include "mmconnection.h"

#include <QObject>
#include <QHostAddress>

class MMClient : public MMConnection
{
    Q_OBJECT
public:
    explicit MMClient(QWidget *parent = 0);
    ~MMClient();

    void Connect(QString host, int port);
    void Disconnect();
    void DeleteSocket();

signals:
    void establishedConnection();

public slots:
};

#endif // MMCLIENT_H
