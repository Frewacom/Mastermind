#ifndef RESPONSE_H
#define RESPONSE_H

#include <QString>
#include <QStringList>

class Response
{
public:
    Response(bool success,
             QStringList lamps,
             QString msg);

    bool Success;
    QStringList Lamps;
    QString Message;

    QString ToQString();
};

#endif // RESPONSE_H
