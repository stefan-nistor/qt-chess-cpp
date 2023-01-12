#ifndef QT_CHESS_CPP_BOARDVIEW_H
#define QT_CHESS_CPP_BOARDVIEW_H

#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <unordered_map>
#include <QMouseEvent>
#include <QTimer>
#include "Tile.h"
#include "Piece.h"
#include "Session.h"

class BoardView : public QGraphicsView{
private:
    bool selected = false;
    int uuid = 0;
    int gameId = 0;
    int playerColor = -1;
    int playerTurn = -1;
    int boardUpdateRequired = -1;
    int gameDone = -1;
    int winnerColor = -1;
    int kingInDanger = -1;

    QGraphicsScene * scene;
    QTimer * timer;
    // map tile to <row , col>
    std::unordered_map<Tile *, std::pair<int, int >> tile_map;
    Tile * mat[8][8];
    std::list<Piece *> piece_list;
    int startR, startC, finalR, finalC;

public:
    explicit BoardView(int uuid = 0, int gameId = 0);

    auto getScene(){
        return this->scene;
    }

    auto placeTiles() -> BoardView &;

    auto mousePressEvent(QMouseEvent * event) -> void;
//    auto mouseReleaseEvent(QMouseEvent * event) -> void;

    auto getReverseCoordinates(QPoint pos) -> std::pair<int, int>;
    void placePiece(int code, int row, int col);
    auto decodePiece(int code) -> Piece *;

    auto fetchGameStatus() -> void;
    auto fetchPiecesPositions() -> void;

    auto clearBoard() -> void;
    auto updateBoard() -> void;
    auto handlePeriodicUpdate() -> void;
    auto fetchPossibleMoves() -> void;

};


#endif //QT_CHESS_CPP_BOARDVIEW_H
