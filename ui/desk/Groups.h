#pragma once
#include <common/base/basefragment.h>

#include <QLabel>
#include <QNetworkAccessManager>
#include <QScrollBar>
#include <QVBoxLayout>

#include <models/cardmodel.h>
#include <models/deskmodel.h>

class Groups: public BaseFragment {
    Q_OBJECT
private:
    QLabel *titleLabel;
    QLabel *description;
    QLabel *users;
    QLabel *progress;

    const QString LOAD_DATA = "load_data";
    const QString CHECK = "check";

    DeskModel *model;
    QNetworkAccessManager *networkManagerGroup;

public:
    Groups();
    ~Groups();


    void loadData();
public slots:
    void onBackPressed();

    void loadGroups();


    void onHttpResult(QNetworkReply *reply);

};
