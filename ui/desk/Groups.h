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

    QHash<QPushButton*,QHBoxLayout*>groupNamesLayoutMap;


    QLabel *noGroupsLabel;

    std::string strFriends;
    std::string strGroups;

    QVBoxLayout *mainVLayout;
    QVBoxLayout *inputContainerGroups;
    QString ID_QSTRING;
    QString NICK_QSTRING;

    QString GROUP_TITLE_QSTRING;

    WaitingSpinnerWidget *loading;

    QLabel *titleLabel;


    QHBoxLayout *GroupContainer2;

    QPushButton *inviteGroupButton2;

    QPushButton *NameGroupButton;

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

    QHBoxLayout *backLayout;


    QString groupNameString;

    QString groupIDString;

    QNetworkAccessManager *addManagerGroup;

    QNetworkAccessManager *ManagerAddFriendToGroup;
    QNetworkAccessManager *ManagerAddFriendsLayout;



public:
    Groups();
    ~Groups();
    QPushButton *GroupNameButton;



signals:
    void sendGroupNameSignal(const QString &text); //название сигнала потом сами пропишите


public slots:




    void friendName2Pressed();


    void loadGroups();

    void loadFriends();

    void onBackPressed();

    void backAddtoGroupPressed();

    void inviteGroupPressed();

    void goToGroup();

    void addGroupButtonPressed();
    void checkNameGroup();

    void onHttpResultAddGroup(QNetworkReply *reply);


    void onHttpResult(QNetworkReply *reply);


    void onHttpResultAddFriendtoGroup(QNetworkReply *reply);
    void onHttpResultManagerAddFriendsLayout(QNetworkReply *reply);

    /**
     * @brief checkData
     *
     * проверка введенных данных
     * на корректность.
     */
    void checkData();
};
