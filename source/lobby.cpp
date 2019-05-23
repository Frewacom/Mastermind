#include "lobby.h"
#include "ui_lobby.h"

Lobby::Lobby(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Lobby)
{
    ui->setupUi(this);

    Helpers::ApplyStyleSheet(ui->centralWidget);
    Helpers::ApplyMaterialShadow(ui->ControlsHFrame);
    Helpers::ApplyElementMaterialShadow(ui->InputSend);
    Helpers::ApplyElementMaterialShadow(ui->ClearOutputButton);
    Helpers::ApplyElementMaterialShadow(ui->Input);
    Helpers::ApplyElementMaterialShadow(ui->Output);

    GameWindow = new MainWindow(this);
    connectWindowObject(GameWindow);

    Server = new MMServer();
    connectServerObject(Server);

    Client = new MMClient();
    connectConnectionObject(Client);
}

// Write helpers
void Lobby::write(QString msg)
{
    ui->Output->append(msg);
}

void Lobby::writeSeparator()
{
    ui->Output->append("-------------------------------------------------------------");
}

QString Lobby::toBold(QString string)
{
    return QString("<span style='font-weight:bold'>"+string+"</span>");
}

QString Lobby::withColor(QString string, QString color)
{
    return QString("<span style='color:" + color + ";'>" + string + "</span>");
}

// Connect helpers
void Lobby::connectWindowObject(MainWindow *obj)
{
    connect(obj, SIGNAL(attemptMade(Code*,Response)),
            this, SLOT(attemptMade(Code*,Response)));
    connect(obj, SIGNAL(codeSet(Code*)), this, SLOT(codeSet(Code*)));
    connect(obj, SIGNAL(playerFoundCode()), this, SLOT(playerFoundCode()));
    connect(obj, SIGNAL(gameFinished()), this, SLOT(gameFinished()));
    connect(obj, SIGNAL(windowClosed()), this, SLOT(gameFinished()));
    connect(ui->Input, SIGNAL(returnPressed()),
            this, SLOT(on_InputSend_clicked()));
}

void Lobby::connectConnectionObject(MMConnection *conn)
{
    connect(conn, SIGNAL(connectionEstablished()),
            this, SLOT(connectionEstablished()));

    connect(conn, SIGNAL(recievedPlayersReady(QString)),
            this, SLOT(recievedPlayersReady(QString)));

    connect(conn, SIGNAL(recievedChatMessage(QString)),
            this, SLOT(recievedChatMessage(QString)));

    connect(conn, SIGNAL(recievedAttempt(QString)),
            this, SLOT(recievedAttempt(QString)));

    connect(conn, SIGNAL(recievedCode(QString)),
            this, SLOT(recievedCode(QString)));

    connect(conn, SIGNAL(recievedPlayerWon(QString)),
            this, SLOT(recievedPlayerWon(QString)));

    connect(conn, SIGNAL(recievedConnectionDenied()),
            this, SLOT(recievedConnectionDenied()));

    connect(conn, SIGNAL(selectCode()),
            this, SLOT(selectCode()));

    connect(conn, SIGNAL(userDisconnected()),
            this, SLOT(userDisconnected()));

    connect(conn, SIGNAL(youDisconnected()),
            this, SLOT(youDisconnected()));

    connect(conn, SIGNAL(errorHandle(QString)),
            this, SLOT(errorHandle(QString)));

    connect(conn, SIGNAL(wroteToChat(QString)),
            this, SLOT(wroteToChat(QString)));
}

void Lobby::connectServerObject(MMServer *server)
{
    connect(server, SIGNAL(userConnected()),
            this, SLOT(userConnected()));

    connect(server, SIGNAL(maximumConnectionsReached()),
            this, SLOT(maximumConnectionsReached()));

    connectConnectionObject(server);
}

void Lobby::connectServerConnectDialog(ServerConnectionDialog *dialog)
{
    connect(dialog, SIGNAL(IPInputFinished(QString)),
            this, SLOT(IPAccepted(QString)));

    connect(dialog, SIGNAL(IPInputDismissed()),
            this, SLOT(IPDenied()));
}

