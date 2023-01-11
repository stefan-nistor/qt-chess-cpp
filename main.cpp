#include <QApplication>
#include "GameWidget.h"
#include "GameView.h"
#include "MainWidget.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MainWidget app;
    app.resize(1280, 920);
    app.initialize();
    app.show();

    return QApplication::exec();
}
