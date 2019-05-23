#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "code.h"
#include "helpers.h"
#include "response.h"
#include "gameoverdialog.h"
#include "highscoredialog.h"
#include "customtextdialog.h"

#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QUrlQuery>
#include <QFile>
#include <QTimer>
#include <QElapsedTimer>
#include <QSettings>
#include <QCloseEvent>
#include <QEvent>
#include <QStyle>
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QGraphicsDropShadowEffect>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(bool isOnline = false, QWidget *parent = 0);
    ~MainWindow();

    QSettings *Settings;
    QNetworkAccessManager *APIManager;
    QVBoxLayout *HistoryLayout;
    QStringList Colors = {"#e0e0e0", "#1b5e20", "#006064", "#3e2723",
                     "#311b92", "#b71c1c", "#880e4f", "#e65100"};
    Code *SecretKey = NULL;

    int AttemptsLeft = 10;
    int NumberOfGuesses = 0;

    bool IsOnline = false;
    bool ShouldSetCode = false;
    bool HasWon = false;

    QTimer *Timer;
    QElapsedTimer *TimerElapsed;
    QTime *SecondsElapsed;

    void StartTimers();
    void ShowCodeSelectInterface();
    void SetCode(QString color1, QString color2,
                 QString color3, QString color4);
    void WriteAttemptHistory(Code *code, Response resp, bool recv);
    void ShowNewCustomTextDialog(QString text);
    void RestoreFullSizeGeometry();

    void ClearStoredQSettings();

signals:
    void codeSet(Code *code);
    void attemptMade(Code *code, Response resp);
    void playerFoundCode();
    void gameFinished();
    void windowClosed();
    void rightClick(QObject *sender);

private slots:
    void onColorBoxClicked();
    void onFinishedClicked();
    void onHighscoreAccepted(int score, QString name);
    void onHighscoreDismissed();
    void onTimerUpdate();
    void onGameOverDismissed();
    void onColorBoxRightClicked(QObject *sender);
    void onCustomTextDialogFinished();

private:
    Ui::MainWindow *ui;

    void connectColorBoxes();
    void setRandomSeed();
    void setRandomCode();
    void updateColorIndex(QPushButton *button, bool positive);
    void updateColor(QPushButton *button);
    void updateAttemptCounter();
    void addNewHighscore(QString name, int score);
    void gameOver();

    void closeEvent(QCloseEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);

    void saveHighscoreToComputer(int score);
    int loadHighscoreFromComputer();

    bool scoreIsGreaterThanPreviousHighscores(int score);
    int getRandomNumber(int min, int max);
    int calculateScore();
    int getIndexPropertyAsInt(QPushButton *button);
    QVariant convertIndexToQVariant(int index);

    QByteArray fullSizeGeometry;
    QLabel *codeSetLabel;
};

#endif // MAINWINDOW_H
