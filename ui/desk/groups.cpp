#include "Groups.h"
#include "Group.h"

#include "../auth/user_data.h"


#include "nlohmann/json.hpp"
#include <iostream>
#include <set>

#include "style/stylecontainer.h"
using namespace styles;
#include "screensfactory.h"

#include <QLabel>
#include <QJsonArray>

#include <QNetworkAccessManager>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QJsonObject>
#include <QJsonDocument>
#include <QSettings>
#include <QMessageBox>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QScrollBar>
#include <QLabel>


#include <QRegularExpression>
#include <ui/view/qsvgbutton.h>
#include <ui/view/waitingspinnerwidget.h>
using namespace screens;

Groups::Groups() {

//    connect(this, SIGNAL(sendGroupNameSignal(const QString &)),
//            Group, SLOT(sendGroupnameSlot(const QString &)));


//    connect(this, sendGroupNameSignal,
//            &Group, &Group::sendGroupNameSlot);

    mainVLayout = new QVBoxLayout;
    QVBoxLayout *inputContainer = new QVBoxLayout;

    QHBoxLayout *titleContainer = new QHBoxLayout;
    QSvgButton *backButton = new QSvgButton(":/resc/resc/arrow_back.svg", QSize(24,24));
    titleLabel = new QLabel("Мои группы");

    //QFrame *loadingContaiter = new QFrame;
   // loading = new WaitingSpinnerWidget(loadingContaiter, true, false);
    //loading->setColor(QT_COLOR_PRIMARY);
    //loadingContaiter->setMinimumWidth(100);

    titleLabel->setStyleSheet(TITLE_LABLE);
    connect(backButton, &QSvgButton::clicked, this, &Groups::onBackPressed);

    titleContainer->addWidget(backButton);
    titleContainer->addWidget(titleLabel);
    titleContainer->setContentsMargins(0,24,0,16);

    titleLabel->setContentsMargins(16,0,0,0);

    QHBoxLayout *addGroupContainer = new QHBoxLayout;

    addGroupEdit = new QLineEdit;


    connect(addGroupEdit, &QLineEdit::textChanged, this, &Groups::checkNameGroup);

    addGroupEdit->setMaximumWidth(355);
    addGroupEdit->setStyleSheet(EDIT_TEXT);
    addGroupEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    addGroupEdit->setPlaceholderText("Имя группы");

    addGroupEdit->setMaximumWidth(600);
    addGroupEdit->setMinimumWidth(600);



    addGroupButton = new QPushButton("Создать группу");

    addGroupButton->setMaximumWidth(400);
    addGroupButton->setMinimumWidth(400);


    connect(addGroupButton, &QPushButton::clicked, this, &Groups::addGroupButtonPressed);

    addGroupButton->setStyleSheet(BUTTON_DISABLED);
    addGroupButton->setDisabled(true);


    addGroupContainer->addWidget(addGroupEdit);

    addGroupContainer->addWidget(addGroupButton);

    addGroupButton->setStyleSheet(BUTTON_DISABLED);
    addGroupButton->setDisabled(true);








    //inputContainer->setAlignment(Qt::AlignCenter);
    inputContainer->addLayout(titleContainer);
    //mainVLayout->setAlignment(Qt::AlignCenter);
    //mainVLayout->addLayout(inputContainer);
    //mainVLayout->addLayout(GroupContainer);
    //mainVLayout->addLayout(GroupContainer2);





    //mainVLayout->addStretch();

    //this->setLayout(mainVLayout);





    QScrollArea *deskScrollArea = new QScrollArea;
    deskScrollArea->setFrameShape(QFrame::NoFrame);
    QWidget *scrolContainer = new QWidget;
    scrolContainer->setObjectName("container");
    scrolContainer->setStyleSheet(GLOBAL_BACK_WHITE);
    deskScrollArea->setStyleSheet(SCROL_BAR);
    QHBoxLayout *content = new QHBoxLayout;
    content->setAlignment(Qt::AlignLeft);
    scrolContainer->setLayout(content);
    deskScrollArea->setWidget(scrolContainer);
    deskScrollArea->setWidgetResizable(true);
    deskScrollArea->horizontalScrollBar()->setEnabled(false);


    loading = new WaitingSpinnerWidget(scrolContainer, true, false);
    loading->setColor(QT_COLOR_PRIMARY);

    loading->start();


    inputContainerGroups = new QVBoxLayout;
      //inputContainerGroups->setAlignment(Qt::AlignCenter);

    inputContainerGroups->setAlignment(Qt::AlignTop);
    inputContainer->setAlignment(Qt::AlignTop);
    addGroupContainer->setAlignment(Qt::AlignTop);

    inputContainerGroups->addLayout(inputContainer);

     inputContainerGroups->addLayout(addGroupContainer);


    //mainHLayout->addWidget(deskScrollArea);
    //mainHLayout->addStretch();

    mainVLayout->setAlignment(Qt::AlignCenter);

    content->addLayout(inputContainerGroups);




    mainVLayout->addWidget(deskScrollArea);




    this->setLayout(mainVLayout);
    this->setStyleSheet(BACK_WHITE);
    this->setObjectName("fragment");

    checkData();

    networkManager = new QNetworkAccessManager();
    connect(networkManager, &QNetworkAccessManager::finished, this, &Groups::onHttpResult);

    addManagerGroup = new QNetworkAccessManager();
    connect(addManagerGroup, &QNetworkAccessManager::finished, this, &Groups::onHttpResultAddGroup);


    ManagerAddFriendToGroup = new QNetworkAccessManager();
    connect(ManagerAddFriendToGroup, &QNetworkAccessManager::finished, this, &Groups::onHttpResultAddFriendtoGroup);


    ManagerAddFriendsLayout = new QNetworkAccessManager();
    connect(ManagerAddFriendsLayout, &QNetworkAccessManager::finished, this, &Groups::onHttpResultManagerAddFriendsLayout);

    loadFriends();


    loadGroups();


}

