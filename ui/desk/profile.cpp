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
#include <QStackedWidget>

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



    innerDataSettigs = new QHBoxLayout;

  //////////////

    QVBoxLayout *personalGeneral = new QVBoxLayout;


    QHBoxLayout *inputNickNameInner = new QHBoxLayout;
    userNickNameEdit = new QLineEdit;
    userNickNameLabel = new QLabel(tr("NickName:"));
    userNickNameLabel->setMaximumWidth(300);
    userNickNameLabel->setStyleSheet(PROFILE_LABEL);
    userNickNameEdit->setMinimumHeight(50);
    userNickNameEdit->setMaximumHeight(50);
    userNickNameEdit->setStyleSheet(EDIT_TEXT);
    userNickNameEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    inputNickNameInner->addWidget(userNickNameLabel);
    inputNickNameInner->addWidget(userNickNameEdit);

    qDebug()<<"2"<<endl;

    QHBoxLayout *inputStatusGeneralInner = new QHBoxLayout;
    userStatusGeneralEdit = new QLineEdit;
    userStatusGeneralLabel = new QLabel(tr("Status:"));
    userStatusGeneralLabel->setMaximumWidth(300);
    userStatusGeneralLabel->setStyleSheet(PROFILE_LABEL);
    userStatusGeneralEdit->setMinimumHeight(50);
    userStatusGeneralEdit->setMaximumHeight(50);
    userStatusGeneralEdit->setStyleSheet(EDIT_TEXT);
    userStatusGeneralEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    inputStatusGeneralInner->addWidget(userStatusGeneralLabel);
    inputStatusGeneralInner->addWidget(userStatusGeneralEdit);

    QVBoxLayout *inputGeneralDescriptionInner = new QVBoxLayout;
    userGeneralDescriptionEdit = new QLineEdit;
    userGeneralDescriptionEdit->setMinimumHeight(220);
    userGeneralDescriptionEdit->setMaximumHeight(220);
    userGeneralDescriptionEdit->setAlignment(Qt::AlignCenter);
    userGeneralDescriptionEdit->setStyleSheet(EDIT_TEXT);
    userGeneralDescriptionEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);


    QHBoxLayout *personalGeneralDescriptionLayout = new QHBoxLayout;

    QLabel *personalGeneralDescriptionLabel = new QLabel(tr("Description"));
    personalGeneralDescriptionLabel->setAlignment(Qt::AlignCenter);
    personalGeneralDescriptionLabel->setStyleSheet(PROFILE_GENERAL_DESCRIPTION);
    personalGeneralDescriptionLabel->setMaximumWidth(400);
    personalGeneralDescriptionLabel->setMinimumWidth(400);

    personalGeneralDescriptionLayout->setAlignment(Qt::AlignCenter);

    personalGeneralDescriptionLayout->addWidget(personalGeneralDescriptionLabel);

    inputGeneralDescriptionInner->addLayout(personalGeneralDescriptionLayout);
    inputGeneralDescriptionInner->addWidget(userGeneralDescriptionEdit);



    qDebug()<<"3"<<endl;


    qDebug()<<"4aaaaaaa"<<endl;


    inputNickNameInner->setContentsMargins(0,25,0,0);
    inputGeneralDescriptionInner->setContentsMargins(0,25,0,0);
    inputStatusGeneralInner->setContentsMargins(0,25,0,0);


    QHBoxLayout *personalGeneralLayout = new QHBoxLayout;

    QLabel *personalGeneralLabel = new QLabel(tr("General"));
    personalGeneralLabel->setAlignment(Qt::AlignCenter);
    personalGeneralLabel->setStyleSheet(PROFILE_LABEL_TITLE);
    personalGeneralLabel->setMaximumWidth(400);
    personalGeneralLabel->setMinimumWidth(400);

    personalGeneralLayout->setAlignment(Qt::AlignCenter);

    personalGeneralLayout->addWidget(personalGeneralLabel);


    personalGeneral->addLayout(personalGeneralLayout);
    personalGeneral->addLayout(inputNickNameInner);
    personalGeneral->addLayout(inputStatusGeneralInner);
    personalGeneral->addLayout(inputGeneralDescriptionInner);






    QVBoxLayout *personalAddress = new QVBoxLayout;


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


    inputcountryInner->setContentsMargins(0,30,0,0);
    inputdistrictInner->setContentsMargins(0,30,0,0);
    inputcityInner->setContentsMargins(0,30,0,0);
    inputstreetInner->setContentsMargins(0,30,0,0);
    inputhousingInner->setContentsMargins(0,30,0,0);
    inputindexInner->setContentsMargins(0,30,0,0);


    QHBoxLayout *personalAddressLayout = new QHBoxLayout;

    QLabel *personalAddressLabel = new QLabel(tr("Address"));
    personalAddressLabel->setAlignment(Qt::AlignCenter);
    personalAddressLabel->setStyleSheet(PROFILE_LABEL_TITLE);
    personalAddressLabel->setMaximumWidth(400);
    personalAddressLabel->setMinimumWidth(400);

    personalAddressLayout->setAlignment(Qt::AlignCenter);

    personalAddressLayout->addWidget(personalAddressLabel);

    personalAddress->addLayout(personalAddressLayout);
    personalAddress->addLayout(inputcountryInner);
    personalAddress->addLayout(inputdistrictInner);
    personalAddress->addLayout(inputcityInner);
    personalAddress->addLayout(inputstreetInner);
    personalAddress->addLayout(inputhousingInner);
    //personalAddress->addLayout(inputbuildingInner);
    personalAddress->addLayout(inputindexInner);




    QVBoxLayout *personalData = new QVBoxLayout;

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

 qDebug()<<"6"<<endl;

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

     qDebug()<<"7"<<endl;

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

     qDebug()<<"8"<<endl;


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

     qDebug()<<"9"<<endl;

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

     qDebug()<<"10"<<endl;


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

     qDebug()<<"11"<<endl;


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

     qDebug()<<"12"<<endl;


    usercountryLabel->setStyleSheet(PROFILE_LABEL);
    userAgeLabel->setStyleSheet(PROFILE_LABEL);
    userMailLabel->setStyleSheet(PROFILE_LABEL);
    userNameLabel->setStyleSheet(PROFILE_LABEL);
    usercityLabel->setStyleSheet(PROFILE_LABEL);
    userLabelLabel->setStyleSheet(PROFILE_LABEL);
    userindexLabel->setStyleSheet(PROFILE_LABEL);
    userStatusLabel->setStyleSheet(PROFILE_LABEL);
    userstreetLabel->setStyleSheet(PROFILE_LABEL);
    userSurnameLabel->setStyleSheet(PROFILE_LABEL);
    userPhoneNumberLabel->setStyleSheet(PROFILE_LABEL);
    userDescriptionLabel->setStyleSheet(PROFILE_LABEL);
    userhousingLabel->setStyleSheet(PROFILE_LABEL);
    userdistrictLabel->setStyleSheet(PROFILE_LABEL);

     qDebug()<<"13"<<endl;

    usercountryLabel->setAlignment(Qt::AlignCenter);
    userAgeLabel->setAlignment(Qt::AlignCenter);
    userMailLabel->setAlignment(Qt::AlignCenter);
    userNameLabel->setAlignment(Qt::AlignCenter);
    usercityLabel->setAlignment(Qt::AlignCenter);
    userLabelLabel->setAlignment(Qt::AlignCenter);
    userindexLabel->setAlignment(Qt::AlignCenter);
    userStatusLabel->setAlignment(Qt::AlignCenter);
    userstreetLabel->setAlignment(Qt::AlignCenter);
    userSurnameLabel->setAlignment(Qt::AlignCenter);
    userPhoneNumberLabel->setAlignment(Qt::AlignCenter);
    userDescriptionLabel->setAlignment(Qt::AlignCenter);
    userhousingLabel->setAlignment(Qt::AlignCenter);
    userdistrictLabel->setAlignment(Qt::AlignCenter);
    userNickNameLabel->setAlignment(Qt::AlignCenter);
    userStatusGeneralLabel->setAlignment(Qt::AlignCenter);


     qDebug()<<"14"<<endl;





    QHBoxLayout *settingButtonContainer = new QHBoxLayout;

    setprofileButton = new QPushButton(tr("                  Save                "));

    setprofileButton->setStyleSheet(BUTTON_SOLID);

    setprofileButton->setDisabled(true);

    setprofileButton->setMaximumWidth(250);
    setprofileButton->setMinimumWidth(250);




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

    QHBoxLayout *personalDataLayout = new QHBoxLayout;

    QLabel *personalDataLabel = new QLabel(tr("Personal Data"));
    personalDataLabel->setAlignment(Qt::AlignCenter);
    personalDataLabel->setStyleSheet(PROFILE_LABEL_TITLE);
    personalDataLabel->setMaximumWidth(400);
    personalDataLabel->setMinimumWidth(400);

    personalDataLayout->setAlignment(Qt::AlignCenter);

    personalDataLayout->addWidget(personalDataLabel);

    personalData->addLayout(personalDataLayout);
    personalData->addLayout(inputNameInner);
    personalData->addLayout(inputSurnameInner);
    personalData->addLayout(inputAgeInner);
    personalData->addLayout(inputPhoneNumberInner);
    personalData->addLayout(inputStatusInner);
    personalData->addLayout(inputLabelInner);
    personalData->addLayout(inputDescriptionInner);
    personalData->addLayout(inputMailInner);


    QIcon *ico;
    ico = new QIcon(":/resc/resc/profile.svg");

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

    settingButtonContainer->setAlignment(Qt::AlignCenter);

    settingButtonContainer->setContentsMargins(50,50,0,0);




    QHBoxLayout *settingButtonRightContainer = new QHBoxLayout;
    setprofileRightButton = new QPushButton(tr("                Save address      "));

    setprofileRightButton->setStyleSheet(BUTTON_DISABLED);

    setprofileRightButton->setDisabled(true);

    setprofileRightButton->setMaximumWidth(250);
    setprofileRightButton->setMinimumWidth(250);
    connect(setprofileRightButton, &QPushButton::clicked, this, &profile::setprofileRightPressed);
    settingButtonRightContainer->addWidget(setprofileRightButton);
    settingButtonRightContainer->setAlignment(Qt::AlignCenter);
    settingButtonRightContainer->setContentsMargins(50,50,0,0);


    QHBoxLayout *settingButtonGeneralContainer = new QHBoxLayout;
    setprofileGeneralButton = new QPushButton(tr("            Save General      "));

    setprofileGeneralButton->setStyleSheet(BUTTON_DISABLED);

    setprofileGeneralButton->setDisabled(true);

    setprofileGeneralButton->setMaximumWidth(250);
    setprofileGeneralButton->setMinimumWidth(250);
    connect(setprofileGeneralButton, &QPushButton::clicked, this, &profile::setprofileGeneralPressed);
    settingButtonGeneralContainer->addWidget(setprofileGeneralButton);
    settingButtonGeneralContainer->setAlignment(Qt::AlignCenter);
    settingButtonGeneralContainer->setContentsMargins(50,50,0,0);



    QPixmap pixmapShedule(":/resc/resc/arrow_up.svg");
    QIcon ButtonIconShedule(pixmapShedule);

    setprofileGeneralButton->setIcon(ButtonIconShedule);
    setprofileGeneralButton->setIconSize(QSize(30,30));
    setprofileGeneralButton -> setLayoutDirection ( Qt :: RightToLeft );

    setprofileRightButton->setIcon(ButtonIconShedule);
    setprofileRightButton->setIconSize(QSize(30,30));
    setprofileRightButton -> setLayoutDirection ( Qt :: RightToLeft );

    setprofileButton -> setLayoutDirection ( Qt :: RightToLeft );
    setprofileButton->setIcon(ButtonIconShedule);
    setprofileButton->setIconSize(QSize(30,30));

    personalGeneral->addLayout(settingButtonGeneralContainer);


    personalAddress->addLayout(settingButtonRightContainer);

    personalData->addLayout(settingButtonContainer);

    personalData->setAlignment(Qt::AlignCenter);

    personalAddress->setAlignment(Qt::AlignCenter);


    check_stack_lay_acc();



    leftButton = new QSvgButton(left_btn, QSize(67,75));
    rightButton = new QSvgButton(right_btn, QSize(67,75));

    leftButton->setStyleSheet("border-radius:25px;");
    rightButton->setStyleSheet("border-radius:25px;");

    connect(leftButton, &QPushButton::clicked, this, &profile::leftButtonClicked);
    connect(rightButton, &QPushButton::clicked, this, &profile::rightButtonClicked);


    QFrame *personalGeneralFrame = new QFrame;

    personalGeneralFrame->setStyleSheet(SETTING_LEFT_STYLE);

    personalGeneralFrame->setLayout(personalGeneral);

    QFrame *personalDataFrame = new QFrame;

    personalDataFrame->setStyleSheet(SETTING_LEFT_STYLE);

    personalDataFrame->setLayout(personalData);

    QFrame *personalAddressFrame = new QFrame;

    personalAddressFrame->setStyleSheet(SETTING_LEFT_STYLE);

    personalAddressFrame->setLayout(personalAddress);


    stackProfile = new QStackedWidget;




    stackProfile->addWidget(personalGeneralFrame);

    stackProfile->addWidget(personalDataFrame);

    stackProfile->addWidget(personalAddressFrame);
    stackProfile->setCurrentIndex(0);

    innerDataSettigs->addWidget(leftButton);

    innerDataSettigs->addWidget(stackProfile);

    innerDataSettigs->addWidget(rightButton);

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

void profile::leftButtonClicked() {


    if(stack_lay_acc > 0){

        stack_lay_acc--;
    }

    check_stack_lay_acc();

    innerDataSettigs->update();

    stackProfile->setCurrentIndex(stack_lay_acc);

}

void profile::rightButtonClicked() {



    if(stack_lay_acc < 2){

        stack_lay_acc++;
    }

    check_stack_lay_acc();

    innerDataSettigs->update();

    stackProfile->setCurrentIndex(stack_lay_acc);


}

void profile::setprofileGeneralPressed() {


}

void profile::check_stack_lay_acc() {

    if(stack_lay_acc == 0){

        left_btn = ":/resc/resc/chevron-left-disabled.svg";
        right_btn = ":/resc/resc/chevron-right.svg";





    } else if (stack_lay_acc == 2){

        left_btn = ":/resc/resc/chevron-left.svg";

        right_btn = ":/resc/resc/chevron-right-disabled.svg";



    } else {
        left_btn = ":/resc/resc/chevron-left.svg";
        right_btn = ":/resc/resc/chevron-right.svg";

}

}



