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

class Settings : public BaseFragment{
    Q_OBJECT

private:

    QLineEdit *userNameEdit;
    QLabel *userNameLabel;

    QLineEdit *userSurnameEdit;
    QLabel *userSurnameLabel;

    QLineEdit *userAgeEdit;
    QLabel *userAgeLabel;

    QLineEdit *userAdressEdit;
    QLabel *userAdressLabel;

    QLineEdit *userMailEdit;
    QLabel *userMailLabel;

    QPushButton *setSettingsButton;


    QLabel *titleLabel;
    QLineEdit *titleEdit;
    QPlainTextEdit *descriptionEdit;

    QNetworkAccessManager *networkManager;

    void setData(BaseModel* model) override;
public:
    Settings();
    ~Settings();


public slots:
    void onBackPressed();
    void onCreatePressed();
    void checkSettings();

    void setSettings();
    void getSettings();
    void onHttpResult(QNetworkReply *reply);

    /**
     * @brief checkData
     *
     * проверка введенных данных
     * на корректность.
     */
    void checkData();
};
