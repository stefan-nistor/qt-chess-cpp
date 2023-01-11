#include <QHBoxLayout>
#include "LobbyWidget.h"

auto LobbyWidget::create() -> Drawable & {

    this->name = new QLabel(this);
    this->status = new QLabel(this);
    this->joinedPlayers = new QLabel(this);

    this->mainLayout = new QHBoxLayout();

    return *this;
}

auto LobbyWidget::place() -> Drawable & {

    this->mainLayout->addWidget(name);
    this->mainLayout->addWidget(status);
    this->mainLayout->addWidget(joinedPlayers);

    this->setLayout(mainLayout);

    return *this;
}

auto LobbyWidget::customize() -> Drawable & {
    return *this;
}

auto LobbyWidget::connectWidgets() -> Drawable & {
    return *this;
}

int LobbyWidget::getId() const {
    return id;
}

void LobbyWidget::setId(int id) {
    LobbyWidget::id = id;
}

QLabel *LobbyWidget::getName() const {
    return name;
}

void LobbyWidget::setName(QLabel *name) {
    LobbyWidget::name = name;
}

QLabel *LobbyWidget::getStatus() const {
    return status;
}

void LobbyWidget::setStatus(QLabel *status) {
    LobbyWidget::status = status;
}

QLabel *LobbyWidget::getJoinedPlayers() const {
    return joinedPlayers;
}

void LobbyWidget::setJoinedPlayers(QLabel *joinedPlayers) {
    LobbyWidget::joinedPlayers = joinedPlayers;
}
