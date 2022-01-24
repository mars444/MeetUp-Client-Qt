#include "Profile.h"

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
profile::profile() {


    std::string IDstd = GetId();

    ID_QSTRING = QString::fromUtf8(IDstd.c_str());



    QVBoxLayout *mainVLayout = new QVBoxLayout;

    QHBoxLayout *titleContainer = new QHBoxLayout;
    QSvgButton *backButton = new QSvgButton(":/resc/resc/arrow_back.svg", QSize(24,24));
    titleLabel = new QLabel(tr("Profile"));


    qDebug()<<"1"<<endl;



    QHBoxLayout *innerDataSettigs = new QHBoxLayout;



    QVBoxLayout *profileInnerRight = new QVBoxLayout;


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


    profileInnerRight->addLayout(inputcountryInner);
    profileInnerRight->addLayout(inputdistrictInner);
    profileInnerRight->addLayout(inputcityInner);
    profileInnerRight->addLayout(inputstreetInner);
    profileInnerRight->addLayout(inputhousingInner);
    //profileInnerRight->addLayout(inputbuildingInner);
    profileInnerRight->addLayout(inputindexInner);




    QVBoxLayout *profileInner = new QVBoxLayout;

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






    QHBoxLayout *settingButtonContainer = new QHBoxLayout;

    setprofileButton = new QPushButton(tr("                                       Save                       "));

    setprofileButton->setStyleSheet(BUTTON_SOLID);

    setprofileButton->setDisabled(true);

    setprofileButton->setMaximumWidth(355);
    setprofileButton->setMinimumWidth(355);




    connect(setprofileButton, &QPushButton::clicked, this, &profile::setprofile);



    titleLabel->setStyleSheet(TITLE_LABLE);

    connect(backButton, &QSvgButton::clicked, this, &profile::onBackPressed);


    QLabel *centerContainer = new QLabel("");
    QMovie *movie = new QMovie( ":/resc/resc/profile_50px.gif" );
    centerContainer->setMovie(movie); // label имеет тип QLabel*
    //movie->start();

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

    profileInner->addLayout(inputNameInner);
    profileInner->addLayout(inputSurnameInner);
    profileInner->addLayout(inputAgeInner);
    profileInner->addLayout(inputPhoneNumberInner);
    profileInner->addLayout(inputStatusInner);
    profileInner->addLayout(inputLabelInner);
    profileInner->addLayout(inputDescriptionInner);
    profileInner->addLayout(inputMailInner);


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





    settingButtonContainer->addWidget(setprofileButton);

    settingButtonContainer->setAlignment(Qt::AlignRight);

    settingButtonContainer->setContentsMargins(30,10,0,0);




    QHBoxLayout *settingButtonRightContainer = new QHBoxLayout;
    setprofileRightButton = new QPushButton(tr("                                Save address              "));

    setprofileRightButton->setStyleSheet(BUTTON_DISABLED);

    setprofileRightButton->setDisabled(true);

    setprofileRightButton->setMaximumWidth(355);
    setprofileRightButton->setMinimumWidth(355);
    connect(setprofileRightButton, &QPushButton::clicked, this, &profile::setprofileRightPressed);
    settingButtonRightContainer->addWidget(setprofileRightButton);
    settingButtonRightContainer->setAlignment(Qt::AlignRight);
    settingButtonRightContainer->setContentsMargins(30,10,0,0);



    QPixmap pixmapShedule(":/resc/resc/arrow_up.svg");
    QIcon ButtonIconShedule(pixmapShedule);
    setprofileRightButton->setIcon(ButtonIconShedule);
    setprofileRightButton->setIconSize(QSize(30,30));
    setprofileRightButton -> setLayoutDirection ( Qt :: RightToLeft );
    setprofileButton -> setLayoutDirection ( Qt :: RightToLeft );
    setprofileButton->setIcon(ButtonIconShedule);
    setprofileButton->setIconSize(QSize(30,30));


    profileInnerRight->addLayout(settingButtonRightContainer);
    profileInner->addLayout(settingButtonContainer);

    profileInner->setAlignment(Qt::AlignCenter);

    profileInnerRight->setAlignment(Qt::AlignCenter);

    QFrame *profileInnerFrame = new QFrame;

    profileInnerFrame->setStyleSheet(SETTING_LEFT_STYLE);

    profileInnerFrame->setLayout(profileInner);

    QFrame *profileInnerRightFrame = new QFrame;

    profileInnerRightFrame->setStyleSheet(SETTING_RIGHT_STYLE);

    profileInnerRightFrame->setLayout(profileInnerRight);


    innerDataSettigs->addWidget(profileInnerFrame);

    innerDataSettigs->addWidget(profileInnerRightFrame);

    innerDataSettigs->setAlignment(Qt::AlignJustify);
    innerDataSettigs->setAlignment(Qt::AlignTop);


    mainVLayout->addLayout(titleContainer);
    mainVLayout->addLayout(innerDataSettigs);


    mainVLayout->setAlignment(Qt::AlignTop);


    this->setLayout(mainVLayout);
    this->setStyleSheet(BACK_WHITE);
    this->setObjectName("fragment");





    setprofileButton->setStyleSheet(BUTTON_DISABLED);


    checkData();

    networkManager = new QNetworkAccessManager();
    connect(networkManager, &QNetworkAccessManager::finished, this, &profile::onHttpResult);

    networkManagerRight = new QNetworkAccessManager();
    connect(networkManagerRight, &QNetworkAccessManager::finished, this, &profile::onHttpResultRight);


    networkManagerSetprofile = new QNetworkAccessManager();
    connect(networkManagerSetprofile, &QNetworkAccessManager::finished, this, &profile::onHttpResultSetprofile);



    networkManagerSetprofileRight = new QNetworkAccessManager();
    connect(networkManagerSetprofileRight, &QNetworkAccessManager::finished, this, &profile::onHttpResultSetprofileRight);

    getprofile();


}

