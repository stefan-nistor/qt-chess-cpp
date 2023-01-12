#include <QVBoxLayout>
#include "MainWidget.h"

auto MainWidget::create() -> Drawable & {

    this->loginWidget = new LoginWidget(this);
    this->lobbyFinderWidget = new LobbyFinderWidget(this);
    this->lobbyFinderWidget->setVisible(false);
    this->mainLayout = new QVBoxLayout();
    this->setLayout(this->mainLayout);
    return * this;
}

auto MainWidget::place() -> Drawable & {
    this->mainLayout->addWidget(this->loginWidget);
    return * this;
}

auto MainWidget::customize() -> Drawable & {
    return * this;
}

auto MainWidget::connectWidgets() -> Drawable & {

    connect(this->loginWidget, &LoginWidget::connected, [this]{
        this->uuid = loginWidget->getUuid();
        this->loginWidget->hide();

        this->lobbyFinderWidget->setUuid(this->uuid);
        this->mainLayout->addWidget(this->lobbyFinderWidget);
        this->lobbyFinderWidget->setVisible(true);
        this->lobbyFinderWidget->initialize();
    });

    connect(this->lobbyFinderWidget, & LobbyFinderWidget::disconnected, [this]{
        this->uuid = 0;
        this->lobbyFinderWidget->hide();
        this->loginWidget->show();
    });

    connect(this->lobbyFinderWidget, & LobbyFinderWidget::gameStarted, [this]{

        if(gameId==0) {
            this->gameId = lobbyFinderWidget->getGameId();
            this->uuid = lobbyFinderWidget->getUuid();
            this->boardView = new BoardView(uuid, gameId);
//            this->gameView->setGameId(gameId);
//            this->gameView->setUserId(uuid);

            this->mainLayout->removeWidget(lobbyFinderWidget);
            this->mainLayout->addWidget(boardView);
        }

    });

    return * this;
}
