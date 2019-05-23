#include "gameoverdialog.h"
#include "ui_gameoverdialog.h"

GameOverDialog::GameOverDialog(Code *secret, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameOverDialog)
{
    ui->setupUi(this);

    Helpers::ApplyStyleSheet(this);
    Helpers::ApplyColorBoxMaterialShadow(ui->ColorBox1);
    Helpers::ApplyColorBoxMaterialShadow(ui->ColorBox2);
    Helpers::ApplyColorBoxMaterialShadow(ui->ColorBox3);
    Helpers::ApplyColorBoxMaterialShadow(ui->ColorBox4);
    Helpers::ApplyElementMaterialShadow(ui->ControlsBox);

    // Det här kan göras på mycket bättre sätt,
    // fixa om du orkar..
    if (secret->CodeColors.count() >= 4)
    {
        setColorBoxStylesheet(ui->ColorBox1, secret->CodeColors[0]);
        setColorBoxStylesheet(ui->ColorBox2, secret->CodeColors[1]);
        setColorBoxStylesheet(ui->ColorBox3, secret->CodeColors[2]);
        setColorBoxStylesheet(ui->ColorBox4, secret->CodeColors[3]);
    }
}

void GameOverDialog::setColorBoxStylesheet(QFrame *box, QString color)
{
    box->setStyleSheet("background-color: " + color);
}

GameOverDialog::~GameOverDialog()
{
    delete ui;
}
