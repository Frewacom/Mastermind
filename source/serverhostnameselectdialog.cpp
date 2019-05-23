#include "serverhostnameselectdialog.h"
#include "ui_serverhostnameselectdialog.h"

ServerHostnameSelectDialog::ServerHostnameSelectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServerHostnameSelectDialog)
{
    ui->setupUi(this);

    Helpers::ApplyStyleSheet(this);

    connect(this, SIGNAL(accepted()), this, SLOT(accepted()));
    connect(this, SIGNAL(rejected()), this, SLOT(rejected()));
}

QComboBox* ServerHostnameSelectDialog::GetComboBox()
{
    return ui->IPComboSelect;
}

void ServerHostnameSelectDialog::accepted()
{
    QString ip = ui->IPComboSelect->currentText();
    emit hostnameSelected(ip);
}

void ServerHostnameSelectDialog::rejected()
{
    emit
}

ServerHostnameSelectDialog::~ServerHostnameSelectDialog()
{
    delete ui;
}
