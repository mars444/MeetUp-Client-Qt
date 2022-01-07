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
    QString token;



    QVBoxLayout *mainVLayout;

    WaitingSpinnerWidget *loading;

    QLabel *titleLabel;
    QLineEdit *titleEdit;
    QPlainTextEdit *descriptionEdit;
    QPushButton *createButton;
    QNetworkAccessManager *networkManager;

public:
    Friends();
    ~Friends();


public slots:


    void loadFriends();

    void onBackPressed();

    void onHttpResult(QNetworkReply *reply);

    /**
     * @brief checkData
     *
     * проверка введенных данных
     * на корректность.
     */
    void checkData();
};
