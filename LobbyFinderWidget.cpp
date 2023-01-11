#include <QHBoxLayout>
#include <QMessageBox>
#include "LobbyFinderWidget.h"
#include "Session.h"


auto LobbyFinderWidget::create() -> Drawable & {

    this->lobbyList = new QListWidget(this);

    this->currentLobbyName = new QLabel(this);
    this->currentLobbyStatus = new QLabel(this);

    this->lobbyName = new QLineEdit(this);
    this->joinLobbyButton = new QPushButton(this);
    this->createLobbyButton = new QPushButton(this);
    this->disconnectButton = new QPushButton(this);
    this->startGameButton = new QPushButton(this);
    this->mainLayout = new QHBoxLayout();
    this->pushButtonLayout = new QVBoxLayout();



    this->refreshTimer = new QTimer();

    return *this;
}

auto LobbyFinderWidget::place() -> Drawable & {

    this->mainLayout->addWidget(lobbyList);
    this->mainLayout->addItem(pushButtonLayout);

    this->pushButtonLayout->addWidget(currentLobbyName);
    this->pushButtonLayout->addWidget(currentLobbyStatus);

    this->pushButtonLayout->addWidget(lobbyName);
    this->pushButtonLayout->addWidget(createLobbyButton);
    this->pushButtonLayout->addWidget(joinLobbyButton);
    this->pushButtonLayout->addWidget(startGameButton);
    this->pushButtonLayout->addWidget(disconnectButton);

    this->setLayout(mainLayout);

    return *this;
}

auto LobbyFinderWidget::customize() -> Drawable & {

    this->lobbyName->setPlaceholderText("Create lobby name");
    this->joinLobbyButton->setText("Join Lobby");
    this->createLobbyButton->setText("Create Lobby");
    this->startGameButton->setText("Start Game");
    this->disconnectButton->setText("Disconnect");

    this->currentLobbyStatus->setText("Current lobby status: ");
    this->currentLobbyName->setText("Current lobby name: ");

    this->startGameButton->setDisabled(true);

    this->pushButtonLayout->setSpacing(15);
    this->pushButtonLayout->setContentsMargins(25, 0, 25, 0);
    this->pushButtonLayout->setAlignment(Qt::AlignBottom);
    this->pushButtonLayout->setSizeConstraint(QLayout::SetMinimumSize);
    this->refreshTimer->start(1000);

    return *this;
}

auto LobbyFinderWidget::connectWidgets() -> Drawable & {

    connect(this->lobbyList, &QListWidget::itemClicked, [this] {
        this->lobbyId = ((LobbyWidget *) this->lobbyList->itemWidget(lobbyList->currentItem()))->getId();
        this->currentLobbyName->setText("Current lobby  name " + ((LobbyWidget *) this->lobbyList->itemWidget(lobbyList->currentItem()))->getName()->text());
        handleCurrentLobbyState(lobbyId);
    });

    connect(this->refreshTimer, &QTimer::timeout, [this] {
        this->handleFetchLobbies();
        if(lobbyId){
            this->handleCurrentLobbyState(lobbyId);
//            this->handleStartGame(lobbyId);
        }
    });

    connect(this->joinLobbyButton, &QPushButton::clicked, [this] {
        this->handleJoinLobby(lobbyId);
    });


    connect(this->createLobbyButton, &QPushButton::clicked, [this] {
        this->handleCreateLobby();
    });

    connect(this->disconnectButton, &QPushButton::clicked, [this] {
        this->handleDisconnect();
    });

    connect(this->startGameButton, &QPushButton::clicked, [this]{
        this->handleStartGame(lobbyId);
    });

    return *this;
}

auto LobbyFinderWidget::handleFetchLobbies() -> void {

    try {

        auto session = Session("lobby", "queryAll");
        session.writeInt(this->uuid);

        int responseStatusCode = session.readInt();
        std::string responseMessage = session.readString();
        int lobbyListSize = session.readInt();

        if (responseStatusCode != 200) {
            throw std::runtime_error(responseMessage);
        }

        std::list<LobbyWidget *> items;
        while (lobbyListSize--) {
            auto id = session.readInt();
            auto name = session.readString();
            auto players = session.readString();

            auto lobby = new LobbyWidget(this);
            lobby->initialize();
            lobby->setId(id);
            lobby->getName()->setText(QString::fromStdString(name));
            lobby->getJoinedPlayers()->setText(QString::fromStdString(players));

            items.push_back(lobby);
            lobbyMap[id] = lobby;
        }

        this->lobbyList->clear();
        for (auto &l: items) {
            auto item = new QListWidgetItem(lobbyList);
            lobbyList->addItem(item);
            item->setSizeHint(l->minimumSizeHint());
            lobbyList->setItemWidget(item, l);
        }
    }
    catch (std::runtime_error const &e) {
        QMessageBox::warning(this, "Warning", e.what());
    }

}

