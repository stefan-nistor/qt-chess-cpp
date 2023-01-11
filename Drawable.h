#ifndef QT_CHESS_CPP_DRAWABLE_H
#define QT_CHESS_CPP_DRAWABLE_H

#include <QWidget>

class Drawable : public QWidget {
    Q_OBJECT
public:

    explicit Drawable(QWidget *parent = nullptr) : QWidget(parent) {}

    virtual auto create() -> Drawable & = 0;

    virtual auto place() -> Drawable & = 0;

    virtual auto customize() -> Drawable & = 0;

    virtual auto connectWidgets() -> Drawable & = 0;

    virtual auto initialize() -> Drawable & {
        this->create().place().customize().connectWidgets();
        return *this;
    }
};

#endif //QT_CHESS_CPP_DRAWABLE_H
