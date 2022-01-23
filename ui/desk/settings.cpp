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


    qDebug()<<"1"<<endl;



    QHBoxLayout *innerDataSettigs = new QHBoxLayout;



    QVBoxLayout *settingsInnerRight = new QVBoxLayout;


    QHBoxLayout *inputcountryInner = new QHBoxLayout;
    usercountryEdit = new QLineEdit;
    usercountryLabel = new QLabel(tr("Country:"));
    usercountryEdit->setMaximumWidth(355);
    usercountryEdit->setMinimumWidth(355);
    usercountryEdit->setMinimumHeight(50);
    usercountryEdit->setMaximumHeight(50);
    usercountryEdit->setStyleSheet(EDIT_TEXT);
    usercountryEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    inputcountryInner->addWidget(usercountryLabel);
    inputcountryInner->addWidget(usercountryEdit);

    qDebug()<<"2"<<endl;

    QHBoxLayout *inputindexInner = new QHBoxLayout;
    userindexEdit = new QLineEdit;
    userindexLabel = new QLabel(tr("Index:"));
    userindexEdit->setMaximumWidth(355);
    userindexEdit->setMinimumWidth(355);
    userindexEdit->setMinimumHeight(50);
    userindexEdit->setMaximumHeight(50);
    userindexEdit->setStyleSheet(EDIT_TEXT);
    userindexEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    inputindexInner->addWidget(userindexLabel);
    inputindexInner->addWidget(userindexEdit);

    QHBoxLayout *inputdistrictInner = new QHBoxLayout;
    userdistrictEdit = new QLineEdit;
    userdistrictLabel = new QLabel(tr("District:"));
    userdistrictEdit->setMaximumWidth(355);
    userdistrictEdit->setMinimumWidth(355);
    userdistrictEdit->setMinimumHeight(50);
    userdistrictEdit->setMaximumHeight(50);
    userdistrictEdit->setStyleSheet(EDIT_TEXT);
    userdistrictEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    inputdistrictInner->addWidget(userdistrictLabel);
    inputdistrictInner->addWidget(userdistrictEdit);

    QHBoxLayout *inputcityInner = new QHBoxLayout;
    usercityEdit = new QLineEdit;
    usercityLabel = new QLabel(tr("City:"));
    usercityEdit->setMaximumWidth(355);
    usercityEdit->setMinimumWidth(355);
    usercityEdit->setMinimumHeight(50);
    usercityEdit->setMaximumHeight(50);
    usercityEdit->setStyleSheet(EDIT_TEXT);
    usercityEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    inputcityInner->addWidget(usercityLabel);
    inputcityInner->addWidget(usercityEdit);


    QHBoxLayout *inputstreetInner = new QHBoxLayout;
    userstreetEdit = new QLineEdit;
    userstreetLabel = new QLabel(tr("Street:"));
    userstreetEdit->setMaximumWidth(355);
    userstreetEdit->setMinimumWidth(355);
    userstreetEdit->setMinimumHeight(50);
    userstreetEdit->setMaximumHeight(50);
    userstreetEdit->setStyleSheet(EDIT_TEXT);
    userstreetEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    inputstreetInner->addWidget(userstreetLabel);
    inputstreetInner->addWidget(userstreetEdit);

    QHBoxLayout *inputhousingInner = new QHBoxLayout;
    userhousingEdit = new QLineEdit;
    userhousingLabel = new QLabel(tr("Housing:"));
    userhousingEdit->setMaximumWidth(355);
    userhousingEdit->setMinimumWidth(355);
    userhousingEdit->setMinimumHeight(50);
    userhousingEdit->setMaximumHeight(50);
    userhousingEdit->setStyleSheet(EDIT_TEXT);
    userhousingEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    inputhousingInner->addWidget(userhousingLabel);
    inputhousingInner->addWidget(userhousingEdit);

    qDebug()<<"3"<<endl;

    QHBoxLayout *inputbuildingInner = new QHBoxLayout;
    userbuildingEdit = new QLineEdit;
    userbuildingLabel = new QLabel(tr("Building:"));
    userbuildingEdit->setMaximumWidth(355);
    userbuildingEdit->setMinimumWidth(355);
    userbuildingEdit->setMinimumHeight(50);
    userbuildingEdit->setMaximumHeight(50);
    userbuildingEdit->setStyleSheet(EDIT_TEXT);
    userbuildingEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    inputbuildingInner->addWidget(userbuildingLabel);
    inputbuildingInner->addWidget(userbuildingEdit);

    qDebug()<<"4"<<endl;


    inputcountryInner->setContentsMargins(0,10,0,0);
    inputdistrictInner->setContentsMargins(0,10,0,0);
    inputcityInner->setContentsMargins(0,10,0,0);
    inputstreetInner->setContentsMargins(0,10,0,0);
    inputhousingInner->setContentsMargins(0,10,0,0);
    inputindexInner->setContentsMargins(0,10,0,0);


    settingsInnerRight->addLayout(inputcountryInner);
    settingsInnerRight->addLayout(inputdistrictInner);
    settingsInnerRight->addLayout(inputcityInner);
    settingsInnerRight->addLayout(inputstreetInner);
    settingsInnerRight->addLayout(inputhousingInner);
    //settingsInnerRight->addLayout(inputbuildingInner);
    settingsInnerRight->addLayout(inputindexInner);




    QVBoxLayout *settingsInner = new QVBoxLayout;

    QHBoxLayout *inputNameInner = new QHBoxLayout;
    userNameEdit = new QLineEdit;

    userNameLabel = new QLabel(tr("Name:"));
    userNameEdit->setMaximumWidth(355);
    userNameEdit->setMinimumWidth(355);
    userNameEdit->setMinimumHeight(50);
    userNameEdit->setMaximumHeight(50);
    userNameEdit->setStyleSheet(EDIT_TEXT);
    userNameEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    inputNameInner->addWidget(userNameLabel);
    inputNameInner->addWidget(userNameEdit);

    qDebug()<<"5"<<endl;



    QHBoxLayout *inputSurnameInner = new QHBoxLayout;
    userSurnameEdit = new QLineEdit;
    userSurnameLabel = new QLabel(tr("Surname:"));
    userSurnameEdit->setMaximumWidth(355);
    userSurnameEdit->setMinimumWidth(355);
    userSurnameEdit->setMinimumHeight(50);
    userSurnameEdit->setMaximumHeight(50);
    userSurnameEdit->setStyleSheet(EDIT_TEXT);
    userSurnameEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    inputSurnameInner->addWidget(userSurnameLabel);
    inputSurnameInner->addWidget(userSurnameEdit);



    QHBoxLayout *inputAgeInner = new QHBoxLayout;
    userAgeEdit = new QLineEdit;
    userAgeLabel = new QLabel(tr("Age:"));
    userAgeEdit->setMaximumWidth(355);
    userAgeEdit->setMinimumWidth(355);
    userAgeEdit->setMinimumHeight(50);
    userAgeEdit->setMaximumHeight(50);
    userAgeEdit->setStyleSheet(EDIT_TEXT);
    userAgeEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    inputAgeInner->addWidget(userAgeLabel);
    inputAgeInner->addWidget(userAgeEdit);

    QHBoxLayout *inputStatusInner = new QHBoxLayout;
    userStatusEdit = new QLineEdit;
    userStatusLabel = new QLabel(tr("Status:"));
    userStatusEdit->setMaximumWidth(355);
    userStatusEdit->setMinimumWidth(355);
    userStatusEdit->setMinimumHeight(50);
    userStatusEdit->setMaximumHeight(50);
    userStatusEdit->setStyleSheet(EDIT_TEXT);
    userStatusEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    inputStatusInner->addWidget(userStatusLabel);
    inputStatusInner->addWidget(userStatusEdit);


    QHBoxLayout *inputDescriptionInner = new QHBoxLayout;
    userDescriptionEdit = new QLineEdit;
    userDescriptionLabel = new QLabel(tr("Description:"));
    userDescriptionEdit->setMaximumWidth(355);
    userDescriptionEdit->setMinimumWidth(355);
    userDescriptionEdit->setMinimumHeight(50);
    userDescriptionEdit->setMaximumHeight(50);
    userDescriptionEdit->setStyleSheet(EDIT_TEXT);
    userDescriptionEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    inputDescriptionInner->addWidget(userDescriptionLabel);
    inputDescriptionInner->addWidget(userDescriptionEdit);

    QHBoxLayout *inputLabelInner = new QHBoxLayout;
    userLabelEdit = new QLineEdit;
    userLabelLabel = new QLabel(tr("Label:"));
    userLabelEdit->setMaximumWidth(355);
    userLabelEdit->setMinimumWidth(355);
    userLabelEdit->setMinimumHeight(50);
    userLabelEdit->setMaximumHeight(50);
    userLabelEdit->setStyleSheet(EDIT_TEXT);
    userLabelEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    inputLabelInner->addWidget(userLabelLabel);
    inputLabelInner->addWidget(userLabelEdit);


    QHBoxLayout *inputPhoneNumberInner = new QHBoxLayout;
    userPhoneNumberEdit = new QLineEdit;
    userPhoneNumberLabel = new QLabel(tr("PhoneNumber:"));
    userPhoneNumberEdit->setMaximumWidth(355);
    userPhoneNumberEdit->setMinimumWidth(355);
    userPhoneNumberEdit->setMinimumHeight(50);
    userPhoneNumberEdit->setMaximumHeight(50);
    userPhoneNumberEdit->setStyleSheet(EDIT_TEXT);
    userPhoneNumberEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    inputPhoneNumberInner->addWidget(userPhoneNumberLabel);
    inputPhoneNumberInner->addWidget(userPhoneNumberEdit);


    QHBoxLayout *inputMailInner = new QHBoxLayout;
    userMailEdit = new QLineEdit;
    userMailLabel = new QLabel(tr("Mail:"));
    userMailEdit->setMinimumWidth(355);
    userMailEdit->setMaximumWidth(355);
    userMailEdit->setMinimumHeight(50);
    userMailEdit->setMaximumHeight(50);
    userMailEdit->setStyleSheet(EDIT_TEXT);
    userMailEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    inputMailInner->addWidget(userMailLabel);
    inputMailInner->addWidget(userMailEdit);


    userMailLabel->setStyleSheet(SETTINGS_LABEL);
    userNameLabel->setStyleSheet(SETTINGS_LABEL);
    userSurnameLabel->setStyleSheet(SETTINGS_LABEL);
    userAgeLabel->setStyleSheet(SETTINGS_LABEL);
    userPhoneNumberLabel->setStyleSheet(SETTINGS_LABEL);
    usercountryLabel->setStyleSheet(SETTINGS_LABEL);
    userbuildingLabel->setStyleSheet(SETTINGS_LABEL);
    userhousingLabel->setStyleSheet(SETTINGS_LABEL);
    userstreetLabel->setStyleSheet(SETTINGS_LABEL);
    usercityLabel->setStyleSheet(SETTINGS_LABEL);
    userdistrictLabel->setStyleSheet(SETTINGS_LABEL);
    userStatusLabel->setStyleSheet(SETTINGS_LABEL);
    userLabelLabel->setStyleSheet(SETTINGS_LABEL);
    userDescriptionLabel->setStyleSheet(SETTINGS_LABEL);
    userindexLabel->setStyleSheet(SETTINGS_LABEL);





    QHBoxLayout *settingButtonContainer = new QHBoxLayout;

    setSettingsButton = new QPushButton(tr("                                       Save                       "));

    setSettingsButton->setStyleSheet(BUTTON_SOLID);

    setSettingsButton->setDisabled(true);

    setSettingsButton->setMaximumWidth(355);
    setSettingsButton->setMinimumWidth(355);




    connect(setSettingsButton, &QPushButton::clicked, this, &Settings::setSettings);



    titleLabel->setStyleSheet(TITLE_LABLE);

    connect(backButton, &QSvgButton::clicked, this, &Settings::onBackPressed);


    QLabel *centerContainer = new QLabel("");
    QMovie *movie = new QMovie( ":/resc/resc/settings_50px.gif" );
    centerContainer->setMovie(movie); // label имеет тип QLabel*
    movie->start();

    titleContainer->addWidget(backButton);
    titleContainer->addWidget(titleLabel);
    titleContainer->addWidget(centerContainer);
    titleContainer->setContentsMargins(0,10,5,25);
    titleLabel->setContentsMargins(16,0,16,0);

    titleContainer->setAlignment(Qt::AlignCenter);

    inputNameInner->setContentsMargins(0,10,0,0);
    inputSurnameInner->setContentsMargins(0,10,0,0);
    inputAgeInner->setContentsMargins(0,10,0,0);
    inputPhoneNumberInner->setContentsMargins(0,10,0,0);
    inputStatusInner->setContentsMargins(0,10,0,0);
    inputLabelInner->setContentsMargins(0,10,0,0);
    inputDescriptionInner->setContentsMargins(0,10,0,0);
    inputMailInner->setContentsMargins(0,10,0,0);

    settingsInner->addLayout(inputNameInner);
    settingsInner->addLayout(inputSurnameInner);
    settingsInner->addLayout(inputAgeInner);
    settingsInner->addLayout(inputPhoneNumberInner);
    settingsInner->addLayout(inputStatusInner);
    settingsInner->addLayout(inputLabelInner);
    settingsInner->addLayout(inputDescriptionInner);
    settingsInner->addLayout(inputMailInner);


    QIcon *ico;
    ico = new QIcon(":/resc/resc/cog.svg");

    userMailEdit->addAction(*ico, QLineEdit::LeadingPosition);
    userNameEdit->addAction(*ico, QLineEdit::LeadingPosition);
    userStatusEdit->addAction(*ico, QLineEdit::LeadingPosition);
    userAgeEdit->addAction(*ico, QLineEdit::LeadingPosition);
    usercityEdit->addAction(*ico, QLineEdit::LeadingPosition);
    userLabelEdit->addAction(*ico, QLineEdit::LeadingPosition);
    userindexEdit->addAction(*ico, QLineEdit::LeadingPosition);
    userstreetEdit->addAction(*ico, QLineEdit::LeadingPosition);
    userSurnameEdit->addAction(*ico, QLineEdit::LeadingPosition);
    usercountryEdit->addAction(*ico, QLineEdit::LeadingPosition);
    userhousingEdit->addAction(*ico, QLineEdit::LeadingPosition);
    userPhoneNumberEdit->addAction(*ico, QLineEdit::LeadingPosition);
    userDescriptionEdit->addAction(*ico, QLineEdit::LeadingPosition);
    userdistrictEdit->addAction(*ico, QLineEdit::LeadingPosition);
    userbuildingEdit->addAction(*ico, QLineEdit::LeadingPosition);





    settingButtonContainer->addWidget(setSettingsButton);

    settingButtonContainer->setAlignment(Qt::AlignRight);

    settingButtonContainer->setContentsMargins(30,10,0,0);




    QHBoxLayout *settingButtonRightContainer = new QHBoxLayout;
    setSettingsRightButton = new QPushButton(tr("                                Save address              "));

    setSettingsRightButton->setStyleSheet(BUTTON_DISABLED);

    setSettingsRightButton->setDisabled(true);

    setSettingsRightButton->setMaximumWidth(355);
    setSettingsRightButton->setMinimumWidth(355);
    connect(setSettingsRightButton, &QPushButton::clicked, this, &Settings::setSettingsRightPressed);
    settingButtonRightContainer->addWidget(setSettingsRightButton);
    settingButtonRightContainer->setAlignment(Qt::AlignRight);
    settingButtonRightContainer->setContentsMargins(30,10,0,0);



    QPixmap pixmapShedule(":/resc/resc/arrow_up.svg");
    QIcon ButtonIconShedule(pixmapShedule);
    setSettingsRightButton->setIcon(ButtonIconShedule);
    setSettingsRightButton->setIconSize(QSize(30,30));
    setSettingsRightButton -> setLayoutDirection ( Qt :: RightToLeft );
    setSettingsButton -> setLayoutDirection ( Qt :: RightToLeft );
    setSettingsButton->setIcon(ButtonIconShedule);
    setSettingsButton->setIconSize(QSize(30,30));


    settingsInnerRight->addLayout(settingButtonRightContainer);
    settingsInner->addLayout(settingButtonContainer);

    settingsInner->setAlignment(Qt::AlignCenter);

    settingsInnerRight->setAlignment(Qt::AlignCenter);

    QFrame *settingsInnerFrame = new QFrame;

    settingsInnerFrame->setStyleSheet(SETTING_LEFT_STYLE);

    settingsInnerFrame->setLayout(settingsInner);

    QFrame *settingsInnerRightFrame = new QFrame;

    settingsInnerRightFrame->setStyleSheet(SETTING_RIGHT_STYLE);

    settingsInnerRightFrame->setLayout(settingsInnerRight);


    innerDataSettigs->addWidget(settingsInnerFrame);

    innerDataSettigs->addWidget(settingsInnerRightFrame);

    innerDataSettigs->setAlignment(Qt::AlignJustify);
    innerDataSettigs->setAlignment(Qt::AlignTop);


    mainVLayout->addLayout(titleContainer);
    mainVLayout->addLayout(innerDataSettigs);


    mainVLayout->setAlignment(Qt::AlignTop);


    this->setLayout(mainVLayout);
    this->setStyleSheet(BACK_WHITE);
    this->setObjectName("fragment");





    setSettingsButton->setStyleSheet(BUTTON_DISABLED);


    checkData();

    networkManager = new QNetworkAccessManager();
    connect(networkManager, &QNetworkAccessManager::finished, this, &Settings::onHttpResult);

    networkManagerRight = new QNetworkAccessManager();
    connect(networkManagerRight, &QNetworkAccessManager::finished, this, &Settings::onHttpResultRight);


    networkManagerSetSettings = new QNetworkAccessManager();
    connect(networkManagerSetSettings, &QNetworkAccessManager::finished, this, &Settings::onHttpResultSetSettings);



    networkManagerSetSettingsRight = new QNetworkAccessManager();
    connect(networkManagerSetSettingsRight, &QNetworkAccessManager::finished, this, &Settings::onHttpResultSetSettingsRight);

    getSettings();


}

