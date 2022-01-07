#include "Shedule.h"
#include "Layouts/Shedule_generation.h"
#include <iostream>
#include <QLabel>
#include <cstring>
#include <QTimeEdit>
#include <QSettings>
#include <QDate>
#include <QVBoxLayout>
#include <QJsonObject>
#include <QJsonDocument>

#include <QJsonArray>
#include <QMessageBox>
#include <QNetworkReply>
#include <QScrollArea>
#include <QScrollBar>
#include <QSvgWidget>
#include <QCalendarWidget>
#include "style/stylecontainer.h"
#include <ui/view/qsvgbutton.h>
#include <ui/view/waitingspinnerwidget.h>
using namespace styles;
#include "screensfactory.h"
using namespace screens;

Shedule::Shedule() {


    mainHLayout = new QHBoxLayout;
    inputContainer = new QVBoxLayout;

    QHBoxLayout *titleContainer = new QHBoxLayout;
    QSvgButton *backButton = new QSvgButton(":/resc/resc/arrow_back.svg", QSize(24,24));
    QLabel *titleLabel = new QLabel("Мое расписание");


    calendar = new QCalendarWidget;


    calendar->setMinimumDate(QDate::currentDate());

    calendar->setMinimumHeight(250);



    calendar->setGridVisible(0);



    calendar->setNavigationBarVisible(1);

    QHBoxLayout *buttoContainer = new QHBoxLayout;
    QHBoxLayout *buttonBoxContainer = new QHBoxLayout;
    createButton_1 = new QPushButton("Отправить расписание");
    createButton_2= new QPushButton("Отправить расписание");

    QFrame *loadingContaiter = new QFrame;
    loading = new WaitingSpinnerWidget(loadingContaiter, true, false);
    loading->setColor(QT_COLOR_PRIMARY);
    loadingContaiter->setMinimumWidth(100);
    QFrame *loadingBoxContaiter = new QFrame;
    loadingBox = new WaitingSpinnerWidget(loadingContaiter, true, false);
    loadingBox->setColor(QT_COLOR_PRIMARY);
    loadingBoxContaiter->setMinimumWidth(100);

    titleEdit = new QLineEdit;
    descriptionEdit = new QPlainTextEdit;

    QScrollArea *deskScrollArea = new QScrollArea;
    deskScrollArea->setMinimumWidth(396);
    deskScrollArea->setFrameShape(QFrame::NoFrame);
    QWidget *scrolContainer = new QWidget;
    scrolContainer->setObjectName("container");
    scrolContainer->setStyleSheet(GLOBAL_BACK_WHITE);
    deskScrollArea->setStyleSheet(SCROL_BAR);
    QHBoxLayout *content = new QHBoxLayout;
    content->setAlignment(Qt::AlignHCenter);
    scrolContainer->setLayout(content);
    deskScrollArea->setWidget(scrolContainer);
    deskScrollArea->setWidgetResizable(true);
    deskScrollArea->horizontalScrollBar()->setEnabled(false);

    // селектор типа карточки
    QHBoxLayout *selectorContainer = new QHBoxLayout;

    selectorContainer->setContentsMargins(0,0,0,25);

    date1Button = new QPushButton("Понедельник");
    date2Button = new QPushButton("Вторник");
    date3Button = new QPushButton("Среда");
    date4Button = new QPushButton("Четверг");
    date5Button = new QPushButton("Пятница");
    date6Button = new QPushButton("Суббота");
    date7Button = new QPushButton("Воскресенье");

    date1Button->setMinimumHeight(60);
    date2Button->setMinimumHeight(60);
    date3Button->setMinimumHeight(60);
    date4Button->setMinimumHeight(60);
    date5Button->setMinimumHeight(60);
    date6Button->setMinimumHeight(60);
    date7Button->setMinimumHeight(60);



    date1Button->setStyleSheet(BUTTON_SOLID);
    date2Button->setStyleSheet(BUTTON_DISABLED);
    date3Button->setStyleSheet(BUTTON_DISABLED);
    date4Button->setStyleSheet(BUTTON_DISABLED);
    date5Button->setStyleSheet(BUTTON_DISABLED);
    date6Button->setStyleSheet(BUTTON_DISABLED);
    date7Button->setStyleSheet(BUTTON_DISABLED);

    selectorContainer->addWidget(date1Button);
    selectorContainer->addWidget(date2Button);
    selectorContainer->addWidget(date3Button);
    selectorContainer->addWidget(date4Button);
    selectorContainer->addWidget(date5Button);
    selectorContainer->addWidget(date6Button);
    selectorContainer->addWidget(date7Button);

    connect(date1Button, &QPushButton::clicked, this, &Shedule::day_btn_1);


    connect(date2Button, &QPushButton::clicked, this, &Shedule::day_btn_2);
    connect(date3Button, &QPushButton::clicked, this, &Shedule::day_btn_3);
    connect(date4Button, &QPushButton::clicked, this, &Shedule::day_btn_4);
    connect(date5Button, &QPushButton::clicked, this, &Shedule::day_btn_5);
    connect(date6Button, &QPushButton::clicked, this, &Shedule::day_btn_6);
    connect(date7Button, &QPushButton::clicked, this, &Shedule::day_btn_7);

    connect(calendar, &QCalendarWidget::clicked, this, &Shedule::calendar_btn);


    //стак для выбора контента
    stack = new QStackedWidget;

    QFrame *day1Widjet = new QFrame;
    QVBoxLayout *day1Layout = new QVBoxLayout;

    QFrame *day2Widget = new QFrame;
    QVBoxLayout *day2Layout = new QVBoxLayout;

    QFrame *day3Widget = new QFrame;
    QVBoxLayout *day3Layout = new QVBoxLayout;

    QFrame *day4Widget = new QFrame;
    QVBoxLayout *day4Layout = new QVBoxLayout;

    QFrame *day5Widget = new QFrame;
    QVBoxLayout *day5Layout = new QVBoxLayout;

    QFrame *day6Widget = new QFrame;
    QVBoxLayout *day6Layout = new QVBoxLayout;

    QFrame *day7Widget = new QFrame;
    QVBoxLayout *day7Layout = new QVBoxLayout;


    day1Widjet->setLayout(day1Layout);
    day1Layout->setAlignment(Qt::AlignTop);

    day2Widget->setLayout(day2Layout);
    day2Layout->setAlignment(Qt::AlignTop);

    day3Widget->setLayout(day3Layout);
    day3Layout->setAlignment(Qt::AlignTop);

    day4Widget->setLayout(day4Layout);
    day4Layout->setAlignment(Qt::AlignTop);

    day5Widget->setLayout(day5Layout);
    day5Layout->setAlignment(Qt::AlignTop);

    day6Widget->setLayout(day6Layout);
    day6Layout->setAlignment(Qt::AlignTop);

    day7Widget->setLayout(day7Layout);
    day7Layout->setAlignment(Qt::AlignTop);

    stack->addWidget(day1Widjet);
    stack->addWidget(day2Widget);
    stack->addWidget(day3Widget);
    stack->addWidget(day4Widget);
    stack->addWidget(day5Widget);
    stack->addWidget(day6Widget);
    stack->addWidget(day7Widget);

    stack->setCurrentIndex(0);

    stack->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);


    // стак для дел
    cardTitleEdit = new QLineEdit;
    connect(cardTitleEdit, &QLineEdit::textChanged, this, &Shedule::checkBoxTitle);

    QHBoxLayout *titleEditContainer = new QHBoxLayout;

    QHBoxLayout *form = new QHBoxLayout;
    left = new QTimeEdit;
    right = new QTimeEdit;

    left->setStyleSheet(Qtimestyle);
    right->setStyleSheet(Qtimestyle);


    addBoxTitleButton = new QSvgButton(":/resc/resc/done_outline.svg", QSize(24,24));
    titleWidgetList = new QVBoxLayout;
    titleWidgetList->setAlignment(Qt::AlignTop);
    connect(addBoxTitleButton, &QSvgButton::clicked, this, &Shedule::onBoxTitleAdd);
    addBoxTitleButton->hide();
    cardTitleEdit->setStyleSheet(EDIT_TEXT);
    cardTitleEdit->setPlaceholderText("Дело...");


    form->addWidget(left);
    form->addWidget(cardTitleEdit);
    form->addWidget(right);

    titleEditContainer->addLayout(form);
    titleEditContainer->addWidget(addBoxTitleButton);

    day1Layout->setContentsMargins(0,0,0,0);
    day1Layout->addLayout(titleWidgetList);
    day1Layout->addLayout(titleEditContainer);
    day1Layout->addLayout(buttonBoxContainer);

    titleLabel->setStyleSheet(TITLE_LABLE);
    connect(backButton, &QSvgButton::clicked, this, &Shedule::onBackPressed);
    titleContainer->addWidget(backButton);
    titleContainer->addWidget(titleLabel);
    titleContainer->setContentsMargins(0,24,0,16);
    titleLabel->setContentsMargins(16,0,0,0);




    buttoContainer->setAlignment(Qt::AlignRight);

    createButton_2->setStyleSheet(BUTTON_SOLID);
    createButton_2->setMaximumWidth(335);
    createButton_2->setMinimumWidth(335);
    connect(createButton_2, &QPushButton::clicked, this, &Shedule::onCreatePressed);
    buttonBoxContainer->addWidget(loadingBoxContaiter);
    buttonBoxContainer->addWidget(createButton_2);
    buttonBoxContainer->setAlignment(Qt::AlignRight);




    inputContainer->setAlignment(Qt::AlignTop);
    inputContainer->addLayout(titleContainer);
    inputContainer->addWidget(calendar);
    inputContainer->addLayout(selectorContainer);
    inputContainer->addWidget(stack);

    content->addLayout(inputContainer);

    mainHLayout->setAlignment(Qt::AlignHCenter);

    mainHLayout->addWidget(deskScrollArea);



    this->setLayout(mainHLayout);
    this->setStyleSheet(BACK_WHITE);
    this->setObjectName("fragment");

    checkData();

    networkManager = new QNetworkAccessManager();
    connect(networkManager, &QNetworkAccessManager::finished, this, &Shedule::onHttpResult);


    setButtonDate();

    loadSheduleFromDate();

}

