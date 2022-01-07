#pragma once

#include <QLineEdit>
#include <QNetworkAccessManager>
#include <QPushButton>
#include <QWidget>
#include <QNetworkReply>
#include <QPlainTextEdit>
#include <QLabel>

#include <common/base/basefragment.h>



#include <ui/view/waitingspinnerwidget.h>

#include <models/deskmodel.h>

class Friends : public BaseFragment{
    Q_OBJECT

private:
    QString token;



    QVBoxLayout *mainVLayout;
    QVBoxLayout *inputContainerFriends;

    WaitingSpinnerWidget *loading;

    QLabel *titleLabel;

    QLineEdit *addFriendEdit;
    QPlainTextEdit *descriptionEdit;
    QPushButton *createButton;
    QPushButton *addFriendButton;
    QNetworkAccessManager *networkManager;

        QNetworkAccessManager *addManagerFriend;

public:
    Friends();
    ~Friends();


public slots:


    void loadFriends();

    void onBackPressed();

    void addFriendButtonPressed();
    void checkNameFriend();

    void onHttpResultFriend(QNetworkReply *reply);


    void onHttpResult(QNetworkReply *reply);

    /**
     * @brief checkData
     *
     * проверка введенных данных
     * на корректность.
     */
    void checkData();
};