Settings::~Settings() {


    //delete loading;
    delete titleLabel;
    networkManager->clearAccessCache();
    networkManagerSetSettingsRight->clearAccessCache();
    networkManagerSetSettings->clearAccessCache();
    networkManagerRight->clearAccessCache();
}


void Settings::getSettings() {

    QJsonObject loadSettingsJson;
    QJsonObject userIDJson;
    userIDJson.insert("user_id", ID_QSTRING);
    loadSettingsJson.insert("get_personal", userIDJson);

    qDebug() << "create request" << endl;



    QNetworkRequest request(QUrl(SERVER_URL + ""));
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      QStringLiteral("application/json;charset=utf-8"));
    qDebug() << "request data"<< QJsonDocument(loadSettingsJson).toJson(QJsonDocument::Compact) << endl;

    request.setRawHeader("JSON_DATA", QJsonDocument(loadSettingsJson).toJson(QJsonDocument::Compact));
    networkManager->post(
                request,
                QJsonDocument(loadSettingsJson).toJson(QJsonDocument::Compact)
                );
    qDebug() << "request send" << endl;


}

void Settings::getSettingsRight() {


    QJsonObject loadSettingsJson;
    QJsonObject userIDJson;
    userIDJson.insert("user_id", ID_QSTRING);
    loadSettingsJson.insert("get_address", userIDJson);

    qDebug() << "create request" << endl;



    QNetworkRequest request(QUrl(SERVER_URL + ""));
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      QStringLiteral("application/json;charset=utf-8"));
    qDebug() << "request data"<< QJsonDocument(loadSettingsJson).toJson(QJsonDocument::Compact) << endl;

    request.setRawHeader("JSON_DATA", QJsonDocument(loadSettingsJson).toJson(QJsonDocument::Compact));
    networkManagerRight->post(
                request,
                QJsonDocument(loadSettingsJson).toJson(QJsonDocument::Compact)
                );
    qDebug() << "request send" << endl;

}


