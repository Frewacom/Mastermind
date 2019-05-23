#include "response.h"

Response::Response(bool success, QStringList lamps, QString msg)
{
    Success = success;
    Lamps = lamps;
    Message = msg;
}

QString Response::ToQString()
{
    QString lamps;

    for (int i = 0; i < Lamps.count(); i++)
    {
        if (i == Lamps.count() - 1)
        {
            lamps += Lamps[i];
        }
        else
        {
            lamps += Lamps[i] + " ";
        }
    }

    return lamps;
}
