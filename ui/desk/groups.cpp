#include "Groups.h"
#include "Group.h"

#include "../auth/user_data.h"

using namespace userData;

#include "nlohmann/json.hpp"
#include <iostream>
#include <set>

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
#include <QScrollArea>
#include <QVBoxLayout>
#include <QScrollBar>
#include <QLabel>


#include <QRegularExpression>
#include <ui/view/qsvgbutton.h>
#include <ui/view/waitingspinnerwidget.h>
using namespace screens;

Groups::Groups() {

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








    inputContainer->setAlignment(Qt::AlignTop);
    inputContainer->addLayout(titleContainer);
   // mainVLayout->setAlignment(Qt::AlignLeft);
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





    inputContainerGroups = new QVBoxLayout;
      inputContainerGroups->setAlignment(Qt::AlignLeft);

    inputContainerGroups->setAlignment(Qt::AlignTop);
    inputContainer->setAlignment(Qt::AlignTop);
    addGroupContainer->setAlignment(Qt::AlignTop);

    inputContainerGroups->addLayout(inputContainer);

     inputContainerGroups->addLayout(addGroupContainer);


    //mainHLayout->addWidget(deskScrollArea);
    //mainHLayout->addStretch();

    mainVLayout->setAlignment(Qt::AlignLeft);

    content->addLayout(inputContainerGroups);




    mainVLayout->addWidget(deskScrollArea);




    this->setLayout(mainVLayout);
    this->setStyleSheet(BACK_WHITE);
    this->setObjectName("fragment");

    checkData();

    networkManager = new QNetworkAccessManager();
    connect(networkManager, &QNetworkAccessManager::finished, this, &Groups::onHttpResult);

    addManagerGroup = new QNetworkAccessManager();
    connect(addManagerGroup, &QNetworkAccessManager::finished, this, &Groups::onHttpResultGroup);


    addManagerFriendtoGroup = new QNetworkAccessManager();
    connect(addManagerFriendtoGroup, &QNetworkAccessManager::finished, this, &Groups::onHttpResultAddFriendtoGroup);

    loadGroups();
}

Groups::~Groups() {


    //delete loading;
    delete titleLabel;
    networkManager->clearAccessCache();
}

void Groups::checkData() {

}

void Groups::onBackPressed() {
    back();
}



void Groups::onHttpResult(QNetworkReply *reply) {




    str = "{\"userID\":\"213564544\",\"Groups\":[\"Group 1\", \"Group 2\",  \"Group 3\",  \"Group 4\", \"Group 5\"]}";

    nlohmann::json j = nlohmann::json::parse(str);


    std::cout << j.size() << std::endl;
    std::cout << j << std::endl;

    nlohmann::json::iterator it = j.begin();
    std::cout << it.key() << std::endl;

    std::string key = it.key();

    nlohmann::json value = j[key];

    std::cout << value << std::endl;


    std::set<std::string> s_Groups;

    for (auto& element : j["Groups"]) {




        GroupContainer2 = new QHBoxLayout;
        QLabel *GroupImageLabel2 = new QLabel("");
        QPixmap GroupImage2(":/resc/resc/group.svg");
        GroupImageLabel2->setPixmap(GroupImage2);
        GroupImageLabel2->setStyleSheet(FRIEND_IMAGE);





        GroupNameButton = new QPushButton(QString::fromStdString(element.dump()).remove('"'));

          connect(GroupNameButton, &QPushButton::clicked, this, &Groups::goToGroup);



        GroupNameButton->setStyleSheet(FRIEND_NAME_SURNAME);

        GroupNameButton->setStyleSheet(BUTTON_WHITE);

        GroupNameButton->setMaximumWidth(300);


        //QPushButton *inviteGroupButton2 = new QPushButton("Пригласить в группу");

        QPushButton *inviteGroupButton2 = new QPushButton("Пригласить в группу");

        inviteGroupButton2->setMaximumWidth(300);
        inviteGroupButton2->setStyleSheet(BUTTON_SOLID);


        QHBoxLayout *GroupButtonContainer2 = new QHBoxLayout;


        //GroupButtonContainer2->addWidget(inviteGroupButton2);
        GroupButtonContainer2->addWidget(inviteGroupButton2);



        GroupContainer2->addWidget(GroupImageLabel2);
        GroupContainer2->addWidget(GroupNameButton);


        GroupContainer2->addLayout(GroupButtonContainer2);

        connect(inviteGroupButton2, &QPushButton::clicked, this, &Groups::inviteGroupPressed);







        inputContainerGroups->addLayout(GroupContainer2);


        mButtonToLayoutMap.insert(inviteGroupButton2,GroupContainer2);





    }


}

void Groups::onHttpResultGroup(QNetworkReply *reply) {



}

void Groups::loadGroups() {

    addGroupEdit->setText("");
    addGroupButton->setStyleSheet(BUTTON_DISABLED);
    addGroupButton->setDisabled(true);
    QJsonObject loadGroupsJson;
    QJsonObject userIDJson;

   // nlohmann::json aaa = nlohmann::json::parse(loadGroupsJson);

    userIDJson.insert("userID", userIDData);
    loadGroupsJson.insert("getGroup", userIDJson);

        qDebug() << "create request" << endl;



        QNetworkRequest request(QUrl(SERVER_URL + ""));
        request.setHeader(QNetworkRequest::ContentTypeHeader,
                          QStringLiteral("application/json;charset=utf-8"));
        qDebug() << "request data"<< QJsonDocument(loadGroupsJson).toJson(QJsonDocument::Compact) << endl;
        networkManager->post(
            request,
            QJsonDocument(loadGroupsJson).toJson(QJsonDocument::Compact)
        );
        qDebug() << "request send" << endl;
    }