void Settings::setSettings() {
    setSettingsButton->setStyleSheet(BUTTON_DISABLED);
    setSettingsButton->setDisabled(true);

    QJsonObject setSettingsJson;
    QJsonObject userIDJson;
    userIDJson.insert("user_id", ID_QSTRING);
    userIDJson.insert("first_name", userNameEdit->text());
    userIDJson.insert("surname", userSurnameEdit->text());
    userIDJson.insert("age", userAgeEdit->text());
    userIDJson.insert("phone_number", userPhoneNumberEdit->text());
    userIDJson.insert("status", userStatusEdit->text());
    userIDJson.insert("label", userLabelEdit->text());
    userIDJson.insert("description", userDescriptionEdit->text());
    userIDJson.insert("email", userMailEdit->text());

    setSettingsJson.insert("write_personal", userIDJson);

    qDebug() << "create request" << endl;


    QNetworkRequest request(QUrl(SERVER_URL + ""));
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      QStringLiteral("application/json;charset=utf-8"));
    qDebug() << "request data"<< QJsonDocument(setSettingsJson).toJson(QJsonDocument::Compact) << endl;

    request.setRawHeader("JSON_DATA", QJsonDocument(setSettingsJson).toJson(QJsonDocument::Compact));

    networkManagerSetSettings->post(
                request,
                QJsonDocument(setSettingsJson).toJson(QJsonDocument::Compact)
                );
    qDebug() << "request send" << endl;
}


