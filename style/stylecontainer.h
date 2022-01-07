#ifndef STYLECONTAINER_H
#define STYLECONTAINER_H

#include <QColor>
#include <QString>

namespace styles{
    /** объявления цветов */
    static const QString COLOR_BACKGROUND = "#FFF";
    static const QString COLOR_TEXT_PRIMARY = "#242424";
    static const QString COLOR_TEXT_HINT= "#A6A6A6";
    static const QString COLOR_PRIMARY = "#A184F9";
    static const QString COLOR_BORDER = "#E6EBF0";
    static const QString COLOR_TEXT_RED = "#FF6262";
    static const QString COLOR_BUTTON_PRESSED = "#8046A4";

    static const QColor QT_COLOR_PRIMARY = QColor(72, 129, 183);

    /** объявления стилей */


    static const QString CALENDAR =


    "selection-background-color: #A184F9;"
    "selection-color: #fff;";




    static const QString EVENT_STYLE =
            "QFrame {"
            "   border-radius:40px;"
            "background: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 #A184F9, stop:1 #8046A4);"

            "   padding-left:10px;"
            "   padding-right:10px;"

            "}";


    static const QString EVENT_READY_STYLE =
            "QFrame {"
            "   border-radius:20px;"
            "background: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 #A184F9, stop:1 #8046A4);"

            "   padding-left:10px;"
            "   padding-right:10px;"

            "   margin-bottom:15px;"

            "}";

    static const QString GROUPS_FRAME =
            "QFrame {"
            "   border-radius:50px;"
            "background: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 #fff, stop:1 #8046A4);"

            "   margin-bottom:15px;"

            "}";

    static const QString SETTING_LEFT_STYLE =
            "QFrame {"
            "   border-radius:20px;"
            "background: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 #A184F9, stop:1 #8046A4);"

            "   padding-left:10px;"
            "   padding-right:10px;"
            "   padding-bottom:15px;"

            "   margin-right:75px;"


            "}";

    static const QString SETTING_RIGHT_STYLE =
            "QFrame {"
            "   border-radius:20px;"
            "background: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 #A184F9, stop:1 #8046A4);"

            "   padding-left:10px;"
            "   padding-right:10px;"
            "   margin-left:75px;"
            "   padding-bottom:15px;"


            "}";

    static const QString FRAME_BUTTONS_MAIN =
            "QFrame {"
            "   border-radius:20px;"
            "background-color: #8046A4);"

            "   padding:10px;"


            "}";


    static const QString PROFILE_IMAGE  =
            "QLabel {"

            "   margin:0px 30px;"
            "}"
            "QPixmap {"

            "   margin:0px 30px;"
            "}";


    static const QString USER_NAME  =
            "   padding-top: 30px;"
            "   margin-top: 30px;"
            "color:" + COLOR_TEXT_PRIMARY + ";"
            "font-size:30px;"
        "QFrame {"
                   "background: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 #A184F9, stop:1 #8046A4);"
                        "}";



    static const QString TIMESTYLE  =
            "QLabel {"
            "   text-align: center;"
            "   border:1px solid #ff0000;"
            "   border-radius:5px;"

            "}";





    static const QString GROUP_IMAGE  =
            "QLabel {"
            "   margin-right: 50px;"

            "   margin-bottom: 50px;"
            "}";


    static const QString TASK_PADDING  =
            "QLabel {"
            "   padding-right: 20px;"
            "   font-size: 25px;"

            "}"

            "QFrame {"
            "background: transparent;"
            "}";

    static const QString SETTINGS_LABEL  =
            "QLabel {"


            "   margin-right:30px;"
            "   font-size: 18px;"
            "   text-align: center;"
            "}"
            "QFrame {"
            "background: transparent;"
            "}";




    static const QString MAIN_TITLE  =
            "QLabel {"

            "   margin-left: 20px;"
            "   font-size: 30px;"
            "   color: "+COLOR_BACKGROUND+";"

            "}";


    static const QString FRIEND_NAME_SURNAME  =
            "QLabel {"
            "   font-size: 25px;"
            "   text-align: center;"
            "   color: "+COLOR_PRIMARY+";"

            "}";




    static const QString FRIEND_IMAGE  =
            "QLabel {"
            "   margin-right: 10px;"


            "}";

    static const QString Qtimestyle =
            "QTimeEdit {"
            "   height:35px;"
            "   text-align: center;"
            "   width:100px;"
            "}";


    static const QString GLOBAL_BACK_WHITE =
            "QWidget#container {"
            "   background-color:"+COLOR_BACKGROUND+";"
            "   border-radius:100px;"            "}"
              "QWidget#fragment {"
             "background: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 #fff, stop:1 #8046A4);"
             "}";

    static const QString FRAME_8PX_WHITE =
            "QFrame {"
            "   background-color:"+COLOR_BACKGROUND+";"
            "   border-radius:10px;"
            "   height:800px;"
            "   width:900px;"
            "}";

    static const QString SPLASH_ICON =
            "   height:500px;"
            "   width:600px;";

    static const QString START_ICON =
            "   height:300px;"
            "   width:300px;";

    static const QString TITLE_LABLE =
            "color:" + COLOR_TEXT_PRIMARY + ";"
            "font-size:30px;";
    static const QString HINT_LABLE =
            "color:" + COLOR_TEXT_HINT + ";"
            "font-size:14px;";

    static const QString BUTTON_SOLID =
            "QPushButton {"
            "color: "+COLOR_BACKGROUND+";"
            "background-color:"+COLOR_PRIMARY+";"
            "border:none;"
            "padding:12px;"
            "border-radius:8px;"
            "font-size:16px;"
            "}"
            "QPushButton:hover {"
            "background-color:"+COLOR_BUTTON_PRESSED+";"
            "}";

