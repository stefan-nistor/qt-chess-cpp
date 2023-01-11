#ifndef QT_CHESS_CPP_GAMEVIEW_H
#define QT_CHESS_CPP_GAMEVIEW_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include "src/board/Board.h"
#include "src/Pieces/Piece.h"

class GameView : public QGraphicsView{
    Q_OBJECT
private:
    QGraphicsScene * graphicsScene;
public:

    GameView();
    Board * board;
    void generatePieces();
    void placePiece(Piece * piece, int boardRow, int boardCol);

};


#endif //QT_CHESS_CPP_GAMEVIEW_H