void Groups::addGroupButtonPressed() {



    QJsonObject addGroupJson;
    QJsonObject bodyJson;
    bodyJson.insert("userID", userIDData);
    bodyJson.insert("GroupName", addGroupEdit->text());
    addGroupJson.insert("setGroup", bodyJson);

        qDebug() << "create request" << endl;



        QNetworkRequest request(QUrl(SERVER_URL + ""));
        request.setHeader(QNetworkRequest::ContentTypeHeader,
                          QStringLiteral("application/json;charset=utf-8"));
        qDebug() << "request data"<< QJsonDocument(addGroupJson).toJson(QJsonDocument::Compact) << endl;
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


        //QPushButton *inviteGroupButton2 = new QPushButton("Пригласить в группу");

        QPushButton *inviteGroupButton2 = new QPushButton("Пригласить в группу");

        inviteGroupButton2->setMaximumWidth(300);
        inviteGroupButton2->setStyleSheet(BUTTON_SOLID);


        QHBoxLayout *GroupButtonContainer2 = new QHBoxLayout;


        //GroupButtonContainer2->addWidget(inviteGroupButton2);
        GroupButtonContainer2->addWidget(inviteGroupButton2);



        GroupContainer2->addWidget(GroupImageLabel2);
        GroupContainer2->addWidget(GroupNameButton);


        GroupContainer2->addLayout(GroupButtonContainer2);

        connect(inviteGroupButton2, &QPushButton::clicked, this, &Groups::inviteGroupPressed);







        inputContainerGroups->addLayout(GroupContainer2);




        mButtonToLayoutMap.insert(inviteGroupButton2,GroupContainer2);




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


    QPushButton *button = qobject_cast<QPushButton*>(sender());

    button->hide();


    QHBoxLayout *layout = mButtonToLayoutMap.take(button);


    QWidget * widget =  layout->itemAt(1)->widget();



    QPushButton* groupName = dynamic_cast<QPushButton*>(widget);


   groupNameString = groupName->text();

    button->setDisabled(true);


        str = "{\"userID\":\"213564544\",\"Friends\":[\"Misha1991\", \"Igor\",  \"Alex\",  \"qwe\", \"Igor\",  \"Alex\",  \"qwe\", \"Igor\",  \"Alex\",  \"qwe\", \"piotr\"]}";

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

         QVBoxLayout *innerScroll = new QVBoxLayout;
         QLabel *friendNamesTitle = new QLabel("Выберите кого пригласить:");

         //friendNamesTitle->setAlignment(Qt::AlignCenter);
         //innerScroll->addWidget(friendNamesTitle);

         innerScroll->setAlignment(Qt::AlignCenter);
         innerScroll->setAlignment(Qt::AlignHCenter);


         QScrollArea *deskScrollArea = new QScrollArea;

         deskScrollArea->setMaximumHeight(250);

         deskScrollArea->setMaximumWidth(300);
         deskScrollArea->setAlignment(Qt::AlignHCenter);
         deskScrollArea->setFrameShape(QFrame::NoFrame);
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

        for (auto& element : j["Friends"]) {









            friendName2 = new QPushButton(QString::fromStdString(element.dump()).remove('"'));

            friendName2->setStyleSheet(FRIEND_NAME_SURNAME);


            friendName2->setStyleSheet(BUTTON_SOLID);
            friendName2->setMinimumWidth(200);



            //friendContainer2->addWidget(friendNamesTitle);
            friendContainer2->addWidget(friendName2);


            connect(friendName2, &QPushButton::clicked, this, &Groups::friendName2Pressed);


            innerScroll->addWidget(deskScrollArea);
            content->addLayout(friendContainer2);
            layout->addLayout(innerScroll);


        }

}



void Groups::friendName2Pressed(){


    QPushButton *button = qobject_cast<QPushButton*>(sender());

    QString friendq = button->text();

        QJsonObject deleteFriendJson;
        QJsonObject bodyJson;
        bodyJson.insert("groupName", (groupNameString));
        bodyJson.insert("friendName", (friendq));
        deleteFriendJson.insert("addToGroup", bodyJson);

            qDebug() << "create request" << endl;



            QNetworkRequest request(QUrl(SERVER_URL + ""));
            request.setHeader(QNetworkRequest::ContentTypeHeader,
                              QStringLiteral("application/json"));
            qDebug() << "request data"<< QJsonDocument(deleteFriendJson).toJson(QJsonDocument::Compact) << endl;
            addManagerFriendtoGroup->post(
                request,
                QJsonDocument(deleteFriendJson).toJson(QJsonDocument::Compact)
            );
            qDebug() << "request send" << endl;


    delete button;



  }



void Groups::goToGroup() {

    QPushButton *button = qobject_cast<QPushButton*>(sender());


    QLabel *nameGroupgo = new QLabel(button->text());

    navigateTo(GROUP);
}







void Groups::onHttpResultDeleteGroup(QNetworkReply *reply) {



}

void Groups::onHttpResultAddFriendtoGroup(QNetworkReply *reply) {



}