Shedule::~Shedule() {
    delete titleEdit;
    delete descriptionEdit;
    delete createButton_1;
    delete date1Button;
    delete date2Button;
    delete date3Button;
    delete date4Button;
    delete date5Button;
    delete date6Button;
    delete date7Button;
    delete loading;
    delete loadingBox;
    //delete networkManager;
}

void Shedule::checkData() {

    if (titleList.size() != 0) {
          createButton_2->setStyleSheet(BUTTON_SOLID);
      } else {
          createButton_2->setStyleSheet(BUTTON_DISABLED);
      }

}

void Shedule::setData(BaseModel *model) {
    DeskModel *desk = dynamic_cast<DeskModel*>(model);
    this->model = desk;
}

void Shedule::onBackPressed() {
    back();
}

void Shedule::onCreatePressed() {
    if (titleEdit->text().length() > 2) {
        if (this->currentType == "checkbox" && titleList.size() == 0) return;
        createButton_1->setDisabled(true);
        loading->show();
        createButton_2->setStyleSheet(BUTTON_DISABLED);
        createButton_2->setDisabled(true);
        loadingBox->show();
        createButton_2->setStyleSheet(BUTTON_DISABLED);

    }



}

void Shedule::onHttpResult(QNetworkReply *reply) {

    reply->deleteLater();
}

