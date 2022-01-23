#pragma once
#include <common/base/basefragment.h>

#include <QLineEdit>
#include <QNetworkAccessManager>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QStackedWidget>
#include <QTimeEdit>
#include <QSvgWidget>
#include <QLabel>

#include <models/deskmodel.h>

#include <ui/view/qsvgbutton.h>
#include <ui/view/waitingspinnerwidget.h>

#include "mytimeedit.h"

class Shedule: public BaseFragment {
    Q_OBJECT
private:

    DeskModel *model;
    QString currentType = "simple";


    QHash<QPushButton*,QHBoxLayout*> deleteTaskButtonToLayoutMap;

    QHash<QPushButton*,QPushButton*> doneButtonToLayoutMap;

    QHash<QPushButton*,QPushButton*> doneButtonYesToLayoutMap;

    QHash<QPushButton*,QFrame*> taskFrameDeleteLayoutMap;

    QHBoxLayout *mainHLayout;

    QFrame *formFrame;

    QVBoxLayout *inputContainer;

    QHBoxLayout *form;


    QString strDinamicckeck = "";

    QCalendarWidget *calendar;
    QString ID_QSTRING;

    QLineEdit *titleEdit;
    QLineEdit *cardTitleEdit;
    QLineEdit *cardDescriptionEdit;

    WaitingSpinnerWidget *loading;
    WaitingSpinnerWidget *loadingBox;

    QPlainTextEdit *descriptionEdit;
    QPushButton *createButton_1;
    QPushButton *createButton_2;
    QPushButton *createButton_3;
    QPushButton *createButton_4;
    QPushButton *createButton_5;
    QPushButton *createButton_6;
    QPushButton *createButton_7;


    QDate date1;
    QDate date2;
    QDate date3;
    QDate date4;
    QDate date5;
    QDate date6;
    QDate date7;


    QString time_begin_string;

    QString time_end_string;


    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit;
    QPushButton *addButtonq;
    QPushButton *deleteButton;

    QSvgButton *addBoxTitleButton;

    QVBoxLayout *titleWidgetList;

    QHBoxLayout *task_container;

    QSvgWidget *mainImageTask;

    QLabel *boxTitleTask;

    QString dateToHTTP;

    QLabel *timeLabelTask;

    QDate datetohttp;

    QSvgButton *deleteTaskButton;

    QSvgButton *updateTaskButton;

    QSvgButton *doneButton;

    QSvgButton *doneButtonYes;


    QHBoxLayout *titleEditContainer;

    QVBoxLayout *task_container_inner;

    QList<QString> titleList;

    QLabel *dateTask;


    QTime time_begin;
    QTime time_end;

    QPushButton *date1Button;
    QPushButton *date2Button;
    QPushButton *date3Button;
    QPushButton *date4Button;
    QPushButton *date5Button;
    QPushButton *date6Button;
    QPushButton *date7Button;


    QSvgButton *calendarOpen;
    QSvgButton *calendarClose;

    QString dateTotask;

    QStackedWidget *stack;

    TimeEdit* left;
    TimeEdit* right;

    QNetworkAccessManager *networkManagerGetEvents;
    QNetworkAccessManager *networkManagerSendShedule;

    QNetworkAccessManager *networkManageraddEvent;

    QNetworkAccessManager *networkManagerDeleteEvent;

public:
    Shedule();
    ~Shedule();

    void setData(BaseModel* model) override;
public slots:
    void onBackPressed();

    void doneButtonYes_pressed();

    void doneButton_pressed();


    void setTimeLeftTimeEdit();

    void setTimeRightTimeEdit(const QTime &time);
    void onCreatePressed();
    void onHttpResultGetEvents(QNetworkReply *reply);

    void onHttpResultSendShedule(QNetworkReply *reply);

    void onHttpResultAddEvent(QNetworkReply *reply);

    void onHttpResultDeleteEvent(QNetworkReply *reply);
    void onBoxTitleAdd();

    void loadSheduleFromDate();

    void day_btn_1();

    void leftButtonClicked();
    void rightButtonClicked();

    void calendarOpenClicked();
    void calendarCloseClicked();

    void day_btn_2();
    void day_btn_3();
    void day_btn_4();
    void day_btn_5();
    void day_btn_6();
    void day_btn_7();
    void deleteButton_pressed();
    void calendar_btn(const QDate &date);
    void setButtonDate(void);
    void sendShedulePressed();
    void updateTaskButton_pressed();

    void clearTasks();

    /**
     * @brief checkData
     *
     * проверка введенных данных
     * на корректность.
     */
    void checkData();
    void checkBoxTitle();
};