void Settings::setSettingsRightPressed() {

    setSettingsRightButton->setStyleSheet(BUTTON_DISABLED);
    setSettingsRightButton->setDisabled(true);

    QJsonObject setSettingsJson;
    QJsonObject userIDJson;
    userIDJson.insert("user_id", ID_QSTRING);
    userIDJson.insert("housing", userhousingEdit->text());
    userIDJson.insert("street", userstreetEdit->text());
    userIDJson.insert("city", usercityEdit->text());
    userIDJson.insert("district", userdistrictEdit->text());
    userIDJson.insert("index", userindexEdit->text());
    userIDJson.insert("country", usercountryEdit->text());

    setSettingsJson.insert("write_address", userIDJson);

    qDebug() << "create request" << endl;


    QNetworkRequest request(QUrl(SERVER_URL + ""));
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      QStringLiteral("application/json;charset=utf-8"));
    qDebug() << "request data"<< QJsonDocument(setSettingsJson).toJson(QJsonDocument::Compact) << endl;

    request.setRawHeader("JSON_DATA", QJsonDocument(setSettingsJson).toJson(QJsonDocument::Compact));

    networkManagerSetSettingsRight->post(
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
            (userPhoneNumberEdit->text().length() >= 4) &&
            (userAgeEdit->text().length() == 2 && userAgeEdit->text() >='0' && userAgeEdit->text() <= '9')) {
        setSettingsButton->setStyleSheet(BUTTON_SOLID);
        setSettingsButton->setDisabled(false);
    } else {
        setSettingsButton->setStyleSheet(BUTTON_DISABLED);
        setSettingsButton->setDisabled(true);
    }
}