Groups::~Groups() {


    //delete loading;
    delete titleLabel;
    networkManager->clearAccessCache();
    addManagerGroup->clearAccessCache();
    ManagerAddFriendToGroup->clearAccessCache();
    ManagerAddFriendsLayout->clearAccessCache();
}

void Groups::checkData() {

}

void Groups::onBackPressed() {
    back();
}

void Groups::onHttpResult(QNetworkReply *reply) {

    loading->stop();

    qDebug() << "http finished" << endl;
    loading->stop();
    checkData();
    if(!reply->error()) {    //
        QByteArray resp = reply->readAll();
        qDebug() <<"ETO OTVET SERVERA Groups :  " + resp  << endl;
        QJsonDocument doc = QJsonDocument::fromJson(resp);
        QJsonObject obj;

        std::string strGroups = resp.toStdString();

        //strGroups = "{\"userID\":\"213564544\",\"Groups\":[\"Group 1\", \"Group 2\"]}";

        nlohmann::json j = nlohmann::json::parse(strGroups);

        nlohmann::json val = j["get_groups"];

        std::cout << "eto strika"<< j << endl;


        if(j["get_groups"].is_string()){   // проверка есть ли groups в строке contains

            noGroupsLabel = new QLabel("Вы не состоите в группе :(");

            inputContainerGroups->addWidget(noGroupsLabel);

            qDebug("NO GROUPS");
            std::set<std::string> s_Groups;




        } else {


        for (auto& element : val) {

            GroupContainer2 = new QHBoxLayout;
            QLabel *GroupImageLabel2 = new QLabel("");
            QPixmap GroupImage2(":/resc/resc/group.svg");
            GroupImageLabel2->setPixmap(GroupImage2);
            GroupImageLabel2->setStyleSheet(FRIEND_IMAGE);

            GroupNameButton = new QPushButton(QString::fromStdString(element["title"].get<std::string>()));

              connect(GroupNameButton, &QPushButton::clicked, this, &Groups::goToGroup);

            GroupNameButton->setStyleSheet(FRIEND_NAME_SURNAME);

            GroupNameButton->setStyleSheet(BUTTON_WHITE);

            GroupNameButton->setMaximumWidth(300);


            //QPushButton *inviteGroupButton2 = new QPushButton("Пригласить в группу");

            stack = new QStackedWidget;

            QFrame *inviteButtonWidjet = new QFrame;
            QVBoxLayout *inviteButtonLayout = new QVBoxLayout;


            QFrame *backWidget = new QFrame;
            QHBoxLayout *backLayout = new QHBoxLayout;

            stack->addWidget(inviteButtonWidjet);
            stack->addWidget(backWidget);

            stack->setCurrentIndex(0);

            stack->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);


            inviteButtonWidjet->setLayout(inviteButtonLayout);


            backWidget->setLayout(backLayout);


            QPushButton *inviteGroupButton2 = new QPushButton("Пригласить в группу");

            inviteGroupButton2->setMaximumWidth(300);
            inviteGroupButton2->setStyleSheet(BUTTON_SOLID);

            connect(inviteGroupButton2, &QPushButton::clicked, this, &Groups::inviteGroupPressed);

            inviteButtonLayout->addWidget(inviteGroupButton2);

            backAddtoGroup = new QPushButton("Отмена");

            backAddtoGroup->setMaximumWidth(300);

            backAddtoGroup->setStyleSheet(BUTTON_PROFILE_RED);

            backLayout->addWidget(backAddtoGroup);

            connect(backAddtoGroup, &QPushButton::clicked, this, &Groups::backAddtoGroupPressed);


    //        QHBoxLayout *GroupButtonContainer2 = new QHBoxLayout;


    //        //GroupButtonContainer2->addWidget(inviteGroupButton2);
    //        //GroupButtonContainer2->addWidget(inviteGroupButton2);



                    GroupContainer2->addWidget(GroupImageLabel2);
                     GroupContainer2->addWidget(GroupNameButton);


    //        GroupContainer2->addLayout(GroupButtonContainer2);

//////////////////////// добавление друзей в слой


            std::cout<< "aaaaaaaaaaaaaaaaaaaaaaa  eto yaaa" << str << endl;

            std::string strFriend = "{\"userID\":\"213564544\",\"Friends\":[\"mars123456\", \"user666666\",  \"Alex\",  \"qwe\", \"piotr\"]}";

            //std::string strFriend = *str;
            nlohmann::json j = nlohmann::json::parse(str);


            std::cout << j.size() << std::endl;
            std::cout << j << std::endl;

            nlohmann::json::iterator it = j.begin();
            std::cout << it.key() << std::endl;

            std::string key = it.key();

            nlohmann::json value = j[key];

            std::cout << value << std::endl;


            std::set<std::string> s_friends;

             friendContainer2 = new QVBoxLayout;

             innerScrollFriends = new QVBoxLayout;
             QLabel *friendNamesTitle = new QLabel("Выберите кого пригласить:");

             //friendNamesTitle->setAlignment(Qt::AlignCenter);
             //innerScroll->addWidget(friendNamesTitle);

           //  innerScroll->setAlignment(Qt::AlignCenter);
    //         innerScrollFriends->setAlignment(Qt::AlignRight);


             QScrollArea *deskScrollArea = new QScrollArea;

             deskScrollArea->setMaximumHeight(250);
             deskScrollArea->setMaximumWidth(300);
             deskScrollArea->setAlignment(Qt::AlignHCenter);
             //deskScrollArea->setFrameShape(QFrame::NoFrame);
             QWidget *scrolContainer = new QWidget;
             scrolContainer->setObjectName("container");


             scrolContainer->setStyleSheet(GLOBAL_BACK_WHITE);
             deskScrollArea->setStyleSheet(SCROL_BAR);
             QHBoxLayout *content = new QHBoxLayout;
             content->setAlignment(Qt::AlignCenter);
             scrolContainer->setLayout(content);
             deskScrollArea->setWidget(scrolContainer);
             deskScrollArea->setWidgetResizable(true);
             deskScrollArea->horizontalScrollBar()->setEnabled(false);


    //         QSvgWidget *done = new QSvgWidget(":/resc/resc/done_outline.svg");
    //        done->setMinimumSize(QSize(24,24));
    //        done->setMaximumSize(QSize(24,24));

            for (auto& element : j["get_contacts"]) {

                friendName2 = new QPushButton(QString::fromStdString(element.dump()).remove('"'));

                friendName2->setStyleSheet(FRIEND_NAME_SURNAME);


                friendName2->setStyleSheet(BUTTON_SOLID);
                friendName2->setMinimumWidth(200);
                  friendName2->setMaximumWidth(300);



                friendContainer2->addWidget(friendNamesTitle);
                friendContainer2->addWidget(friendName2);


                connect(friendName2, &QPushButton::clicked, this, &Groups::friendName2Pressed);


                innerScrollFriends->addWidget(friendName2);

                //content->addLayout(friendContainer2);

                ///innerScroll->addLayout(friendContainer2);



                backLayout->addLayout(innerScrollFriends);





            }


            GroupContainer2->addWidget(stack);


            inputContainerGroups->addLayout(GroupContainer2);

             mButtonBackToLayoutMap.insert(backAddtoGroup,GroupContainer2);


            mButtonToLayoutMap.insert(inviteGroupButton2,GroupContainer2);


        }

    }} else {

        qDebug() << reply->errorString();

        qDebug() <<  reply->readAll() << endl;

        qDebug () << reply -> error ();

        QMessageBox::warning(this, "Ошибка",
        "При подключениии произошла ошибка.\n");


    }

    reply->deleteLater();

}

