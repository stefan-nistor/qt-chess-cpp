#ifndef QT_CHESS_CPP_LOBBYFINDERWIDGET_H
#define QT_CHESS_CPP_LOBBYFINDERWIDGET_H

#include <QListWidget>
#include <QPushButton>
#include <QTimer>
#include "Drawable.h"
#include "LobbyWidget.h"


class LobbyFinderWidget : public Drawable{
private:

    int uuid;
    int lobbyId;
    QListWidget * lobbyList;

    QPushButton * joinLobbyButton;
    QPushButton * createLobbyButton;
    QPushButton * disconnectButton;

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

    auto inline setUuid(int uuid) -> void {
        this->uuid = uuid;
    }

};


#endif //QT_CHESS_CPP_LOBBYFINDERWIDGET_H
