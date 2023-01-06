#include <QHBoxLayout>
#include <QMessageBox>
#include "LoginWidget.h"
#include "utility.h"

auto LoginWidget::create() -> Drawable & {

    this->usernameInput = new QLineEdit(this);
    this->passwordInput = new QLineEdit(this);

    this->loginButton = new QPushButton(this);
    this->createAccountButton = new QPushButton(this);

    this->mainLayout = new QVBoxLayout();
    this->lineEditLayout = new QVBoxLayout();
    this->pushButtonLayout = new QHBoxLayout();

    return *this;
}

auto LoginWidget::place() -> Drawable & {

    this->lineEditLayout->addWidget(usernameInput);
    this->lineEditLayout->addWidget(passwordInput);

    this->pushButtonLayout->addWidget(loginButton);
    this->pushButtonLayout->addWidget(createAccountButton);

    this->mainLayout->addItem(lineEditLayout);
    this->mainLayout->addItem(pushButtonLayout);

    this->setLayout(mainLayout);

    return *this;
}

auto LoginWidget::customize() -> Drawable & {

    this->setWindowTitle("Chess");

    this->usernameInput->setPlaceholderText("Username");
    this->passwordInput->setPlaceholderText("Password");
    this->passwordInput->setEchoMode(QLineEdit::Password);

    this->loginButton->setText("Login");
    this->loginButton->setDefault(true);
    this->createAccountButton->setText("Create account");

    this->mainLayout->setAlignment(Qt::AlignCenter);
    this->pushButtonLayout->setAlignment(Qt::AlignRight);
    this->lineEditLayout->setAlignment(Qt::AlignCenter);

    return *this;
}

auto LoginWidget::connectWidgets() -> Drawable & {

    connect(this->loginButton, &QPushButton::clicked, [this] {
        this->uuid = this->handlePushButton("auth");
    });

    connect(this->createAccountButton, &QPushButton::clicked, [this] {
        this->uuid = this->handlePushButton("create");
    });

    return *this;
}

auto LoginWidget::validateCredentials(const QString &u, const QString &p) -> bool {
    if (u.isEmpty() || p.isEmpty()) {
        throw std::runtime_error("Username or password cannot be empty.");
    }
}

auto LoginWidget::handlePushButton(const QString &operation) -> int {
    auto u = this->usernameInput->text();
    auto p = this->passwordInput->text();

    try {
        validateCredentials(u, p);

        writeString("user", 0);
        writeString(operation.toStdString(), 0);
        writeString(u.toStdString(), 0);
        writeString(p.toStdString(), 0);

        auto responseStatusCode = readInt(0);
        auto responseMessage = readString(0);
        auto uuid = readInt(0);

        if (responseStatusCode == 200 || responseStatusCode == 201) {
            return uuid;
        } else {
            QMessageBox::warning(this, operation, "Invalid credentials");
        }

    } catch (std::runtime_error const &e) {
        QMessageBox::warning(this, operation, e.what());
    }
    return -1;
}

int LoginWidget::getUuid() const {
    return uuid;
}