void Shedule::day_btn_1() {
    calendar->setSelectedDate(date1);
    date1Button->setStyleSheet(BUTTON_SOLID);
    date2Button->setStyleSheet(BUTTON_DISABLED);
    date3Button->setStyleSheet(BUTTON_DISABLED);
    date4Button->setStyleSheet(BUTTON_DISABLED);
    date5Button->setStyleSheet(BUTTON_DISABLED);
    date6Button->setStyleSheet(BUTTON_DISABLED);
    date7Button->setStyleSheet(BUTTON_DISABLED);

    stack->setCurrentIndex(0);
    this->currentType = "checkbox";
}

void Shedule::day_btn_2() {
    calendar->setSelectedDate(date2);
    date2Button->setStyleSheet(BUTTON_SOLID);
    date1Button->setStyleSheet(BUTTON_DISABLED);
    date3Button->setStyleSheet(BUTTON_DISABLED);
    date4Button->setStyleSheet(BUTTON_DISABLED);
    date5Button->setStyleSheet(BUTTON_DISABLED);
    date6Button->setStyleSheet(BUTTON_DISABLED);
    date7Button->setStyleSheet(BUTTON_DISABLED);
    stack->setCurrentIndex(0);
    this->currentType = "checkbox";
}

void Shedule::day_btn_3() {
    calendar->setSelectedDate(date3);
    date3Button->setStyleSheet(BUTTON_SOLID);
    date1Button->setStyleSheet(BUTTON_DISABLED);
    date2Button->setStyleSheet(BUTTON_DISABLED);
    date4Button->setStyleSheet(BUTTON_DISABLED);
    date5Button->setStyleSheet(BUTTON_DISABLED);
    date6Button->setStyleSheet(BUTTON_DISABLED);
    date7Button->setStyleSheet(BUTTON_DISABLED);
    stack->setCurrentIndex(0);
    this->currentType = "checkbox";
}

void Shedule::day_btn_4() {
    calendar->setSelectedDate(date4);
    date4Button->setStyleSheet(BUTTON_SOLID);
    date1Button->setStyleSheet(BUTTON_DISABLED);
    date2Button->setStyleSheet(BUTTON_DISABLED);
    date3Button->setStyleSheet(BUTTON_DISABLED);
    date5Button->setStyleSheet(BUTTON_DISABLED);
    date6Button->setStyleSheet(BUTTON_DISABLED);
    date7Button->setStyleSheet(BUTTON_DISABLED);
    stack->setCurrentIndex(0);
    this->currentType = "checkbox";
}

