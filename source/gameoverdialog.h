#ifndef GAMEOVERDIALOG_H
#define GAMEOVERDIALOG_H

#include "code.h"
#include "helpers.h"

#include <QDialog>
#include <QFile>
#include <QFrame>

namespace Ui {
class GameOverDialog;
}

class GameOverDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GameOverDialog(Code *secret, QWidget *parent = 0);
    ~GameOverDialog();

private:
    Ui::GameOverDialog *ui;

    void setColorBoxStylesheet(QFrame *box, QString color);
};

#endif // GAMEOVERDIALOG_H
