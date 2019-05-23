#include "serverconnectiondialog.h"
#include "ui_serverconnectiondialog.h"

ServerConnectionDialog::ServerConnectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServerConnectionDialog)
{
    ui->setupUi(this);

    Helpers::ApplyStyleSheet(this);
    Helpers::ApplyElementMaterialShadow(ui->buttonBox);
    Helpers::ApplyElementMaterialShadow(ui->Input);

    connect(this, SIGNAL(accepted()), this, SLOT(accepted()));
    connect(this, SIGNAL(rejected()), this, SLOT(rejected()));

    ui->Input->setFocus();
}

void ServerConnectionDialog::accepted()
{
    QString input = ui->Input->text();

    if (!input.isEmpty())
    {
        emit IPInputFinished(input);
    }
    else
    {
        emit IPInputDismissed();
    }
}

void ServerConnectionDialog::rejected()
{
    emit IPInputDismissed();
}

ServerConnectionDialog::~ServerConnectionDialog()
{
    delete ui;
}
