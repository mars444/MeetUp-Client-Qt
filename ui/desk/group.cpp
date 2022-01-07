#include "Group.h"

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
    mainVLayout->setAlignment(Qt::AlignLeft);
    mainVLayout->addLayout(inputContainer);
       mainVLayout->addLayout(GroupContainerMain);
    mainVLayout->addLayout(GroupContainer);






    mainVLayout->addStretch();

    this->setLayout(mainVLayout);
    this->setStyleSheet(BACK_WHITE);
    this->setObjectName("fragment");

    checkData();

    networkManager = new QNetworkAccessManager();
    connect(networkManager, &QNetworkAccessManager::finished, this, &Group::onHttpResult);

    loadGroup();
}

Group::~Group() {


    //delete loading;
    delete GrouptitleLabel;
    networkManager->clearAccessCache();
}

void Group::checkData() {

}

void Group::onBackPressed() {
    back();
}



void Group::onHttpResult(QNetworkReply *reply) {

}

void Group::loadGroup() {
    QJsonObject loadGroupJson;
    QJsonObject userIDJson;
    userIDJson.insert("userID", "213564544");
    loadGroupJson.insert("getGroup", userIDJson);

        qDebug() << "create request" << endl;



        QNetworkRequest request(QUrl(SERVER_URL + ""));
        request.setHeader(QNetworkRequest::ContentTypeHeader,
                          QStringLiteral("application/json;charset=utf-8"));
        qDebug() << "request data"<< QJsonDocument(loadGroupJson).toJson(QJsonDocument::Compact) << endl;
        networkManager->post(
            request,
            QJsonDocument(loadGroupJson).toJson(QJsonDocument::Compact)
        );
        qDebug() << "request send" << endl;
    }




