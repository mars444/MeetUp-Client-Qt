#ifndef MAINFRAGMENT_H
#define MAINFRAGMENT_H

#include <common/base/basefragment.h>

#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPushButton>
#include <QVBoxLayout>
#include <models/deskmodel.h>
#include <ui/view/waitingspinnerwidget.h>

class MainFragment: public BaseFragment {
    Q_OBJECT
private:
    QNetworkAccessManager *networkManager;

    QString lastRequest;

    QPushButton *exitButton;

    QLabel *userName;

    QLabel *profileImageLabel;

    QVBoxLayout *userContainer;

    WaitingSpinnerWidget *loading;
    WaitingSpinnerWidget *loadingExit;

public:
    MainFragment();
    ~MainFragment();

    QString user_ID;

    void onResume() override;
public slots:

    void imageFunc();
    void onExit();
    void myFriends();
    void myShedule();
    void myGroups();
    void mySettings();
    void myProfile();
    void Group();
    void onHttpResult(QNetworkReply *reply);
};

#endif // MAINFRAGMENT_H
