#ifndef HELPERS_H
#define HELPERS_H

#include <QMainWindow>
#include <QDialog>
#include <QFile>
#include <QGraphicsDropShadowEffect>
#include <QColor>

namespace Helpers
{
    void ApplyStyleSheet(QWidget *centralWidget);
    void ApplyMaterialShadow(QWidget *widget,
                             bool down = false,
                             QColor color = QColor::fromRgb(20,20,20));
    void ApplyElementMaterialShadow(QWidget *widget);
    void ApplyColorBoxMaterialShadow(QWidget *widget);
}

#endif // HELPERS_H
