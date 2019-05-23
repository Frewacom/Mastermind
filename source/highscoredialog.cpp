#include "highscoredialog.h"
#include "ui_highscoredialog.h"

HighscoreDialog::HighscoreDialog(int score, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HighscoreDialog)
{
    ui->setupUi(this);

    Helpers::ApplyStyleSheet(this);
    Helpers::ApplyElementMaterialShadow(ui->buttonBox);
    Helpers::ApplyElementMaterialShadow(ui->NameInput);

    ui->ScoreLabel->setText("Poäng: " + QString::number(score));
    m_score = score;
}

HighscoreDialog::~HighscoreDialog()
{
    delete ui;
}


void HighscoreDialog::on_buttonBox_accepted()
{
    QString name = ui->NameInput->text();
    if (name.length() <= 25)
    {
        emit onDialogAccepted(m_score, name);
    }
}
