#ifndef QT_CHESS_CPP_PIECE_H
#define QT_CHESS_CPP_PIECE_H

#include <QtCore/QString>
#include <QGraphicsRectItem>
#include "Properties.h"

class Piece : public QGraphicsPixmapItem{
private:

    const QString IMAGE_PATH_PREFIX = "../images/pieces/";

    Properties::Color color;
    Properties::Type type;
    bool isDead;
    int col, row;
    QPixmap image;

public:

    Piece(Properties::Color color, Properties::Type type, int col, int row);
    auto setImage() -> void;
    auto mousePressEvent(QGraphicsSceneHoverEvent * event) -> void;
    auto mouseReleaseEvent(QGraphicsSceneHoverEvent * event) -> void;

    auto getCol() -> int {
        return col;
    }

    auto getRow() -> int {
        return row;
    }

};


#endif //QT_CHESS_CPP_PIECE_H
