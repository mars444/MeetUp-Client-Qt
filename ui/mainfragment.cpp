#include "mainfragment.h"

#include "auth/user_data.h"

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
#include <iostream>
#include <QMovie>
#include <QToolButton>


using namespace screens;


MainFragment::MainFragment() {


    QHBoxLayout *mainHLayout = new QHBoxLayout;
    QVBoxLayout *profileContainer = new QVBoxLayout;

    QVBoxLayout *lentContainer = new QVBoxLayout;

    QPushButton *mySheduleButton = new QPushButton("Мое расписание");
    QPushButton *myFriendsButton = new QPushButton("Мои друзья");
    QPushButton *myGroupsButton = new QPushButton("Мои группы");
    QPushButton *mySettingsButton = new QPushButton("Профиль");



    QPixmap pixmapShedule(":/resc/resc/calendar.svg");
    QIcon ButtonIconShedule(pixmapShedule);
    mySheduleButton->setIcon(ButtonIconShedule);
    mySheduleButton->setIconSize(QSize(20,20));

    QPixmap pixmapFriends(":/resc/resc/user.svg");
    QIcon ButtonIconFriends(pixmapFriends);
    myFriendsButton->setIcon(ButtonIconFriends);
    myFriendsButton->setIconSize(QSize(20,20));

    QPixmap pixmapGroups(":/resc/resc/users.svg");
    QIcon ButtonIconGroups(pixmapGroups);

    myGroupsButton->setIcon(ButtonIconGroups);
    myGroupsButton->setIconSize(QSize(20,20));

    QPixmap pixmapSettings(":/resc/resc/cog.svg");
    QIcon ButtonIconSettings(pixmapSettings);
    mySettingsButton->setIcon(ButtonIconSettings);
    mySettingsButton->setIconSize(QSize(20,20));

    // QPushButton *mySettingsButton1 = new QPushButton("qwrqwrewrwer");

    exitButton = new QPushButton("Выйти из профиля");

    QPixmap pixmapexitButton(":/resc/resc/enter.svg");
    QIcon ButtonIconexitButton(pixmapexitButton);
    exitButton->setIcon(ButtonIconexitButton);
    exitButton->setIconSize(QSize(20,20));

    userContainer = new QVBoxLayout;
    QLabel *profileImageLabel = new QLabel("");
    QPixmap profileImage(":/resc/resc/user2.png");
    profileImageLabel->setPixmap(profileImage);


    QHBoxLayout *fuckContainer = new QHBoxLayout;

    //QString strq = QString::fromUtf8(userNameData.c_str());  // преобразование std string в QString

    std::string nick = GetNickname();

    QString nickQ = QString::fromUtf8(nick.c_str());


    userName = new QLabel(nickQ);

    userName->setAlignment(Qt::AlignCenter);

    QLabel *mainTitle = new QLabel("Лента новостей:");
    mainTitle->setAlignment(Qt::AlignCenter);

    mainTitle->setStyleSheet(MAIN_TITLE);

    QScrollArea *deskScrollArea = new QScrollArea;
    //deskScrollArea->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    deskScrollArea->setMinimumWidth(500);
    //deskScrollArea->setContentsMargins(50,0,0,0);
    //deskScrollArea->setFrameShape(QFrame::NoFrame);
    QWidget *scrolContainer = new QWidget;


    QFrame *loadingExitContainer = new QFrame;
    loadingExitContainer->setMinimumHeight(200);
    loadingExit = new WaitingSpinnerWidget(loadingExitContainer, true, false);
    loadingExit->setColor(QT_COLOR_PRIMARY);

    scrolContainer->setObjectName("container");
    scrolContainer->setStyleSheet(GLOBAL_BACK_WHITE);
    deskScrollArea->setStyleSheet(GLOBAL_BACK_WHITE);
    QHBoxLayout *deskContainer = new QHBoxLayout;
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



//    QLabel *centerContainer = new QLabel("");
//    QPixmap profileImage(":/resc/resc/loader.gif");
//    centerContainer->setPixmap(profileImage);





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


    QLabel *centerContainer = new QLabel("");
    QMovie *movie = new QMovie( ":/resc/resc/loader3.gif" );
    centerContainer->setMovie(movie); // label имеет тип QLabel*
    movie->start();

    deskContainer->addWidget(centerContainer);

    deskContainer->setAlignment(Qt::AlignCenter);

    mainHLayout->addLayout(profileContainer);
    mainHLayout->addLayout(lentContainer);
    mainHLayout->setAlignment(Qt::AlignHCenter);

    this->setLayout(mainHLayout);
    this->setStyleSheet(GLOBAL_BACK_WHITE);
    this->setObjectName("fragment");


    networkManager = new QNetworkAccessManager();
    connect(networkManager, &QNetworkAccessManager::finished, this, &MainFragment::onHttpResult);
}

MainFragment::~MainFragment() {
    delete networkManager;
    delete userName;
    delete loading;
    delete loadingExit;
    delete exitButton;
}

void MainFragment::onResume() {

}


void MainFragment::onExit() {
    navigateTo(START_TAG);
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

void MainFragment::Group() {
    navigateTo(GROUP);
}



void MainFragment::onHttpResult(QNetworkReply *reply) {

}







