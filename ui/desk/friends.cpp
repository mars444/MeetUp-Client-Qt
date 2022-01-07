#include "Friends.h"

#include "style/stylecontainer.h"
using namespace styles;
#include "screensfactory.h"

#include <QLabel>
#include <QNetworkAccessManager>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QJsonObject>
#include <QJsonDocument>
#include <QSettings>
#include <QMessageBox>

#include <ui/view/qsvgbutton.h>
#include <ui/view/waitingspinnerwidget.h>
using namespace screens;

Friends::Friends() {

    mainVLayout = new QVBoxLayout;
    QVBoxLayout *inputContainer = new QVBoxLayout;

    QHBoxLayout *titleContainer = new QHBoxLayout;
    QSvgButton *backButton = new QSvgButton(":/resc/resc/arrow_back.svg", QSize(24,24));
    titleLabel = new QLabel("Мои друзья");

    createButton = new QPushButton("Добавить друзей");


    QFrame *friendFrame = new QFrame;




    QHBoxLayout *friendContainer = new QHBoxLayout;

    QPushButton *inviteGroupButton = new QPushButton("Пригласить в группу");

    QPushButton *deleteFriendButton = new QPushButton("Удалить из друзей");


    inviteGroupButton->setStyleSheet(BUTTON_SOLID);


    deleteFriendButton->setStyleSheet(BUTTON_SOLID);

    QHBoxLayout *friendButtonContainer = new QHBoxLayout;


    friendButtonContainer->addWidget(inviteGroupButton);
     friendButtonContainer->addWidget(deleteFriendButton);




    QLabel *friendImageLabel = new QLabel("");
    QPixmap friendImage(":/resc/resc/user_circle.svg");

    friendImageLabel->setPixmap(friendImage);
    friendImageLabel->setStyleSheet(FRIEND_IMAGE);


    QLabel *friendName = new QLabel("Ablemipt");


    friendName->setStyleSheet(FRIEND_NAME_SURNAME);



    QLabel *friendOnlineStatusLabel = new QLabel("");
    QPixmap friendOnlineStatusImage(":/resc/resc/online_status_onn.svg");
    friendOnlineStatusLabel->setPixmap(friendOnlineStatusImage.scaled(15,15, Qt::KeepAspectRatio));

    friendOnlineStatusLabel->setStyleSheet(ONLINE_STATUS);

     friendContainer->setAlignment(Qt::AlignTop);


     friendContainer->addWidget(friendImageLabel);
     friendContainer->addWidget(friendName);

     friendContainer->addWidget(friendOnlineStatusLabel);

     friendContainer->addLayout(friendButtonContainer);




    QHBoxLayout *friendContainer2 = new QHBoxLayout;
    QLabel *friendImageLabel2 = new QLabel("");
    QPixmap friendImage2(":/resc/resc/user_circle.svg");
    friendImageLabel2->setPixmap(friendImage2);
    friendImageLabel2->setStyleSheet(FRIEND_IMAGE);


    QLabel *friendName2 = new QLabel("AlexAn1812");

    friendName2->setStyleSheet(FRIEND_NAME_SURNAME);


    QLabel *friendOnlineStatusLabel2 = new QLabel("");
    QPixmap friendOnlineStatusImage2(":/resc/resc/online_status_off.svg");
    friendOnlineStatusLabel2->setPixmap(friendOnlineStatusImage2.scaled(15,15, Qt::KeepAspectRatio));

    friendOnlineStatusLabel2->setStyleSheet(ONLINE_STATUS);



    QPushButton *inviteGroupButton2 = new QPushButton("Пригласить в группу");

    QPushButton *deleteFriendButton2 = new QPushButton("Удалить из друзей");


    inviteGroupButton2->setStyleSheet(BUTTON_SOLID);


    deleteFriendButton2->setStyleSheet(BUTTON_SOLID);

    QHBoxLayout *friendButtonContainer2 = new QHBoxLayout;


    friendButtonContainer2->addWidget(inviteGroupButton2);
     friendButtonContainer2->addWidget(deleteFriendButton2);



    friendContainer2->addWidget(friendImageLabel2);
    friendContainer2->addWidget(friendName2);

    friendContainer2->addWidget(friendOnlineStatusLabel2);
    friendContainer2->addLayout(friendButtonContainer2);


    friendContainer2->setAlignment(Qt::AlignTop);


    //QFrame *loadingContaiter = new QFrame;
   // loading = new WaitingSpinnerWidget(loadingContaiter, true, false);
    //loading->setColor(QT_COLOR_PRIMARY);
    //loadingContaiter->setMinimumWidth(100);


    titleLabel->setStyleSheet(TITLE_LABLE);
    connect(backButton, &QSvgButton::clicked, this, &Friends::onBackPressed);

    titleContainer->addWidget(backButton);
    titleContainer->addWidget(titleLabel);
    titleContainer->setContentsMargins(0,24,0,16);

    titleLabel->setContentsMargins(16,0,0,0);



    inputContainer->setAlignment(Qt::AlignTop);
    inputContainer->addLayout(titleContainer);
    mainVLayout->setAlignment(Qt::AlignLeft);
    mainVLayout->addLayout(inputContainer);
    mainVLayout->addLayout(friendContainer);
    mainVLayout->addLayout(friendContainer2);





    mainVLayout->addStretch();

    this->setLayout(mainVLayout);
    this->setStyleSheet(BACK_WHITE);
    this->setObjectName("fragment");

    checkData();

    networkManager = new QNetworkAccessManager();
    connect(networkManager, &QNetworkAccessManager::finished, this, &Friends::onHttpResult);
}

Friends::~Friends() {


    //delete loading;
    delete titleLabel;
    networkManager->clearAccessCache();
}

void Friends::checkData() {

}

void Friends::onBackPressed() {
    back();
}



void Friends::onHttpResult(QNetworkReply *reply) {

}

void Friends::loadFriends() {
    QJsonObject loadFriendsJson;
    QJsonObject userIDJson;
    userIDJson.insert("userID", "213564544");
    loadFriendsJson.insert("getFriends", userIDJson);

        qDebug() << "create request" << endl;



        QNetworkRequest request(QUrl(SERVER_URL + ""));
        request.setHeader(QNetworkRequest::ContentTypeHeader,
                          QStringLiteral("application/json;charset=utf-8"));
        qDebug() << "request data"<< QJsonDocument(loadFriendsJson).toJson(QJsonDocument::Compact) << endl;
        networkManager->post(
            request,
            QJsonDocument(loadFriendsJson).toJson(QJsonDocument::Compact)
        );
        qDebug() << "request send" << endl;
    }




