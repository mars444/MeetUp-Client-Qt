#include "Group.h"

#include "style/stylecontainer.h"
using namespace styles;
#include "screensfactory.h"

#include "nlohmann/json.hpp"
#include <iostream>
#include <set>


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

Group::Group() {

    mainVLayout = new QVBoxLayout;
    QVBoxLayout *inputContainer = new QVBoxLayout;

    QHBoxLayout *titleContainer = new QHBoxLayout;
    QSvgButton *backButton = new QSvgButton(":/resc/resc/arrow_back.svg", QSize(24,24));
    GrouptitleLabel = new QLabel("Group 1");

    createButton = new QPushButton("Добавить друзей");



    QHBoxLayout *GroupContainerMain = new QHBoxLayout;



    QLabel *groupEventDateLabelMain = new QLabel("Дата");
    QLabel *groupEventMain = new QLabel("Начало встречи");
    QLabel *groupEventendMain = new QLabel("Конец встречи");


    groupEventDateLabelMain->setStyleSheet(SETTINGS_LABEL);
    groupEventMain->setStyleSheet(SETTINGS_LABEL);
    groupEventendMain->setStyleSheet(SETTINGS_LABEL);


    GroupContainerMain->addWidget(groupEventDateLabelMain);
    GroupContainerMain->addWidget(groupEventMain);
    GroupContainerMain->addWidget(groupEventendMain);



    QHBoxLayout *groupButtonsContainer = new QHBoxLayout;

    groupList = new QPushButton("Участники");

    groupMeets = new QPushButton("Встречи");

      connect(groupList, &QPushButton::clicked, this, &Group::groupListPressed);

        connect(groupMeets, &QPushButton::clicked, this, &Group::groupMeetsPressed);



    groupMeets->setStyleSheet(BUTTON_SOLID);
    groupList->setStyleSheet(BUTTON_DISABLED);


    groupButtonsContainer->addWidget(groupMeets);
      groupButtonsContainer->addWidget(groupList);


    QHBoxLayout *GroupContainer = new QHBoxLayout;

    groupEventDateLabel = new QLabel("12-12-21");
    groupEventDateLabel->setStyleSheet(SETTINGS_LABEL);
    groupEventstart = new QLabel("11:00");
     groupEventstart->setStyleSheet(SETTINGS_LABEL);
    groupEventend = new QLabel("15:00");
     groupEventend->setStyleSheet(SETTINGS_LABEL);

    GroupContainer->addWidget(groupEventDateLabel);
    GroupContainer->addWidget(groupEventstart);
    GroupContainer->addWidget(groupEventend);









    //QFrame *loadingContaiter = new QFrame;
   // loading = new WaitingSpinnerWidget(loadingContaiter, true, false);
    //loading->setColor(QT_COLOR_PRIMARY);
    //loadingContaiter->setMinimumWidth(100);


    GrouptitleLabel->setStyleSheet(TITLE_LABLE);
    connect(backButton, &QSvgButton::clicked, this, &Group::onBackPressed);

    titleContainer->addWidget(backButton);
    titleContainer->addWidget(GrouptitleLabel);
    titleContainer->setContentsMargins(0,24,0,16);

    GrouptitleLabel->setContentsMargins(16,0,0,0);



    inputContainer->setAlignment(Qt::AlignTop);
    inputContainer->addLayout(titleContainer);

    QVBoxLayout *stackMeets = new QVBoxLayout;

    stackMeets->addLayout(GroupContainerMain);
    stackMeets->addLayout(GroupContainer);


    stackList = new QVBoxLayout;

    stack = new QStackedWidget;

    QFrame *stackMeetsWidget = new QFrame;
    stackMeetsWidget->setLayout(stackMeets);


   stackListWidget = new QFrame;
   stackListWidget->setLayout(stackList);


    stack->addWidget(stackMeetsWidget);
    stack->addWidget(stackListWidget);
    stack->setCurrentIndex(0);


    mainVLayout->setAlignment(Qt::AlignLeft);

    mainVLayout->addLayout(inputContainer);

    mainVLayout->addLayout(groupButtonsContainer);

    mainVLayout->addWidget(stack);








    mainVLayout->setAlignment(Qt::AlignTop);
    mainVLayout->addStretch();

    this->setLayout(mainVLayout);
    this->setStyleSheet(BACK_WHITE);
    this->setObjectName("fragment");


    networkManagerGetList = new QNetworkAccessManager();
    connect(networkManagerGetList, &QNetworkAccessManager::finished, this, &Group::onHttpResultnetworkManagerGetList);

    networkManagerGetMeets = new QNetworkAccessManager();
    connect(networkManagerGetMeets, &QNetworkAccessManager::finished, this, &Group::onHttpResultnetworkManagerGetMeets);

    networkManagerDeleteFriendFromGroup = new QNetworkAccessManager();
    connect(networkManagerDeleteFriendFromGroup, &QNetworkAccessManager::finished, this, &Group::onHttpResultnetworkManagerDeleteFriendFromGroup);


  getMeets();
}