void Settings::checkSettingsRight() {
    if (
            //(userbuildingEdit->text().length() >= 1 ) &&
            (userhousingEdit->text().length() >= 1 ) &&
            (userstreetEdit->text().length() >= 4) &&
            (usercityEdit->text().length() >= 4) &&
            (userdistrictEdit->text().length() >= 4) &&
            (userindexEdit->text().length() > 5) &&
            (usercountryEdit->text().length() >= 4)) {

        setSettingsRightButton->setStyleSheet(BUTTON_SOLID);
        setSettingsRightButton->setDisabled(false);
    } else {
        setSettingsRightButton->setStyleSheet(BUTTON_DISABLED);
        setSettingsRightButton->setDisabled(true);
    }
}




void Settings::onCreatePressed() {

}

void Settings::onHttpResult(QNetworkReply *reply) {

    qDebug() << "http finished" << endl;


    if(!reply->error()) {  //
        QByteArray resp = reply->readAll();
        qDebug() <<"ETO OTVET SERVERA GET settings :  " + resp  << endl;
        QJsonDocument doc = QJsonDocument::fromJson(resp);
        QJsonObject obj;


        std::string abc = resp.toStdString();

        qDebug() << "1111111111111\n";

        nlohmann::json j = nlohmann::json::parse(abc);

        qDebug() << "22222222222222222222 \n";

        if(j["get_personal"] != nullptr){

            qDebug() << "33333333333333333 \n";

            nlohmann::json value = j["get_personal"];

            qDebug() << "44444444444444 \n";

            userPhoneNumberEdit->setText(QString::fromStdString(value["phone_number"]).remove('"'));
            userAgeEdit->setText(QString::fromStdString(value["age"]).remove('"'));
            userLabelEdit->setText(QString::fromStdString(value["label"]).remove('"'));
            userStatusEdit->setText(QString::fromStdString(value["status"]).remove('"'));
            userSurnameEdit->setText(QString::fromStdString(value["surname"]).remove('"'));
            userNameEdit->setText(QString::fromStdString(value["first_name"]).remove('"'));
            userDescriptionEdit->setText(QString::fromStdString(value["description"]).remove('"'));
            userMailEdit->setText(QString::fromStdString(value["email"]).remove('"'));

            qDebug() << "5555555555555555 \n";

        }


    } else {


        qDebug() << reply->errorString();

        qDebug() <<  reply->readAll() << endl;

        qDebug () << reply -> error ();

        QMessageBox::warning(this, "Ошибка",
                             "Connection ERROR!\n");

    }


    reply->deleteLater();

    networkManager->clearAccessCache();

    getSettingsRight();



}

