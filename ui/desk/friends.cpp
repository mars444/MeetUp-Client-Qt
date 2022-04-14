#include "Friends.h"
#include "Layouts/friendlayout.h"

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
#include "ui/auth/user_data.h"

#include <QJsonArray>
#include <QRegularExpression>
#include <ui/view/qsvgbutton.h>
#include <ui/view/waitingspinnerwidget.h>

#include "flowlayout.h"
using namespace screens;

Friends::Friends() {

    QVBoxLayout *mainVerticalLayout = new QVBoxLayout;

    QHBoxLayout *friendHeaderInner = new QHBoxLayout;

    QSvgButton *backButton = new QSvgButton(":/resc/resc/arrow-left.svg", QSize(30,30));
    connect(backButton, &QPushButton::clicked, this, &Friends::onBackPressed);
    QLabel *friendHeaderTitle = new QLabel(tr("Friends"));
    friendHeaderTitle->setStyleSheet(TITLE_STYLE);
    friendHeaderTitle->setAlignment(Qt::AlignCenter);

    friendHeaderInner->addWidget(backButton);
    friendHeaderInner->addWidget(friendHeaderTitle);
    friendHeaderInner->setContentsMargins(40,20,40,30);

    QFrame *friendHeaderInnerFrame = new QFrame;
    friendHeaderInnerFrame->setContentsMargins(0,0,0,0);

    friendHeaderInnerFrame->setLayout(friendHeaderInner);

    friendHeaderInnerFrame->setStyleSheet(HEADER_FRAME_STYLE);


    QHBoxLayout *friendSearchInner = new QHBoxLayout;
    friendSearchInner->setContentsMargins(40,30,40,30);
    friendSearchInner->setAlignment(Qt::AlignCenter);


    QLineEdit *friendEdit = new QLineEdit;
    friendEdit->setMinimumHeight(50);
    friendEdit->setMaximumHeight(50);
    friendEdit->setMaximumWidth(800);
    friendEdit->setStyleSheet(EDIT_TEXT);
    friendEdit->setContentsMargins(0,0,50,0);

    QIcon *icoSearch;
    icoSearch = new QIcon(":/resc/resc/search.svg");
    friendEdit->addAction(*icoSearch, QLineEdit::LeadingPosition);

    QPushButton *addFriendButton = new QPushButton(tr("Add friend"));
    addFriendButton->setMinimumWidth(300);
    addFriendButton->setMaximumWidth(300);
    addFriendButton->setMaximumHeight(50);
    addFriendButton->setMinimumHeight(50);
    addFriendButton->setStyleSheet(BUTTON_SOLID);

    friendSearchInner->addWidget(friendEdit);
    friendSearchInner->addWidget(addFriendButton);

    FlowLayout *flowLayoutFriends = new FlowLayout;
    flowLayoutFriends->setContentsMargins(60,0,30,0);
    flowLayoutFriends->setAlignment(Qt::AlignCenter);

    for (int i=0;i<30 ;i ++ ) {
        friendInner = new QHBoxLayout;

        QLabel *friendImageLabel = new QLabel("");
        QPixmap friendImagePix(":/resc/resc/person.png");

        friendImageLabel->setPixmap(friendImagePix.scaled(100, 100, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
        friendImageLabel->setStyleSheet("QFrame {""background: transparent""}");
        friendImageLabel->setContentsMargins(0,20,0,0);


        QString s = QString::number(i);
        QPushButton *friendName = new QPushButton(s);
        friendName->setStyleSheet(FRIEND_NAME_STYLE);

        QLabel *friendStatusLabel = new QLabel("");
        QPixmap friendStatuseImagePix(":/resc/resc/online_status_onn.svg");
        friendStatusLabel->setPixmap(friendStatuseImagePix.scaled(15, 15, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
        friendStatusLabel->setStyleSheet("QFrame {""background: transparent""}");
        friendStatusLabel->setContentsMargins(0,20,0,0);



        deleteFriendBtn = new QPushButton("del");
        connect(deleteFriendBtn, &QPushButton::clicked, this, &Friends::deleteFriendBtnPressed);
        deleteFriendBtn->setMinimumHeight(50);


        deleteFriendYesBtn = new QPushButton("yes");
        connect(deleteFriendYesBtn, &QPushButton::clicked, this, &Friends::deleteFriendYesBtnPressed);

        deleteFriendNoBtn = new QPushButton("no");
        connect(deleteFriendNoBtn, &QPushButton::clicked, this, &Friends::deleteFriendNoBtnPressed);

        deleteFriendText = new QLabel(tr("You are sure??"));

        deleteFriendYesBtn->hide();
        deleteFriendNoBtn->hide();
        deleteFriendText->hide();

        friendInner->addWidget(friendImageLabel);
        friendInner->addWidget(friendName);
        friendInner->addWidget(friendStatusLabel);
        friendInner->addWidget(deleteFriendBtn);

        friendInner->addWidget(deleteFriendText);
        friendInner->addWidget(deleteFriendYesBtn);
        friendInner->addWidget(deleteFriendNoBtn);



        QFrame *friendFrame = new QFrame;
        friendFrame->setStyleSheet(HEADER_FRIEND_FRAME_STYLE);
        friendFrame->setLayout(friendInner);
        friendFrame->setMinimumWidth(500);
        friendFrame->setMaximumWidth(700);
        friendFrame->setMaximumHeight(200);
        friendFrame->setMinimumHeight(200);

        flowLayoutFriends->addWidget(friendFrame);
    }






    mainVerticalLayout->addWidget(friendHeaderInnerFrame);
    mainVerticalLayout->addLayout(friendSearchInner);
    mainVerticalLayout->setAlignment(Qt::AlignTop);
    mainVerticalLayout->setAlignment(Qt::AlignHCenter);


    QWidget *scrolContainer = new QWidget;
    scrolContainer->setLayout(flowLayoutFriends);
    scrolContainer->setStyleSheet("QFrame {""background: #ff0000""}");

    QScrollArea *deskScrollAreaFriends = new QScrollArea;
    deskScrollAreaFriends->setStyleSheet(SCROL_BAR);
    deskScrollAreaFriends->setWidget(scrolContainer);
    deskScrollAreaFriends->setAlignment(Qt::AlignCenter);
    deskScrollAreaFriends->setWidgetResizable(true);
    deskScrollAreaFriends->horizontalScrollBar()->setEnabled(false);

    mainVerticalLayout->addWidget(deskScrollAreaFriends);

    mainVerticalLayout->setContentsMargins(0,0,0,0);

    this->setLayout(mainVerticalLayout);
    this->setStyleSheet(BACK_WHITE);
    this->setObjectName("BG");
    this->setContentsMargins(0,0,0,0);



}

Friends::~Friends() {

}



void Friends::onBackPressed() {
    back();
}

void Friends::deleteFriendBtnPressed() {

    deleteFriendBtn->hide();
    deleteFriendYesBtn->show();
    deleteFriendNoBtn->show();
    deleteFriendText->show();
}

void Friends::deleteFriendYesBtnPressed() {

}


void Friends::deleteFriendNoBtnPressed() {
    deleteFriendBtn->show();
    deleteFriendYesBtn->hide();
    deleteFriendNoBtn->hide();
    deleteFriendText->hide();
}