void Lobby::connectHostnameChooseDialog(ServerHostnameSelectDialog *dialog)
{
    connect(dialog, SIGNAL(rejected()),
            this, SLOT(hostnameSelectCancelled()));
    connect(dialog, SIGNAL(hostnameSelected(QString)),
            this, SLOT(hostnameSelected(QString)));
}

// Functions
void Lobby::newGameWindow(bool online)
{
    GameWindow = new MainWindow(online, this);
    connectWindowObject(GameWindow);
}

void Lobby::startGameWindow(bool online)
{
    newGameWindow(online);
    GameWindow->show();
}

void Lobby::startNewMatch()
{
    writeSeparator();
    write(toBold("Startar match.."));

    if (Server->ServerMadeLastCode == NULL)
    {
        qDebug() << "yes+";
        int roll = Server->RollFirstPlayerToGuess(generateSeed());

        // Borde ha en enum istället för siffror här
        if (roll == 0)
        {
            clientShouldMakeCode();
        }
        else if (roll == 1)
        {
            serverShouldMakeCode();
        }
    }
    else if (Server->ServerMadeLastCode)
    {
        clientShouldMakeCode();
    }
    else if (!Server->ServerMadeLastCode)
    {
        serverShouldMakeCode();
    }

    writeSeparator();

    opponentWantsRematch = false;
    youWantRematch = false;
}

void Lobby::serverShouldMakeCode()
{
    // Klienten börjar gissa
    Server->WriteToNetwork(Headers::PlayersReady, QString::number(1));
    write(toBold("Du kommer nu få göra en kod:"));
    write(toBold("Öppnar ett nytt fönster om 5 sekunder.."));
    emit selectCode();
    Server->ServerMadeLastCode = true;
}

void Lobby::clientShouldMakeCode()
{
    // Servern börjar gissa
    Server->WriteToNetwork(Headers::PlayersReady, QString::number(0));
    write(toBold("Motspelaren ska nu välja en kod"));
    write(toBold("Väntar på att motspelaren ska göra sin kod..."));
    Server->ServerMadeLastCode = false;
}

void Lobby::gameFinished()
{
    GameWindow->close();
}

