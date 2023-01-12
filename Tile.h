#ifndef QT_CHESS_CPP_TILE_H
#define QT_CHESS_CPP_TILE_H

#include <QGraphicsRectItem>
#include <QBrush>

class Tile : public QGraphicsRectItem{
    int row, col;
    QBrush brush;

public:
    explicit Tile(int i, int j, QGraphicsItem * parent = nullptr) : QGraphicsRectItem(parent){
        this->row = i;
        this->col = j;

        brush.setStyle(Qt::SolidPattern);
        brush.setColor(this->getColor());
        this->setBrush(brush);

    }

    auto getColor() const -> QColor {
        if (col % 2 == 0) {
            if (row % 2 == 0)
                return {196, 178, 140}; //white
            else
                return {157, 128, 101}; //black
        } else {
            if (row % 2 == 0)
                return {157, 128, 101}; //black
            else
                return {196, 178, 140}; //white
        }
    }

    auto setHighlight() -> void {
//        QBrush brush;
//        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::cyan);
        this->setBrush(brush);
    }

};

#endif //QT_CHESS_CPP_TILE_H
