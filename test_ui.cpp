#include <QApplication>
#include "BoardView.h"


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    BoardView app;
    app.resize(1280, 920);
    app.placeTiles();
    app.placePiece(10,1,1);
//    app.placePiece(0,0,0);
    app.show();

    return QApplication::exec();
}
