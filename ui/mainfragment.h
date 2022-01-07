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
    QString token;
    QString lastRequest;

    QPushButton *exitButton;

    QList<DeskModel*> deskList;
    QLabel *userName;

    QVBoxLayout *userContainer;

    QVBoxLayout *start;
    QVBoxLayout *end;

    WaitingSpinnerWidget *loading;
    WaitingSpinnerWidget *loadingExit;


    const QString EXIT = "req_exit";
    const QString LIST = "req_list";

    void loadUserName();

public:
    MainFragment();
    ~MainFragment();

    void onResume() override;
public slots:
    void onExit();
    void myFriends();
    void myShedule();
    void myGroups();
    void mySettings();
    void Group();


    void onHttpResult(QNetworkReply *reply);
};

#endif // MAINFRAGMENT_H
