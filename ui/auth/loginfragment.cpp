#include "loginfragment.h"
#include "nlohmann/json.hpp"
#include <iostream>
#include <set>
#include "../mainfragment.h"
#include "user_data.h"

#include "models/usermodel.h"

#include <QJsonValue>
#include <QLabel>
#include <QPushButton>
#include <QSvgWidget>
#include <QTreeWidgetItem>
#include <QVBoxLayout>
#include <ui/view/qsvgbutton.h>
#include <ui/view/waitingspinnerwidget.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QSettings>
#include <QString>

#include <QUrlQuery>
#include <QUrl>





#include "style/stylecontainer.h"
using namespace styles;
#include "screensfactory.h"
using namespace screens;

LoginFragment::LoginFragment() {


    QVBoxLayout *mainVLayout = new QVBoxLayout;                                 // создаем общую обертку  типа QVBoxLayout V - VERTICAL  (SPISOK)
    QHBoxLayout *mainHLayout = new QHBoxLayout;                                 // создаем общую обертку  типа QHBoxLayout H - GORIZONTAL (DISPLAY FLEX)
    QFrame *centerConainer = new QFrame;                                        // создаем объект типа QFrame    (РАМКА)

    QVBoxLayout *startMainLayout = new QVBoxLayout;                             // создаем внутренню обертку объект типа QVBoxLayout
    QHBoxLayout *startContent = new QHBoxLayout;                                // создаем внутренню обертку объект типа QVBoxLayout
    QSvgWidget *mainImage = new QSvgWidget(":/resc/resc/logo.svg");         // создаем объект типа QSvgWidget и указываем ссылку на картинку
    mainImage->setMaximumSize(175,175);
    QVBoxLayout *backContainer = new QVBoxLayout;                               // создаем внутренню обертку объект типа QVBoxLayout
    QSvgButton *backImage = new QSvgButton(":/resc/resc/arrow_back.svg", QSize(25,25));

    QVBoxLayout *startVerticalContent = new QVBoxLayout;                        // создаем правую внутренню обертку объект типа QVBoxLayout
    QLabel *title = new QLabel("Вход в приложение");                            // создаем Qlabel(строка обычная)
    QLabel *subtitle = new QLabel("Приветсвуем!");                              // создаем правую внутренню обертку объект типа QVBoxLayout
    loginEdit = new QLineEdit;                                                  // создаем Qlabel логин(поле ввода, инпут)
    passwordEdit = new QLineEdit;                                               // создаем Qlabel пароль (поле ввода, инпут)

    startVerticalContent->setContentsMargins(0,0,0,50);

    QVBoxLayout *buttonContainer = new QVBoxLayout;                             // создаем  обертку кнопки типа QVBoxLayout
    QHBoxLayout *loadingButtonContainer = new QHBoxLayout;                      // создаем  обертку кнопки типа QHBoxLayout
    loadingContaiter = new QFrame;                                              // создаем объект типа QFrame    (РАМКА)
    loading = new WaitingSpinnerWidget(loadingContaiter, true, false);          // https://github.com/snowwlex/QtWaitingSpinner виджет загрузки
    loading->setColor(QT_COLOR_PRIMARY);                                        // стиль для загрузки колор  QT_COLOR_PRIMARY
    loadingContaiter->setMinimumWidth(100);                                     // minwidth загрузки
    loadingContaiter->hide();                                                   // пока что скрываем ее

    loginButton = new QPushButton("Войти");

    title->setStyleSheet(TITLE_LABLE);                                          // задаем title  стиль  TITLE_LABLE из файла  #include "style/stylecontainer.h"
    subtitle->setStyleSheet(HINT_LABLE);
    subtitle->setMaximumWidth(355);                                             // макс длина в пикселях
    subtitle->setMinimumWidth(355);
    subtitle->setWordWrap(true);                                                // перевод слов на новую строку

    startVerticalContent->addWidget(title);                                     // вносим титле в startVerticalContent
    startVerticalContent->addWidget(subtitle);
    startVerticalContent->setAlignment(Qt::AlignTop);                           // текст сверху б кнопки к низу
    startMainLayout->setContentsMargins(100,0,0,0);
    buttonContainer->setAlignment(Qt::AlignBottom);

    startMainLayout->addLayout(startVerticalContent);                           // вносим все в главный контейнер
    startMainLayout->addLayout(buttonContainer);

    loginEdit->setMaximumWidth(355);                                          // поле ввода логина длна 355
    loginEdit->setStyleSheet(EDIT_TEXT);
    loginEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    loginEdit->setPlaceholderText("Логин");

    passwordEdit->setMaximumWidth(355);
    passwordEdit->setStyleSheet(EDIT_TEXT);
    passwordEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    passwordEdit->setPlaceholderText("Пароль");
    passwordEdit->setEchoMode(QLineEdit::Password);

    connect(loginEdit, &QLineEdit::textChanged, this, &LoginFragment::checkData);
    connect(passwordEdit, &QLineEdit::textChanged, this, &LoginFragment::checkData);

    loginButton->setStyleSheet(BUTTON_SOLID);
    connect(loginButton, &QPushButton::clicked, this, &LoginFragment::onLoginPressed);

    buttonContainer->addWidget(loginEdit);
    buttonContainer->addWidget(passwordEdit);
    loadingButtonContainer->addWidget(loginButton);
    loadingButtonContainer->addWidget(loadingContaiter);
    buttonContainer->addLayout(loadingButtonContainer);

    startContent->setContentsMargins(50,50,50,50);

    backImage->setStyleSheet(BACK_WHITE);
    connect(backImage, &QSvgButton::clicked, this, &LoginFragment::onBackPressed);

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
    checkData();
    networkManager = new QNetworkAccessManager();
    connect(networkManager, &QNetworkAccessManager::finished, this, &LoginFragment::onHttpResult);
}

