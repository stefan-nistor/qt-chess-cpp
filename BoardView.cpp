#include "BoardView.h"
#include <QMessageBox>

BoardView::BoardView(int uuid, int gameId) {
    this->uuid = uuid;
    this->gameId = gameId;
    this->scene = new QGraphicsScene(this);
    this->setScene(this->scene);
    this->placeTiles();
}

auto BoardView::placeTiles() -> BoardView & {
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            auto tile = new Tile(i, j);
            this->scene->addItem(tile);
            tile->setRect(j*100, i*100, 100, 100);
            this->tile_map.emplace(tile, std::make_pair(i, j));
            mat[i][j] = tile;
        }
    }
    return * this;
}

#include <iostream>
auto BoardView::mousePressEvent(QMouseEvent *event) -> void {
    auto reversed_coord = getReverseCoordinates(event->pos());
    std::cout << reversed_coord.first << " " << reversed_coord.second << '\n';
}

auto BoardView::getReverseCoordinates(QPoint pos) -> std::pair<int, int> {
    Tile * tile;
    auto scene_point = mapToScene(pos);
    auto item = getScene()->itemAt(scene_point, transform());

    tile = dynamic_cast<Tile *>(item);
    if(tile != nullptr)
        return {7 - this->tile_map[tile].first, this->tile_map[tile].second};

    auto piece = dynamic_cast<Piece *>(item);
    if(piece != nullptr){
        tile = piece->tile;
        return {7 - this->tile_map[tile].first, this->tile_map[tile].second};
    }
}

void BoardView::placePiece(int code, int row, int col) {
    if(code == 0)
        return;

    auto piece = decodePiece(code);
    piece->row = row;
    piece->col = col;
    piece->tile = mat[row][col];
    piece->setPos(col * 100, row * 100);
    this->scene->addItem(piece);
    this->piece_list.push_back(piece);
}

auto BoardView::decodePiece(int code) -> Piece *{
    auto color = (Piece::Color) (code / 10 * 10);
    auto value = (Piece::Value) (code % 10);
    return new Piece(color, value);
}

auto BoardView::fetchPiecesPositions() -> void {
    try {
        auto session = Session("game", "queryBoard");
        session.writeInt(uuid);
        session.writeInt(gameId);

        auto responseStatus = session.readInt();
        auto responseMessage = session.readString();

        if(responseStatus == 200){
            clearBoard();

            for(int i = 0; i < 8; i++){
                for(int j = 0; j < 8; j++){
                    int code = session.readInt();
                    std::cout << "i: " << i << " j: " << j << " code " << code << '\n';
                    placePiece(code, i, j);
                }
            }
        }
        else throw std::runtime_error(responseMessage.c_str());

    } catch (std::runtime_error const & e){
        QMessageBox::warning(this, "Warning", e.what());
    }
}

auto BoardView::clearBoard() -> void {
    for (auto &item: piece_list){
        this->scene->removeItem(item);
    }
}


//auto BoardView::mouseReleaseEvent(QMouseEvent *event) -> void {
//
//}
