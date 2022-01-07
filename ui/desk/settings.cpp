#include "Settings.h"

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
Settings::Settings() {

    QHBoxLayout *mainHLayout = new QHBoxLayout;
    QVBoxLayout *inputContainer = new QVBoxLayout;

    QHBoxLayout *titleContainer = new QHBoxLayout;
    QSvgButton *backButton = new QSvgButton(":/resc/resc/arrow_back.svg", QSize(24,24));
    titleLabel = new QLabel("Настройки");

    QHBoxLayout *buttoContainer = new QHBoxLayout;
    createButton = new QPushButton("Добавить друзей");

    //QFrame *loadingContaiter = new QFrame;
   // loading = new WaitingSpinnerWidget(loadingContaiter, true, false);
    //loading->setColor(QT_COLOR_PRIMARY);
    //loadingContaiter->setMinimumWidth(100);




    titleLabel->setStyleSheet(TITLE_LABLE);
    connect(backButton, &QSvgButton::clicked, this, &Settings::onBackPressed);
    titleContainer->addWidget(backButton);
    titleContainer->addWidget(titleLabel);
    titleContainer->setContentsMargins(0,24,0,16);
    titleLabel->setContentsMargins(16,0,0,0);



    createButton->setStyleSheet(BUTTON_SOLID);
    createButton->setMaximumWidth(335);
    createButton->setMinimumWidth(335);
    connect(createButton, &QPushButton::clicked, this, &Settings::onCreatePressed);
   // buttoContainer->addWidget(loadingContaiter);
    buttoContainer->addWidget(createButton);
    buttoContainer->setAlignment(Qt::AlignRight);


    inputContainer->setAlignment(Qt::AlignTop);
    inputContainer->addLayout(titleContainer);
    inputContainer->addLayout(buttoContainer);
    mainHLayout->setAlignment(Qt::AlignLeft);
    mainHLayout->addLayout(inputContainer);

    this->setLayout(mainHLayout);
    this->setStyleSheet(BACK_WHITE);
    this->setObjectName("fragment");

    checkData();

    networkManager = new QNetworkAccessManager();
    connect(networkManager, &QNetworkAccessManager::finished, this, &Settings::onHttpResult);
}

Settings::~Settings() {


    //delete loading;
    delete titleLabel;
    networkManager->clearAccessCache();
}

void Settings::checkData() {

}

void Settings::onBackPressed() {
    back();
}

void Settings::onCreatePressed() {

}

void Settings::onHttpResult(QNetworkReply *reply) {

}

void Settings::setData(BaseModel *model) {

}