LoginFragment::~LoginFragment() {
    delete loginEdit;
    delete passwordEdit;
    delete loginButton;
    delete loading;
    delete loadingContaiter;
    networkManager->clearAccessCache();
}

void LoginFragment::onLoginPressed() {

//     QNetworkRequest request(QUrl(SERVER_URL + ""));

//     request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

//     QByteArray data("{\"key1\":\"value1\",\"key2\":\"value2\"}}");

//     networkManager->post(request,data);

//    QNetworkRequest request(QUrl("http://192.168.31.207:9999"));
//    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

//     request.setRawHeader("JSON_DATA", "{{HELLOOOOOOOOOOOOOOOOOOOOOOO}}");
//    QByteArray body = "{{HELLOOOOOOOOOOOOOOOOOOOOOOO}}";
//    networkManager->post(request, body);


    QJsonObject RegJson;
    QJsonObject param;
       param.insert("nickname", loginEdit->text());
       param.insert("password", passwordEdit->text());
       RegJson.insert("autorization", param);
       if (loginEdit->text().length() > 5 && passwordEdit->text().length() > 5) {
           loadingContaiter->show();
           loading->start();

           loginButton->setDisabled(true);
           loginButton->setStyleSheet(BUTTON_DISABLED);

           qDebug() << "create request" << endl;
           QNetworkRequest request(QUrl(SERVER_URL + ""));
           request.setHeader(QNetworkRequest::ContentTypeHeader,
                             QStringLiteral("application/json;charset=utf-8"));

           request.setRawHeader("JSON_DATA", QJsonDocument(RegJson).toJson(QJsonDocument::Compact));

           qDebug() << "request data"<< QJsonDocument(RegJson).toJson(QJsonDocument::Compact) << endl;
           networkManager->post(
               request,
               QJsonDocument(RegJson).toJson(QJsonDocument::Compact)
           );
           qDebug() << "request send" << endl;
       }


//    QUrl url("SERVER_URL");
//    QNetworkRequest request;
//    request.setUrl(url);
//    networkManager->get(request);


//////// Через QURL
//    loadingContaiter->show();
//    loading->start();
//    networkManager = new QNetworkAccessManager(this);
//    const QUrl url(SERVER_URL);
//    QNetworkRequest request(url);
//    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

//    request.setRawHeader("Accept-Encoding", "identity");

//        QJsonObject loginPasswordValues;
//        QJsonObject loginPasswordValues1;
//        loginPasswordValues1.insert("login", loginEdit->text());
//        loginPasswordValues1.insert("password", passwordEdit->text());

//        loginPasswordValues.insert("autorization", loginPasswordValues1);
//        QJsonDocument doc(loginPasswordValues);
//        QByteArray data = doc.toJson();

//           qDebug() << data;


////    std::string aaa = "{dwefwef}}";

////    QByteArray bite =  QByteArray(aaa.c_str(), aaa.size());

////    QByteArray data("{\"key1\":\"value1\",\"key2\":\"value2\"}");

//    QNetworkReply *reply = networkManager->post(request, data);

//    QObject::connect(reply, &QNetworkReply::finished, [=](){
//        if(reply->error() == QNetworkReply::NoError){
//            QString contents = QString::fromUtf8(reply->readAll());
//            qDebug() << contents;
//        }
//        else{
//            QString err = reply->errorString();
//            qDebug() << err;
//        }
//    });


}

void LoginFragment::onHttpResult(QNetworkReply *reply) {

    qDebug() << "http finished" << endl;
    loading->stop();
    loadingContaiter->hide();
    loginButton->setDisabled(false);
    checkData();
    if(!reply->error()) {
        QByteArray resp = reply->readAll();
        qDebug() <<"ETO OTVET SERVERA AUTORIZATION :  " + resp  << endl;
        QJsonDocument doc = QJsonDocument::fromJson(resp);
        QJsonObject obj;

        std::string str = resp.toStdString();

        std::cout << "str  " + str << std::endl;

        nlohmann::json j = nlohmann::json::parse(str);

        if(j["autorization"].contains("user_id")) {

            std::string IDValue = j["autorization"]["user_id"].get<std::string>();

            //userId = QString::fromUtf8(IDValue.c_str());;

            std::cout << "ID: " << IDValue << std::endl;

             QFile file("C:\\user_id.txt");

             if (file.open(QIODevice::WriteOnly))
             {
                 file.write("Test string\n");

                 file.close();
             }


            newRootScreen(MAIN_TAG);

        } else {

           std::string reg_error = j["autorization"].get<std::string>();
           std::cout << "error: " << reg_error << std::endl;

           qDebug("autorization error");

           QMessageBox::warning(this, "Ошибка", "Неверный логин или пароль");

}

        } else {

        qDebug() << reply->errorString();

        qDebug() << "Server answer: " +  reply->readAll() << endl;

        qDebug () << reply -> error ();

        QMessageBox::warning(this, "Ошибка",
            "При подключениии произошла ошибка.\n");
        // newRootScreen(MAIN_TAG);

}
    //newRootScreen(MAIN_TAG);
    reply->deleteLater();
    networkManager->clearAccessCache();
}

void LoginFragment::checkData() {
    if (loginEdit->text().length() >= 4 && passwordEdit->text().length() >= 8) {
        loginButton->setStyleSheet(BUTTON_SOLID);
    } else {
        loginButton->setStyleSheet(BUTTON_DISABLED);
    }
}

void LoginFragment::onBackPressed() {
    back();
}










