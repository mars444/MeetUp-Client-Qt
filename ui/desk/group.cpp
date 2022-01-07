#include "Group.h"
#include "Groups.h"

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
#include <QJsonArray>

#include <iostream>
#include <set>

#include <ui/view/qsvgbutton.h>
#include <ui/view/waitingspinnerwidget.h>
using namespace screens;

#include "ui/auth/user_data.h"


Group::Group() {

    std::string IDstd = GetId();

    ID_QSTRING = QString::fromUtf8(IDstd.c_str());

    std::string GroupTitil = GetGroupTitle();

    GROUP_TITLE_QSTRING = QString::fromUtf8(GroupTitil.c_str());

    mainVLayout = new QVBoxLayout;
    QVBoxLayout *inputContainer = new QVBoxLayout;

    QHBoxLayout *titleContainer = new QHBoxLayout;
    QSvgButton *backButton = new QSvgButton(":/resc/resc/arrow_back.svg", QSize(24,24));
    GrouptitleLabel = new QLabel(GROUP_TITLE_QSTRING);

    createButton = new QPushButton(tr("Add Friends"));



    QHBoxLayout *GroupContainerMain = new QHBoxLayout;



    QLabel *groupEventDateLabelMain = new QLabel(tr("Date"));
    QLabel *groupEventMain = new QLabel(tr("Meeting start"));
    QLabel *groupEventendMain = new QLabel(tr("meeting end"));


    groupEventDateLabelMain->setStyleSheet(SETTINGS_LABEL);
    groupEventMain->setStyleSheet(SETTINGS_LABEL);
    groupEventendMain->setStyleSheet(SETTINGS_LABEL);


    //GroupContainerMain->addWidget(groupEventDateLabelMain);
    GroupContainerMain->addWidget(groupEventMain);
    GroupContainerMain->addWidget(groupEventendMain);



    QHBoxLayout *groupButtonsContainer = new QHBoxLayout;

    groupList = new QPushButton(tr("Members"));

    groupMeets = new QPushButton(tr("Meets"));

    groupDelete = new QPushButton(tr("Delete group  "));


    QPixmap pixmapgroupDelete(":/resc/resc/cross.svg");
    QIcon ButtonIcongroupDelete(pixmapgroupDelete);

    groupDelete->setIcon(ButtonIcongroupDelete);
    groupDelete-> setLayoutDirection ( Qt :: RightToLeft );
    groupDelete-> setStyleSheet("text-align: right");
    groupDelete->setIconSize(QSize(20,20));

      connect(groupList, &QPushButton::clicked, this, &Group::groupListPressed);

      connect(groupMeets, &QPushButton::clicked, this, &Group::groupMeetsPressed);

      connect(groupDelete, &QPushButton::clicked, this, &Group::groupDeletePressed);


    groupDelete->setStyleSheet(BUTTON_PROFILE_RED);

    groupDelete->setMaximumWidth(180);



    groupMeets->setStyleSheet(BUTTON_SOLID);
    groupList->setStyleSheet(BUTTON_DISABLED);


    groupButtonsContainer->addWidget(groupMeets);

     groupButtonsContainer->addWidget(groupList);

     groupButtonsContainer->addWidget(groupDelete);

      QHBoxLayout *daysButtonsContainer = new QHBoxLayout;
      QDate date =   QDate::currentDate();


      day1Button = new QPushButton(date.toString("dd-MM-yyyy"));
      day2Button = new QPushButton(date.addDays(1).toString("dd-MM-yyyy"));
      day3Button = new QPushButton(date.addDays(2).toString("dd-MM-yyyy"));
      day4Button = new QPushButton(date.addDays(3).toString("dd-MM-yyyy"));
      day5Button = new QPushButton(date.addDays(4).toString("dd-MM-yyyy"));
      day6Button = new QPushButton(date.addDays(5).toString("dd-MM-yyyy"));
      day7Button = new QPushButton(date.addDays(6).toString("dd-MM-yyyy"));

      day1Button->setStyleSheet(BUTTON_SOLID);
      day2Button->setStyleSheet(BUTTON_DISABLED);
      day3Button->setStyleSheet(BUTTON_DISABLED);
      day4Button->setStyleSheet(BUTTON_DISABLED);
      day5Button->setStyleSheet(BUTTON_DISABLED);
      day6Button->setStyleSheet(BUTTON_DISABLED);
      day7Button->setStyleSheet(BUTTON_DISABLED);

      daysButtonsContainer->addWidget(day1Button);
      daysButtonsContainer->addWidget(day2Button);
      daysButtonsContainer->addWidget(day3Button);
      daysButtonsContainer->addWidget(day4Button);
      daysButtonsContainer->addWidget(day5Button);
      daysButtonsContainer->addWidget(day6Button);
      daysButtonsContainer->addWidget(day7Button);

      connect(day1Button, &QPushButton::clicked, this, &Group::getIventsDatePressed);
      connect(day2Button, &QPushButton::clicked, this, &Group::getIventsDatePressed);
      connect(day3Button, &QPushButton::clicked, this, &Group::getIventsDatePressed);
      connect(day4Button, &QPushButton::clicked, this, &Group::getIventsDatePressed);
      connect(day5Button, &QPushButton::clicked, this, &Group::getIventsDatePressed);
      connect(day6Button, &QPushButton::clicked, this, &Group::getIventsDatePressed);
      connect(day7Button, &QPushButton::clicked, this, &Group::getIventsDatePressed);


    QHBoxLayout *GroupContainer = new QHBoxLayout;

    groupEventDateLabel = new QLabel("12-12-21");
    groupEventDateLabel->setStyleSheet(SETTINGS_LABEL);
    groupEventstart = new QLabel("11:00");
     groupEventstart->setStyleSheet(SETTINGS_LABEL);
    groupEventend = new QLabel("15:00");
     groupEventend->setStyleSheet(SETTINGS_LABEL);

    //GroupContainer->addWidget(groupEventDateLabel);
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

    titleContainer->setAlignment(Qt::AlignCenter);

    GrouptitleLabel->setContentsMargins(16,0,0,0);



    inputContainer->setAlignment(Qt::AlignTop);
    inputContainer->addLayout(titleContainer);

    QVBoxLayout *stackMeets = new QVBoxLayout;

    stackMeets->addLayout(daysButtonsContainer);
    stackMeets->addLayout(GroupContainerMain);

    stackMeets->addLayout(GroupContainer);


    stackList = new QVBoxLayout;

    stack = new QStackedWidget;

    QFrame *stackMeetsWidget = new QFrame;
    stackMeetsWidget->setLayout(stackMeets);


   stackListWidget = new QFrame;
   stackListWidget->setLayout(stackList);

   stackList->setAlignment(Qt::AlignCenter);


    stack->addWidget(stackMeetsWidget);
    stack->addWidget(stackListWidget);
    stack->setCurrentIndex(0);


    mainVLayout->setAlignment(Qt::AlignLeft);
    inputContainer->setAlignment(Qt::AlignTop);
    groupButtonsContainer->setAlignment(Qt::AlignTop);
    daysButtonsContainer->setAlignment(Qt::AlignTop);
    stackList->setAlignment(Qt::AlignTop);
    stackMeets->setAlignment(Qt::AlignTop);

    mainVLayout->addLayout(inputContainer);

    mainVLayout->addLayout(groupButtonsContainer);



    mainVLayout->addWidget(stack);








    mainVLayout->setAlignment(Qt::AlignTop);
    mainVLayout->addStretch();

    this->setLayout(mainVLayout);
    this->setStyleSheet(BACK_WHITE);
    this->setObjectName("fragment");


    networkManagerloadFriends = new QNetworkAccessManager();
    connect(networkManagerloadFriends, &QNetworkAccessManager::finished, this, &Group::onHttpResultnetworkManagerGetList);

    networkManagerGetMeets = new QNetworkAccessManager();
    connect(networkManagerGetMeets, &QNetworkAccessManager::finished, this, &Group::onHttpResultnetworkManagerGetMeets);

    networkManagerDeleteFriendFromGroup = new QNetworkAccessManager();
    connect(networkManagerDeleteFriendFromGroup, &QNetworkAccessManager::finished, this, &Group::onHttpResultnetworkManagerDeleteFriendFromGroup);

    networkManagerDeleteGroup = new QNetworkAccessManager();
    connect(networkManagerDeleteGroup, &QNetworkAccessManager::finished, this, &Group::onHttpResultDeleteGroup);



  getMeets();
  loadFriends();
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



    groupMeets->setStyleSheet(BUTTON_SOLID);

    groupList->setStyleSheet(BUTTON_DISABLED);

    stack->setCurrentIndex(0);

}


