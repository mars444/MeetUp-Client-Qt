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

class Settings : public BaseFragment{
    Q_OBJECT

private:


    QLineEdit *userAgeEdit;
    QLabel *userAgeLabel;
    QString ID_QSTRING;


    QLabel *titleLabel;
    QLineEdit *titleEdit;
    QPlainTextEdit *descriptionEdit;

    QNetworkAccessManager *networkManager;
    QNetworkAccessManager *networkManagerRight;

    QNetworkAccessManager *networkManagerSetSettings;
    QNetworkAccessManager *networkManagerSetSettingsRight;

public:
    Settings();
    ~Settings();


public slots:
    void onBackPressed();


};
