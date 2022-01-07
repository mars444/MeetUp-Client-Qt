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

#include <ui/view/qsvgbutton.h>
#include <ui/view/waitingspinnerwidget.h>
using namespace screens;
Settings::Settings() {





    QVBoxLayout *mainVLayout = new QVBoxLayout;
   QHBoxLayout *inputContainer = new QHBoxLayout;

    QHBoxLayout *titleContainer = new QHBoxLayout;
    QSvgButton *backButton = new QSvgButton(":/resc/resc/arrow_back.svg", QSize(24,24));
    titleLabel = new QLabel("Настройки");


     QVBoxLayout *settingsInner = new QVBoxLayout;







     QHBoxLayout *inputNameInner = new QHBoxLayout;
     userNameEdit = new QLineEdit;
     userNameLabel = new QLabel("Name:");
     userNameEdit->setMaximumWidth(355);
     userNameEdit->setMinimumWidth(355);
     userNameEdit->setStyleSheet(EDIT_TEXT);
     userNameEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
     userNameEdit->setPlaceholderText("2");
     inputNameInner->addWidget(userNameLabel);
     inputNameInner->addWidget(userNameEdit);



     QHBoxLayout *inputSurnameInner = new QHBoxLayout;
     userSurnameEdit = new QLineEdit;
     userSurnameLabel = new QLabel("Surname:");
     userSurnameEdit->setMaximumWidth(355);
     userSurnameEdit->setMinimumWidth(355);
     userSurnameEdit->setStyleSheet(EDIT_TEXT);
     userSurnameEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
     userSurnameEdit->setPlaceholderText("3");
     inputSurnameInner->addWidget(userSurnameLabel);
     inputSurnameInner->addWidget(userSurnameEdit);



     QHBoxLayout *inputAgeInner = new QHBoxLayout;
     userAgeEdit = new QLineEdit;
     userAgeLabel = new QLabel("Age:");
     userAgeEdit->setMaximumWidth(355);
     userAgeEdit->setMinimumWidth(355);
     userAgeEdit->setStyleSheet(EDIT_TEXT);
     userAgeEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
     userAgeEdit->setPlaceholderText("4");
     inputAgeInner->addWidget(userAgeLabel);
     inputAgeInner->addWidget(userAgeEdit);


    QHBoxLayout *inputAdressInner = new QHBoxLayout;
     userAdressEdit = new QLineEdit;
     userAdressLabel = new QLabel("Adress:");
     userAdressEdit->setMaximumWidth(355);
     userAdressEdit->setMinimumWidth(355);
     userAdressEdit->setStyleSheet(EDIT_TEXT);
     userAdressEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
     userAdressEdit->setPlaceholderText("5");
     inputAdressInner->addWidget(userAdressLabel);
      inputAdressInner->addWidget(userAdressEdit);


    QHBoxLayout *inputMailInner = new QHBoxLayout;
    userMailEdit = new QLineEdit;

     userMailLabel = new QLabel("Mail:");
      userMailEdit->setMinimumWidth(355);
     userMailEdit->setMaximumWidth(355);
     userMailEdit->setStyleSheet(EDIT_TEXT);
     userMailEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
     userMailEdit->setPlaceholderText("6");
     inputMailInner->addWidget(userMailLabel);
     inputMailInner->addWidget(userMailEdit);







    userMailLabel->setStyleSheet(SETTINGS_LABEL);
    userNameLabel->setStyleSheet(SETTINGS_LABEL);
    userSurnameLabel->setStyleSheet(SETTINGS_LABEL);
    userAgeLabel->setStyleSheet(SETTINGS_LABEL);
    userAdressLabel->setStyleSheet(SETTINGS_LABEL);



    QHBoxLayout *settingButtonContainer = new QHBoxLayout;

    setSettingsButton = new QPushButton("Сохранить");

    setSettingsButton->setStyleSheet(BUTTON_SOLID);

    setSettingsButton->setMaximumWidth(355);
    setSettingsButton->setMinimumWidth(355);



     connect(setSettingsButton, &QPushButton::clicked, this, &Settings::setSettings);





    titleLabel->setStyleSheet(TITLE_LABLE);
    connect(backButton, &QSvgButton::clicked, this, &Settings::onBackPressed);
    titleContainer->addWidget(backButton);
    titleContainer->addWidget(titleLabel);
    titleContainer->setContentsMargins(0,24,0,16);
    titleLabel->setContentsMargins(16,0,0,0);

    titleContainer->setAlignment(Qt::AlignHCenter);

    inputContainer->setAlignment(Qt::AlignLeft);
    inputContainer->addLayout(titleContainer);

    settingsInner->addLayout(inputContainer);
    settingsInner->addLayout(inputNameInner);
    settingsInner->addLayout(inputSurnameInner);
    settingsInner->addLayout(inputAgeInner);
    settingsInner->addLayout(inputAdressInner);
    settingsInner->addLayout(inputMailInner);
    settingButtonContainer->addWidget(setSettingsButton);
    settingButtonContainer->setAlignment(Qt::AlignRight);
    settingButtonContainer->setContentsMargins(30,30,0,0);
    settingsInner->addLayout(settingButtonContainer);

    settingsInner->setAlignment(Qt::AlignTop);
    settingsInner->setAlignment(Qt::AlignHCenter);




    mainVLayout->addLayout(settingsInner);
    mainVLayout->setAlignment(Qt::AlignHCenter);
    mainVLayout->setAlignment(Qt::AlignTop);




    this->setLayout(mainVLayout);
    this->setStyleSheet(BACK_WHITE);
    this->setObjectName("fragment");

    setSettingsButton->setStyleSheet(BUTTON_DISABLED);
     setSettingsButton->setDisabled(true);

    connect(userMailEdit, &QLineEdit::textChanged, this, &Settings::checkSettings);
    connect(userNameEdit, &QLineEdit::textChanged, this, &Settings::checkSettings);
    connect(userSurnameEdit, &QLineEdit::textChanged, this, &Settings::checkSettings);
    connect(userAgeEdit, &QLineEdit::textChanged, this, &Settings::checkSettings);
    connect(userAdressEdit, &QLineEdit::textChanged, this, &Settings::checkSettings);


    checkData();

    networkManager = new QNetworkAccessManager();
    connect(networkManager, &QNetworkAccessManager::finished, this, &Settings::onHttpResult);


    networkManagerSetSettings = new QNetworkAccessManager();
    connect(networkManagerSetSettings, &QNetworkAccessManager::finished, this, &Settings::onHttpResultSetSettings);

        getSettings();


}

