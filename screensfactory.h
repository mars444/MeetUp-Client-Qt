#ifndef SCREENSFACTORY_H
#define SCREENSFACTORY_H

#include <common/base/basescreensfactory.h>


namespace screens {

static const QString SERVER_URL = "http://192.168.31.207:8080/";
//static const QString SERVER_URL = "http://192.168.31.233:8080/";   // Alya
//static const QString SERVER_URL = "https://httpbin.org/post";
//static const QString SERVER_URL = "http://localhost:8080/";


static const QString SPLASH_TAG = "splash";
static const QString START_TAG = "start";
static const QString LOGIN_TAG = "login";
static const QString REGISTRATION_TAG = "registration";
static const QString MAIN_TAG = "main";
static const QString MY_FRIENDS_SCREEN = "friends_screen";
static const QString MY_GROUPS_SCREEN = "groups_screen";
static const QString MY_SHEDULE_SCREEN = "shedule_screen";
static const QString MY_SETTINGS_SCREEN = "settings_screen";
static const QString GROUP = "group_screen";

};

class ScreensFactory: public BaseScreensFactory {
public:
    ScreensFactory();
    ~ScreensFactory();

    BaseFragment* create(QString tag) override;
    QString createStart() override;
};

#endif // SCREENSFACTORY_H