void Group::groupListPressed() {


    groupMeets->setStyleSheet(BUTTON_DISABLED);

    groupList->setStyleSheet(BUTTON_SOLID);

    stack->setCurrentIndex(1);






}


void Group::loadFriends() {

    //TEST get_group_data: {"get_data_group":{"title":"Texnosrac"}}



    QJsonObject loadFriendsGroupJson;
    QJsonObject usernameGroupJson;

   // nlohmann::json aaa = nlohmann::json::parse(loadFriendsJson);

    usernameGroupJson.insert("title", GROUP_TITLE_QSTRING);
    loadFriendsGroupJson.insert("get_data_group", usernameGroupJson);

        qDebug() << "create request" << endl;



        QNetworkRequest request(QUrl(SERVER_URL + ""));

        request.setRawHeader("JSON_DATA", QJsonDocument(loadFriendsGroupJson).toJson(QJsonDocument::Compact));

        request.setHeader(QNetworkRequest::ContentTypeHeader,
                          QStringLiteral("application/json;charset=utf-8"));
        qDebug() << "request data"<< QJsonDocument(loadFriendsGroupJson).toJson(QJsonDocument::Compact) << endl;
        networkManagerloadFriends->post(
            request,
            QJsonDocument(loadFriendsGroupJson).toJson(QJsonDocument::Compact)
        );
        qDebug() << "request send" << endl;
    }




