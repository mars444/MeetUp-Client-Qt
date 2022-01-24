#include "Settings.h"

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
#include <QMovie>

#include "ui/auth/user_data.h"

#include <ui/view/qsvgbutton.h>
#include <ui/view/waitingspinnerwidget.h>
using namespace screens;
Settings::Settings() {

    std::string IDstd = GetId();

    ID_QSTRING = QString::fromUtf8(IDstd.c_str());

    QVBoxLayout *mainVLayout = new QVBoxLayout;

    QHBoxLayout *titleContainer = new QHBoxLayout;
    QSvgButton *backButton = new QSvgButton(":/resc/resc/arrow_back.svg", QSize(24,24));
    titleLabel = new QLabel(tr("Settings"));

    connect(backButton, &QSvgButton::clicked, this, &Settings::onBackPressed);


    titleContainer->addWidget(backButton);
    titleContainer->addWidget(titleLabel);


    mainVLayout->addLayout(titleContainer);


    mainVLayout->setAlignment(Qt::AlignTop);


    this->setLayout(mainVLayout);
    this->setStyleSheet(BACK_WHITE);
    this->setObjectName("fragment");

    setSettingsButton->setStyleSheet(BUTTON_DISABLED);

}

Settings::~Settings() {


    //delete loading;
    delete titleLabel;
    networkManager->clearAccessCache();

}




void Settings::onBackPressed() {
    back();
}

