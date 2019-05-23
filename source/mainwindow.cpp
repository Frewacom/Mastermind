#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(bool isOnline, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Helpers::ApplyStyleSheet(ui->centralWidget);
    Helpers::ApplyMaterialShadow(ui->HeaderFrame);
    Helpers::ApplyColorBoxMaterialShadow(ui->ColorBox1);
    Helpers::ApplyColorBoxMaterialShadow(ui->ColorBox2);
    Helpers::ApplyColorBoxMaterialShadow(ui->ColorBox3);
    Helpers::ApplyColorBoxMaterialShadow(ui->ColorBox4);
    Helpers::ApplyColorBoxMaterialShadow(ui->ColorBoxFinished);

    HistoryLayout = ui->AttemptHistoryVLayout;
    APIManager = new QNetworkAccessManager(this);
    Settings = new QSettings("Fredrik Engstrand", "Mastermind");

    connectColorBoxes();

    if (isOnline)
    {
        IsOnline = true;
    }
    else
    {
        setRandomSeed();
        setRandomCode();

        qDebug() << SecretKey->CodeColors[0];
        qDebug() << SecretKey->CodeColors[1];
        qDebug() << SecretKey->CodeColors[2];
        qDebug() << SecretKey->CodeColors[3];
    }
}

// Public functions
void MainWindow::StartTimers()
{
    Timer = new QTimer(this);
    TimerElapsed = new QElapsedTimer();
    SecondsElapsed = new QTime(0,0,0);

    connect(Timer, SIGNAL(timeout()), this, SLOT(onTimerUpdate()));
    Timer->start(1000);
    TimerElapsed->start();
}

void MainWindow::SetCode(QString color1, QString color2,
                         QString color3, QString color4)
{
    SecretKey = new Code(color1, color2, color3, color4);
}

void MainWindow::WriteAttemptHistory(Code *code, Response resp, bool recv)
{
    AttemptsLeft -= 1;
    updateAttemptCounter();

    QHBoxLayout *colors = new QHBoxLayout;
    QHBoxLayout *lamps = new QHBoxLayout;

    for (int i = 0; i < code->CodeColors.length(); i++)
    {
        QPushButton *btn = new QPushButton;
        btn->setStyleSheet("background-color:"+code->CodeColors[i]);

        btn->setAccessibleName("ColorBox");
        Helpers::ApplyColorBoxMaterialShadow(btn);

        colors->addWidget(btn);
    }

    for (int colorIndex = 0; colorIndex < resp.Lamps.count(); colorIndex++)
    {
        QFrame *frame = new QFrame;
        frame->setAccessibleName("LampFrame");
        Helpers::ApplyColorBoxMaterialShadow(frame);

        if (resp.Lamps[colorIndex] == "2")
        {
            frame->setStyleSheet("background-color:#1b5e20");
        }
        else if (resp.Lamps[colorIndex] == "1")
        {
            frame->setStyleSheet("background-color:#b31217");
        }
        else
        {
            frame->setStyleSheet("background-color:#e0e0e0");
        }

        lamps->addWidget(frame);
    }

    colors->addLayout(lamps);
    HistoryLayout->insertLayout(HistoryLayout->count()-1,colors);

    NumberOfGuesses += 1;

    if (IsOnline)
    {
        if (!recv)
        {
            emit attemptMade(code, resp);
        }
    }
}

void MainWindow::ClearStoredQSettings()
{
    Settings->setValue("highscore", 0);
}

// Public UI Helpers
void MainWindow::ShowCodeSelectInterface()
{
    ui->HeaderFrame->hide();
    ShouldSetCode = true;
    fullSizeGeometry = this->saveGeometry();
    resize(this->width(), 100);

    codeSetLabel = new QLabel(this);
    QString text;
    text += "\nGör en kod med de vita rutorna nedan.\n";
    text += "Du kan byta färg genom att klicka på rutorna med vänster och högerklick.\n";
    text += "När du är nöjd: tryck på klar i det nedre högra hörnet.\n";
    text += "Så fort du tryckt på klar kommer koden att skickas till ";
    text += "din motspelare.\n";
    text += "Du kommer att få se tiden som gått, antal försök, samt motspelarens gissningar.\n";
    text += "När du är klar är det bara att luta dig tillbaka och kolla på.";
    codeSetLabel->setText(text);

    HistoryLayout->addWidget(codeSetLabel);
    ui->ColorBoxFinished->setText("Klar");
}