void Group::onHttpResult(QNetworkReply *reply) {

}

void Group::onHttpResultnetworkManagerGetList(QNetworkReply *reply) {

    //str = "{\"userID\":\"213564544\",\"Friends\":[\"66666\", \"Igor\",  \"Alex\",  \"qwe\", \"piotr\"]}";



    qDebug() << "http finished" << endl;

    if(!reply->error()) {
        QByteArray resp = reply->readAll();
        qDebug() <<"ETO OTVET SERVERA get_data_group :  " + resp  << endl;
        QJsonDocument doc = QJsonDocument::fromJson(resp);
        QJsonObject obj;

        std::string str = resp.toStdString();


        nlohmann::json j = nlohmann::json::parse(str);

        nlohmann::json::iterator it = j.begin();

        std::string key = it.key();

        nlohmann::json value = j[key];

        for (auto& element : value) {

            nlohmann::json members = element["members"];

            for (auto& member : members) {

                friendContainer2 = new QHBoxLayout;
                QLabel *friendImageLabel2 = new QLabel("");
                QPixmap friendImage2(":/resc/resc/user_circle.svg");
                friendImageLabel2->setPixmap(friendImage2);
                friendImageLabel2->setStyleSheet(FRIEND_IMAGE);

                friendName2 = new QLabel(QString::fromStdString(member.dump()).remove('"'));

                qDebug() << friendName2 << endl;

                friendName2->setStyleSheet(FRIEND_NAME_SURNAME);


                QLabel *friendOnlineStatusLabel2 = new QLabel("");
                QPixmap friendOnlineStatusImage2(":/resc/resc/online_status_off.svg");
                friendOnlineStatusLabel2->setPixmap(friendOnlineStatusImage2.scaled(15,15, Qt::KeepAspectRatio));

                //friendOnlineStatusLabel2->setStyleSheet(ONLINE_STATUS);



                QPushButton *inviteGroupButton2 = new QPushButton(tr("Invite to Group"));

                QPushButton *deleteFriendButton2 = new QPushButton(tr("      Delete from group     "));

                QPixmap pixmapdeleteFriend(":/resc/resc/bin_white.svg");
                QIcon ButtonIcondeleteFriend(pixmapdeleteFriend);

                deleteFriendButton2->setIcon(ButtonIcondeleteFriend);
                deleteFriendButton2 -> setLayoutDirection ( Qt :: RightToLeft );
                deleteFriendButton2 -> setStyleSheet("text-align: right");
                deleteFriendButton2->setIconSize(QSize(20,20));

                deleteFriendButton2->setMaximumWidth(250);
                deleteFriendButton2->setMinimumWidth(250);


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

               // friendContainer2->setAlignment(Qt::AlignCenter);
                stackList->addLayout(friendContainer2);


                mButtonToLayoutMap.insert(deleteFriendButton2,friendContainer2);





                std::cout << member.get<std::string>() << std::endl;  // выводит в cout участников всех групп. Если подается одна группа, то в рамках одной группы
            }
        }
        }

         else {

        qDebug() << reply->errorString();

        qDebug() << "Server answer: " +  reply->readAll() << endl;

        qDebug () << reply -> error ();

        QMessageBox::warning(this, tr("Error"),
            "Connection ERROR!\n");

}

    reply->deleteLater();
    networkManagerloadFriends->clearAccessCache();

}

