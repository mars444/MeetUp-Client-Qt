#include "Groups.h"

#include "Friends.h"

#include "style/stylecontainer.h"
using namespace styles;
#include "screensfactory.h"

#include <QLabel>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QScrollBar>
#include <QSettings>
#include <QCheckBox>
#include <QJsonDocument>
#include <QMessageBox>

#include <models/cardmodel.h>

#include <ui/view/qsvgbutton.h>
#include <QNetworkAccessManager>

#include <models/deskmodel.h>
using namespace screens;

Groups::Groups() {

    QVBoxLayout *mainHLayout = new QVBoxLayout;
    QVBoxLayout *infoContainer = new QVBoxLayout;

    QHBoxLayout *titleContainer = new QHBoxLayout;
    QSvgButton *backButton = new QSvgButton(":/resc/resc/arrow_back.svg", QSize(24,24));
    titleLabel = new QLabel("Мои группы");

    QHBoxLayout *buttonContainer = new QHBoxLayout;




    titleContainer->addWidget(backButton);
    titleContainer->addWidget(titleLabel);
    titleContainer->setContentsMargins(0,24,0,16);
    titleLabel->setContentsMargins(16,0,0,0);
    titleLabel->setWordWrap(true);
    titleLabel->setMinimumWidth(325);
    titleLabel->setMaximumWidth(325);
    titleLabel->setMaximumWidth(325-24-16);
    titleLabel->setStyleSheet(TITLE_LABLE);
    connect(backButton, &QSvgButton::clicked, this, &Groups::onBackPressed);





    infoContainer->setAlignment(Qt::AlignTop);
    infoContainer->addLayout(titleContainer);
    infoContainer->addLayout(buttonContainer);

    QHBoxLayout *groupContainer = new QHBoxLayout;

    QPushButton *inviteGroupButton = new QPushButton("Пригласить в группу");



    inviteGroupButton->setStyleSheet(BUTTON_SOLID);




    QHBoxLayout *groupButtonContainer = new QHBoxLayout;


    groupButtonContainer->addWidget(inviteGroupButton);





    QLabel *groupImageLabel = new QLabel("");

    QPixmap groupImage(":/resc/resc/group.svg");

    groupImageLabel->setPixmap(groupImage);
    groupImageLabel->setStyleSheet(FRIEND_IMAGE);


    QLabel *groupName = new QLabel("Group 1");


    groupName->setStyleSheet(FRIEND_NAME_SURNAME);






     groupContainer->setAlignment(Qt::AlignTop);


     groupContainer->addWidget(groupImageLabel);
     groupContainer->addWidget(groupName);



    groupContainer->addLayout(groupButtonContainer);


    QHBoxLayout *groupContainer2 = new QHBoxLayout;
    QLabel *groupImageLabel2 = new QLabel("");
    QPixmap groupImage2(":/resc/resc/group.svg");
    groupImageLabel2->setPixmap(groupImage2);
    groupImageLabel2->setStyleSheet(FRIEND_IMAGE);

    QLabel *groupName2 = new QLabel("Group 2");

    groupName2->setStyleSheet(FRIEND_NAME_SURNAME);

    QPushButton *inviteGroupButton2 = new QPushButton("Пригласить в группу");

    inviteGroupButton2->setStyleSheet(BUTTON_SOLID);

    QHBoxLayout *groupButtonContainer2 = new QHBoxLayout;

    groupButtonContainer2->addWidget(inviteGroupButton2);
    groupContainer2->addWidget(groupImageLabel2);
    groupContainer2->addWidget(groupName2);
    groupContainer2->addLayout(groupButtonContainer2);
    groupContainer2->setAlignment(Qt::AlignTop);


    QHBoxLayout *groupContainer3 = new QHBoxLayout;
    QLabel *groupImageLabel3 = new QLabel("");
    QPixmap groupImage3(":/resc/resc/group.svg");
    groupImageLabel3->setPixmap(groupImage3);
    groupImageLabel3->setStyleSheet(FRIEND_IMAGE);

    QLabel *groupName3 = new QLabel("Group 3");

    groupName3->setStyleSheet(FRIEND_NAME_SURNAME);

    QPushButton *inviteGroupButton3 = new QPushButton("Пригласить в группу");

    inviteGroupButton3->setStyleSheet(BUTTON_SOLID);

    QHBoxLayout *groupButtonContainer3 = new QHBoxLayout;

    groupButtonContainer3->addWidget(inviteGroupButton3);
    groupContainer3->addWidget(groupImageLabel3);
    groupContainer3->addWidget(groupName3);
    groupContainer3->addLayout(groupButtonContainer3);
    groupContainer3->setAlignment(Qt::AlignTop);




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


    QScrollArea *deskScrollArea = new QScrollArea;
    deskScrollArea->setMinimumWidth(396);
    deskScrollArea->setFrameShape(QFrame::NoFrame);
    QWidget *scrolContainer = new QWidget;
    scrolContainer->setObjectName("container");
    scrolContainer->setStyleSheet(GLOBAL_BACK_WHITE);
    deskScrollArea->setStyleSheet(SCROL_BAR);
    QHBoxLayout *content = new QHBoxLayout;
    content->setAlignment(Qt::AlignHCenter);
    scrolContainer->setLayout(content);
    deskScrollArea->setWidget(scrolContainer);
    deskScrollArea->setWidgetResizable(true);
    deskScrollArea->horizontalScrollBar()->setEnabled(false);



    mainHLayout->addLayout(infoContainer);

    mainHLayout->addLayout(groupContainer);
    mainHLayout->addLayout(groupContainer2);
    //mainHLayout->addLayout(groupContainer3);

    //mainHLayout->addWidget(deskScrollArea);
    mainHLayout->addStretch();

    mainHLayout->setAlignment(Qt::AlignLeft);

    this->setLayout(mainHLayout);
    this->setStyleSheet(BACK_WHITE);
    this->setObjectName("fragment");

    networkManagerGroup = new QNetworkAccessManager();
    connect(networkManagerGroup, &QNetworkAccessManager::finished, this, &Groups::onHttpResult);

    loadGroups();
}

Groups::~Groups() {
    delete titleLabel;
    delete networkManagerGroup;
}





void Groups::onBackPressed() {
    back();
}


void Groups::onHttpResult(QNetworkReply *reply) {

}

void Groups::loadGroups() {
    QJsonObject loadGroupsJson;
    QJsonObject userIDJson;
    userIDJson.insert("userID", "213564544");
    loadGroupsJson.insert("getGroups", userIDJson);

        qDebug() << "create request" << endl;



        QNetworkRequest request(QUrl(SERVER_URL + ""));
        request.setHeader(QNetworkRequest::ContentTypeHeader,
                          QStringLiteral("application/json;charset=utf-8"));
        qDebug() << "request data"<< QJsonDocument(loadGroupsJson).toJson(QJsonDocument::Compact) << endl;
        networkManagerGroup->post(
            request,
            QJsonDocument(loadGroupsJson).toJson(QJsonDocument::Compact)
        );
        qDebug() << "request send" << endl;
    }


