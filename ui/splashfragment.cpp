#include "splashfragment.h"

#include <QFrame>
#include <QLabel>
#include <QSettings>
#include <QTimer>
#include <QMovie>
#include <QVBoxLayout>
#include <qsvgwidget.h>

#include <style/stylecontainer.h>
#include <screensfactory.h>
using namespace styles;
using namespace screens;

SplashFragment::SplashFragment() {
    qDebug("SplashFragment create");

    QVBoxLayout *mainVLayout = new QVBoxLayout;
    QHBoxLayout *mainHLayout = new QHBoxLayout;
    //QSvgWidget *centerContainer = new QSvgWidget(":/resc/resc/logo.svg");

    //QLabel *titleLabel = new QLabel("Загрузка...");
    //titleLabel->setStyleSheet(TITLE_LABLE);




    QLabel *centerContainer = new QLabel("");
    //QPixmap profileImage(":/resc/resc/loader.gif");
    //centerContainer->setPixmap(profileImage);


    QMovie *movie = new QMovie( ":/resc/resc/loader3.gif" );
    centerContainer->setMovie(movie); // label имеет тип QLabel*
    movie->start();

    centerContainer->setStyleSheet(SPLASH_ICON);
    mainHLayout->addWidget(centerContainer);
    mainHLayout->setAlignment(Qt::AlignCenter);

    mainVLayout->addLayout(mainHLayout);
     //mainVLayout->addWidget(titleLabel);
    mainVLayout->setAlignment(Qt::AlignCenter);


    this->setStyleSheet(BACK_WHITE);
    this->setObjectName("fragment");
    this->setLayout(mainVLayout);

    QTimer::singleShot(4000, this, SLOT(openStartScreen()));
    qDebug("SplashFragment crete finished!!");
}

SplashFragment::~SplashFragment() {

}

void SplashFragment::openStartScreen() {
    QSettings *settings = new QSettings("settings.ini", QSettings::IniFormat);
    if(settings->value("token", "").toString() != "") {                                      // если есть токен(пользователь уже авторизован) то открыть экран полбз
        newRootScreen(MAIN_TAG);
    } else {                                                                                   // иначе окно входа
        newRootScreen(START_TAG);
    }
}