Group::~Group() {


    //delete loading;
    delete GrouptitleLabel;
    //networkManager->clearAccessCache();
}

void Group::getMeets() {


    QJsonObject getMeetsJson;
    QJsonObject bodyJson;
    bodyJson.insert("groupName", (GrouptitleLabel->text()));

    getMeetsJson.insert("getMeets", bodyJson);

        qDebug() << "create request" << endl;



        QNetworkRequest request(QUrl(SERVER_URL + ""));
        request.setHeader(QNetworkRequest::ContentTypeHeader,
                          QStringLiteral("application/json"));
        qDebug() << "request data"<< QJsonDocument(getMeetsJson).toJson(QJsonDocument::Compact) << endl;
        networkManagerGetMeets->post(
            request,
            QJsonDocument(getMeetsJson).toJson(QJsonDocument::Compact)
        );
        qDebug() << "request send" << endl;


}

void Group::onBackPressed() {
    back();
}


void Group::groupMeetsPressed() {

    getMeets();


    QHBoxLayout *layout2 = friendContainer2;
        while (layout2->count() != 0) {
            QLayoutItem *item = layout2->takeAt(0);
            delete item->widget();
        }


    QVBoxLayout *layout = stackList;
        while (layout->count() != 0) {
            QLayoutItem *item = layout->takeAt(0);
            delete item->widget();
            delete item;
        }



    groupMeets->setStyleSheet(BUTTON_SOLID);
    groupList->setStyleSheet(BUTTON_DISABLED);
        stack->setCurrentIndex(0);
}


void Group::groupListPressed() {


    groupMeets->setStyleSheet(BUTTON_DISABLED);
    groupList->setStyleSheet(BUTTON_SOLID);
        stack->setCurrentIndex(1);


        QJsonObject getGroupMembersJson;
        QJsonObject bodyJson;

        bodyJson.insert("groupName", GrouptitleLabel->text());

        getGroupMembersJson.insert("getGroupMembers", bodyJson);

            qDebug() << "create request" << endl;



            QNetworkRequest request(QUrl(SERVER_URL + ""));
            request.setHeader(QNetworkRequest::ContentTypeHeader,
                              QStringLiteral("application/json"));
            qDebug() << "request data"<< QJsonDocument(getGroupMembersJson).toJson(QJsonDocument::Compact) << endl;
            networkManagerGetList->post(
                request,
                QJsonDocument(getGroupMembersJson).toJson(QJsonDocument::Compact)
            );
            qDebug() << "request send" << endl;


}




void Group::onHttpResult(QNetworkReply *reply) {

}

