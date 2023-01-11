#include <QVBoxLayout>
#include "MainWidget.h"

auto MainWidget::create() -> Drawable & {

    this->loginWidget = new LoginWidget(this);
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
        this->mainLayout->removeWidget(this->loginWidget);
        delete loginWidget;
        this->lobbyFinderWidget = new LobbyFinderWidget(this);
        this->lobbyFinderWidget->setUuid(this->uuid);
        this->mainLayout->addWidget(this->lobbyFinderWidget);
        this->lobbyFinderWidget->initialize();
    });
    return * this;
}
