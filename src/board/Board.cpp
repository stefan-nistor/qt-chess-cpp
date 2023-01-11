#include "Board.h"
#include "BoardTile.h"

Board::Board(QGraphicsScene * parent) {
    setRect(0, 0, 800, 800);
    this->parent = parent;
}


auto Board::draw() -> Board & {
    for(int i = 0; i < 8; i++){
        placeBoardFields(i * 100, i);
    }
    return *this;
}

auto Board::placeBoardFields(int x, int col) -> Board & {
    for (int row = 0; row < 8; row++) {
        auto tile = new BoardTile(col, row, determineFieldColor(row, col), this);
        tile->setRect(x, row * 100, 100, 100);
        tile->setSceneX(x);
        tile->setSceneY(row * 100);
        this->boardTiles.append(tile);
    }
    return *this;
}

auto Board::determineFieldColor(int row, int column) -> QColor {
    if (column % 2 == 0) {
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

auto Board::generatePieces() -> Board & {
    for(int i = 0; i < 8; i++){
        auto white_pawn = new Piece(Properties::Color::White, Properties::Type::Pawn, i, 1);
        this->getBoardTile(1, i).setPiece(white_pawn);
        this->pieces.append(white_pawn);

        auto black_pawn = new Piece(Properties::Color::Black, Properties::Type::Pawn, i, 8);
        this->getBoardTile(7, i).setPiece(white_pawn);
        this->pieces.append(black_pawn);
    }
    return * this;
}

auto Board::placePieces() -> Board &{
    for(int i = 0; i < 8; i++){

    }
    return * this;
}

auto Board::getBoardTile(int row, int col) -> BoardTile & {
    for(auto tile : boardTiles){
        if(tile->getRow() == row && tile->getCol() == col )
            return * tile;
    }
}


