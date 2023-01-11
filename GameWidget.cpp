#include "GameWidget.h"

auto GameWidget::create() -> Drawable & {

    this->mainLayout = new QHBoxLayout();
    this->controlLayout = new QVBoxLayout();
    this->boardLayout = new QGridLayout();
    this->disconnectButton = new QPushButton(this);

    this->graphicsScene = new QGraphicsScene(this);
    this->graphicsView = new QGraphicsView(this);

    return * this;
}

auto GameWidget::place() -> Drawable & {

    this->setLayout(mainLayout);

    this->mainLayout->addItem(boardLayout);
    this->mainLayout->addItem(controlLayout);

    this->controlLayout->addWidget(disconnectButton);
    this->controlLayout->setAlignment(Qt::AlignRight);
    this->controlLayout->setAlignment(Qt::AlignBottom);
    this->graphicsView->setScene(graphicsScene);

    return * this;
}

auto GameWidget::customize() -> Drawable & {
    this->disconnectButton->setText("Disconnect");
    this->graphicsScene->setBackgroundBrush(QPixmap("../images/chess_board.svg"));
    return * this;
}

auto GameWidget::connectWidgets() -> Drawable & {
    return * this;
}