auto LobbyFinderWidget::handleJoinLobby(int lobbyId) -> void {
    try {
        auto session = Session("lobby", "join");
        session.writeInt(this->uuid);
        session.writeInt(lobbyId);
        int responseStatusCode = session.readInt();
        std::string responseMessage = session.readString();
        if (responseStatusCode == 200) {
            joinLobby(lobbyId);
        } else throw std::runtime_error(responseMessage);
    } catch (std::runtime_error const &e) {
        QMessageBox::warning(this, "Warning", e.what());
    }
}

auto LobbyFinderWidget::handleDisconnect() -> void {
    auto session = Session("user", "disconnect");
    this->refreshTimer->stop();
    session.writeInt(this->uuid);
    emit disconnected();
}

auto LobbyFinderWidget::handleCreateLobby() -> void {

    try {
        if (this->lobbyName->text().isEmpty())
            throw std::runtime_error("Cannot create lobby with no name");

        auto session = Session("lobby", "create");
        session.writeInt(this->uuid);
        session.writeString(this->lobbyName->text().toStdString());

        auto responseStatusCode = session.readInt();
        auto responseMessage = session.readString();
        auto responseLobbyId = session.readInt();

        if (responseStatusCode != 201)
            throw std::runtime_error(responseMessage);

//        handleCurrentLobbyState(responseLobbyId);
        this->currentLobbyName->setText("Current lobby name: " + this->lobbyName->text());
//        this->currentLobbyStatus->setText("Current lobby status: Waiting for other players");

        this->lobbyId = responseLobbyId;
        this->lobbyName->clear();
    } catch (std::runtime_error const &e) {
        QMessageBox::warning(this, "Warning", e.what());
    }

}

auto LobbyFinderWidget::joinLobby(int lobbyId) -> void {
    try {
        auto lobby = lobbyMap[lobbyId];
        if (!lobby) {
            throw std::runtime_error("Null lobby");
        }
        auto session = Session("lobby", "queryCurrent");
        session.writeInt(this->uuid);
        session.writeInt(lobbyId);

        auto responseStatus = session.readInt();
        auto responseMessage = session.readString();
        auto gameId = session.readInt();

        this->currentLobbyStatus->setText("Current lobby status: " + QString::fromStdString(responseMessage));
        this->currentLobbyName->setText("Current lobby name: " + lobby->getName()->text());
    }
    catch (std::runtime_error const &e) {
        QMessageBox::warning(this, "Warning", e.what());
    }
}

#include "GameView.h"
auto LobbyFinderWidget::handleCurrentLobbyState(int lobbyId) -> void {
    try {
        auto session = Session("lobby", "queryCurrent");
        session.writeInt(this->uuid);
        session.writeInt(lobbyId);

        auto responseStatus = session.readInt();
        auto responseMessage = session.readString();
        auto gameId = session.readInt();
        this->gameId = gameId;
        if(responseStatus == 410)
            throw std::runtime_error(responseMessage.c_str());
        this->currentLobbyStatus->setText("Current lobby status: " + QString::fromStdString(responseMessage));
        if(responseStatus == 302){
            this->startGameButton->setDisabled(false);
        }

        if(responseStatus == 308){

            emit gameStarted();
        }

    } catch (std::runtime_error const & e){
        QMessageBox::warning(this, "Warning", e.what());
    }
}

auto LobbyFinderWidget::handleStartGame(int lobbyId) -> void {
    try{
        auto session = Session("lobby", "start");
        session.writeInt(this->uuid);
        session.writeInt(lobbyId);

        auto responseStatus = session.readInt();
        auto responseMessage = session.readString();
        auto gameId = session.readInt();
        this->gameId = gameId;
        if(responseStatus != 200){
            return;
            throw std::runtime_error(responseMessage.c_str());
        }
        emit gameStarted();
    } catch (std::runtime_error const & e){
        QMessageBox::warning(this, "warning", e.what());
    }
}
