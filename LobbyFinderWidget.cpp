#include <QHBoxLayout>
#include <QMessageBox>
#include "LobbyFinderWidget.h"
#include "Session.h"


auto LobbyFinderWidget::create() -> Drawable & {

    this->lobbyList = new QListWidget(this);

    this->joinLobbyButton = new QPushButton(this);
    this->createLobbyButton = new QPushButton(this);
    this->disconnectButton = new QPushButton(this);

    this->mainLayout = new QHBoxLayout();
    this->pushButtonLayout = new QVBoxLayout();

    this->refreshTimer = new QTimer();

    return *this;
}

auto LobbyFinderWidget::place() -> Drawable & {

    this->mainLayout->addWidget(lobbyList);
    this->mainLayout->addItem(pushButtonLayout);

    this->pushButtonLayout->addWidget(joinLobbyButton);
    this->pushButtonLayout->addWidget(createLobbyButton);
    this->pushButtonLayout->addWidget(disconnectButton);

    this->setLayout(mainLayout);

    return *this;
}

auto LobbyFinderWidget::customize() -> Drawable & {

    this->joinLobbyButton->setText("Join Lobby");
    this->createLobbyButton->setText("Create Lobby");
    this->disconnectButton->setText("Disconnect");

    this->pushButtonLayout->setSpacing(15);
    this->pushButtonLayout->setContentsMargins(25, 0, 25, 0);
    this->pushButtonLayout->setAlignment(Qt::AlignBottom);

    this->refreshTimer->start(50);

    return *this;
}

auto LobbyFinderWidget::connectWidgets() -> Drawable & {

    connect(this->lobbyList, &QListWidget::itemClicked, [this] {
        this->lobbyId = ((LobbyWidget *) this->lobbyList->itemWidget(lobbyList->currentItem()))->getId();
    });

    connect(this->refreshTimer, &QTimer::timeout, [this] {
        this->handleFetchLobbies();
    });

    connect(this->joinLobbyButton, &QPushButton::clicked, [this] {
        this->handleJoinLobby(lobbyId);
    });

    connect(this->disconnectButton, &QPushButton::clicked, [this] {
        auto session = Session("user", "disconnect");
        this->refreshTimer->stop();
        session.writeInt(this->uuid);
        emit disconnected();
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

        while (lobbyListSize--) {
            auto lobby = new LobbyWidget(this);
            lobby->setId(session.readInt());
            lobby->getName()->setText(QString::fromStdString(session.readString()));
            lobby->getJoinedPlayers()->setText(QString::fromStdString(session.readString()));

            auto item = new QListWidgetItem(lobbyList);
            lobbyList->addItem(item);
            lobbyList->setItemWidget(item, lobby);
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
    } catch (std::runtime_error const & e ){
        QMessageBox::warning(this, "Warning", e.what());
    }
}