void Shedule::day_btn_5() {
    calendar->setSelectedDate(date5);
    date5Button->setStyleSheet(BUTTON_SOLID);
    date1Button->setStyleSheet(BUTTON_DISABLED);
    date2Button->setStyleSheet(BUTTON_DISABLED);
    date3Button->setStyleSheet(BUTTON_DISABLED);
    date4Button->setStyleSheet(BUTTON_DISABLED);
    date6Button->setStyleSheet(BUTTON_DISABLED);
    date7Button->setStyleSheet(BUTTON_DISABLED);
    stack->setCurrentIndex(0);
    this->currentType = "checkbox";
}

void Shedule::day_btn_6() {
    calendar->setSelectedDate(date6);
    date6Button->setStyleSheet(BUTTON_SOLID);
    date1Button->setStyleSheet(BUTTON_DISABLED);
    date2Button->setStyleSheet(BUTTON_DISABLED);
    date3Button->setStyleSheet(BUTTON_DISABLED);
    date4Button->setStyleSheet(BUTTON_DISABLED);
    date5Button->setStyleSheet(BUTTON_DISABLED);
    date7Button->setStyleSheet(BUTTON_DISABLED);
    stack->setCurrentIndex(0);
    this->currentType = "checkbox";
}

void Shedule::day_btn_7() {

    calendar->setSelectedDate(date7);

    date7Button->setStyleSheet(BUTTON_SOLID);
    date1Button->setStyleSheet(BUTTON_DISABLED);
    date2Button->setStyleSheet(BUTTON_DISABLED);
    date3Button->setStyleSheet(BUTTON_DISABLED);
    date4Button->setStyleSheet(BUTTON_DISABLED);
    date5Button->setStyleSheet(BUTTON_DISABLED);
    date6Button->setStyleSheet(BUTTON_DISABLED);
    stack->setCurrentIndex(0);
    this->currentType = "checkbox";
}

void Shedule::checkBoxTitle() {
    if (cardTitleEdit->text().length() >= 3 && cardTitleEdit->text().length() <= 30) {
        addBoxTitleButton->show();
    } else {
        addBoxTitleButton->hide();
    }
}


void Shedule::onBoxTitleAdd() {

    titleList.append(cardTitleEdit->text());

    timeLabelTask = new QLabel;

    QTime time_begin = left->time();
    QTime time_end = right->time();

    QString time_begin_string = time_begin.toString("hh:mm");
    QString time_end_string = time_end.toString("hh:mm");


    deleteTaskButton = new QSvgButton(":/resc/resc/bin.svg", QSize(24,24));

    connect(deleteTaskButton, &QSvgButton::clicked, this, &Shedule::deleteButton_pressed);



    timeLabelTask->setText(QString("Начало: %1 Конец: %2.").arg(time_begin_string, time_end_string));


    titleList.append(cardTitleEdit->text());
    boxTitleTask = new QLabel(cardTitleEdit->text());
    boxTitleTask->setStyleSheet(TEXT_DARK_LABLE);

    mainImageTask = new QSvgWidget(":/resc/resc/done_outline.svg");
    mainImageTask->setMinimumSize(QSize(24,24));
    mainImageTask->setMaximumSize(QSize(24,24));

    task_container = new QHBoxLayout;

    task_container->addWidget(mainImageTask);
    task_container->addWidget(boxTitleTask);
    task_container->addWidget(timeLabelTask);
    task_container->addWidget(deleteTaskButton);

    titleWidgetList->addLayout(task_container);
    cardTitleEdit->setText("");
    checkBoxTitle();
    checkData();
}

void Shedule::deleteButton_pressed() {

    checkData();

    delete this->mainImageTask;
    delete this->deleteTaskButton;
    delete this->boxTitleTask;
    delete this->timeLabelTask;
    delete this->task_container;
    checkData();

    titleWidgetList->update();

    checkData();


}









