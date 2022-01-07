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
    QString token;

    bool editmode = false;
    DeskModel *model;

    WaitingSpinnerWidget *loading;

    QLabel *titleLabel;
    QLineEdit *titleEdit;
    QPlainTextEdit *descriptionEdit;
    QPushButton *createButton;
    QNetworkAccessManager *networkManager;

    void setData(BaseModel* model) override;
public:
    Settings();
    ~Settings();


public slots:
    void onBackPressed();
    void onCreatePressed();
    void onHttpResult(QNetworkReply *reply);

    /**
     * @brief checkData
     *
     * проверка введенных данных
     * на корректность.
     */
    void checkData();
};
