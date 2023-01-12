#ifndef QT_CHESS_CPP_BOARDVIEW_H
#define QT_CHESS_CPP_BOARDVIEW_H

#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <unordered_map>
#include <QMouseEvent>
#include "Tile.h"
#include "Piece.h"
#include "Session.h"

class BoardView : public QGraphicsView{
private:
    int uuid = 0;
    int gameId = 0;
    QGraphicsScene * scene;
    std::unordered_map<Tile *, std::pair<int, int >> tile_map;
    Tile * mat[8][8];
    std::list<Piece *> piece_list;

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

    auto fetchPiecesPositions() -> void;

    auto clearBoard() -> void;
};


#endif //QT_CHESS_CPP_BOARDVIEW_H
