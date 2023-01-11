#ifndef QT_CHESS_CPP_BOARD_H
#define QT_CHESS_CPP_BOARD_H

#include <QGraphicsRectItem>
#include "BoardTile.h"
#include "../Pieces/Piece.h"

class Board : public QGraphicsRectItem{
private:
    QList<BoardTile *> boardTiles;
    QList<Piece * > pieces;
    QGraphicsScene * parent;
public:

    Board(QGraphicsScene * parent = nullptr);

    auto draw() -> Board &;
    auto placeBoardFields(int x, int num) -> Board &;
    static auto determineFieldColor(int row, int column) -> QColor;

    auto getBoardTile(int row, int col) -> BoardTile &;

    auto generatePieces() -> Board &;
    auto placePieces() -> Board &;

    auto getScene(){
        return this->parent;
    }

    auto getPieces(){
        return this->pieces;
    }

    auto addPiece(Piece * piece){
        this->pieces.append(piece);
    }

};


#endif //QT_CHESS_CPP_BOARD_H
