#ifndef SERVERCONNECTIONDIALOG_H
#define SERVERCONNECTIONDIALOG_H

#include "helpers.h"
#include <QDialog>

namespace Ui {
class ServerConnectionDialog;
}

class ServerConnectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ServerConnectionDialog(QWidget *parent = 0);
    ~ServerConnectionDialog();

signals:
    void IPInputFinished(QString ip);
    void IPInputDismissed();

public slots:
    void accepted();
    void rejected();

private:
    Ui::ServerConnectionDialog *ui;
};

#endif // SERVERCONNECTIONDIALOG_H
