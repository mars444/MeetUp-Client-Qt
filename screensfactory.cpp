#include "screensfactory.h"

#include <ui/mainfragment.h>
#include <ui/splashfragment.h>

#include <ui/auth/loginfragment.h>
#include <ui/auth/registrationfragment.h>
#include <ui/auth/startfragment.h>

#include <ui/desk/Shedule.h>
#include <ui/desk/Friends.h>
#include <ui/desk/Groups.h>
#include <ui/desk/Groups.h>
#include <ui/desk/Profile.h>
#include <ui/desk/Group.h>
#include <ui/desk/Settings.h>


using namespace screens;

ScreensFactory::ScreensFactory() {

}

ScreensFactory::~ScreensFactory() {

}

BaseFragment* ScreensFactory::create(QString tag) {
    qDebug("ScreensFactory create");
    if (tag == SPLASH_TAG) {
        return new SplashFragment;
    } else if (tag == START_TAG) {
        return new StartFragment;
    } else if (tag == LOGIN_TAG) {
        return new LoginFragment;
    } else if (tag == REGISTRATION_TAG) {
        return new RegistrationFragment;
    } else if (tag == MAIN_TAG) {
        return new MainFragment;
    } else if (tag == MY_FRIENDS_SCREEN) {
        return new Friends;
    } else if (tag == MY_GROUPS_SCREEN) {
        return new Groups;
    } else if (tag == MY_SHEDULE_SCREEN) {
        return new Shedule;
    } else if (tag == MY_SETTINGS_SCREEN) {
        return new Settings;
    }  else if (tag == MY_PROFILE_SCREEN) {
        return new profile;
    } else if (tag == GROUP) {
        return new Group;
    } else {
        return nullptr;
    }
}

QString ScreensFactory::createStart() {
    return SPLASH_TAG;
}


