#include <iostream>
#include "Piece.h"

Piece::Piece(Properties::Color color, Properties::Type type, int col, int row){
    this->color = color;
    this->type = type;
    this->col = col;
    this->row = row;
    this->setImage();
    this->setPixmap(image);

    this->setPos(col * 100, (7-row) * 100);


}

auto Piece::setImage() -> void {
    QString color, type;

    switch(this->color){
        case Properties::White: color = ""; break;
        case Properties::Black: color = "1"; break;
    }

    switch(this->type){
        case Properties::Pawn: type = "0";
            break;
        case Properties::Rook: type = "1";
            break;
        case Properties::Bishop: type = "2";
            break;
        case Properties::Knight: type = "3";
            break;
        case Properties::Queen: type = "4";
            break;
        case Properties::King: type = "5";
            break;
    }

    this->image = QPixmap(IMAGE_PATH_PREFIX + type + color + ".png");
}
