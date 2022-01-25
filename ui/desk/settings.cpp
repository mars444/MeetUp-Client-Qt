#include "Settings.h"
#include "switch.h"

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

     qDebug() << "1111111 \n";

    std::string IDstd = GetId();

    ID_QSTRING = QString::fromUtf8(IDstd.c_str());

    QVBoxLayout *mainVLayout = new QVBoxLayout;

    qDebug() << "2222222 \n";

    QHBoxLayout *titleContainer = new QHBoxLayout;
    QSvgButton *backButton = new QSvgButton(":/resc/resc/arrow_back.svg", QSize(24,24));
    titleLabel = new QLabel(tr("Settings"));
    titleLabel->setStyleSheet(TITLE_LABLE);
    titleLabel->setContentsMargins(16,0,16,0);

    qDebug() << "3333333 \n";

    connect(backButton, &QSvgButton::clicked, this, &Settings::onBackPressed);


    titleContainer->addWidget(backButton);
    titleContainer->setContentsMargins(0,10,5,25);
    titleContainer->setAlignment(Qt::AlignCenter);
    titleContainer->addWidget(titleLabel);



    QVBoxLayout *settingInner = new QVBoxLayout;

    QHBoxLayout *themeLayout = new QHBoxLayout;

    themeLayout->setAlignment(Qt::AlignCenter);

    QLabel *themeLabel = new QLabel(tr("Theme"));
    themeLabel->setStyleSheet(SETTINGSS_LABEL);

    QLabel *themeLightLabel = new QLabel(tr("    "));
    themeLightLabel->setStyleSheet(LIGHT);

    QLabel *themeDarkLabel = new QLabel(tr("    "));
    themeDarkLabel->setStyleSheet(DARK);

    themeLabel->setMaximumWidth(300);
    themeLabel->setMinimumWidth(300);

    themeLightLabel->setContentsMargins(0,0,50,0);

    themeDarkLabel->setContentsMargins(50,0,0,0);

    themeLightLabel->setMaximumWidth(60);
    themeLightLabel->setMinimumWidth(60);
    themeLightLabel->setMaximumHeight(60);
    themeLightLabel->setMinimumHeight(60);
    themeDarkLabel->setMaximumWidth(60);
    themeDarkLabel->setMinimumWidth(60);
    themeLabel->setAlignment(Qt::AlignCenter);

    Switch *dark_theme_switch = new Switch;

    dark_theme_switch->setMaximumWidth(75);
    dark_theme_switch->setMinimumWidth(75);

    dark_theme_switch->setContentsMargins(50,50,50,50);





    QFrame *settingFrame = new QFrame;
    settingFrame->setStyleSheet(SETTING_LEFT_STYLE);

    themeLayout->addWidget(themeLabel);

    themeLayout->addWidget(themeDarkLabel);

    themeLayout->addWidget(dark_theme_switch);

    themeLayout->addWidget(themeLightLabel);


    QHBoxLayout *languageLayout = new QHBoxLayout;

    QLabel *languageLabel = new QLabel(tr("Language"));
    languageLabel->setStyleSheet(SETTINGSS_LABEL);

    languageLabel->setMaximumWidth(300);
    languageLabel->setMinimumWidth(300);
    languageLabel->setMinimumHeight(60);

    languageLabel->setAlignment(Qt::AlignCenter);

    languageLayout->setAlignment(Qt::AlignCenter);

    languageLayout->setMargin(50);


    QComboBox *languageBox = new QComboBox;

    languageBox->setMinimumWidth(210);
    languageBox->setMaximumWidth(210);


    languageBox->addItem("English");
    languageBox->addItem("Русский");

    languageLayout->addWidget(languageLabel);
    languageLayout->addWidget(languageBox);




    settingInner->addLayout(themeLayout);
    settingInner->addLayout(languageLayout);

    settingFrame->setLayout(settingInner);




    qDebug() << "44444444 \n";


    mainVLayout->addLayout(titleContainer);

    mainVLayout->addWidget(settingFrame);

    qDebug() << "55555555 \n";


    mainVLayout->setAlignment(Qt::AlignTop);


    this->setLayout(mainVLayout);
    this->setStyleSheet(BACK_WHITE);
    this->setObjectName("fragment");

    qDebug() << "6666666 \n";

    qDebug() << "2222222 \n";

}

Settings::~Settings() {


    //delete loading;
    delete titleLabel;


}




void Settings::onBackPressed() {
    back();
}

