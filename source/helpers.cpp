#include "helpers.h"

void Helpers::ApplyStyleSheet(QWidget *centralWidget)
{
    // Ladda stylesheet
    QFile file(":/style.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    centralWidget->setStyleSheet(styleSheet);
}

void Helpers::ApplyMaterialShadow(QWidget *widget, bool down, QColor color)
{
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;

    if (down)
    {
        effect->setBlurRadius(15);
        effect->setXOffset(0);
        effect->setYOffset(-1);
    }
    else
    {
        effect->setBlurRadius(25);
        effect->setXOffset(0);
        effect->setYOffset(2);
    }

    effect->setColor(color);

    widget->setGraphicsEffect(effect);
}

void Helpers::ApplyColorBoxMaterialShadow(QWidget *widget)
{
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(20);
    effect->setXOffset(3);
    effect->setYOffset(3);
    effect->setColor(QColor::fromRgb(5,5,5));

    widget->setGraphicsEffect(effect);
}

void Helpers::ApplyElementMaterialShadow(QWidget *widget)
{
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(5);
    effect->setXOffset(1);
    effect->setYOffset(1);
    effect->setColor(QColor::fromRgb(15,15,15));

    widget->setGraphicsEffect(effect);
}
