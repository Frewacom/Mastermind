#ifndef SERVERHOSTNAMESELECTDIALOG_H
#define SERVERHOSTNAMESELECTDIALOG_H

#include "helpers.h"

#include <QDialog>
#include <QComboBox>

namespace Ui {
class ServerHostnameSelectDialog;
}

class ServerHostnameSelectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ServerHostnameSelectDialog(QWidget *parent = 0);
    ~ServerHostnameSelectDialog();

    QComboBox* GetComboBox();

private slots:
    void accepted();
    void rejected();

signals:
    void hostnameSelected(QString ip);

private:
    Ui::ServerHostnameSelectDialog *ui;
};

#endif // SERVERHOSTNAMESELECTDIALOG_H
