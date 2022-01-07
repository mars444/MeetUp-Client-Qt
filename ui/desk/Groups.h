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

class Groups : public BaseFragment{
    Q_OBJECT

private:

    QHash<QPushButton*,QHBoxLayout*> mButtonToLayoutMap;
    QHash<QPushButton*,QHBoxLayout*>mButtonBackToLayoutMap;




    std::string str;


    QVBoxLayout *mainVLayout;
    QVBoxLayout *inputContainerGroups;

    WaitingSpinnerWidget *loading;

    QLabel *titleLabel;

     QHBoxLayout *GroupContainer2;

    QPushButton *inviteGroupButton2;
    QPushButton *deleteGroupButton2;

    QLabel *GroupImageLabel2;

    QVBoxLayout *friendContainer2;

    QLineEdit *addGroupEdit;
    QPlainTextEdit *descriptionEdit;
    QPushButton *createButton;
    QPushButton *addGroupButton;
    QNetworkAccessManager *networkManager;

    QNetworkAccessManager *addManagerFriendtoGroup;

    QPushButton *friendName2;

    QStackedWidget *stack;


    QPushButton *inviteGroupButton;
    QVBoxLayout *innerScrollFriends;

    QPushButton *backAddtoGroup;


    QString groupNameString;

    QNetworkAccessManager *addManagerGroup;

    QPushButton *GroupNameButton;

public:
    Groups();
    ~Groups();




public slots:


     void friendName2Pressed();


    void loadGroups();

    void onBackPressed();

    void backAddtoGroupPressed();

    void inviteGroupPressed();

        void goToGroup();

    void addGroupButtonPressed();
    void checkNameGroup();

    void onHttpResultGroup(QNetworkReply *reply);


    void onHttpResult(QNetworkReply *reply);

    void onHttpResultDeleteGroup(QNetworkReply *reply);

    void onHttpResultAddFriendtoGroup(QNetworkReply *reply);


    /**
     * @brief checkData
     *
     * проверка введенных данных
     * на корректность.
     */
    void checkData();
};
