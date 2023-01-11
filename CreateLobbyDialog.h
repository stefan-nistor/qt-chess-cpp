#ifndef QT_CHESS_CPP_CREATELOBBYDIALOG_H
#define QT_CHESS_CPP_CREATELOBBYDIALOG_H


#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QDialogButtonBox>
#include "Drawable.h"

class CreateLobbyDialog : public QDialog{
    Q_OBJECT
private:

    QLineEdit * lobbyNameInput;
    QLayout * mainLayout;
    QDialogButtonBox * buttonBox;
    QPushButton * okButton;
    QPushButton * cancelButton;

public:

    explicit CreateLobbyDialog(QWidget * parent = 0);
    auto getLobbyString() -> const QString &;

signals:
    void okClicked();
    void cancelCLicked();

};


#endif //QT_CHESS_CPP_CREATELOBBYDIALOG_H
