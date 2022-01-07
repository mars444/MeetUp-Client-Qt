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

    QHash<QPushButton*,QHBoxLayout*> mButtonToLayoutMap;



    std::string str;

    QMovie *movieloading;

    QLabel *centerContainer;

    QVBoxLayout *mainVLayout;

    QVBoxLayout *inputContainerFriends;

    WaitingSpinnerWidget *loading;

    QLabel *titleLabel;

    QHBoxLayout *friendContainer2;

    QPushButton *inviteGroupButton2;
    QPushButton *deleteFriendButton2;

    QLabel *friendImageLabel2;


    QPushButton *addFriendButton;
    QLineEdit *addFriendEdit;
    QPlainTextEdit *descriptionEdit;
    QPushButton *createButton;

    QNetworkAccessManager *networkManager;

        QNetworkAccessManager *addManagerFriend;

public:
    Friends();
    ~Friends();

     QLabel *friendName2;


public slots:


    void loadFriends();

    void onBackPressed();

    void deleteFriendPressed();



    void addFriendButtonPressed();
    void checkNameFriend();

    void onHttpResultFriend(QNetworkReply *reply);


    void onHttpResult(QNetworkReply *reply);

    void onHttpResultDeleteFriend(QNetworkReply *reply);


    /**
     * @brief checkData
     *
     * проверка введенных данных
     * на корректность.
     */
    void checkData();
};
