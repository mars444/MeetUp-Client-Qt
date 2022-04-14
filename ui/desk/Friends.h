#pragma once

#include <QLineEdit>
#include <QNetworkAccessManager>
#include <QPushButton>
#include <QWidget>
#include <QNetworkReply>
#include <QPlainTextEdit>
#include <QLabel>

#include <common/base/basefragment.h>



#include <ui/view/waitingspinnerwidget.h>

#include <models/deskmodel.h>

class Friends : public BaseFragment{
    Q_OBJECT

private:

    QPushButton *userName;

    QPushButton *deleteFriendYesBtn;
    QPushButton *deleteFriendNoBtn;
    QLabel *deleteFriendText;
    QPushButton *deleteFriendBtn;

    QHBoxLayout *friendInner;


public:
    Friends();
    ~Friends();

    QLabel *friendName2;


public slots:
    void deleteFriendYesBtnPressed();
    void deleteFriendNoBtnPressed();


    void onBackPressed();
    void deleteFriendBtnPressed();

};
