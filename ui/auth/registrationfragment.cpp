#include "registrationfragment.h"

#include "style/stylecontainer.h"
using namespace styles;
#include "screensfactory.h"

#include "user_data.h"

#include "nlohmann/json.hpp"
#include <iostream>
#include <set>
#include "../mainfragment.h"
#include "user_data.h"

#include <QSvgWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QSettings>
#include <QJsonObject>
#include <QMessageBox>

#include <ui/view/qsvgbutton.h>
#include <ui/view/waitingspinnerwidget.h>
using namespace screens;

RegistrationFragment::RegistrationFragment() {
    qDebug("SplashFragnebt crete");

    QVBoxLayout *mainVLayout = new QVBoxLayout;
    QHBoxLayout *mainHLayout = new QHBoxLayout;
    QFrame *centerConainer = new QFrame;

    QVBoxLayout *startMainLayout = new QVBoxLayout;
    QHBoxLayout *startContent = new QHBoxLayout;
    QSvgWidget *mainImage = new QSvgWidget(":/resc/resc/logo.svg");
    mainImage->setMaximumSize(175,175);

    QVBoxLayout *backContainer = new QVBoxLayout;
    QSvgButton *backImage = new QSvgButton(":/resc/resc/arrow_back.svg", QSize(25,25));


    QVBoxLayout *startVerticalContent = new QVBoxLayout;
    QLabel *title = new QLabel(tr("Registration"));
    QLabel *subtitle = new QLabel(tr("Come up with a password and login so that we can recognize you on other devices.\n"
                                     "Login min 4 characters.\n"
                                     "Password min 8 characters.\n")

                                  );
    loginEdit = new QLineEdit;
    passwordEdit = new QLineEdit;
    repeatPasswordEdit = new QLineEdit;

    QVBoxLayout *buttonContainer = new QVBoxLayout;

    QHBoxLayout *loadingButtonContainer = new QHBoxLayout;
    loadingContaiter = new QFrame;
    loading = new WaitingSpinnerWidget(loadingContaiter, true, false);
    loading->setColor(QT_COLOR_PRIMARY);
    loadingContaiter->setMinimumWidth(100);
    loadingContaiter->hide();

    loginButton = new QPushButton(tr("Create Profile"));

    title->setStyleSheet(TITLE_LABLE);
    subtitle->setStyleSheet(HINT_LABLE);
    subtitle->setMaximumWidth(355);
    subtitle->setMinimumWidth(355);
    subtitle->setWordWrap(true);
    startVerticalContent->addWidget(title);
    startVerticalContent->addWidget(subtitle);
    startVerticalContent->setAlignment(Qt::AlignTop);
    buttonContainer->setAlignment(Qt::AlignBottom);

    startMainLayout->addLayout(startVerticalContent);
    startMainLayout->addLayout(buttonContainer);
    startMainLayout->setContentsMargins(100,0,0,0);


    loginEdit->setMaximumWidth(355);
    loginEdit->setStyleSheet(EDIT_TEXT);
    loginEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    loginEdit->setPlaceholderText(tr("NickName"));
    connect(loginEdit, &QLineEdit::textChanged, this, &RegistrationFragment::checkData);

    passwordEdit->setMaximumWidth(355);
    passwordEdit->setStyleSheet(EDIT_TEXT);
    passwordEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    passwordEdit->setPlaceholderText(tr("Password"));
    passwordEdit->setEchoMode(QLineEdit::Password);
    connect(passwordEdit, &QLineEdit::textChanged, this, &RegistrationFragment::checkData);

    repeatPasswordEdit->setMaximumWidth(355);
    repeatPasswordEdit->setStyleSheet(EDIT_TEXT);
    repeatPasswordEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    repeatPasswordEdit->setPlaceholderText(tr("Repeat Password"));
    repeatPasswordEdit->setEchoMode(QLineEdit::Password);
    connect(repeatPasswordEdit, &QLineEdit::textChanged, this, &RegistrationFragment::checkData);


    QIcon *icoLogin;
    icoLogin = new QIcon(":/resc/resc/user.svg");

    loginEdit->addAction(*icoLogin, QLineEdit::LeadingPosition);


    QIcon *icoPassword;
    icoPassword = new QIcon(":/resc/resc/key.svg");

    passwordEdit->addAction(*icoPassword, QLineEdit::LeadingPosition);
    repeatPasswordEdit->addAction(*icoPassword, QLineEdit::LeadingPosition);

    loginButton->setStyleSheet(BUTTON_SOLID);
    connect(loginButton, &QPushButton::clicked, this, &RegistrationFragment::onRegPressed);

    buttonContainer->addWidget(loginEdit);
    buttonContainer->addWidget(passwordEdit);
    buttonContainer->addWidget(repeatPasswordEdit);

    loadingButtonContainer->addWidget(loginButton);
    loadingButtonContainer->addWidget(loadingContaiter);
    buttonContainer->addLayout(loadingButtonContainer);

    startContent->setContentsMargins(50,50,50,50);
    backImage->setStyleSheet(BACK_WHITE);

    connect(backImage, &QSvgButton::clicked, this, &RegistrationFragment::onBackPressed);

    centerConainer->setStyleSheet(FRAME_8PX_WHITE);
    centerConainer->setLayout(startContent);

    mainImage->setStyleSheet(START_ICON);
    backContainer->addWidget(backImage);
    backContainer->setAlignment(Qt::AlignTop);

    startContent->addLayout(backContainer);
    startContent->addWidget(mainImage);
    startContent->addLayout(startMainLayout);

    mainHLayout->addWidget(centerConainer);
    mainHLayout->setAlignment(Qt::AlignCenter);
    mainVLayout->addLayout(mainHLayout);
    mainVLayout->setAlignment(Qt::AlignCenter);

    this->setLayout(mainVLayout);
    networkManager = new QNetworkAccessManager();
    connect(networkManager, &QNetworkAccessManager::finished, this, &RegistrationFragment::onRegResult);
    checkData();
}