void Group::onHttpResultnetworkManagerGetList(QNetworkReply *reply) {

    str = "{\"userID\":\"213564544\",\"Friends\":[\"Misha1991\", \"Igor\",  \"Alex\",  \"qwe\", \"piotr\"]}";

    nlohmann::json j = nlohmann::json::parse(str);


    std::cout << j.size() << std::endl;
    std::cout << j << std::endl;

    nlohmann::json::iterator it = j.begin();
    std::cout << it.key() << std::endl;

    std::string key = it.key();

    nlohmann::json value = j[key];

    std::cout << value << std::endl;


    std::set<std::string> s_friends;

    for (auto& element : j["Friends"]) {




        friendContainer2 = new QHBoxLayout;
        QLabel *friendImageLabel2 = new QLabel("");
        QPixmap friendImage2(":/resc/resc/user_circle.svg");
        friendImageLabel2->setPixmap(friendImage2);
        friendImageLabel2->setStyleSheet(FRIEND_IMAGE);





        friendName2 = new QLabel(QString::fromStdString(element.dump()).remove('"'));

        friendName2->setStyleSheet(FRIEND_NAME_SURNAME);


        QLabel *friendOnlineStatusLabel2 = new QLabel("");
        QPixmap friendOnlineStatusImage2(":/resc/resc/online_status_off.svg");
        friendOnlineStatusLabel2->setPixmap(friendOnlineStatusImage2.scaled(15,15, Qt::KeepAspectRatio));

        friendOnlineStatusLabel2->setStyleSheet(ONLINE_STATUS);



        QPushButton *inviteGroupButton2 = new QPushButton("Пригласить в группу");

        QPushButton *deleteFriendButton2 = new QPushButton("Удалить из группы");


        inviteGroupButton2->setStyleSheet(BUTTON_SOLID);


        deleteFriendButton2->setStyleSheet(BUTTON_SOLID);

        QHBoxLayout *friendButtonContainer2 = new QHBoxLayout;


        //friendButtonContainer2->addWidget(inviteGroupButton2);
        friendButtonContainer2->addWidget(deleteFriendButton2);



        friendContainer2->addWidget(friendImageLabel2);
        friendContainer2->addWidget(friendName2);

        friendContainer2->addWidget(friendOnlineStatusLabel2);
        friendContainer2->addLayout(friendButtonContainer2);

       connect(deleteFriendButton2, &QPushButton::clicked, this, &Group::deleteFriendPressed);






        stackList->addLayout(friendContainer2);


        mButtonToLayoutMap.insert(deleteFriendButton2,friendContainer2);

}
}

void Group::onHttpResultnetworkManagerGetMeets(QNetworkReply *reply) {

}

void Group::onHttpResultnetworkManagerDeleteFriendFromGroup(QNetworkReply *reply) {

}

void Group::deleteFriendPressed() {


    QPushButton *button = qobject_cast<QPushButton*>(sender());

    QHBoxLayout *layout = mButtonToLayoutMap.take(button);


    QWidget * widget =  layout->itemAt(1)->widget();



    QLabel* xxx = dynamic_cast<QLabel*>(widget);


    QString aaa = xxx->text();

    QJsonObject deleteFriendJson;
        QJsonObject bodyJson;
        bodyJson.insert("userID", "213564544");
        bodyJson.insert("friendName", (aaa));
        bodyJson.insert("groupName", (GrouptitleLabel->text()));
        deleteFriendJson.insert("deleteFriendFromGroup", bodyJson);

            qDebug() << "create request" << endl;



            QNetworkRequest request(QUrl(SERVER_URL + ""));
            request.setHeader(QNetworkRequest::ContentTypeHeader,
                              QStringLiteral("application/json;charset=utf-8"));
            qDebug() << "request data"<< QJsonDocument(deleteFriendJson).toJson(QJsonDocument::Compact) << endl;
            networkManagerDeleteFriendFromGroup->post(
                request,
                QJsonDocument(deleteFriendJson).toJson(QJsonDocument::Compact)
            );
            qDebug() << "request send" << endl;

    while (layout->count() != 0) {
        QLayoutItem *item = layout->takeAt(0);
        delete item->widget();
        delete item;
    }

    delete button;
    delete layout;

}

void Group::loadGroup() {

}




