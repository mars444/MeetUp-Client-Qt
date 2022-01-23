#include "startfragment.h"

#include <QApplication>

#include <QComboBox>
#include <QTranslator>
#include <QLibraryInfo>
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
    QLabel *title = new QLabel(tr("Hello"));
    QLabel *subtitle = new QLabel(tr("Our application will help you organize joint meetings with family and friends."));

    QVBoxLayout *buttonContainer = new QVBoxLayout;

    QPushButton *loginButton = new QPushButton(tr("Log In"));
    QPushButton *regButton = new QPushButton(tr("Registration"));

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


    // Задаём два пункта с текстом локалей в комбобоксе

    QComboBox *comboBox = new QComboBox;
    comboBox->addItems(QStringList() << "ru\_RU" << "en\_US");

    // подключаем к сигналу изменения пункта комбобокса лямбда функцию,
    // в которой будет изменяться перевод приложения
    // Здесь имеется интересный момент. Поскольку QComboBox имеет перегрузку сигнатуры сигнала,
    // то нам необходимо скастовать сигнал к нужной сигнатуре.
    // В данном случае будем использовать название пункта при его изменении
    connect(comboBox, static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
            [=](const QString &str){
        qtLanguageTranslator.load("QtLanguage\_" + str, ".");   // Загружаем перевод
        qApp->installTranslator(&qtLanguageTranslator);        // Устанавливаем перевод в приложение
    });

    // Сделаем первоначальную инициализацию перевода для окна прилоежния
    qtLanguageTranslator.load(QString("QtLanguage\_") + QString("ru\_RU"));
    qApp->installTranslator(&qtLanguageTranslator);

    mainHLayout->addWidget(centerContainer);                                                 // ВЫРАВНИВАНИЕ ПО ЦЕНТРУ
    mainHLayout->setAlignment(Qt::AlignCenter);
    mainVLayout->addLayout(mainHLayout);
    mainVLayout->setAlignment(Qt::AlignCenter);




    this->setLayout(mainVLayout);
}

void StartFragment::changeEvent(QEvent *event)
{
    // В случае получения события изменения языка приложения
    if (event->type() == QEvent::LanguageChange) {
        //        retranslateUi(this);    // переведём окно заново
    }
}

//void retranslateUi(QMainWindow *MainWindow)
//{
//    MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));

//} // retranslateUi

StartFragment::~StartFragment() {

}

void StartFragment::openLogin() {
    navigateTo(LOGIN_TAG);
}

void StartFragment::openRegistration() {
    navigateTo(REGISTRATION_TAG);
}