Settings::~Settings() {


    //delete loading;
    delete titleLabel;
    networkManager->clearAccessCache();
}


void Settings::getSettings() {


  str = "{\"userAdress\":\"moscow\",\"userAge\":\"34\",\"userID\":\"213564544\",\"userMail\":\"eml@mail.ru\",\"userName\":\"piter\",\"userSurname\":\"pamuj\"}";

    //str = "{\"userID\":\"666666\",\"userName\":\"MeetUser\"}";
       nlohmann::json j = nlohmann::json::parse(str);


        nlohmann::json value = j;


        userAdressEdit->setText(QString::fromStdString(value["userAdress"]).remove('"'));
        userAgeEdit->setText(QString::fromStdString(value["userAge"]).remove('"'));
        userMailEdit->setText(QString::fromStdString(value["userMail"]).remove('"'));
        userNameEdit->setText(QString::fromStdString(value["userName"]).remove('"'));
        userSurnameEdit->setText(QString::fromStdString(value["userSurname"]).remove('"'));



//    QJsonObject loadSettingsJson;
//    QJsonObject userIDJson;
//    userIDJson.insert("userID", "213564544");
//    loadSettingsJson.insert("getSettings", userIDJson);

//        qDebug() << "create request" << endl;



//        QNetworkRequest request(QUrl(SERVER_URL + ""));
//        request.setHeader(QNetworkRequest::ContentTypeHeader,
//                          QStringLiteral("application/json;charset=utf-8"));
//        qDebug() << "request data"<< QJsonDocument(loadSettingsJson).toJson(QJsonDocument::Compact) << endl;
//        networkManager->post(
//            request,
//            QJsonDocument(loadSettingsJson).toJson(QJsonDocument::Compact)
//        );
//        qDebug() << "request send" << endl;
}


void Settings::setSettings() {
    setSettingsButton->setStyleSheet(BUTTON_DISABLED);
     setSettingsButton->setDisabled(true);

    QJsonObject setSettingsJson;
    QJsonObject userIDJson;
    userIDJson.insert("userID", "213564544");
    userIDJson.insert("userName", userNameEdit->text());
    userIDJson.insert("userSurname", userSurnameEdit->text());
    userIDJson.insert("userAge", userAgeEdit->text());
    userIDJson.insert("userAdress", userAdressEdit->text());
    userIDJson.insert("userMail", userMailEdit->text());

    setSettingsJson.insert("getSettings", userIDJson);

        qDebug() << "create request" << endl;



        QNetworkRequest request(QUrl(SERVER_URL + ""));
        request.setHeader(QNetworkRequest::ContentTypeHeader,
                          QStringLiteral("application/json;charset=utf-8"));
        qDebug() << "request data"<< QJsonDocument(setSettingsJson).toJson(QJsonDocument::Compact) << endl;
        networkManager->post(
            request,
            QJsonDocument(setSettingsJson).toJson(QJsonDocument::Compact)
        );
        qDebug() << "request send" << endl;
    }






void Settings::checkData() {

}

void Settings::onBackPressed() {
    back();
}

void Settings::checkSettings() {
    if ((userMailEdit->text().length() >= 4) &&
            (userNameEdit->text().length() >= 4) &&
            (userSurnameEdit->text().length() >= 4) &&
            (userAdressEdit->text().length() >= 4) &&
            (userAgeEdit->text().length() == 2 && userAgeEdit->text() >='0' && userAgeEdit->text() <= '9')) {
        setSettingsButton->setStyleSheet(BUTTON_SOLID);
         setSettingsButton->setDisabled(false);
    } else {
        setSettingsButton->setStyleSheet(BUTTON_DISABLED);
         setSettingsButton->setDisabled(true);
    }
}

void Settings::onCreatePressed() {

}

void Settings::onHttpResult(QNetworkReply *reply) {

}

void Settings::onHttpResultSetSettings(QNetworkReply *reply) {

}

void Settings::setData(BaseModel *model) {

}
