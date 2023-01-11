#ifndef QT_CHESS_CPP_GAMEWIDGET_H
#define QT_CHESS_CPP_GAMEWIDGET_H


#include <QPushButton>
#include <QGridLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsLayout>

#include "Drawable.h"

class GameWidget : public Drawable{
private:
    QLayout * boardLayout;
    QLayout * mainLayout;
    QLayout * controlLayout;
    QPushButton * disconnectButton;
    QGraphicsScene * graphicsScene;
    QGraphicsView * graphicsView;

public:

    auto create() -> Drawable & override;
    auto place() -> Drawable & override;
    auto customize() -> Drawable & override;
    auto connectWidgets() -> Drawable & override;


};


#endif //QT_CHESS_CPP_GAMEWIDGET_H