void Lobby::delay(int n)
{
    QTime dieTime= QTime::currentTime().addSecs(n);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

uint Lobby::generateSeed()
{
    // Random seed
    QTime seed = QTime::currentTime();
    return (uint)seed.msec();
}

QStringList Lobby::packetParser(QString data)
{
    QStringList items = data.split(" ");
    return items;
}

// Dialog SLOTS
void Lobby::IPAccepted(QString ip)
{
    Client = new MMClient();
    connectConnectionObject(Client);

    Client->Connect(ip, Client->DefaultListenPort);
}

void Lobby::IPDenied()
{
    // Ta bort??
}

void Lobby::hostnameSelected(QString ip)
{
    if(Server->Start(ip))
    {
        writeSeparator();
        write(toBold("[*] Servern startades utan problem"));
        write(toBold("[*] IP: ")+Server->CurrentHost.toString());
        write(toBold("[*] PORT: ")+QString::number(Server->CurrentPort));
        writeSeparator();

        ui->CreateServer->setText("Stoppa servern");
    }
    else
    {
        write(withColor(toBold("Kunde inte starta servern via port " +
              QString::number(Server->DefaultListenPort)), "#D32F2F"));
    }
}

// Server SLOTS
void Lobby::userConnected()
{
    write("En användare anslöt");
    isConnected = true;
    QApplication::setActiveWindow(this);

    startNewMatch();
}

void Lobby::maximumConnectionsReached()
{
    write("En anslutning nekades då lobbyn är full");
}

// Connection SLOTS
void Lobby::recievedPlayersReady(QString data)
{
    qDebug() << "Players ready";
    QStringList startId = packetParser(data);

    if (startId.count() >= 1)
    {
        if (startId[0] == "0")
        {
            writeSeparator();
            write(toBold("Du kommer nu få göra en kod:"));
            write(toBold("Öppnar ett nytt fönster om 5 sekunder.."));
            writeSeparator();
            emit selectCode();
        }
        else
        {
            writeSeparator();
            write(toBold("Motspelaren ska göra en kod"));
            write(toBold("Väntar på att motspelaren ska göra sin kod..."));
            writeSeparator();
        }
    }
}

void Lobby::recievedChatMessage(QString msg)
{
    qDebug() << "Recieved chat message";
    write(otherPrefix + msg);

    if (msg == "!rematch" || msg == "!REMATCH")
    {
        opponentWantsRematch = true;

        if (youWantRematch && opponentWantsRematch)
        {
            if (!isClient)
            {
                startNewMatch();
            }
        }
        else
        {
            write("Motspelaren vill spela igen, skriv !rematch");
        }
    }
}

void Lobby::recievedAttempt(QString data)
{
    qDebug() << "Recieved attempt";
    QStringList items = packetParser(data);
    if (items.count() == 8)
    {
        Code *code = new Code(items[0],items[1],items[2],items[3]);
        QStringList lamps = {items[4],items[5],items[6],items[7]};
        // Egentligen borde writeAttemptHistory bara ta QStringList och inte
        // ett helt response objekt
        Response resp(false, lamps, " ");

        GameWindow->WriteAttemptHistory(code, resp, true);
    }
}

void Lobby::recievedCode(QString data)
{
    write("Motspelaren har valt en kod, lycka till!");
    QStringList colors = packetParser(data);
    if(colors.count() == 4)
    {
        // For-loop kanske
        startGameWindow(true);
        GameWindow->StartTimers();
        GameWindow->SetCode(colors[0],colors[1],colors[2],colors[3]);
    }
    else
    {
        write(withColor(toBold("Koden blev korrupt på vägen, testa att starta om."),"red"));
    }
    IsInGame = true;
}

void Lobby::recievedPlayerWon(QString data)
{
    writeSeparator();
    write(withColor(toBold("Motspelaren hittade koden!"), "green"));
    write(toBold("Om du vill köra igen: skriv !rematch"));
    writeSeparator();

    GameWindow->ShowNewCustomTextDialog("Motspelaren hittade koden!");
    GameWindow->HasWon = true;

    IsInGame = false;
    opponentWantsRematch = false;
    youWantRematch = false;
}

void Lobby::recievedConnectionDenied()
{
    if (isClient)
    {
        Client->DeleteSocket();
        write(toBold("Anslutningen nekades av servern (SERVERN ÄR FULL)"));
    }
}

void Lobby::userDisconnected()
{
    write(withColor(toBold("Motspelaren bröt anslutningen"),"red"));

    if (isClient)
    {
        Client->DeleteSocket();
        ui->ConnectToServer->setText("Anslut till server");
        isClient = false;
        isConnected = false;
    }

    QApplication::setActiveWindow(this);

    if (IsInGame)
    {
        QString text = "Motspelaren stängde ner spelet, avbryter..";
        writeSeparator();
        GameWindow->ShowNewCustomTextDialog(text);
    }
}

void Lobby::wroteToChat(QString msg)
{
    write(youPrefix + msg);
}

void Lobby::errorHandle(QString msg)
{
    write(msg);
    QApplication::setActiveWindow(this);
}

void Lobby::youDisconnected()
{
    write("Du bröt anslutningen");
    isConnected = false;
    IsInGame = false;
}

// Client SLOTS
void Lobby::connectionEstablished()
{
    write(withColor(toBold("Ansluten till servern med IP: " +
            Client->Socket->peerAddress().toString()),"green"));

    ui->ConnectToServer->setText("Koppla ifrån");

    isClient = true;
    isConnected = true;
}

// Gamestate SLOTS
void Lobby::selectCode()
{
    delay(3);
    startGameWindow(true);
    GameWindow->ShowCodeSelectInterface();
    IsInGame = true;
}

void Lobby::codeSet(Code *code)
{
    if (isConnected)
    {
        QString data = code->ToQString();

        if (isClient)
        {
            Client->WriteToNetwork(Headers::SetCode, data);
        }
        else
        {
            Server->WriteToNetwork(Headers::SetCode, data);
        }

        write("Du har valt en kod, motspelaren ska nu gissa");

        GameWindow->RestoreFullSizeGeometry();
        GameWindow->StartTimers();
    }
}

void Lobby::attemptMade(Code *code, Response resp)
{
    if (isConnected)
    {
        QString colors = code->ToQString();
        QString lamps = resp.ToQString();

        QString data = colors + " " + lamps;

        if (isClient)
        {
            Client->WriteToNetwork(Headers::Attempt, data);
        }
        else if (!isClient)
        {
            Server->WriteToNetwork(Headers::Attempt, data);
        }
    }
}

void Lobby::playerFoundCode()
{
    if (isClient)
    {
        Client->WriteToNetwork(Headers::PlayerWon);
    }
    else
    {
       Server->WriteToNetwork(Headers::PlayerWon);
    }

    writeSeparator();
    write(withColor(toBold("Grattis, du vann!"), "green"));
    write(toBold("Om du vill köra igen: skriv !rematch"));
    writeSeparator();
    IsInGame = false;
}

// Button SLOTS
void Lobby::on_PlayOffline_clicked()
{
    startGameWindow(false);
}

void Lobby::on_CreateServer_clicked()
{
    if (!Server->isRunning && !isClient)
    {
        ServerHostnameSelectDialog *hostSelectDialog = new ServerHostnameSelectDialog(this);
        Server->PopulateHostnameComboBox(hostSelectDialog->GetComboBox());
        connectHostnameChooseDialog(hostSelectDialog);
        hostSelectDialog->show();
    }
    else
    {
        write(withColor(toBold("Servern stoppades"), "#D32F2F"));
        Server->Stop();
        ui->CreateServer->setText("Starta servern");
    }
}

void Lobby::on_ConnectToServer_clicked()
{
    if (isClient)
    {
        Client->Disconnect();
        ui->ConnectToServer->setText("Anslut till server");
        isClient = false;
    }
    else
    {
        if (!Server->isRunning)
        {
            ServerConnectionDialog *dialog = new ServerConnectionDialog(this);
            dialog->show();
            connectServerConnectDialog(dialog);
        }
    }
}

void Lobby::on_InputSend_clicked()
{
    QString input = ui->Input->text();
    // Skulle kunna göra om den här if-satsen så att den blir
    // mindre och mer lättförstålig.
    if (isClient)
    {
        if (Client->hasConnection)
        {
            if (!input.isEmpty())
            {
                Client->WriteChat(input);
                ui->Input->clear();
            }
        }
    }
    else
    {
        if (Server->isRunning)
        {
            if (Server->hasConnection)
            {
                if (!input.isEmpty())
                {
                    Server->WriteChat(input);
                    ui->Input->clear();
                }
            }
        }
    }

    if (input == "clearHighscores")
    {
        GameWindow->ClearStoredQSettings();
        write("Tog bort highscore-data");
        ui->Input->clear();
    }
    else if (input == "!rematch")
    {
        youWantRematch = true;
        if (!opponentWantsRematch)
        {
            write("Du är redo, väntar på motspelaren");
        }
        else
        {
            if (!isClient)
            {
                delay(1);
                startNewMatch();
            }
        }
    }
}

void Lobby::on_ClearOutputButton_clicked()
{
    ui->Output->clear();
    ui->Input->clear();
}

Lobby::~Lobby()
{
    // Det här bör förhindra servern från att fortsätta köras om
    // en användare anslutit och du stänger av programet utan att
    // först stoppa servern.
    Server->Stop();
    Client->Disconnect();

    delete ui;
}