void Groups::onHttpResultAddGroup(QNetworkReply *reply) {


    qDebug() << "http AddGroup finished" << endl;
    loading->stop();
    checkData();
    if(!reply->error()) {
        QByteArray resp = reply->readAll();
        qDebug() <<"ETO OTVET SERVERA ADD GROUP :  " + resp  << endl;
        QJsonDocument doc = QJsonDocument::fromJson(resp);
        QJsonObject obj;

        std::string strq = resp.toStdString();

        std::cout << "str  " + strq << std::endl;

        nlohmann::json j = nlohmann::json::parse(strq);

        std::string addGroup  = j["create_group"].get<std::string>();

        if(addGroup == "OK") {



            std::cout << "ADD GROUP: " << addGroup << std::endl;

}

        } else {

        qDebug() << reply->errorString();

        qDebug() <<  reply->readAll() << endl;

        qDebug () << reply -> error ();

        QMessageBox::warning(this, "Ошибка",
            "При подключениии произошла ошибка.\n");
        // newRootScreen(MAIN_TAG);

}
    //newRootScreen(MAIN_TAG);
    reply->deleteLater();


     addManagerGroup->clearAccessCache();



}

void Groups::loadGroups() {

    addGroupEdit->setText("");
    addGroupButton->setStyleSheet(BUTTON_DISABLED);
    addGroupButton->setDisabled(true);



    QJsonObject loadGroupsJson;
    QJsonObject userIDJson;

   // nlohmann::json aaa = nlohmann::json::parse(loadGroupsJson);


    QJsonArray nickArray;

    nickArray.push_back("mars1234");

    userIDJson.insert("members", nickArray);


    loadGroupsJson.insert("get_groups", userIDJson);

        qDebug() << "create request" << endl;



        QNetworkRequest request(QUrl(SERVER_URL + ""));
        request.setHeader(QNetworkRequest::ContentTypeHeader,
                          QStringLiteral("application/json;charset=utf-8"));
        qDebug() << "request data"<< QJsonDocument(loadGroupsJson).toJson(QJsonDocument::Compact) << endl;

        request.setRawHeader("JSON_DATA", QJsonDocument(loadGroupsJson).toJson(QJsonDocument::Compact));
        networkManager->post(
            request,
            QJsonDocument(loadGroupsJson).toJson(QJsonDocument::Compact)
        );
        qDebug() << "request send" << endl;
    }