profile::~profile() {


    //delete loading;
    delete titleLabel;
    networkManager->clearAccessCache();
    networkManagerSetprofileRight->clearAccessCache();
    networkManagerSetprofile->clearAccessCache();
    networkManagerRight->clearAccessCache();
}


void profile::getprofile() {

    QJsonObject loadprofileJson;
    QJsonObject userIDJson;
    userIDJson.insert("user_id", ID_QSTRING);
    loadprofileJson.insert("get_personal", userIDJson);

    qDebug() << "create request" << endl;



    QNetworkRequest request(QUrl(SERVER_URL + ""));
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      QStringLiteral("application/json;charset=utf-8"));
    qDebug() << "request data"<< QJsonDocument(loadprofileJson).toJson(QJsonDocument::Compact) << endl;

    request.setRawHeader("JSON_DATA", QJsonDocument(loadprofileJson).toJson(QJsonDocument::Compact));
    networkManager->post(
                request,
                QJsonDocument(loadprofileJson).toJson(QJsonDocument::Compact)
                );
    qDebug() << "request send" << endl;


}

void profile::getprofileRight() {


    QJsonObject loadprofileJson;
    QJsonObject userIDJson;
    userIDJson.insert("user_id", ID_QSTRING);
    loadprofileJson.insert("get_address", userIDJson);

    qDebug() << "create request" << endl;



    QNetworkRequest request(QUrl(SERVER_URL + ""));
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      QStringLiteral("application/json;charset=utf-8"));
    qDebug() << "request data"<< QJsonDocument(loadprofileJson).toJson(QJsonDocument::Compact) << endl;

    request.setRawHeader("JSON_DATA", QJsonDocument(loadprofileJson).toJson(QJsonDocument::Compact));
    networkManagerRight->post(
                request,
                QJsonDocument(loadprofileJson).toJson(QJsonDocument::Compact)
                );
    qDebug() << "request send" << endl;

}


void profile::setprofile() {
    setprofileButton->setStyleSheet(BUTTON_DISABLED);
    setprofileButton->setDisabled(true);

    QJsonObject setprofileJson;
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

    setprofileJson.insert("write_personal", userIDJson);

    qDebug() << "create request" << endl;


    QNetworkRequest request(QUrl(SERVER_URL + ""));
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      QStringLiteral("application/json;charset=utf-8"));
    qDebug() << "request data"<< QJsonDocument(setprofileJson).toJson(QJsonDocument::Compact) << endl;

    request.setRawHeader("JSON_DATA", QJsonDocument(setprofileJson).toJson(QJsonDocument::Compact));

    networkManagerSetprofile->post(
                request,
                QJsonDocument(setprofileJson).toJson(QJsonDocument::Compact)
                );
    qDebug() << "request send" << endl;
}


