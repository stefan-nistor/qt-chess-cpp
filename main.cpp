#include <QApplication>
#include "MainWidget.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    LobbyFinderWidget app;

    app.initialize();
    app.resize(1280, 720);
    app.show();

    return QApplication::exec();
}
