#include "code.h"

Code::Code(QString color1,QString color2,QString color3,QString color4)
{
    CodeColors.append(color1);
    CodeColors.append(color2);
    CodeColors.append(color3);
    CodeColors.append(color4);
}

QString Code::ToQString()
{
    QString colors;

    for (int i = 0; i < CodeColors.count(); i++)
    {
        if (i == CodeColors.count() - 1)
        {
            colors += CodeColors[i];
        }
        else
        {
            colors += CodeColors[i] + " ";
        }
    }

    return colors;
}

Response Code::Compare(Code *secret)
{
    int correctColorCount = 0;
    int correctSpotCount = 0;

    // why tho?
    // bool codeUsed[CodeColors.count()] = {false, false, false, false};
    // bool guessUsed[secret->CodeColors.count()] = {false, false, false, false};
    bool codeUsed[4] = {false, false, false, false};
    bool guessUsed[4] = {false, false, false, false};

    for (int index = 0; index < secret->CodeColors.count(); index++)
    {
        if (CodeColors[index].toLower() == secret->CodeColors[index].toLower())
        {
            correctSpotCount += 1;
            codeUsed[index] = true;
            guessUsed[index] = true;
        }
    }

    for (int codeIndex = 0; codeIndex < secret->CodeColors.count(); codeIndex++)
    {
        for (int guessIndex = 0; guessIndex < CodeColors.count(); guessIndex++)
        {
            if (!codeUsed[codeIndex] && !guessUsed[guessIndex] &&
                    secret->CodeColors[codeIndex].toLower() == CodeColors[guessIndex].toLower())
            {
                correctColorCount += 1;
                codeUsed[codeIndex] = true;
                guessUsed[guessIndex] = true;
                break;
            }
        }
    }

    QString correctSpotCountString = QString::number(correctSpotCount);
    QString correctColorCountString = QString::number(correctColorCount);

    QStringList lamps;

    if (correctColorCount + correctSpotCount <= 4)
    {
        for (int spotIndex = 0; spotIndex < correctSpotCount; spotIndex++)
        {
            lamps.append("2");
        }

        for (int colorIndex = 0; colorIndex < correctColorCount; colorIndex++)
        {
            lamps.append("1");
        }

        if (lamps.count() != 4)
        {
            while (lamps.count() < 4)
            {
                lamps.append("0");
            }
        }
    }
    else
    {
        qDebug() << "CorrectColorCount + CorrectSpotCount is greater than 4";
    }

    if (correctSpotCount == 4)
    {
        return Response(true,
                        lamps,
                        QString("<span style='font-style:bold'>Korrekt</span>, du gissade rätt!"));
    }
    else
    {
        if (correctSpotCount == 0)
        {
            if (correctColorCount == 0)
            {
                return Response(false,
                                lamps,
                                QString("<span style='font-style:bold'>Inga</span> färger är av rätt färg eller sitter på rätt plats."));
            }
            else
            {
                return Response(false,
                                lamps,
                                QString("<span style='font-style:bold'>" + correctColorCountString +
                               "</span> är av rätt färg, men fel plats."));
            }
        }
        else
        {
            return Response(false,
                            lamps,
                            QString("<span style='font-style:bold'>" + correctSpotCountString +
                           "</span> färger satt på rätt plats och " +
                           "<span style='font-style:bold'>" +
                           correctColorCountString + "</span> är av rätt färg."));
        }
    }

}