void Shedule::calendar_btn(const QDate &date) {


      QString strdate = date.toString();

    if(!strDinamicckeck.contains(strdate) && date !=   QDate::currentDate()){

        strDinamicckeck = strDinamicckeck + strdate;
        QDynamicButton *button = new QDynamicButton(this);  // Создаем объект динамической кнопки
        inputContainer->addLayout(button);

    }


    checkData();

    stack->setCurrentIndex(0);
    this->currentType = "checkbox";

    QString strcheck = date.toString();

    QString str1;
    QString str2;
    QString str3;
    QString str4;
    QString str5;
    QString str6;
    QString str7;


    if(strcheck.contains("пн")) {
         date1Button->setStyleSheet(BUTTON_SOLID);
         date2Button->setStyleSheet(BUTTON_DISABLED);
         date3Button->setStyleSheet(BUTTON_DISABLED);
         date4Button->setStyleSheet(BUTTON_DISABLED);
         date5Button->setStyleSheet(BUTTON_DISABLED);
         date6Button->setStyleSheet(BUTTON_DISABLED);
         date7Button->setStyleSheet(BUTTON_DISABLED);

          str1 = date.toString("dddd\n dd MMMM");
          str2 = date.addDays(1).toString("dddd\n dd MMMM");
          str3 = date.addDays(2).toString("dddd\n dd MMMM");
          str4 = date.addDays(3).toString("dddd\n dd MMMM");
          str5 = date.addDays(4).toString("dddd\n dd MMMM");
          str6 = date.addDays(5).toString("dddd\n dd MMMM");
          str7 = date.addDays(6).toString("dddd\n dd MMMM");


          date1 = date;
          date2 = date.addDays(1);
          date3 = date.addDays(2);
          date4 = date.addDays(3);
          date5 = date.addDays(4);
          date6 = date.addDays(5);
          date7 = date.addDays(6);

     } else if(strcheck.contains("вт")) {

         date2Button->setStyleSheet(BUTTON_SOLID);
         date1Button->setStyleSheet(BUTTON_DISABLED);
         date3Button->setStyleSheet(BUTTON_DISABLED);
         date4Button->setStyleSheet(BUTTON_DISABLED);
         date5Button->setStyleSheet(BUTTON_DISABLED);
         date6Button->setStyleSheet(BUTTON_DISABLED);
         date7Button->setStyleSheet(BUTTON_DISABLED);

          str1 = date.addDays(-1).toString("dddd\n dd MMMM");
          str2 = date.toString("dddd\n dd MMMM");
          str3 = date.addDays(1).toString("dddd\n dd MMMM");
          str4 = date.addDays(2).toString("dddd\n dd MMMM");
          str5 = date.addDays(3).toString("dddd\n dd MMMM");
          str6 = date.addDays(4).toString("dddd\n dd MMMM");
          str7 = date.addDays(5).toString("dddd\n dd MMMM");

          date1 = date.addDays(-1);
          date2 = date;
          date3 = date.addDays(1);
          date4 = date.addDays(2);
          date5 = date.addDays(3);
          date6 = date.addDays(4);
          date7 = date.addDays(5);
     } else if(strcheck.contains("ср")) {

         date3Button->setStyleSheet(BUTTON_SOLID);
         date2Button->setStyleSheet(BUTTON_DISABLED);
         date1Button->setStyleSheet(BUTTON_DISABLED);
         date4Button->setStyleSheet(BUTTON_DISABLED);
         date5Button->setStyleSheet(BUTTON_DISABLED);
         date6Button->setStyleSheet(BUTTON_DISABLED);
         date7Button->setStyleSheet(BUTTON_DISABLED);

          str1 = date.addDays(-2).toString("dddd\n dd MMMM");
          str2 = date.addDays(-1).toString("dddd\n dd MMMM");
          str3 = date.toString("dddd\n dd MMMM");
          str4 = date.addDays(1).toString("dddd\n dd MMMM");
          str5 = date.addDays(2).toString("dddd\n dd MMMM");
          str6 = date.addDays(3).toString("dddd\n dd MMMM");
          str7 = date.addDays(4).toString("dddd\n dd MMMM");

          date1 = date.addDays(-2);
          date2 = date.addDays(-1);
          date3 = date;
          date4 = date.addDays(1);
          date5 = date.addDays(2);
          date6 = date.addDays(3);
          date7 = date.addDays(4);



     } else if(strcheck.contains("чт")) {

         date4Button->setStyleSheet(BUTTON_SOLID);
         date1Button->setStyleSheet(BUTTON_DISABLED);
         date2Button->setStyleSheet(BUTTON_DISABLED);
         date3Button->setStyleSheet(BUTTON_DISABLED);
         date5Button->setStyleSheet(BUTTON_DISABLED);
         date6Button->setStyleSheet(BUTTON_DISABLED);
         date7Button->setStyleSheet(BUTTON_DISABLED);

          str1 = date.addDays(-3).toString("dddd\n dd MMMM");
          str2 = date.addDays(-2).toString("dddd\n dd MMMM");
          str3 = date.addDays(-1).toString("dddd\n dd MMMM");
          str4 = date.toString("dddd\n dd MMMM");
          str5 = date.addDays(1).toString("dddd\n dd MMMM");
          str6 = date.addDays(2).toString("dddd\n dd MMMM");
          str7 = date.addDays(3).toString("dddd\n dd MMMM");


          date1 = date.addDays(-3);
          date2 = date.addDays(-2);
          date3 = date.addDays(-1);
          date4 = date;
          date5 = date.addDays(1);
          date6 = date.addDays(2);
          date7 = date.addDays(3);

     } else if(strcheck.contains("пт")) {

         date5Button->setStyleSheet(BUTTON_SOLID);
         date1Button->setStyleSheet(BUTTON_DISABLED);
         date3Button->setStyleSheet(BUTTON_DISABLED);
         date4Button->setStyleSheet(BUTTON_DISABLED);
         date2Button->setStyleSheet(BUTTON_DISABLED);
         date6Button->setStyleSheet(BUTTON_DISABLED);
         date7Button->setStyleSheet(BUTTON_DISABLED);

          str1 = date.addDays(-4).toString("dddd\n dd MMMM");
          str2 = date.addDays(-3).toString("dddd\n dd MMMM");
          str3 = date.addDays(-2).toString("dddd\n dd MMMM");
          str4 = date.addDays(-1).toString("dddd\n dd MMMM");
          str5 = date.toString("dddd\n dd MMMM");
          str6 = date.addDays(1).toString("dddd\n dd MMMM");
          str7 = date.addDays(2).toString("dddd\n dd MMMM");


          date1 = date.addDays(-4);
          date2 = date.addDays(-3);
          date3 = date.addDays(-2);
          date4 = date.addDays(-1);
          date5 = date;
          date6 = date.addDays(1);
          date7 = date.addDays(2);


     } else if(strcheck.contains("сб")) {

         date6Button->setStyleSheet(BUTTON_SOLID);
         date1Button->setStyleSheet(BUTTON_DISABLED);
         date3Button->setStyleSheet(BUTTON_DISABLED);
         date4Button->setStyleSheet(BUTTON_DISABLED);
         date5Button->setStyleSheet(BUTTON_DISABLED);
         date1Button->setStyleSheet(BUTTON_DISABLED);
         date7Button->setStyleSheet(BUTTON_DISABLED);

          str1 = date.addDays(-5).toString("dddd\n dd MMMM");
          str2 = date.addDays(-4).toString("dddd\n dd MMMM");
          str3 = date.addDays(-3).toString("dddd\n dd MMMM");
          str4 = date.addDays(-2).toString("dddd\n dd MMMM");
          str5 = date.addDays(-1).toString("dddd\n dd MMMM");
          str6 = date.toString("dddd\n dd MMMM");
          str7 = date.addDays(1).toString("dddd\n dd MMMM");


          date1 = date.addDays(-5);
          date2 = date.addDays(-4);
          date3 = date.addDays(-3);
          date4 = date.addDays(-2);
          date5 = date.addDays(-1);
          date6 = date;
          date7 = date.addDays(1);
     }   else if(strcheck.contains("вс")) {

         date7Button->setStyleSheet(BUTTON_SOLID);
         date1Button->setStyleSheet(BUTTON_DISABLED);
         date3Button->setStyleSheet(BUTTON_DISABLED);
         date4Button->setStyleSheet(BUTTON_DISABLED);
         date5Button->setStyleSheet(BUTTON_DISABLED);
         date6Button->setStyleSheet(BUTTON_DISABLED);
         date1Button->setStyleSheet(BUTTON_DISABLED);

          str1 = date.addDays(-6).toString("dddd\n dd MMMM");
          str2 = date.addDays(-5).toString("dddd\n dd MMMM");
          str3 = date.addDays(-4).toString("dddd\n dd MMMM");
          str4 = date.addDays(-3).toString("dddd\n dd MMMM");
          str5 = date.addDays(-2).toString("dddd\n dd MMMM");
          str6 = date.addDays(-1).toString("dddd\n dd MMMM");
          str7 = date.toString("dddd\n dd MMMM");

          date1 = date.addDays(-6);
          date2 = date.addDays(-5);
          date3 = date.addDays(-4);
          date4 = date.addDays(-2);
          date5 = date.addDays(-2);
          date6 = date.addDays(-1);
          date7 = date;
     }



    QString text1 = QString("%1").arg(str1);
    QString text2 = QString("%1").arg(str2);
    QString text3 = QString("%1").arg(str3);
    QString text4 = QString("%1").arg(str4);
    QString text5 = QString("%1").arg(str5);
    QString text6 = QString("%1").arg(str6);
    QString text7 = QString("%1").arg(str7);







    date1Button->setText(text1);
    date2Button->setText(text2);
    date3Button->setText(text3);
    date4Button->setText(text4);
    date5Button->setText(text5);
    date6Button->setText(text6);
    date7Button->setText(text7);


}




