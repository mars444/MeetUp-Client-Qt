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

class Group : public BaseFragment{
    Q_OBJECT

private:

    QLabel *groupEventDateLabel;
    QLabel *groupEventstart;
    QLabel *groupEventend;



    QVBoxLayout *mainVLayout;



    QLabel *GrouptitleLabel;
    QLineEdit *titleEdit;
    QPlainTextEdit *descriptionEdit;
    QPushButton *createButton;
    QNetworkAccessManager *networkManager;

public:
    Group();
    ~Group();


public slots:


    void loadGroup();

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
