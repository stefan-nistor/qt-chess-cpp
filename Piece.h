#ifndef QT_CHESS_CPP_PIECE_H
#define QT_CHESS_CPP_PIECE_H

#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include "Tile.h"


class Piece : public QGraphicsPixmapItem{
public:
    enum class Color {
        None = 0,
        White = 10,
        Black = 20
    };

    enum class Value {
        None = -1,
        Pawn = 0,
        Knight = 1,
        Bishop = 2,
        Rook = 3,
        Queen = 4,
        King = 5
    };

    const QString IMAGE_PATH_PREFIX = "../images/pieces/";

    int row, col;
    Tile * tile;

    auto getImagePath(Color color, Value value){
        QString c, type;

        switch(color){
            case Color::White: c = "1"; break;
            case Color::Black: c = "2"; break;
            case Color::None:
                break;
        }

        switch(value){
            case Value::Pawn: type = "0";
                break;
            case Value::Rook: type = "3";
                break;
            case Value::Bishop: type = "2";
                break;
            case Value::Knight: type = "1";
                break;
            case Value::Queen: type = "4";
                break;
            case Value::King: type = "5";
                break;
            case Value::None:
                break;
        }
        QString path = IMAGE_PATH_PREFIX + c+type + ".png";
        return path;
    }


    explicit Piece(Color color, Value value, int row = 0, int col = 0){
        this->row = row;
        this->col = col;
        this->setPixmap(QPixmap(getImagePath(color, value)));
        this->setFlag(ItemIsMovable);
        this->setFlag(ItemSendsGeometryChanges);
    }

};


#endif //QT_CHESS_CPP_PIECE_H