RegistrationFragment::~RegistrationFragment() {
    delete loginEdit;
    delete passwordEdit;
    delete loginButton;
    delete networkManager;
    delete loading;
    delete loadingContaiter;
}


void RegistrationFragment::onRegPressed() {

    if(passwordEdit->text() != repeatPasswordEdit->text()){
        QMessageBox::warning(this,tr("Регистрация"),tr("Пароли не совпадают!"));
    } else {

        std::string NizkName = loginEdit->text().toStdString();
        WriteNickname(NizkName);

        QJsonObject loginPasswordValues;
        QJsonObject loginPasswordValues1;
        loginPasswordValues1.insert("nickname", loginEdit->text());
        loginPasswordValues1.insert("password", passwordEdit->text());

        loginPasswordValues.insert("registration", loginPasswordValues1);
        if (loginEdit->text().length() >= 4 && passwordEdit->text().length() >= 8) {
            loadingContaiter->show();
            loading->start();

            loginButton->setDisabled(true);
            loginButton->setStyleSheet(BUTTON_DISABLED);

            qDebug() << "create request" << endl;


            QNetworkRequest request(QUrl(SERVER_URL + ""));
            request.setHeader(QNetworkRequest::ContentTypeHeader,
                              QStringLiteral("application/json"));
            qDebug() << "request data"<< QJsonDocument(loginPasswordValues).toJson(QJsonDocument::Compact) << endl;
            request.setRawHeader("JSON_DATA", QJsonDocument(loginPasswordValues).toJson(QJsonDocument::Compact));
            networkManager->post(
                        request,
                        QJsonDocument(loginPasswordValues).toJson(QJsonDocument::Compact)
                        );
            qDebug() << "request send" << endl;
        }
    }





}



void RegistrationFragment::onRegResult(QNetworkReply *reply) {

    qDebug() << "http finished" << endl;
    loading->stop();
    loadingContaiter->hide();
    loginButton->setDisabled(false);
    checkData();
    if(!reply->error()) {
        QByteArray resp = reply->readAll();
        qDebug() << resp  << endl;

        qDebug() <<"ETO OTVET SERVERA REG :  " + resp  << endl;

        std::string str = resp.toStdString();

        std::cout << "str  " + str << std::endl;

        nlohmann::json j = nlohmann::json::parse(str);

        if(j["registration"].contains("user_id")) {

            std::string IDValue = j["registration"]["user_id"].get<std::string>();

            std::cout << "ID: " << IDValue << std::endl;


            WriteId(IDValue);
            newRootScreen(MAIN_TAG);

        } else {

            std::string reg_error = j["registration"].get<std::string>();
            std::cout << "error: " << reg_error << std::endl;

            qDebug("registration error");

            QMessageBox::warning(this, tr("Error"), tr("User with this name exists!"));

        }

    } else {

        qDebug() << reply->errorString();

        qDebug() <<  reply->readAll() << endl;

        qDebug () << reply -> error ();


        QMessageBox::warning(this, tr("Error"),
                             tr("Connection ERROR!\n"));



    }
    reply->deleteLater();
}

void RegistrationFragment::checkData() {
    if (loginEdit->text().length() >= 4 && passwordEdit->text().length() >= 8 && repeatPasswordEdit->text().length() >= 8) {
        loginButton->setStyleSheet(BUTTON_SOLID);
    } else {
        loginButton->setStyleSheet(BUTTON_DISABLED);
    }
}

void RegistrationFragment::onBackPressed() {
    back();
}