    static const QString BUTTON_SOLID_DELETE =
            "QPushButton {"
            "color: "+COLOR_BACKGROUND+";"
            "background-color:"+COLOR_PRIMARY+";"
            "border:none;"
            "padding:12px;"
            "border-radius:22px;"
            "font-size:16px;"
            "}"
            "QPushButton:hover {"
            "background-color:"+COLOR_TEXT_RED+";"
            "}";



    static const QString BUTTON_WHITE =
            "QPushButton {"
            "color: "+COLOR_PRIMARY+";"
            "background-color:"+COLOR_BACKGROUND+";"
            "padding:10px 20px;"
            "border-radius:10px;"
            "cursor:pointer;"

             "text-transform:underline;"

            "font-size:25px;"
            "}"
            "QPushButton:hover {"
            "background-color:red;"
            "cursor:pointer;"
            "}"
            "QFrame {""background: transparent""}"
    "QCursor {""cursor: pointer""}";

    static const QString BUTTON_DISABLED =
            "QPushButton {"
            "color: "+COLOR_TEXT_HINT+";"
            "background-color:"+COLOR_BORDER+";"
            "border:none;"
            "padding:12px;"
            "border-radius:8px;"
            "font-size:16px;"
            "}"
            "QPushButton:hover {"
            "background-color:"+COLOR_BORDER+";"
            "}";

    static const QString BUTTON_EMPTY =
            "QPushButton {"
            "color: "+COLOR_PRIMARY+";"
            "background-color:"+COLOR_BACKGROUND+";"
            "border:1px solid "+COLOR_PRIMARY+";"
            "padding:12px;"
            "border-radius:8px;"
            "font-size:16px;"
            "}"
            "QPushButton:hover {"
            "background-color:"+COLOR_BORDER+";"
            "}";

    static const QString BUTTON_PROFILE =
            "QPushButton {"
            "color: "+COLOR_PRIMARY+";"
            "background-color:"+COLOR_BACKGROUND+";"
            "border:1px solid "+COLOR_BORDER+";"
            "padding:12px;"
            "border-radius:8px;"
            "font-size:16px;"
            "}"
            "QPushButton:hover {"
            "background-color:"+COLOR_BORDER+";"
            "}"
                                            /* "QPushButton::text {"
                                             "margin-left:16px;"
                                             "}"*/;

    static const QString BUTTON_PROFILE_RED =
            "QPushButton {"
            "color: "+COLOR_TEXT_RED+";"
            "background-color:"+COLOR_BACKGROUND+";"
            "border:1px solid "+COLOR_BORDER+";"
            "padding:12px;"
            "border-radius:8px;"
            "font-size:16px;"
            "}"
            "QPushButton:hover {"
            "background-color:"+COLOR_BORDER+";"
            "}";

    static const QString EDIT_TEXT =
            "border: 1px solid "+COLOR_BORDER+";"
            "color: "+COLOR_TEXT_PRIMARY+";"
            "background-color:"+COLOR_BACKGROUND+";"
            "font-size:16px;"
            "border-radius:10px;"
            "padding:12px;";

    static const QString EDIT_TEXT_EVENT_TITLE =
            "border: 1px solid "+COLOR_BORDER+";"
            "color: "+COLOR_TEXT_PRIMARY+";"
            "background-color:"+COLOR_BACKGROUND+";"
            "font-size:20px;"
            "border-radius:10px;"
            "width:200px;"
            "padding:12px;";

    static const QString EDIT_TEXT_SMALL =
            "border: 1px solid "+COLOR_BORDER+";"
            "color: "+COLOR_TEXT_PRIMARY+";"
            "background-color:"+COLOR_BACKGROUND+";"
            "font-size:16px;"
            "border-radius:10px;"
            "padding:12px;";

    static const QString BACK_WHITE =
            "QFrame#fragment {"
            "background-color:"+COLOR_BACKGROUND+";"
                                                 "}";

    static const QString DESK_WIDGET =
            "QFrame#desk {"
            "background-color:"+COLOR_BACKGROUND+";"
            "border:1px solid "+COLOR_BORDER+";"
            "font-size:16px;"
            "padding: 0px;"
            "border-radius:8px;"
            "}";

    static const QString SCROL_BAR =
            "QFrame {""background: transparent""}"
            "QScrollBar:vertical {"
            "   border: 0px solid "+COLOR_BORDER+";"
            "   background: transparent;"
            "   width: 0px;"
            "   margin: 0px 0px 0px 0px;"
            "}"
            "QScrollBar:horizontal {"
            "   border: 0px solid "+COLOR_BORDER+";"
            "   background: transparent;"
            "   height: 0px;"
            "   margin: 0px 0px 0px 0px;"
            "}"
            "QScrollBar::handle {"
            "   background: transparent;"
            "   border: 0px solid "+COLOR_BORDER+";"
            "   border-radius: 0px;"
            "}"
            "QScrollBar::add-line:vertical {"
            "   height: 0px;"
            "   subcontrol-position: bottom;"
            "   subcontrol-origin: margin;"
            "}"
            "QScrollBar::sub-line:vertical {"
            "   height: 0 px;"
            "   subcontrol-position: top;"
            "   subcontrol-origin: margin;"
            "}"
            "QScrollBar::add-line:horizontal {"
            "   width: 0px;"
            "   subcontrol-position: right;"
            "   subcontrol-origin: margin;"
            "}"
            "QScrollBar::sub-line:horizontal {"
            "   width: 0 px;"
            "   subcontrol-position: left;"
            "   subcontrol-origin: margin;"
            "}";

};


class StyleContainer
{
public:
    StyleContainer();
};

#endif // STYLECONTAINER_H