void Groups::loadFriends() {

    QJsonObject loadFriendsJson;
    QJsonObject userIDJson;

   // nlohmann::json aaa = nlohmann::json::parse(loadFriendsJson);

    userIDJson.insert("user_id", "1");
    loadFriendsJson.insert("get_contacts", userIDJson);

        qDebug() << "create request" << endl;


        QNetworkRequest request(QUrl(SERVER_URL + ""));
        request.setHeader(QNetworkRequest::ContentTypeHeader,
                          QStringLiteral("application/json;charset=utf-8"));
        qDebug() << "request data"<< QJsonDocument(loadFriendsJson).toJson(QJsonDocument::Compact) << endl;

        request.setRawHeader("JSON_DATA", QJsonDocument(loadFriendsJson).toJson(QJsonDocument::Compact));
        ManagerAddFriendsLayout->post(
            request,
            QJsonDocument(loadFriendsJson).toJson(QJsonDocument::Compact)
        );
        qDebug() << "request send" << endl;
}





void Groups::addGroupButtonPressed() {

    QJsonObject addGroupJson;
    QJsonObject bodyJson;


    QJsonArray arrayUsers;
    arrayUsers.push_back("mars1234");

    bodyJson.insert("title", addGroupEdit->text());
    bodyJson.insert("members", arrayUsers);

    addGroupJson.insert("create_group", bodyJson);



        qDebug() << "create request" << endl;


        QNetworkRequest request(QUrl(SERVER_URL + ""));
        request.setHeader(QNetworkRequest::ContentTypeHeader,
                          QStringLiteral("application/json;charset=utf-8"));
        qDebug() << "request data"<< QJsonDocument(addGroupJson).toJson(QJsonDocument::Compact) << endl;

         request.setRawHeader("JSON_DATA", QJsonDocument(addGroupJson).toJson(QJsonDocument::Compact));
        addManagerGroup->post(
            request,
            QJsonDocument(addGroupJson).toJson(QJsonDocument::Compact)
        );
        qDebug() << "request send" << endl;



        GroupContainer2 = new QHBoxLayout;
        QLabel *GroupImageLabel2 = new QLabel("");
        QPixmap GroupImage2(":/resc/resc/group.svg");
        GroupImageLabel2->setPixmap(GroupImage2);
        GroupImageLabel2->setStyleSheet(FRIEND_IMAGE);





        GroupNameButton = new QPushButton(addGroupEdit->text());

        connect(GroupNameButton, &QPushButton::clicked, this, &Groups::goToGroup);

        addGroupEdit->setText("");

        GroupNameButton->setStyleSheet(FRIEND_NAME_SURNAME);

        GroupNameButton->setStyleSheet(BUTTON_WHITE);

        GroupNameButton->setMaximumWidth(300);
///////////////////////////////////////////////////////////////////////////////////////////////

        stack = new QStackedWidget;

        QFrame *inviteButtonWidjet = new QFrame;
        QVBoxLayout *inviteButtonLayout = new QVBoxLayout;


        QFrame *backWidget = new QFrame;
        QHBoxLayout *backLayout = new QHBoxLayout;

        stack->addWidget(inviteButtonWidjet);
        stack->addWidget(backWidget);

        stack->setCurrentIndex(0);

        stack->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);




        inviteButtonWidjet->setLayout(inviteButtonLayout);


        backWidget->setLayout(backLayout);


        QPushButton *inviteGroupButton2 = new QPushButton("Пригласить в группу");

        inviteGroupButton2->setMaximumWidth(300);
        inviteGroupButton2->setStyleSheet(BUTTON_SOLID);

        connect(inviteGroupButton2, &QPushButton::clicked, this, &Groups::inviteGroupPressed);

        inviteButtonLayout->addWidget(inviteGroupButton2);

        backAddtoGroup = new QPushButton("Отмена");

        backAddtoGroup->setMaximumWidth(200);

        backAddtoGroup->setStyleSheet(BUTTON_PROFILE_RED);

        backLayout->addWidget(backAddtoGroup);

        connect(backAddtoGroup, &QPushButton::clicked, this, &Groups::backAddtoGroupPressed);


