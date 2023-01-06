#ifndef QT_CHESS_CPP_MAINWIDGET_H
#define QT_CHESS_CPP_MAINWIDGET_H


#include <QWidget>
#include "Drawable.h"
#include "LoginWidget.h"
#include "LobbyFinderWidget.h"

class MainWidget : public Drawable{
private:

    int uuid = 0;
    LoginWidget * loginWidget;
    LobbyFinderWidget * lobbyFinderWidget;
    QLayout * mainLayout;

public:

    explicit MainWidget(QWidget * parent = nullptr) : Drawable(parent){};

    auto create() -> Drawable & override;
    auto place() -> Drawable & override;
    auto customize() -> Drawable & override;
    auto connectWidgets() -> Drawable & override;


};


#endif //QT_CHESS_CPP_MAINWIDGET_H
