#ifndef QT_CHESS_CPP_LOBBYFINDERWIDGET_H
#define QT_CHESS_CPP_LOBBYFINDERWIDGET_H

#include <QListWidget>
#include <QPushButton>
#include <QTimer>
#include <QLineEdit>
#include <unordered_map>
#include "Drawable.h"
#include "LobbyWidget.h"


class LobbyFinderWidget : public Drawable{
    Q_OBJECT
private:

    int uuid;
    int lobbyId;
    int gameId = 0;
    QListWidget * lobbyList;
    std::unordered_map<int, LobbyWidget *> lobbyMap;

    QLabel * currentLobbyStatus;
    QLabel * currentLobbyName;
    QLineEdit * lobbyName;
    QPushButton * joinLobbyButton;
    QPushButton * createLobbyButton;
    QPushButton * disconnectButton;

    QPushButton * startGameButton;

    QLayout * mainLayout;
    QLayout * pushButtonLayout;
    QTimer * refreshTimer;

public:

    explicit LobbyFinderWidget(QWidget * parent = nullptr) : Drawable(parent) {}

    auto create() -> Drawable & override;
    auto place() -> Drawable & override;
    auto customize() -> Drawable & override;
    auto connectWidgets() -> Drawable & override;

    auto handleFetchLobbies() -> void;
    auto handleJoinLobby(int lobbyId) -> void;
    auto handleCreateLobby() -> void;
    auto handleDisconnect() -> void;
    auto handleCurrentLobbyState(int lobbyId) -> void;
    auto handleStartGame(int lobbyId) -> void;

    auto joinLobby(int lobbyId) -> void;

    auto inline setUuid(int uuid) -> void {
        this->uuid = uuid;
    }

    auto inline getGameId() const -> int {
        return this->gameId;
    }

    auto inline getUuid() const -> int {
        return this->uuid;
    }


signals:
    void disconnected();
    void gameStarted();

};


#endif //QT_CHESS_CPP_LOBBYFINDERWIDGET_H
