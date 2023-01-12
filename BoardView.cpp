#include "BoardView.h"
#include <QMessageBox>

BoardView::BoardView(int uuid, int gameId) {
    this->uuid = uuid;
    this->gameId = gameId;
    this->scene = new QGraphicsScene(this);
    this->setScene(this->scene);
    this->placeTiles();

    this->timer = new QTimer();
    this->timer->start(100);

    connect(this->timer, &QTimer::timeout, [this]{
        this->handlePeriodicUpdate();
    });

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

    if(!selected) {
        selected = true;
        this->startR = reversed_coord.first;
        this->startC = reversed_coord.second;
        std::cout << "init R " << this->startR << " init C " << this->startC << '\n';
//        fetchPossibleMoves();
    } else {
        selected = false;
        this->finalR = reversed_coord.first;
        this->finalC = reversed_coord.second;
        std::cout << "final R " << this->finalR << " final C " << this->finalC << '\n';

        try{
            auto session = Session("game", "movePiece");
            session.writeInt(uuid);
            session.writeInt(gameId);
            session.writeInt(startC);
            session.writeInt(startR);
            session.writeInt(finalC);
            session.writeInt(finalR);

            auto responseStatus = session.readInt();
            auto responseString = session.readString();

            if(responseStatus!=200){
                std::cout << responseString << '\n';
            }

        } catch(std::runtime_error const & e){
            cerr << e.what() << '\n';
        }

    }
    QGraphicsView::mousePressEvent(event);
}
//
//auto BoardView::mouseReleaseEvent(QMouseEvent *event) -> void {
//    auto reversed_coord = getReverseCoordinates(event->pos());
//    std::cout << "final R " << reversed_coord.first << " final C " << reversed_coord.second << '\n';
//    this->finalR = reversed_coord.first;
//    this->finalC = reversed_coord.second;
//
//    try{
//        auto session = Session("game", "movePiece");
//        session.writeInt(uuid);
//        session.writeInt(gameId);
//
//        session.writeInt(startC);
//        session.writeInt(startR);
//        session.writeInt(finalC);
//        session.writeInt(finalR);
//
//        auto responseStatus = session.readInt();
//        auto responseMessage = session.readString();
//
//        if(responseStatus !=200)
//            std::cout << responseMessage << '\n';
//
//    } catch(std::runtime_error const & e){
////        QMessageBox::warning(this, "Warning", e.what());
//        std::cout << e.what() << '\n';
//    }
//    QGraphicsView::mouseReleaseEvent(event);
//}


auto BoardView::getReverseCoordinates(QPoint pos) -> std::pair<int, int> {
    Tile * tile;
    auto scene_point = mapToScene(pos);
    auto item = getScene()->itemAt(scene_point, transform());


    tile = dynamic_cast<Tile *>(item);
    std::pair<int, int> return_value;
    if(tile != nullptr)
        if(playerColor == 20)
            return_value = {this->tile_map[tile].first, this->tile_map[tile].second};
        else return_value = {7 - this->tile_map[tile].first, this->tile_map[tile].second};

    auto piece = dynamic_cast<Piece *>(item);
    if(piece != nullptr){
        tile = piece->tile;
        if(playerColor == 20)
            return_value = {this->tile_map[tile].first, this->tile_map[tile].second};
        else return_value = {7 - this->tile_map[tile].first, this->tile_map[tile].second};
    }
    return return_value;
}

void BoardView::placePiece(int code, int row, int col) {
    if(code == 0)
        return;

    if(playerColor == 10)
        row = 7-row;

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
            for(int i = 0; i < 8; i++){
                for(int j = 0; j < 8; j++){
                    int code = session.readInt();
//                    std::cout << "i: " << i << " j: " << j << " code " << code << '\n';
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
    if(piece_list.empty())
        return;

    for (auto &item: piece_list){
        if(item->scene() != nullptr)
            this->scene->removeItem(item);
    }
}

auto BoardView::updateBoard() -> void {
    this->clearBoard();
    this->fetchPiecesPositions();
}

auto BoardView::fetchGameStatus() -> void {
    try{
        auto session = Session("game", "queryStatus");
        session.writeInt(uuid);
        session.writeInt(gameId);

        auto responseStatus = session.readInt();
        auto responseMessage = session.readString();

//        if(responseStatus!=200)
//            std::cout << responseMessage << '\n';

        if(responseStatus == 200) {
            this->playerColor = session.readInt();
            this->playerTurn = session.readInt();
            this->boardUpdateRequired = session.readInt();
            this->gameDone = session.readInt();
            this->winnerColor = session.readInt();
            this->kingInDanger = session.readInt();
        }

    } catch (std::runtime_error const & e){
        std::cerr<<e.what() << '\n';
    }
}

auto BoardView::handlePeriodicUpdate() -> void {
    fetchGameStatus();
    if(boardUpdateRequired == 1){
        updateBoard();
    }
}

auto BoardView::fetchPossibleMoves() -> void {
    try {
        auto session = Session("game", "queryPiece");
        session.writeInt(uuid);
        session.writeInt(gameId);

        auto responseStatus = session.readInt();

        auto responseMessage = session.readString();
        auto moves_list_size = session.readInt();
        if(responseStatus == 200) {
            for (int n = 0; n < moves_list_size; n++) {
                int x = session.readInt();
                int y = session.readInt();
                mat[x][y]->setHighlight();
                this->scene->itemAt(x*100, y*100, transform());

                Tile * tile;
                auto item = getScene()->itemAt(QPointF(x*100, y*100), transform());
                tile = dynamic_cast<Tile *>(item);
                if(tile != nullptr)
                    tile->setHighlight();


            }
        }
    } catch (std::runtime_error const & e){
        std::cerr << e.what() << '\n';
    }
}
