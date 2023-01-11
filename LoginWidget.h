#ifndef QT_CHESS_CPP_LOGINWIDGET_H
#define QT_CHESS_CPP_LOGINWIDGET_H


#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include "Drawable.h"


class LoginWidget : public Drawable{
Q_OBJECT
private:

    int uuid = 0;

private:

    QLineEdit * usernameInput;
    QLineEdit * passwordInput;

    QPushButton * loginButton;
    QPushButton * createAccountButton;

    QLayout * mainLayout;
    QLayout * lineEditLayout;
    QLayout * pushButtonLayout;

public:

    explicit LoginWidget(QWidget *parent = nullptr) : Drawable(parent) {};

    auto create() -> Drawable & override;
    auto place() -> Drawable & override;
    auto customize() -> Drawable & override;
    auto connectWidgets() -> Drawable & override;

    static auto validateCredentials(const QString& u, const QString & p) -> bool;
    auto handlePushButton(const QString & operation) -> int;

    auto initialize() -> Drawable & override {
        this->create().place().customize().connectWidgets();
        return * this;
    }

    int getUuid() const;

signals:
    void connected();

};


#endif //QT_CHESS_CPP_LOGINWIDGET_H