//        QHBoxLayout *GroupButtonContainer2 = new QHBoxLayout;


//        //GroupButtonContainer2->addWidget(inviteGroupButton2);
//        //GroupButtonContainer2->addWidget(inviteGroupButton2);



                GroupContainer2->addWidget(GroupImageLabel2);
                 GroupContainer2->addWidget(GroupNameButton);


//        GroupContainer2->addLayout(GroupButtonContainer2);



        //str = "{\"userID\":\"213564544\",\"Friends\":[\"mars123456\", \"user666666\",  \"Alex\",  \"qwe\", \"piotr\"]}";


        std::string string = str;
        nlohmann::json j = nlohmann::json::parse(string);


        std::cout << j.size() << std::endl;
        std::cout << j << std::endl;

        nlohmann::json::iterator it = j.begin();
        std::cout << it.key() << std::endl;

        std::string key = it.key();

        nlohmann::json value = j[key];

        std::cout << value << std::endl;


        std::set<std::string> s_friends;

         friendContainer2 = new QVBoxLayout;

         innerScrollFriends = new QVBoxLayout;
         QLabel *friendNamesTitle = new QLabel("Выберите кого пригласить:");

         //friendNamesTitle->setAlignment(Qt::AlignCenter);
         //innerScroll->addWidget(friendNamesTitle);

       //  innerScroll->setAlignment(Qt::AlignCenter);