void Group::onHttpResultnetworkManagerGetMeets(QNetworkReply *reply) {

}

void Group::onHttpResultnetworkManagerDeleteFriendFromGroup(QNetworkReply *reply) {


    qDebug() << "http finished" << endl;
    if(!reply->error()) {
        QByteArray resp = reply->readAll();
        qDebug() <<"ETO OTVET SERVERA DELETE FRIEND FROM GROUP :  " + resp  << endl;
        QJsonDocument doc = QJsonDocument::fromJson(resp);
        QJsonObject obj;

        std::string str = resp.toStdString();

        std::cout << "str  " + str << std::endl;

        nlohmann::json j = nlohmann::json::parse(str);

        std::string delete_group_result = j["kick"].get<std::string>();

        if(delete_group_result == "OK") {



            std::cout << "delete friebd from group: " << delete_group_result << std::endl;

}

        } else {

        qDebug() << reply->errorString();

        qDebug() <<  reply->readAll() << endl;

        qDebug () << reply -> error ();

        QMessageBox::warning(this, tr("Error"),
            "Connection ERROR!\n");


}
    reply->deleteLater();


     networkManagerDeleteFriendFromGroup->clearAccessCache();




}

void Group::deleteFriendPressed() {


    QPushButton *button = qobject_cast<QPushButton*>(sender());

    QHBoxLayout *layout = mButtonToLayoutMap.take(button);


    QWidget * widget =  layout->itemAt(1)->widget();



    QLabel* xxx = dynamic_cast<QLabel*>(widget);


    QString nameGroup = xxx->text();



    //QString friendq = button->text();



    //emit sendGroupNameSignal(friendq); //вызывая сигнал нужно в скобочках указать текст, который мы передаем другому классу,


            QJsonObject deleFromGroupJson;
            QJsonObject bodyJson;

            QJsonArray arrayUsers;
            arrayUsers.push_back(nameGroup);

            bodyJson.insert("title", GROUP_TITLE_QSTRING);
            bodyJson.insert("members", arrayUsers);

            deleFromGroupJson.insert("kick", bodyJson);

                qDebug() << "create request" << endl;


                QNetworkRequest request(QUrl(SERVER_URL + ""));
                request.setHeader(QNetworkRequest::ContentTypeHeader,
                                  QStringLiteral("application/json;charset=utf-8"));
                qDebug() << "request data"<< QJsonDocument(deleFromGroupJson).toJson(QJsonDocument::Compact) << endl;

                request.setRawHeader("JSON_DATA", QJsonDocument(deleFromGroupJson).toJson(QJsonDocument::Compact));

                qDebug() << "JSON_DATA send" << endl;

                networkManagerDeleteFriendFromGroup->post(
                    request,
                    QJsonDocument(deleFromGroupJson).toJson(QJsonDocument::Compact)
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

void Group::getIventsDatePressed() {
    day1Button->setStyleSheet(BUTTON_DISABLED);
    day2Button->setStyleSheet(BUTTON_DISABLED);
    day3Button->setStyleSheet(BUTTON_DISABLED);
    day4Button->setStyleSheet(BUTTON_DISABLED);
    day5Button->setStyleSheet(BUTTON_DISABLED);
    day6Button->setStyleSheet(BUTTON_DISABLED);
    day7Button->setStyleSheet(BUTTON_DISABLED);

    QPushButton *button = qobject_cast<QPushButton*>(sender());

    QString Date = button->text();

    button->setStyleSheet(BUTTON_SOLID);

    qDebug() << Date << endl;


}


void Group::sendGroupNameSlot(const QString &text)
{

    QString abc = text;

    GrouptitleLabel->setText(text);
}


void Group::groupDeletePressed(){

    QJsonObject deleteGroupJson;
    QJsonObject bodyJson;
    bodyJson.insert("title", GrouptitleLabel->text());


    deleteGroupJson.insert("delete_group", bodyJson);

        qDebug() << "create request" << endl;


        QNetworkRequest request(QUrl(SERVER_URL + ""));
        request.setHeader(QNetworkRequest::ContentTypeHeader,
                          QStringLiteral("application/json;charset=utf-8"));

        request.setRawHeader("JSON_DATA", QJsonDocument(deleteGroupJson).toJson(QJsonDocument::Compact));
        qDebug() << "request data"<< QJsonDocument(deleteGroupJson).toJson(QJsonDocument::Compact) << endl;
        networkManagerDeleteGroup->post(
            request,
            QJsonDocument(deleteGroupJson).toJson(QJsonDocument::Compact)
        );
        qDebug() << "request send" << endl;


}

void Group::onHttpResultDeleteGroup(QNetworkReply *reply){


    qDebug() << "http finished" << endl;
    if(!reply->error()) {
        QByteArray resp = reply->readAll();
        qDebug() <<"ETO OTVET SERVERA DELETE GRROUP :  " + resp  << endl;
        QJsonDocument doc = QJsonDocument::fromJson(resp);
        QJsonObject obj;

        std::string str = resp.toStdString();

        std::cout << "str  " + str << std::endl;

        nlohmann::json j = nlohmann::json::parse(str);

        std::string delete_group_result = j["delete_group"].get<std::string>();

        if(delete_group_result == "OK") {

            QMessageBox::information(this, tr("Group deleting"),
                tr("Group is delete!\n"));

            newRootScreen(MAIN_TAG);

            std::cout << "delete friebd: " << delete_group_result << std::endl;

}

        } else {

        qDebug() << reply->errorString();

        qDebug() <<  reply->readAll() << endl;

        qDebug () << reply -> error ();

        QMessageBox::warning(this, tr("Error"),
            "Connection ERROR!\n");
        // newRootScreen(MAIN_TAG);

}
    reply->deleteLater();


     networkManagerDeleteGroup->clearAccessCache();


}