void profile::setprofileRightPressed() {

    setprofileRightButton->setStyleSheet(BUTTON_DISABLED);
    setprofileRightButton->setDisabled(true);

    QJsonObject setprofileJson;
    QJsonObject userIDJson;
    userIDJson.insert("user_id", ID_QSTRING);
    userIDJson.insert("housing", userhousingEdit->text());
    userIDJson.insert("street", userstreetEdit->text());
    userIDJson.insert("city", usercityEdit->text());
    userIDJson.insert("district", userdistrictEdit->text());
    userIDJson.insert("index", userindexEdit->text());
    userIDJson.insert("country", usercountryEdit->text());

    setprofileJson.insert("write_address", userIDJson);

    qDebug() << "create request" << endl;


    QNetworkRequest request(QUrl(SERVER_URL + ""));
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      QStringLiteral("application/json;charset=utf-8"));
    qDebug() << "request data"<< QJsonDocument(setprofileJson).toJson(QJsonDocument::Compact) << endl;

    request.setRawHeader("JSON_DATA", QJsonDocument(setprofileJson).toJson(QJsonDocument::Compact));

    networkManagerSetprofileRight->post(
                request,
                QJsonDocument(setprofileJson).toJson(QJsonDocument::Compact)
                );
    qDebug() << "request send" << endl;

}








void profile::checkData() {

}

void profile::onBackPressed() {
    back();
}

void profile::checkprofile() {
    if ((userMailEdit->text().length() >= 4) &&
            (userNameEdit->text().length() >= 4) &&
            (userSurnameEdit->text().length() >= 4) &&
            (userPhoneNumberEdit->text().length() >= 4) &&
            (userAgeEdit->text().length() == 2 && userAgeEdit->text() >='0' && userAgeEdit->text() <= '9')) {
        setprofileButton->setStyleSheet(BUTTON_SOLID);
        setprofileButton->setDisabled(false);
    } else {
        setprofileButton->setStyleSheet(BUTTON_DISABLED);
        setprofileButton->setDisabled(true);
    }
}

void profile::checkprofileRight() {
    if (
            //(userbuildingEdit->text().length() >= 1 ) &&
            (userhousingEdit->text().length() >= 1 ) &&
            (userstreetEdit->text().length() >= 4) &&
            (usercityEdit->text().length() >= 4) &&
            (userdistrictEdit->text().length() >= 4) &&
            (userindexEdit->text().length() > 5) &&
            (usercountryEdit->text().length() >= 4)) {

        setprofileRightButton->setStyleSheet(BUTTON_SOLID);
        setprofileRightButton->setDisabled(false);
    } else {
        setprofileRightButton->setStyleSheet(BUTTON_DISABLED);
        setprofileRightButton->setDisabled(true);
    }
}




void profile::onCreatePressed() {

}

void profile::onHttpResult(QNetworkReply *reply) {

    qDebug() << "http finished" << endl;


    if(!reply->error()) {  //
        QByteArray resp = reply->readAll();
        qDebug() <<"ETO OTVET SERVERA GET profile :  " + resp  << endl;
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

    getprofileRight();



}

void profile::onHttpResultRight(QNetworkReply *reply) {

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

    connect(userMailEdit, &QLineEdit::textChanged, this, &profile::checkprofile);
    connect(userNameEdit, &QLineEdit::textChanged, this, &profile::checkprofile);
    connect(userSurnameEdit, &QLineEdit::textChanged, this, &profile::checkprofile);
    connect(userAgeEdit, &QLineEdit::textChanged, this, &profile::checkprofile);
    connect(userPhoneNumberEdit, &QLineEdit::textChanged, this, &profile::checkprofile);


    //connect(userbuildingEdit, &QLineEdit::textChanged, this, &profile::checkprofileRight);
    connect(userhousingEdit, &QLineEdit::textChanged, this, &profile::checkprofileRight);
    connect(userstreetEdit, &QLineEdit::textChanged, this, &profile::checkprofileRight);
    connect(usercityEdit, &QLineEdit::textChanged, this, &profile::checkprofileRight);
    connect(userdistrictEdit, &QLineEdit::textChanged, this, &profile::checkprofileRight);
    connect(userindexEdit, &QLineEdit::textChanged, this, &profile::checkprofileRight);
    connect(usercountryEdit, &QLineEdit::textChanged, this, &profile::checkprofileRight);

}




void profile::onHttpResultSetprofile(QNetworkReply *reply) {


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

    networkManagerSetprofile->clearAccessCache();

}




void profile::onHttpResultSetprofileRight(QNetworkReply *reply) {

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

    networkManagerSetprofileRight->clearAccessCache();

}

void profile::setData(BaseModel *model) {

}