//         innerScrollFriends->setAlignment(Qt::AlignRight);


//         QScrollArea *deskScrollArea = new QScrollArea;

//         deskScrollArea->setMaximumHeight(250);
//         deskScrollArea->setMaximumWidth(300);
//         deskScrollArea->setAlignment(Qt::AlignHCenter);
//         //deskScrollArea->setFrameShape(QFrame::NoFrame);
//         QWidget *scrolContainer = new QWidget;
//         scrolContainer->setObjectName("container");


//         scrolContainer->setStyleSheet(GLOBAL_BACK_WHITE);
//         deskScrollArea->setStyleSheet(SCROL_BAR);
//         QHBoxLayout *content = new QHBoxLayout;
//         content->setAlignment(Qt::AlignCenter);
//         scrolContainer->setLayout(content);
//         deskScrollArea->setWidget(scrolContainer);
//         deskScrollArea->setWidgetResizable(true);
//         deskScrollArea->horizontalScrollBar()->setEnabled(false);


//         QSvgWidget *done = new QSvgWidget(":/resc/resc/done_outline.svg");
//        done->setMinimumSize(QSize(24,24));
//        done->setMaximumSize(QSize(24,24));

        for (auto& element : j["get_contacts"]) {

            friendName2 = new QPushButton(QString::fromStdString(element.dump()).remove('"'));

            friendName2->setStyleSheet(FRIEND_NAME_SURNAME);


            friendName2->setStyleSheet(BUTTON_SOLID);
            friendName2->setMinimumWidth(200);
              friendName2->setMaximumWidth(300);



            friendContainer2->addWidget(friendNamesTitle);
            friendContainer2->addWidget(friendName2);


            connect(friendName2, &QPushButton::clicked, this, &Groups::friendName2Pressed);


            innerScrollFriends->addWidget(friendName2);

            //content->addLayout(friendContainer2);

            ///innerScroll->addLayout(friendContainer2);



            backLayout->addLayout(innerScrollFriends);





        }


        GroupContainer2->addWidget(stack);


        inputContainerGroups->addLayout(GroupContainer2);

         mButtonBackToLayoutMap.insert(backAddtoGroup,GroupContainer2);


        mButtonToLayoutMap.insert(inviteGroupButton2,GroupContainer2);

//////////////

    }


void Groups::onHttpResultManagerAddFriendsLayout(QNetworkReply *reply) {


     qDebug() << "http finished" << endl;


     if(!reply->error()) {  //
         QByteArray resp = reply->readAll();
         qDebug() <<"ETO OTVET SERVERA GET CONTACTS for group layout :  " + resp  << endl;
         QJsonDocument doc = QJsonDocument::fromJson(resp);
         QJsonObject obj;


         std::string abc = resp.toStdString();
         str = abc;


         //std::cout << "str  " << str << std::endl;

         } else {


         qDebug() << reply->errorString();

         qDebug() <<  reply->readAll() << endl;

         qDebug () << reply -> error ();

         QMessageBox::warning(this, "Ошибка",
             "При подключениии произошла ошибка.\n");

 }


     reply->deleteLater();

     ManagerAddFriendsLayout->clearAccessCache();


}




