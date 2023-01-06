#include <QHBoxLayout>
#include "LobbyFinderWidget.h"

auto LobbyFinderWidget::create() -> Drawable & {

    this->lobbyList = new QListWidget(this);

    this->joinLobbyButton = new QPushButton(this);
    this->createLobbyButton = new QPushButton(this);
    this->disconnectButton = new QPushButton(this);

    this->mainLayout = new QHBoxLayout();
    this->pushButtonLayout = new QVBoxLayout();

    return * this;
}

auto LobbyFinderWidget::place() -> Drawable & {

    this->mainLayout->addWidget(lobbyList);
    this->mainLayout->addItem(pushButtonLayout);

    this->pushButtonLayout->addWidget(joinLobbyButton);
    this->pushButtonLayout->addWidget(createLobbyButton);
    this->pushButtonLayout->addWidget(disconnectButton);

    this->setLayout(mainLayout);

    return * this;
}

auto LobbyFinderWidget::customize() -> Drawable & {

    this->joinLobbyButton->setText("Join Lobby");
    this->createLobbyButton->setText("Create Lobby");
    this->disconnectButton->setText("Disconnect");

    this->pushButtonLayout->setSpacing(15);
    this->pushButtonLayout->setContentsMargins(25, 0, 25, 0);
    this->pushButtonLayout->setAlignment(Qt::AlignBottom);

    return * this;
}

auto LobbyFinderWidget::connectWidgets() -> Drawable & {
    return * this;
}