void MainWindow::ShowNewCustomTextDialog(QString text)
{
    CustomTextDialog *dialog = new CustomTextDialog(text, this);
    connect(dialog, SIGNAL(accepted()),
            this, SLOT(onCustomTextDialogFinished()));
    connect(dialog, SIGNAL(rejected()),
            this, SLOT(onCustomTextDialogFinished()));
    dialog->show();
}

void MainWindow::RestoreFullSizeGeometry()
{
    this->restoreGeometry(fullSizeGeometry);
    delete codeSetLabel;
    ui->ColorBoxFinished->setText("Gissa");
}

// Connect helpers
void MainWindow::connectColorBoxes()
{

    connect(ui->ColorBox1, SIGNAL(clicked()), this, SLOT(onColorBoxClicked()));
    connect(ui->ColorBox2, SIGNAL(clicked()), this, SLOT(onColorBoxClicked()));
    connect(ui->ColorBox3, SIGNAL(clicked()), this, SLOT(onColorBoxClicked()));
    connect(ui->ColorBox4, SIGNAL(clicked()), this, SLOT(onColorBoxClicked()));

    connect(ui->ColorBoxFinished, SIGNAL(clicked()), this, SLOT(onFinishedClicked()));

    ui->ColorBox1->setProperty("index", 0);
    ui->ColorBox2->setProperty("index", 0);
    ui->ColorBox3->setProperty("index", 0);
    ui->ColorBox4->setProperty("index", 0);

    updateColor(ui->ColorBox1);
    updateColor(ui->ColorBox2);
    updateColor(ui->ColorBox3);
    updateColor(ui->ColorBox4);

    ui->ColorBox1->installEventFilter(this);
    ui->ColorBox2->installEventFilter(this);
    ui->ColorBox3->installEventFilter(this);
    ui->ColorBox4->installEventFilter(this);

    connect(this, SIGNAL(rightClick(QObject*)), this, SLOT(onColorBoxRightClicked(QObject*)));
}

// Helper funtions
void MainWindow::setRandomSeed()
{
    // Random seed
    QTime seed = QTime::currentTime();
    qsrand((uint)seed.msec());
}

int MainWindow::getRandomNumber(int min, int max)
{
    return ((qrand() % ((max + 1) - min)) + min);
}

int MainWindow::getIndexPropertyAsInt(QPushButton *button)
{
    QVariant index = button->property("index");
    return index.toInt();
}

QVariant MainWindow::convertIndexToQVariant(int index)
{
    QVariant variant(index);
    return variant;
}

bool MainWindow::scoreIsGreaterThanPreviousHighscores(int score)
{
    int prevScore = loadHighscoreFromComputer();
    if (prevScore != 0)
    {
        if (score > prevScore)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return true;
    }
}

void MainWindow::saveHighscoreToComputer(int score)
{
    Settings->setValue("highscore", score);
}

int MainWindow::loadHighscoreFromComputer()
{
    int prevScore = Settings->value("highscore").toInt();
    return prevScore;
}

// Events
bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *keyEvent = static_cast<QMouseEvent*>(event);
        if (keyEvent->button() == Qt::RightButton)
        {
            qDebug() << "rigth clicked";
            emit rightClick(watched);
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    emit windowClosed();
}

// SLOTS
void MainWindow::onTimerUpdate()
{
    if (!HasWon)
    {
        *SecondsElapsed = SecondsElapsed->addMSecs(Timer->interval());
        QString time = SecondsElapsed->toString("hh:mm:ss");
        ui->TimeElapsed->setText(time);
    }
}

void MainWindow::onCustomTextDialogFinished()
{
    if (HasWon)
    {
        this->close();
    }
    // Vad ska vi göra här?
}

void MainWindow::onColorBoxClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    updateColorIndex(button, true);
    updateColor(button);
}

void MainWindow::onColorBoxRightClicked(QObject *sender)
{
    QPushButton *button = qobject_cast<QPushButton*>(sender);
    updateColorIndex(button, false);
    updateColor(button);
}