void Shedule::setButtonDate(void) {

    QDate date =   QDate::currentDate();

            checkData();

            stack->setCurrentIndex(0);
            this->currentType = "checkbox";

            QString strcheck = date.toString();

            QString str1;
            QString str2;
            QString str3;
            QString str4;
            QString str5;
            QString str6;
            QString str7;


             if(strcheck.contains("пн")) {
                 date1Button->setStyleSheet(BUTTON_SOLID);
                 date2Button->setStyleSheet(BUTTON_DISABLED);
                 date3Button->setStyleSheet(BUTTON_DISABLED);
                 date4Button->setStyleSheet(BUTTON_DISABLED);
                 date5Button->setStyleSheet(BUTTON_DISABLED);
                 date6Button->setStyleSheet(BUTTON_DISABLED);
                 date7Button->setStyleSheet(BUTTON_DISABLED);

                  str1 = date.toString("dddd\n dd MMMM");
                  str2 = date.addDays(1).toString("dddd\n dd MMMM");
                  str3 = date.addDays(2).toString("dddd\n dd MMMM");
                  str4 = date.addDays(3).toString("dddd\n dd MMMM");
                  str5 = date.addDays(4).toString("dddd\n dd MMMM");
                  str6 = date.addDays(5).toString("dddd\n dd MMMM");
                  str7 = date.addDays(6).toString("dddd\n dd MMMM");

             } else if(strcheck.contains("вт")) {

                 date2Button->setStyleSheet(BUTTON_SOLID);
                 date1Button->setStyleSheet(BUTTON_DISABLED);
                 date3Button->setStyleSheet(BUTTON_DISABLED);
                 date4Button->setStyleSheet(BUTTON_DISABLED);
                 date5Button->setStyleSheet(BUTTON_DISABLED);
                 date6Button->setStyleSheet(BUTTON_DISABLED);
                 date7Button->setStyleSheet(BUTTON_DISABLED);

                  str1 = date.addDays(-1).toString("dddd\n dd MMMM");
                  str2 = date.toString("dddd\n dd MMMM");
                  str3 = date.addDays(1).toString("dddd\n dd MMMM");
                  str4 = date.addDays(2).toString("dddd\n dd MMMM");
                  str5 = date.addDays(3).toString("dddd\n dd MMMM");
                  str6 = date.addDays(4).toString("dddd\n dd MMMM");
                  str7 = date.addDays(5).toString("dddd\n dd MMMM");
             } else if(strcheck.contains("ср")) {

                 date3Button->setStyleSheet(BUTTON_SOLID);
                 date2Button->setStyleSheet(BUTTON_DISABLED);
                 date1Button->setStyleSheet(BUTTON_DISABLED);
                 date4Button->setStyleSheet(BUTTON_DISABLED);
                 date5Button->setStyleSheet(BUTTON_DISABLED);
                 date6Button->setStyleSheet(BUTTON_DISABLED);
                 date7Button->setStyleSheet(BUTTON_DISABLED);

                  str1 = date.addDays(-2).toString("dddd\n dd MMMM");
                  str2 = date.addDays(-1).toString("dddd\n dd MMMM");
                  str3 = date.toString("dddd\n dd MMMM");
                  str4 = date.addDays(1).toString("dddd\n dd MMMM");
                  str5 = date.addDays(2).toString("dddd\n dd MMMM");
                  str6 = date.addDays(3).toString("dddd\n dd MMMM");
                  str7 = date.addDays(4).toString("dddd\n dd MMMM");
             } else if(strcheck.contains("чт")) {

                 date4Button->setStyleSheet(BUTTON_SOLID);
                 date1Button->setStyleSheet(BUTTON_DISABLED);
                 date3Button->setStyleSheet(BUTTON_DISABLED);
                 date1Button->setStyleSheet(BUTTON_DISABLED);
                 date5Button->setStyleSheet(BUTTON_DISABLED);
                 date6Button->setStyleSheet(BUTTON_DISABLED);
                 date7Button->setStyleSheet(BUTTON_DISABLED);

                  str1 = date.addDays(-3).toString("dddd\n dd MMMM");
                  str2 = date.addDays(-2).toString("dddd\n dd MMMM");
                  str3 = date.addDays(-1).toString("dddd\n dd MMMM");
                  str4 = date.toString("dddd\n dd MMMM");
                  str5 = date.addDays(1).toString("dddd\n dd MMMM");
                  str6 = date.addDays(2).toString("dddd\n dd MMMM");
                  str7 = date.addDays(3).toString("dddd\n dd MMMM");
             } else if(strcheck.contains("пт")) {

                 date5Button->setStyleSheet(BUTTON_SOLID);
                 date1Button->setStyleSheet(BUTTON_DISABLED);
                 date3Button->setStyleSheet(BUTTON_DISABLED);
                 date4Button->setStyleSheet(BUTTON_DISABLED);
                 date2Button->setStyleSheet(BUTTON_DISABLED);
                 date6Button->setStyleSheet(BUTTON_DISABLED);
                 date7Button->setStyleSheet(BUTTON_DISABLED);

                  str1 = date.addDays(-4).toString("dddd\n dd MMMM");
                  str2 = date.addDays(-3).toString("dddd\n dd MMMM");
                  str3 = date.addDays(-2).toString("dddd\n dd MMMM");
                  str4 = date.addDays(-1).toString("dddd\n dd MMMM");
                  str5 = date.toString("dddd\n dd MMMM");
                  str6 = date.addDays(1).toString("dddd\n dd MMMM");
                  str7 = date.addDays(2).toString("dddd\n dd MMMM");
             } else if(strcheck.contains("сб")) {

                 date6Button->setStyleSheet(BUTTON_SOLID);
                 date1Button->setStyleSheet(BUTTON_DISABLED);
                 date3Button->setStyleSheet(BUTTON_DISABLED);
                 date4Button->setStyleSheet(BUTTON_DISABLED);
                 date5Button->setStyleSheet(BUTTON_DISABLED);
                 date1Button->setStyleSheet(BUTTON_DISABLED);
                 date7Button->setStyleSheet(BUTTON_DISABLED);

                  str1 = date.addDays(-5).toString("dddd\n dd MMMM");
                  str2 = date.addDays(-4).toString("dddd\n dd MMMM");
                  str3 = date.addDays(-3).toString("dddd\n dd MMMM");
                  str4 = date.addDays(-2).toString("dddd\n dd MMMM");
                  str5 = date.addDays(-1).toString("dddd\n dd MMMM");
                  str6 = date.toString("dddd\n dd MMMM");
                  str7 = date.addDays(1).toString("dddd\n dd MMMM");
             }   else if(strcheck.contains("вс")) {

                 date7Button->setStyleSheet(BUTTON_SOLID);
                 date1Button->setStyleSheet(BUTTON_DISABLED);
                 date3Button->setStyleSheet(BUTTON_DISABLED);
                 date4Button->setStyleSheet(BUTTON_DISABLED);
                 date5Button->setStyleSheet(BUTTON_DISABLED);
                 date6Button->setStyleSheet(BUTTON_DISABLED);
                 date1Button->setStyleSheet(BUTTON_DISABLED);

                  str1 = date.addDays(-6).toString("dddd\n dd MMMM");
                  str2 = date.addDays(-5).toString("dddd\n dd MMMM");
                  str3 = date.addDays(-4).toString("dddd\n dd MMMM");
                  str4 = date.addDays(-3).toString("dddd\n dd MMMM");
                  str5 = date.addDays(-2).toString("dddd\n dd MMMM");
                  str6 = date.addDays(-1).toString("dddd\n dd MMMM");
                  str7 = date.toString("dddd\n dd MMMM");
             }



            QString text1 = QString("%1").arg(str1);
            QString text2 = QString("%1").arg(str2);
            QString text3 = QString("%1").arg(str3);
            QString text4 = QString("%1").arg(str4);
            QString text5 = QString("%1").arg(str5);
            QString text6 = QString("%1").arg(str6);
            QString text7 = QString("%1").arg(str7);







            date1Button->setText(text1);
            date2Button->setText(text2);
            date3Button->setText(text3);
            date4Button->setText(text4);
            date5Button->setText(text5);
            date6Button->setText(text6);
            date7Button->setText(text7);

}


void Shedule::on_addButton_clicked() {


}


void Shedule::loadSheduleFromDate() {
    QDate date =   QDate::currentDate();
    QJsonObject loadSheduleJson;
    QJsonObject currentDate;
    currentDate.insert("date", date.toString("dd-MM-yy"));

    loadSheduleJson.insert("getSheduleFromDate", currentDate);

        qDebug() << "create request" << endl;



        QNetworkRequest request(QUrl(SERVER_URL + ""));
        request.setHeader(QNetworkRequest::ContentTypeHeader,
                          QStringLiteral("application/json;charset=utf-8"));
        qDebug() << "request data"<< QJsonDocument(loadSheduleJson).toJson(QJsonDocument::Compact) << endl;
        networkManager->post(
            request,
            QJsonDocument(loadSheduleJson).toJson(QJsonDocument::Compact)
        );
        qDebug() << "request send" << endl;
    }






