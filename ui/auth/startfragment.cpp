#include "startfragment.h"

#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QSvgWidget>
#include <QVBoxLayout>
#include "style/stylecontainer.h"
#include "screensfactory.h"

using namespace styles;
using namespace screens;

StartFragment::StartFragment(){
    qDebug("SplashFragnebt crete");

    QVBoxLayout *mainVLayout = new QVBoxLayout;                                                     // общая обертка
    QHBoxLayout *mainHLayout = new QHBoxLayout;
    QFrame *centerContainer = new QFrame;

    QVBoxLayout *startMainLayout = new QVBoxLayout;
    QHBoxLayout *startContent = new QHBoxLayout;
    QSvgWidget *mainImage = new QSvgWidget(":/resc/resc/logo.svg");                             // svg иконки слева

mainImage->setMaximumSize(175,175);


    QVBoxLayout *startVerticalContent = new QVBoxLayout;
    QLabel *title = new QLabel("Hello!");
    QLabel *subtitle = new QLabel("Наше приложение поможет вам организовать совместные встерчи с родными и друзьями.");

    QVBoxLayout *buttonContainer = new QVBoxLayout;

    QPushButton *loginButton = new QPushButton("Войти");
    QPushButton *regButton = new QPushButton("Регистрация");

    title->setStyleSheet(TITLE_LABLE);
    title->setWordWrap(true);
    subtitle->setStyleSheet(HINT_LABLE);
    subtitle->setMaximumWidth(355);
    subtitle->setMinimumWidth(355);
    subtitle->setWordWrap(true);
    startVerticalContent->addWidget(title);
    startVerticalContent->addWidget(subtitle);
    startVerticalContent->setAlignment(Qt::AlignTop);                                       // Контент сверху родителя
    buttonContainer->setAlignment(Qt::AlignBottom);                                         // кнопку снизу родителя

    startMainLayout->addLayout(startVerticalContent);                                        // засовывваем startVerticalContent в основной контент
    startMainLayout->addLayout(buttonContainer);                                             // засовывваем кнопку в основной контент
    startMainLayout->setContentsMargins(100,0,0,0);
    loginButton->setStyleSheet(BUTTON_SOLID);
    connect(loginButton, &QPushButton::clicked, this, &StartFragment::openLogin);            // сигнал от кнопки:нажата к функции openLogin (откроет окно логина)

    regButton->setStyleSheet(BUTTON_EMPTY);
    connect(regButton, &QPushButton::clicked, this, &StartFragment::openRegistration);       // сигнал от кнопки:нажата к функции openRegistration (откроет окно рег)

    buttonContainer->addWidget(loginButton);                                                 // помещаем кнопку в  buttonContainer
    buttonContainer->addWidget(regButton);

    startContent->setContentsMargins(81,50,50,50);                                           // отступы

    centerContainer->setStyleSheet(FRAME_8PX_WHITE);                                         // стиль окна бэкграунд
    centerContainer->setLayout(startContent);                                                // помещаем setLayout  бэкграунд
    mainImage->setStyleSheet(START_ICON);
    startContent->addWidget(mainImage);
    startContent->addLayout(startMainLayout);

    mainHLayout->addWidget(centerContainer);                                                 // ВЫРАВНИВАНИЕ ПО ЦЕНТРУ
    mainHLayout->setAlignment(Qt::AlignCenter);
    mainVLayout->addLayout(mainHLayout);
    mainVLayout->setAlignment(Qt::AlignCenter);

    this->setLayout(mainVLayout);
}

StartFragment::~StartFragment() {

}

void StartFragment::openLogin() {
    navigateTo(LOGIN_TAG);
}

void StartFragment::openRegistration() {
    navigateTo(REGISTRATION_TAG);
}
