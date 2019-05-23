#include "customtextdialog.h"
#include "ui_customtextdialog.h"

CustomTextDialog::CustomTextDialog(QString text, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomTextDialog)
{
    ui->setupUi(this);

    Helpers::ApplyStyleSheet(this);
    ui->CustomLabel->setText(text);
}

CustomTextDialog::~CustomTextDialog()
{
    delete ui;
}
