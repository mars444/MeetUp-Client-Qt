#include "registrationfragment.h"

#include "style/stylecontainer.h"
using namespace styles;
#include "screensfactory.h"

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
    QLabel *title = new QLabel("Регистрация");
    QLabel *subtitle = new QLabel(
                "Придумайте себе пароль и логин для входа, "
                "чтобы мы могли вас узнавать на других устройствах.\n"
                "Логин min 4 символов. Пароль min 8 символов"
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

    loginButton = new QPushButton("Создать профиль");

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
    loginEdit->setPlaceholderText("Логин");
    connect(loginEdit, &QLineEdit::textChanged, this, &RegistrationFragment::checkData);

    passwordEdit->setMaximumWidth(355);
    passwordEdit->setStyleSheet(EDIT_TEXT);
    passwordEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    passwordEdit->setPlaceholderText("Пароль");
    passwordEdit->setEchoMode(QLineEdit::Password);
    connect(passwordEdit, &QLineEdit::textChanged, this, &RegistrationFragment::checkData);

    repeatPasswordEdit->setMaximumWidth(355);
    repeatPasswordEdit->setStyleSheet(EDIT_TEXT);
    repeatPasswordEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    repeatPasswordEdit->setPlaceholderText("Повтор пароля");
    repeatPasswordEdit->setEchoMode(QLineEdit::Password);
    connect(repeatPasswordEdit, &QLineEdit::textChanged, this, &RegistrationFragment::checkData);

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
         QMessageBox::warning(this,"Регистрация","Пароли не совпадают!");
    } else {

        QJsonObject param;
        QJsonObject logpass;
        logpass.insert("login", loginEdit->text());
        logpass.insert("password", passwordEdit->text());
        param.insert("registration", logpass);
        if (loginEdit->text().length() >= 4 && passwordEdit->text().length() >= 8 && repeatPasswordEdit->text().length() >= 8) {
            loadingContaiter->show();
            loading->start();
            loginButton->setDisabled(true);
            loginButton->setStyleSheet(BUTTON_DISABLED);

            QNetworkRequest request(QUrl(SERVER_URL + "/registration/"+repeatPasswordEdit->text()));
            request.setHeader(QNetworkRequest::ContentTypeHeader,
                              QStringLiteral("application/json;charset=utf-8"));
            networkManager->post(
                request,
                QJsonDocument(param).toJson(QJsonDocument::Compact)
            );
        }




    }

}

void RegistrationFragment::onRegResult(QNetworkReply *reply) {
    loading->stop();
    loadingContaiter->hide();
    loginButton->setDisabled(false);
    checkData();

    if(!reply->error()) {
        QByteArray resp = reply->readAll();
        qDebug() << resp << endl;
        QJsonDocument doc = QJsonDocument::fromJson(resp);
        QJsonObject obj;
        if(!doc.isNull()) {
            if(doc.isObject()) {
                obj = doc.object();
                qDebug() << obj["success"].toBool() << endl;
            }
            else {
                qDebug() << "Document is not an object" << endl;
            }
        } else {
            qDebug() << "Invalid JSON...\n" << endl;
        }
        if (obj["success"].toBool()) {
            newRootScreen(MAIN_TAG);
        } else {
            qDebug("login error");
            QMessageBox::warning(this, "Ошибка", obj["message"].toString());
        }
    } else {
        QMessageBox::warning(this, "Ошибка",
            "При подключениии произошла ошибка.\n"        );
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
