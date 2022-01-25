QT       += core gui
QT += svg
QT += network
QT += sql
QT += websockets
QT += widgets
QT += networkauth

TARGET = QtLanguage
TEMPLATE = app


TRANSLATIONS += QtLanguage_ru.ts

CODECFORSRC     = UTF-8

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
    models/usermodel.cpp \
    screensfactory.cpp \
    style/stylecontainer.cpp \
    ui/auth/googleauth.cpp \
    ui/auth/loginfragment.cpp \
    ui/auth/registrationfragment.cpp \
    ui/auth/startfragment.cpp \
    ui/auth/user_data.cpp \
    ui/desk/Layouts/friendlayout.cpp \
    ui/desk/Layouts/shedule_generation.cpp \
    ui/desk/friends.cpp \
    ui/desk/group.cpp \
    ui/desk/groups.cpp \
    ui/desk/mytimeedit.cpp \
    ui/desk/profile.cpp \
    ui/desk/settings.cpp \
    ui/desk/shedule.cpp \
    ui/desk/switch.cpp \
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
    nlohmann/adl_serializer.hpp \
    nlohmann/byte_container_with_subtype.hpp \
    nlohmann/detail/conversions/from_json.hpp \
    nlohmann/detail/conversions/to_chars.hpp \
    nlohmann/detail/conversions/to_json.hpp \
    nlohmann/detail/exceptions.hpp \
    nlohmann/detail/hash.hpp \
    nlohmann/detail/input/binary_reader.hpp \
    nlohmann/detail/input/input_adapters.hpp \
    nlohmann/detail/input/json_sax.hpp \
    nlohmann/detail/input/lexer.hpp \
    nlohmann/detail/input/parser.hpp \
    nlohmann/detail/input/position_t.hpp \
    nlohmann/detail/iterators/internal_iterator.hpp \
    nlohmann/detail/iterators/iter_impl.hpp \
    nlohmann/detail/iterators/iteration_proxy.hpp \
    nlohmann/detail/iterators/iterator_traits.hpp \
    nlohmann/detail/iterators/json_reverse_iterator.hpp \
    nlohmann/detail/iterators/primitive_iterator.hpp \
    nlohmann/detail/json_pointer.hpp \
    nlohmann/detail/json_ref.hpp \
    nlohmann/detail/macro_scope.hpp \
    nlohmann/detail/macro_unscope.hpp \
    nlohmann/detail/meta/call_std/begin.hpp \
    nlohmann/detail/meta/call_std/end.hpp \
    nlohmann/detail/meta/cpp_future.hpp \
    nlohmann/detail/meta/detected.hpp \
    nlohmann/detail/meta/identity_tag.hpp \
    nlohmann/detail/meta/is_sax.hpp \
    nlohmann/detail/meta/type_traits.hpp \
    nlohmann/detail/meta/void_t.hpp \
    nlohmann/detail/output/binary_writer.hpp \
    nlohmann/detail/output/output_adapters.hpp \
    nlohmann/detail/output/serializer.hpp \
    nlohmann/detail/string_escape.hpp \
    nlohmann/detail/value_t.hpp \
    nlohmann/json.hpp \
    nlohmann/json_fwd.hpp \
    nlohmann/ordered_map.hpp \
    nlohmann/thirdparty/hedley/hedley.hpp \
    nlohmann/thirdparty/hedley/hedley_undef.hpp \
    screensfactory.h \
    single_include/nlohmann/json.hpp \
    style/stylecontainer.h \
    ui/auth/googleauth.h \
    ui/auth/user_data.h \
    ui/desk/Friends.h \
    ui/desk/Group.h \
    ui/desk/Groups.h \
    ui/desk/Layouts/Shedule_generation.h \
    ui/desk/Layouts/friendlayout.h \
    ui/desk/Profile.h \
    ui/desk/Settings.h \
    ui/desk/Shedule.h \
    ui/auth/loginfragment.h \
    ui/auth/registrationfragment.h \
    ui/auth/startfragment.h \
    ui/desk/mytimeedit.h \
    ui/desk/switch.h \
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
    resc.qrc



win32:RC_ICONS += resc/icon.ico

DISTFILES += \
    resc/QtLanguage_ru.qm \
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