void Settings::onHttpResultRight(QNetworkReply *reply) {

    qDebug() << "http finished" << endl;


    if(!reply->error()) {  //
        QByteArray resp = reply->readAll();
        qDebug() <<"ETO OTVET SERVERA GET sett right:  " + resp  << endl;
        QJsonDocument doc = QJsonDocument::fromJson(resp);
        QJsonObject obj;


        std::string abc = resp.toStdString();

        nlohmann::json j = nlohmann::json::parse(abc);




        if(j["get_address"] != nullptr){

            nlohmann::json value = j["get_address"];

            //             userbuildingEdit->setText(QString::fromStdString(value["building"]).remove('"'));
            userhousingEdit->setText(QString::fromStdString(value["housing"]).remove('"'));
            userstreetEdit->setText(QString::fromStdString(value["street"]).remove('"'));
            usercityEdit->setText(QString::fromStdString(value["city"]).remove('"'));
            userdistrictEdit->setText(QString::fromStdString(value["district"]).remove('"'));
            userindexEdit->setText(QString::fromStdString(value["index"]).remove('"'));
            usercountryEdit->setText(QString::fromStdString(value["country"]).remove('"'));

        }


    } else {


        qDebug() << reply->errorString();

        qDebug() <<  reply->readAll() << endl;

        qDebug () << reply -> error ();

        QMessageBox::warning(this, "Ошибка",
                             "Connection ERROR!\n");

    }


    reply->deleteLater();

    networkManagerRight->clearAccessCache();

    connect(userMailEdit, &QLineEdit::textChanged, this, &Settings::checkSettings);
    connect(userNameEdit, &QLineEdit::textChanged, this, &Settings::checkSettings);
    connect(userSurnameEdit, &QLineEdit::textChanged, this, &Settings::checkSettings);
    connect(userAgeEdit, &QLineEdit::textChanged, this, &Settings::checkSettings);
    connect(userPhoneNumberEdit, &QLineEdit::textChanged, this, &Settings::checkSettings);


    //connect(userbuildingEdit, &QLineEdit::textChanged, this, &Settings::checkSettingsRight);
    connect(userhousingEdit, &QLineEdit::textChanged, this, &Settings::checkSettingsRight);
    connect(userstreetEdit, &QLineEdit::textChanged, this, &Settings::checkSettingsRight);
    connect(usercityEdit, &QLineEdit::textChanged, this, &Settings::checkSettingsRight);
    connect(userdistrictEdit, &QLineEdit::textChanged, this, &Settings::checkSettingsRight);
    connect(userindexEdit, &QLineEdit::textChanged, this, &Settings::checkSettingsRight);
    connect(usercountryEdit, &QLineEdit::textChanged, this, &Settings::checkSettingsRight);

}




