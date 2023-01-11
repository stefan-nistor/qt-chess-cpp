#include <QHBoxLayout>
#include "CreateLobbyDialog.h"

CreateLobbyDialog::CreateLobbyDialog(QWidget *parent) {
    this->mainLayout = new QVBoxLayout();
    this->lobbyNameInput = new QLineEdit(this);
    this->lobbyNameInput->setPlaceholderText("Lobby name");
    this->setLayout(mainLayout);
    this->okButton = new QPushButton("Create", this);
    this->cancelButton = new QPushButton("Cancel", this);

    this->buttonBox = new QDialogButtonBox(Qt::Horizontal, this);

    this->buttonBox->addButton(this->cancelButton, QDialogButtonBox::RejectRole);
    this->buttonBox->addButton(this->okButton, QDialogButtonBox::AcceptRole);

    this->mainLayout->addWidget(this->lobbyNameInput);
    this->mainLayout->addWidget(this->buttonBox);

    connect(this->okButton, &QPushButton::clicked, [this]{
        emit okClicked();
    });
    connect(this->cancelButton, &QPushButton::clicked, [this]{
        emit cancelCLicked();
    });
}

#include <iostream>
auto CreateLobbyDialog::getLobbyString() -> const QString & {
    std::cout << this->lobbyNameInput->text().toStdString();
    return this->lobbyNameInput->text();
}
