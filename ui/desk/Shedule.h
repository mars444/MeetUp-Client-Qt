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

class Shedule: public BaseFragment {
    Q_OBJECT
private:

    DeskModel *model;
    QString currentType = "simple";

    QHBoxLayout *mainHLayout;
    QVBoxLayout *inputContainer;

    QString strDinamicckeck = "";

   QCalendarWidget *calendar;

    QLineEdit *titleEdit;
    QLineEdit *cardTitleEdit;

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



    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit;
    QPushButton *addButtonq;
    QPushButton *deleteButton;

    QSvgButton *addBoxTitleButton;

    QVBoxLayout *titleWidgetList;

    QHBoxLayout *task_container;

    QSvgWidget *mainImageTask;

    QLabel *boxTitleTask;

    QLabel *timeLabelTask;

    QSvgButton *deleteTaskButton;



    QList<QString> titleList;

    QPushButton *date1Button;
    QPushButton *date2Button;
    QPushButton *date3Button;
    QPushButton *date4Button;
    QPushButton *date5Button;
    QPushButton *date6Button;
    QPushButton *date7Button;

    QStackedWidget *stack;

    QTimeEdit* left;
    QTimeEdit* right;

    QNetworkAccessManager *networkManager;

public:
    Shedule();
    ~Shedule();

    void setData(BaseModel* model) override;
public slots:
    void onBackPressed();
    void onCreatePressed();
    void onHttpResult(QNetworkReply *reply);
    void onBoxTitleAdd();

    void loadSheduleFromDate();

    void day_btn_1();
    void day_btn_2();
    void day_btn_3();
    void day_btn_4();
    void day_btn_5();
    void day_btn_6();
    void day_btn_7();
    void deleteButton_pressed();
    void calendar_btn(const QDate &date);
    void setButtonDate(void);
    void on_addButton_clicked();

    /**
     * @brief checkData
     *
     * проверка введенных данных
     * на корректность.
     */
    void checkData();
    void checkBoxTitle();
};
