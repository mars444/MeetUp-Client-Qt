#pragma once

#include <QLineEdit>
#include <QNetworkAccessManager>
#include <QPushButton>
#include <QWidget>
#include <QNetworkReply>
#include <QPlainTextEdit>
#include <QLabel>
#include <QStackedWidget>

#include <common/base/basefragment.h>

 static QString *nameGroupString;


#include <ui/view/waitingspinnerwidget.h>

#include <models/deskmodel.h>

class Group : public BaseFragment{
    Q_OBJECT

private:

    QHash<QPushButton*,QHBoxLayout*> mButtonToLayoutMap;

    QLabel *groupEventDateLabel;
    QLabel *groupEventstart;
    QLabel *groupEventend;

    QString ID_QSTRING;

    QString GROUP_TITLE_QSTRING;

    QVBoxLayout *inputContainerGroups;

    QFrame *stackListWidget;

    QVBoxLayout *stackList;

       std::string str;

       QLabel *friendName2;

         QHBoxLayout *friendContainer2;

    QPushButton *addFriendButton;
    QLineEdit *addFriendEdit;

        QVBoxLayout *inputContainerFriends;



     QStackedWidget *stack;

     QVBoxLayout *mainVLayout;

     QPushButton *groupMeets;

     QPushButton *groupList;

     QPushButton *groupDelete;




    QPushButton *day1Button;
    QPushButton *day2Button;
    QPushButton *day3Button;
    QPushButton *day4Button;
    QPushButton *day5Button;
    QPushButton *day6Button;
    QPushButton *day7Button;

    QLabel *GrouptitleLabel;





    QLineEdit *titleEdit;
    QPlainTextEdit *descriptionEdit;
    QPushButton *createButton;
    QNetworkAccessManager *networkManagerloadFriends;
    QNetworkAccessManager *networkManagerGetMeets;
    QNetworkAccessManager *networkManagerDeleteFriendFromGroup;
    QNetworkAccessManager *networkManagerDeleteGroup;


public:
    Group();
    ~Group();








public slots:

    void sendGroupNameSlot(const QString &text);



    void loadGroup();

    void loadFriends();

    void onBackPressed();

    void groupListPressed();

     void groupMeetsPressed();

     void groupDeletePressed();

     void deleteFriendPressed();

     //void setNameGroup();


      void onHttpResultnetworkManagerGetList(QNetworkReply *reply);

       void onHttpResultnetworkManagerGetMeets(QNetworkReply *reply);

       void onHttpResultnetworkManagerDeleteFriendFromGroup(QNetworkReply *reply);

       void getIventsDatePressed();


    void getMeets();
    void onHttpResult(QNetworkReply *reply);


    void onHttpResultDeleteGroup(QNetworkReply *reply);



    /**
     * @brief checkData
     *
     * проверка введенных данных
     * на корректность.
     */

};
