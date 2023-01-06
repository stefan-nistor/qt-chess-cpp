#include "MainWidget.h"

auto MainWidget::create() -> Drawable & {

    this->loginWidget = new LoginWidget(this);

    return * this;
}

auto MainWidget::place() -> Drawable & {
    return * this;
}

auto MainWidget::customize() -> Drawable & {
    return * this;
}

auto MainWidget::connectWidgets() -> Drawable & {
    return * this;
}
