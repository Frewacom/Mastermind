#ifndef CODE_H
#define CODE_H

#include "response.h"

#include <QString>
#include <QStringList>
#include <QDebug>

class Code
{
public:
    Code(QString color1,
         QString color2,
         QString color3,
         QString color4);

    QStringList CodeColors;

    QString ToQString();
    Response Compare(Code *secret);
};

#endif // CODE_H
