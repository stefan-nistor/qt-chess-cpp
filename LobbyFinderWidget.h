#ifndef QT_CHESS_CPP_LOBBYFINDERWIDGET_H
#define QT_CHESS_CPP_LOBBYFINDERWIDGET_H

#include <QListWidget>
#include <QPushButton>
#include "Drawable.h"

class LobbyFinderWidget : public Drawable{
private:

    QListWidget * lobbyList;

    QPushButton * joinLobbyButton;
    QPushButton * createLobbyButton;
    QPushButton * disconnectButton;

    QLayout * mainLayout;
    QLayout * pushButtonLayout;

public:

    explicit LobbyFinderWidget(QWidget * parent = nullptr) : Drawable(parent) {}

    auto create() -> Drawable & override;
    auto place() -> Drawable & override;
    auto customize() -> Drawable & override;
    auto connectWidgets() -> Drawable & override;


};


#endif //QT_CHESS_CPP_LOBBYFINDERWIDGET_H
