#ifndef QT_CHESS_CPP_LOBBYWIDGET_H
#define QT_CHESS_CPP_LOBBYWIDGET_H

#include <QLabel>
#include "Drawable.h"

class LobbyWidget : public Drawable {
    Q_OBJECT
private:
    int id;

    QLabel *name;
    QLabel *status;
    QLabel *joinedPlayers;

    QLayout *mainLayout;

public:

    explicit LobbyWidget(QWidget *parent = nullptr) : Drawable(parent) {}

    auto create() -> Drawable & override;

    auto place() -> Drawable & override;

    auto customize() -> Drawable & override;

    auto connectWidgets() -> Drawable & override;

    int getId() const;

    void setId(int id);

    QLabel *getName() const;

    void setName(QLabel *name);

    QLabel *getStatus() const;

    void setStatus(QLabel *status);

    QLabel *getJoinedPlayers() const;

    void setJoinedPlayers(QLabel *joinedPlayers);
};


#endif //QT_CHESS_CPP_LOBBYWIDGET_H
