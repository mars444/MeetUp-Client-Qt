QT       += core gui
QT += svg
QT += network
QT += sql
QT += websockets
QT += widgets
QT += networkauth

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    common/base/basefragment.cpp \
    common/base/basescreensfactory.cpp \
    common/navigator.cpp \
    main.cpp \
    mainwindow.cpp \
    models/basemodel.cpp \
    models/cardmodel.cpp \
    models/checkboxmodel.cpp \
    models/deskmodel.cpp \
    models/historymodel.cpp \
    models/usermodel.cpp \
    screensfactory.cpp \
    style/stylecontainer.cpp \
    ui/auth/googleauth.cpp \
    ui/auth/loginfragment.cpp \
    ui/auth/registrationfragment.cpp \
    ui/auth/startfragment.cpp \
    ui/desk/Layouts/friendlayout.cpp \
    ui/desk/friends.cpp \
    ui/desk/group.cpp \
    ui/desk/groups.cpp \
    ui/desk/settings.cpp \
    ui/desk/shedule.cpp \
    ui/mainfragment.cpp \
    ui/splashfragment.cpp \
    ui/view/deletesvgbutton.cpp \
    ui/view/qsvgbutton.cpp \
    ui/view/waitingspinnerwidget.cpp

HEADERS += \
    common/base/basefragment.h \
    common/base/basescreensfactory.h \
    common/navigator.h \
    mainwindow.h \
    models/basemodel.h \
    models/cardmodel.h \
    models/checkboxmodel.h \
    models/deskmodel.h \
    models/historymodel.h \
    models/usermodel.h \
    screensfactory.h \
    single_include/nlohmann/json.hpp \
    style/stylecontainer.h \
    ui/auth/googleauth.h \
    ui/desk/Friends.h \
    ui/desk/Group.h \
    ui/desk/Groups.h \
    ui/desk/Layouts/shedule_generation.h \
    ui/desk/Layouts/friendlayout.h \
    ui/desk/Settings.h \
    ui/desk/Shedule.h \
    ui/auth/loginfragment.h \
    ui/auth/registrationfragment.h \
    ui/auth/startfragment.h \
    ui/invite/invitelistfragment.h \
    ui/mainfragment.h \
    ui/splashfragment.h \
    ui/view/deletesvgbutton.h \
    ui/view/loadingwidget.h \
    ui/view/qsvgbutton.h \
    ui/view/userwidget.h \
    ui/view/waitingspinnerwidget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resc.qrc \
    resc.qrc \
    resc.qrc


win32:RC_ICONS += resc/icon.ico

FORMS += \
    ui/desk/dialog.ui

DISTFILES += \
    resc/arrow_back.svg \
    resc/bin.svg \
    resc/client_secret_googleusercontent.com.json \
    resc/done_outline.svg \
    resc/group.svg \
    resc/groupusers.svg \
    resc/loader.gif \
    resc/loader2.gif \
    resc/loader3.gif \
    resc/logo.png \
    resc/logo.svg \
    resc/online_status_off.svg \
    resc/online_status_onn.svg \
    resc/search.svg \
    resc/user.png \
    resc/user_circle.svg