void MainWindow::onFinishedClicked()
{
    int index1 = getIndexPropertyAsInt(ui->ColorBox1);
    int index2 = getIndexPropertyAsInt(ui->ColorBox2);
    int index3 = getIndexPropertyAsInt(ui->ColorBox3);
    int index4 = getIndexPropertyAsInt(ui->ColorBox4);

    QString color1 = Colors[index1];
    QString color2 = Colors[index2];
    QString color3 = Colors[index3];
    QString color4 = Colors[index4];

    Code *code = new Code(color1, color2, color3, color4);
    // Vi behöver något bättre sätt att kolla ifall
    // vi har satt en kod och ifall vi är den som ska
    // bestämma koden

    if (ShouldSetCode)
    {
        // menar den här skiten
        if (SecretKey == NULL)
        {
            emit codeSet(code);
            ui->HeaderFrame->show();
            SecretKey = code;
            this->restoreGeometry(fullSizeGeometry);
        }
    }
    else
    {
        if (AttemptsLeft > 0)
        {
            Response resp = code->Compare(SecretKey);

            WriteAttemptHistory(code, resp, false);

            if (resp.Success)
            {
                int score = calculateScore();

                if (scoreIsGreaterThanPreviousHighscores(score))
                {
                    HighscoreDialog *dialog = new HighscoreDialog(score, this);
                    connect(dialog, SIGNAL(onDialogAccepted(int, QString)),
                                this, SLOT(onHighscoreAccepted(int, QString)));
                    connect(dialog, SIGNAL(rejected()),
                            this, SLOT(onHighscoreDismissed()));
                    dialog->show();
                    saveHighscoreToComputer(score);
                }
                else
                {
                    int highscore = loadHighscoreFromComputer();
                    QString text;
                    text += "Grattis, du vann!\n";
                    text += "Tyvärr så slog du inte något rekord den här gången!\n";
                    text += "Ditt personliga bästa är: ";
                    text += QString::number(highscore) + " poäng\n";
                    text += "Den här omgången fick du: ";
                    text += QString::number(score) + " poäng";
                    ShowNewCustomTextDialog(text);
                }

                emit playerFoundCode();
                HasWon = true;
            }
            else
            {
                if (AttemptsLeft <= 0)
                {
                    gameOver();
                }
            }
        }
    }
}

void MainWindow::onGameOverDismissed()
{
    emit gameFinished();
}

void MainWindow::onHighscoreAccepted(int score, QString name)
{
    addNewHighscore(name, score);
    emit gameFinished();
}

void MainWindow::onHighscoreDismissed()
{
    emit gameFinished();
}

// MAIN Functions (private)
void MainWindow::setRandomCode()
{
    QString color1 = Colors[getRandomNumber(0,Colors.count() - 1)];
    QString color2 = Colors[getRandomNumber(0,Colors.count() - 1)];
    QString color3 = Colors[getRandomNumber(0,Colors.count() - 1)];
    QString color4 = Colors[getRandomNumber(0,Colors.count() - 1)];
    SecretKey = new Code(color1, color2, color3, color4);
}

void MainWindow::updateColorIndex(QPushButton *button, bool positive)
{
    int index = getIndexPropertyAsInt(button);

    if (positive)
    {
        if (index < Colors.count() - 1)
        {
            index++;
        }
        else
        {
            index = 0;
        }
    }
    else
    {
        if (index <= 0)
        {
            index = Colors.count() - 1;
        }
        else
        {
            index--;
        }
    }

    button->setProperty("index", convertIndexToQVariant(index));
}

void MainWindow::updateColor(QPushButton *button)
{
    int index = getIndexPropertyAsInt(button);
    button->setStyleSheet("background-color: " + Colors[index]);
}

void MainWindow::updateAttemptCounter()
{
    QString placeholder = "Försök kvar: ";
    QString attemptsLeft = QString::number(AttemptsLeft);
    ui->Attempts->setText(placeholder + attemptsLeft);
}

int MainWindow::calculateScore()
{
    int timeSmall = TimerElapsed->elapsed() / 1000;

    if (timeSmall >= 300000)
    {
        timeSmall = 300000;
    }

    int timeScore = 300000 / timeSmall;
    int multiplier = 11 - NumberOfGuesses;

    int score = timeScore * multiplier;

    return score;
}

void MainWindow::addNewHighscore(QString name, int score)
{
    QUrl url("http://127.0.0.1/mastermind/api.php");
    QUrlQuery params;

    params.addQueryItem("name", name);
    params.addQueryItem("score", QString::number(score));
    url.setQuery(params.query());

    QNetworkRequest request(url);
    APIManager->get(request);
    qDebug() << "added new highscore";
}

void MainWindow::gameOver()
{
    // visa du förlorade dialog
    GameOverDialog *dialog = new GameOverDialog(SecretKey,this);
    dialog->show();
    connect(dialog, SIGNAL(accepted()), this, SLOT(onGameOverDismissed()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
