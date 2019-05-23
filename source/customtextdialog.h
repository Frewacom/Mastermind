#ifndef CUSTOMTEXTDIALOG_H
#define CUSTOMTEXTDIALOG_H

#include "helpers.h"

#include <QDialog>

namespace Ui {
class CustomTextDialog;
}

class CustomTextDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CustomTextDialog(QString text, QWidget *parent = 0);
    ~CustomTextDialog();

private:
    Ui::CustomTextDialog *ui;
};

#endif // CUSTOMTEXTDIALOG_H