void Groups::checkNameGroup() {
    if (addGroupEdit->text().length() >= 4) {
        addGroupButton->setStyleSheet(BUTTON_SOLID);
         addGroupButton->setDisabled(false);
    } else {
        addGroupButton->setStyleSheet(BUTTON_DISABLED);
         addGroupButton->setDisabled(true);
    }
}


void Groups::inviteGroupPressed(){


    inviteGroupButton = qobject_cast<QPushButton*>(sender());

    QHBoxLayout *layout = mButtonToLayoutMap.value(inviteGroupButton);






        QWidget * stackWidjet =  layout->itemAt(2)->widget();

        QStackedWidget* stack = dynamic_cast<QStackedWidget*>(stackWidjet);

        stack->setCurrentIndex(1);


        layout->update();


        QWidget * widget =  layout->itemAt(1)->widget();

        QPushButton* groupName = dynamic_cast<QPushButton*>(widget);

        groupNameString = groupName->text();





    //QStackedWidget* stack = dynamic_cast<QStackedWidget*>(stack);

   //groupNameString = stack->text();

}



void Groups::friendName2Pressed(){


    QPushButton *button = qobject_cast<QPushButton*>(sender());


    QString friendq = button->text();






            QJsonObject inviteGroupJson;
            QJsonObject bodyJson;

            QJsonArray arrayUsers;
            arrayUsers.push_back(friendq);

            bodyJson.insert("title", groupNameString);
            bodyJson.insert("members", arrayUsers);

            inviteGroupJson.insert("invite", bodyJson);

                qDebug() << "create request" << endl;


                QNetworkRequest request(QUrl(SERVER_URL + ""));
                request.setHeader(QNetworkRequest::ContentTypeHeader,
                                  QStringLiteral("application/json;charset=utf-8"));
                qDebug() << "request data"<< QJsonDocument(inviteGroupJson).toJson(QJsonDocument::Compact) << endl;

                request.setRawHeader("JSON_DATA", QJsonDocument(inviteGroupJson).toJson(QJsonDocument::Compact));

                qDebug() << "JSON_DATA send" << endl;

                ManagerAddFriendToGroup->post(
                    request,
                    QJsonDocument(inviteGroupJson).toJson(QJsonDocument::Compact)
                );
                qDebug() << "request send" << endl;


           delete button;

  }



void Groups::goToGroup() {
       inviteGroupButton = qobject_cast<QPushButton*>(sender());

        QString aaa = inviteGroupButton->text();



             qDebug() << aaa << endl;


    navigateTo(GROUP);
}


void Groups::backAddtoGroupPressed() {

    inviteGroupButton = qobject_cast<QPushButton*>(sender());

    QHBoxLayout *layout = mButtonBackToLayoutMap.value(inviteGroupButton);


    QWidget * stackWidjet =  layout->itemAt(2)->widget();

    QStackedWidget* stack = dynamic_cast<QStackedWidget*>(stackWidjet);

    stack->setCurrentIndex(0);
    layout->update();

}

void Groups::onHttpResultDeleteGroup(QNetworkReply *reply) {


}



void Groups::onHttpResultAddFriendtoGroup(QNetworkReply *reply) {


    qDebug() << "http finished" << endl;
    loading->stop();
    checkData();
    if(!reply->error()) {
        QByteArray resp = reply->readAll();
        qDebug() <<"ETO OTVET SERVERA ADD To GROUP FRIEND :  " + resp  << endl;
        QJsonDocument doc = QJsonDocument::fromJson(resp);
        QJsonObject obj;

        std::string str = resp.toStdString();

        std::cout << "str  " + str << std::endl;

        nlohmann::json j = nlohmann::json::parse(str);

        std::string invite_friend_result = j["invite"].get<std::string>();

        if(invite_friend_result == "OK") {



            std::cout << "invite friebd: " << invite_friend_result << std::endl;

}

        } else {

        qDebug() << reply->errorString();

        qDebug() <<  reply->readAll() << endl;

        qDebug () << reply -> error ();

        QMessageBox::warning(this, "Ошибка",
            "При подключениии произошла ошибка.\n");
        // newRootScreen(MAIN_TAG);


}

    reply->deleteLater();

        ManagerAddFriendToGroup->clearAccessCache();
}

