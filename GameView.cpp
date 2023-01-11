#include "GameView.h"

GameView::GameView() {
    this->graphicsScene = new QGraphicsScene(this);

    this->board = new Board();

    this->setScene(graphicsScene);

    auto pieces = this->board->getPieces();
    for (const auto &item: pieces){
        this->scene()->addItem(item);
    }

    this->scene()->addItem(board);
    board->draw();
    this->generatePieces();
}

void GameView::generatePieces() {
    for(int i = 0; i < 8; i++) {
        auto white_pawn = new Piece(Properties::Color::White, Properties::Type::Pawn, i, 1);
        this->scene()->addItem(white_pawn);

        auto black_pawn = new Piece(Properties::Color::Black, Properties::Type::Pawn, i, 6);
        this->scene()->addItem(black_pawn);
    }

    this->scene()->addItem(new Piece(Properties::Color::White, Properties::Type::Rook, 0, 0));
    this->scene()->addItem(new Piece(Properties::Color::White, Properties::Type::Rook, 7, 0));
    this->scene()->addItem(new Piece(Properties::Color::Black, Properties::Type::Rook, 0, 7));
    this->scene()->addItem(new Piece(Properties::Color::Black, Properties::Type::Rook, 7, 7));

    this->scene()->addItem(new Piece(Properties::Color::White, Properties::Type::Knight, 1, 0));
    this->scene()->addItem(new Piece(Properties::Color::White, Properties::Type::Knight, 6, 0));
    this->scene()->addItem(new Piece(Properties::Color::Black, Properties::Type::Knight, 1, 7));
    this->scene()->addItem(new Piece(Properties::Color::Black, Properties::Type::Knight, 6, 7));

    this->scene()->addItem(new Piece(Properties::Color::White, Properties::Type::Bishop, 2, 0));
    this->scene()->addItem(new Piece(Properties::Color::White, Properties::Type::Bishop, 5, 0));
    this->scene()->addItem(new Piece(Properties::Color::Black, Properties::Type::Bishop, 2, 7));
    this->scene()->addItem(new Piece(Properties::Color::Black, Properties::Type::Bishop, 5, 7));

    this->scene()->addItem(new Piece(Properties::Color::White, Properties::Type::Queen, 3, 0));
    this->scene()->addItem(new Piece(Properties::Color::Black, Properties::Type::Queen, 3, 7));

    this->scene()->addItem(new Piece(Properties::Color::White, Properties::Type::King, 4, 0));
    this->scene()->addItem(new Piece(Properties::Color::Black, Properties::Type::King, 4, 7));

}

void GameView::placePiece(Piece * piece, int boardRow, int boardCol) {
    board->getBoardTile(boardRow, boardCol).setPiece(piece);

}