void Settings::onHttpResultSetSettings(QNetworkReply *reply) {


    qDebug() << "http finished" << endl;


    if(!reply->error()) {  //
        QByteArray resp = reply->readAll();
        qDebug() <<"ETO OTVET SERVERA GET CONTACTS for group layout :  " + resp  << endl;
        QJsonDocument doc = QJsonDocument::fromJson(resp);
        QJsonObject obj;


        std::string abc = resp.toStdString();

        nlohmann::json j = nlohmann::json::parse(abc);

        nlohmann::json value = j;

        if(j["write_personal"] == "OK"){

            qDebug() << "Данные польз записаны" << endl;

        }


    } else {


        qDebug() << reply->errorString();

        qDebug() <<  reply->readAll() << endl;

        qDebug () << reply -> error ();

        QMessageBox::warning(this, "Error",
                             "Connection ERROR!\n");

    }


    reply->deleteLater();

    networkManagerSetSettings->clearAccessCache();

}




void Settings::onHttpResultSetSettingsRight(QNetworkReply *reply) {

    qDebug() << "http finished" << endl;


    if(!reply->error()) {  //
        QByteArray resp = reply->readAll();
        qDebug() <<"ETO OTVET SERVERA GET CONTACTS for group layout :  " + resp  << endl;
        QJsonDocument doc = QJsonDocument::fromJson(resp);
        QJsonObject obj;


        std::string abc = resp.toStdString();

        nlohmann::json j = nlohmann::json::parse(abc);

        nlohmann::json value = j;

        if(j["write_adress"] == "OK"){

            qDebug() << "Данные  адрес записаны" << endl;

        }

    } else {


        qDebug() << reply->errorString();

        qDebug() <<  reply->readAll() << endl;

        qDebug () << reply -> error ();

        QMessageBox::warning(this, "Ошибка",
                             "Connection ERROR!\n");

    }


    reply->deleteLater();

    networkManagerSetSettingsRight->clearAccessCache();

}

void Settings::setData(BaseModel *model) {

}
