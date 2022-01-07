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



#include <ui/view/waitingspinnerwidget.h>

#include <models/deskmodel.h>

class Group : public BaseFragment{
    Q_OBJECT

private:

    QHash<QPushButton*,QHBoxLayout*> mButtonToLayoutMap;

    QLabel *groupEventDateLabel;
    QLabel *groupEventstart;
    QLabel *groupEventend;


    QVBoxLayout *inputContainerGroups;

    QFrame *stackListWidget;

    QVBoxLayout *stackList;

       std::string str;

       QLabel *friendName2;

         QHBoxLayout *friendContainer2;

    QPushButton *addFriendButton;
    QLineEdit *addFriendEdit;

        QVBoxLayout *inputContainerFriends;

     QLabel *GrouptitleLabel;

     QStackedWidget *stack;

    QVBoxLayout *mainVLayout;

        QPushButton *groupMeets;

            QPushButton *groupList;




    QLineEdit *titleEdit;
    QPlainTextEdit *descriptionEdit;
    QPushButton *createButton;
    QNetworkAccessManager *networkManagerGetList;
    QNetworkAccessManager *networkManagerGetMeets;
    QNetworkAccessManager *networkManagerDeleteFriendFromGroup;


public:
    Group();
    ~Group();




public slots:


    void loadGroup();

    void onBackPressed();

    void groupListPressed();

     void groupMeetsPressed();

     void deleteFriendPressed();


      void onHttpResultnetworkManagerGetList(QNetworkReply *reply);

       void onHttpResultnetworkManagerGetMeets(QNetworkReply *reply);

       void onHttpResultnetworkManagerDeleteFriendFromGroup(QNetworkReply *reply);

    void getMeets();
    void onHttpResult(QNetworkReply *reply);



    /**
     * @brief checkData
     *
     * проверка введенных данных
     * на корректность.
     */

};
