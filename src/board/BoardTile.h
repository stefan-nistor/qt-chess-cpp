#ifndef QT_CHESS_CPP_BOARDTILE_H
#define QT_CHESS_CPP_BOARDTILE_H

#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QBrush>
#include "../Pieces/Piece.h"

class BoardTile : public QGraphicsRectItem {
private:
    int x;
    int y;
    int col;
    int row;
    QColor color;
    Piece *piece;

public:
    explicit BoardTile(int x, int y, QColor color = nullptr, QGraphicsItem *parent = nullptr) : x(x), y(y),
                                                                                                color(color),
                                                                                                QGraphicsRectItem(
                                                                                                        parent) {

        this->piece = nullptr;
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(color);
        this->setBrush(brush);
    };

    inline auto getCol() const -> int {
        return this->x;
    }

    inline auto getRow() const -> int {
        return this->y;
    }

    inline auto setPiece(Piece *piece) -> void {
        this->piece = piece;
        this->piece->setZValue(100);
        this->piece->setPos(x * 100, y * 100);
    }

    void setSceneX(int x) {
        this->x = x;
    }

    void setSceneY(int y) {
        this->y = y;
    }

    auto getSceneX() -> int {
        return this->x;
    }

    auto getSceneY() -> int {
        return this->y;
    }

};


#endif //QT_CHESS_CPP_BOARDTILE_H
