#ifndef HIGHSCOREDIALOG_H
#define HIGHSCOREDIALOG_H

#include "helpers.h"

#include <QDialog>
#include <QAbstractButton>
#include <QFile>

namespace Ui {
class HighscoreDialog;
}

class HighscoreDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HighscoreDialog(int score, QWidget *parent = 0);
    ~HighscoreDialog();

signals:
    void onDialogAccepted(int score, QString name);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::HighscoreDialog *ui;
    int m_score = 0;
};

#endif // HIGHSCOREDIALOG_H
