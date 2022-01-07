#include "mainfragment.h"

#include "ui/auth/loginfragment.h"

#include "style/stylecontainer.h"
using namespace styles;
#include "screensfactory.h"

#include <QLabel>
#include <QPushButton>
#include <QSettings>
#include <QSvgWidget>
#include <QVBoxLayout>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QJsonArray>
#include <QScrollArea>
#include <QScrollBar>


using namespace screens;



MainFragment::MainFragment() {


    QHBoxLayout *mainHLayout = new QHBoxLayout;
    QVBoxLayout *profileContainer = new QVBoxLayout;

    QVBoxLayout *lentContainer = new QVBoxLayout;

    QPushButton *mySheduleButton = new QPushButton("Мое расписание");
    QPushButton *myFriendsButton = new QPushButton("Мои друзья");
    QPushButton *myGroupsButton = new QPushButton("Мои группы");
    QPushButton *mySettingsButton = new QPushButton("Настройки");
    exitButton = new QPushButton("Выйти из профиля");

    userContainer = new QVBoxLayout;
    QLabel *profileImageLabel = new QLabel("");
    QPixmap profileImage(":/resc/resc/user.png");
    profileImageLabel->setPixmap(profileImage);

    QHBoxLayout *fuckContainer = new QHBoxLayout;
    userName = new QLabel("Mars_444");


    QLabel *mainTitle = new QLabel("Лента новостей:");
    mainTitle->setAlignment(Qt::AlignCenter);

    mainTitle->setStyleSheet(MAIN_TITLE);



    QScrollArea *deskScrollArea = new QScrollArea;
    //deskScrollArea->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    deskScrollArea->setMinimumWidth(500);
    //deskScrollArea->setContentsMargins(50,0,0,0);
    //deskScrollArea->setFrameShape(QFrame::NoFrame);
    QWidget *scrolContainer = new QWidget;

    loading = new WaitingSpinnerWidget(scrolContainer, true, false);
    loading->setColor(QT_COLOR_PRIMARY);

    QFrame *loadingExitContainer = new QFrame;
    loadingExitContainer->setMinimumHeight(200);
    loadingExit = new WaitingSpinnerWidget(loadingExitContainer, true, false);
    loadingExit->setColor(QT_COLOR_PRIMARY);

    scrolContainer->setObjectName("container");
    scrolContainer->setStyleSheet(GLOBAL_BACK_WHITE);
    deskScrollArea->setStyleSheet(SCROL_BAR);
    QHBoxLayout *deskContainer = new QHBoxLayout;
    start = new QVBoxLayout;
    start->setAlignment(Qt::AlignTop);
    end = new QVBoxLayout;
    end->setAlignment(Qt::AlignTop);
    deskContainer->addLayout(start);
    deskContainer->addLayout(end);
    scrolContainer->setLayout(deskContainer);
    deskScrollArea->setWidget(scrolContainer);
    deskScrollArea->setWidgetResizable(true);
    deskScrollArea->horizontalScrollBar()->setEnabled(false);

    profileImageLabel->setStyleSheet(PROFILE_IMAGE);

    fuckContainer->addWidget(profileImageLabel);
    userContainer->addLayout(fuckContainer);
    userName->setStyleSheet(TITLE_LABLE);
    userName->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    userName->setContentsMargins(35,0,35,24);
    userContainer->addWidget(userName);
    userContainer->setAlignment(Qt::AlignCenter);

    mySheduleButton->setStyleSheet(BUTTON_PROFILE);
    mySheduleButton->setMaximumWidth(270);
    mySheduleButton->setMinimumWidth(270);
    connect(mySheduleButton, &QPushButton::clicked, this, &MainFragment::myShedule);

    myFriendsButton->setStyleSheet(BUTTON_PROFILE);
    myFriendsButton->setMaximumWidth(270);
    myFriendsButton->setMinimumWidth(270);
    connect(myFriendsButton, &QPushButton::clicked, this, &MainFragment::myFriends);

    myGroupsButton->setStyleSheet(BUTTON_PROFILE);
    myGroupsButton->setMaximumWidth(270);
    myGroupsButton->setMinimumWidth(270);
    connect(myGroupsButton, &QPushButton::clicked, this, &MainFragment::myGroups);

    mySettingsButton->setStyleSheet(BUTTON_PROFILE);
    mySettingsButton->setMaximumWidth(270);
    mySettingsButton->setMinimumWidth(270);
    connect(mySettingsButton, &QPushButton::clicked, this, &MainFragment::mySettings);

    exitButton->setStyleSheet(BUTTON_PROFILE_RED);
    exitButton->setMaximumWidth(270);
    exitButton->setMinimumWidth(270);
    connect(exitButton, &QPushButton::clicked, this, &MainFragment::onExit);

    profileContainer->addLayout(userContainer);
    profileContainer->addWidget(mySheduleButton);
    profileContainer->addWidget(myFriendsButton);
    profileContainer->addWidget(myGroupsButton);
    profileContainer->addWidget(mySettingsButton);
    profileContainer->addWidget(exitButton);
    profileContainer->addWidget(loadingExitContainer);
    profileContainer->setAlignment(Qt::AlignTop);

    lentContainer->addWidget(mainTitle);
    lentContainer->addWidget(deskScrollArea);

    mainHLayout->addLayout(profileContainer);
    mainHLayout->addLayout(lentContainer);
    mainHLayout->setAlignment(Qt::AlignHCenter);

    this->setLayout(mainHLayout);
    this->setStyleSheet(BACK_WHITE);
    this->setObjectName("fragment");

    loading->start();

    networkManager = new QNetworkAccessManager();
    connect(networkManager, &QNetworkAccessManager::finished, this, &MainFragment::onHttpResult);
    loadUserName();
}

MainFragment::~MainFragment() {
    delete networkManager;
    delete userName;
    delete start;
    delete end;
    delete loading;
    delete loadingExit;
    delete exitButton;
}

void MainFragment::onResume() {
    qDebug("main fragment onResume()");
    loading->start();
    loadUserName();
}

void MainFragment::loadUserName() {
    QJsonObject getUserNameJson;
    getUserNameJson.insert("getUserName", "");

    QNetworkRequest request(QUrl(SERVER_URL + ""));
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      QStringLiteral("application/json;charset=utf-8"));
     qDebug() << "request data"<< QJsonDocument(getUserNameJson).toJson(QJsonDocument::Compact) << endl;
    request.setRawHeader("Authorization", ("Bearer " + token).toLocal8Bit());
    networkManager->post(
        request,
      QJsonDocument(getUserNameJson).toJson(QJsonDocument::Compact)
    );
}

void MainFragment::onExit() {
    loadingExit->start();
    exitButton->setDisabled(true);

    QNetworkRequest request(QUrl(SERVER_URL + "exit"));
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      QStringLiteral("application/json;charset=utf-8"));
    request.setRawHeader("Authorization", ("Bearer " + token).toLocal8Bit());
    QNetworkReply* reply = networkManager->post(
        request,
        ""
    );
    reply->setProperty("type", EXIT);
    navigateTo(LOGIN_TAG);
}

void MainFragment::myFriends() {
    navigateTo(MY_FRIENDS_SCREEN);
}

void MainFragment::myGroups() {
    navigateTo(MY_GROUPS_SCREEN);
}


void MainFragment::myShedule() {
    navigateTo(MY_SHEDULE_SCREEN);
}

void MainFragment::mySettings() {
    navigateTo(MY_SETTINGS_SCREEN);
}



void MainFragment::onHttpResult(QNetworkReply *reply) {

}







