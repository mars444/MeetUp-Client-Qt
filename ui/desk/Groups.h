#pragma once
#include <common/base/basefragment.h>

#include <QLabel>
#include <QNetworkAccessManager>
#include <QScrollBar>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>

#include <models/cardmodel.h>
#include <models/deskmodel.h>

class Groups: public BaseFragment {
    Q_OBJECT
private:
    QLabel *titleLabel;
    QLabel *description;
    QLabel *users;
    QLabel *progress;

    QVBoxLayout *inputContainer;

    QVBoxLayout *mainHLayout;

    QPushButton *addGroupButton;
    QLineEdit *addGroupEdit;

    const QString LOAD_DATA = "load_data";
    const QString CHECK = "check";

    DeskModel *model;
    QNetworkAccessManager *networkManagerGroup;

    QNetworkAccessManager *addManagerGroup;

public:
    Groups();
    ~Groups();


    void loadData();
public slots:
    void onBackPressed();

    void loadGroups();


    void addGroupButtonPressed();

    void checkNameGroup();


    void onHttpResult(QNetworkReply *reply);

      void onHttpResultsetGroup(QNetworkReply *reply);

};
