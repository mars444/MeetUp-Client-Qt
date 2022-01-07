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
#include "nlohmann/json.hpp"

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
    inputContainer->setAlignment(Qt::AlignTop);
    mainHLayout->setAlignment(Qt::AlignTop);

    QHBoxLayout *titleContainer = new QHBoxLayout;
    titleContainer->setAlignment(Qt::AlignTop);
    QSvgButton *backButton = new QSvgButton(":/resc/resc/arrow_back.svg", QSize(24,24));
    QLabel *titleLabel = new QLabel("Мое расписание");


    calendar = new QCalendarWidget;
 calendar->setMinimumDate(QDate::currentDate().addDays(-4));

    calendar->setMinimumHeight(350);



    calendar->setGridVisible(0);

    calendar->setMaximumHeight(350);



    calendar->setNavigationBarVisible(1);

    QHBoxLayout *buttoContainer = new QHBoxLayout;
    QHBoxLayout *buttonBoxContainer = new QHBoxLayout;
    createButton_1 = new QPushButton("Отправить расписание");
    createButton_2= new QPushButton("Сохранить расписание");
    createButton_2->setDisabled(true);
    createButton_2->setStyleSheet(BUTTON_DISABLED);

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
    content->setAlignment(Qt::AlignTop);
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
    connect(createButton_2, &QPushButton::clicked, this, &Shedule::sendShedulePressed);
    buttonBoxContainer->addWidget(loadingBoxContaiter);
    //buttonBoxContainer->addWidget(createButton_2);
    buttonBoxContainer->setAlignment(Qt::AlignRight);




    inputContainer->setAlignment(Qt::AlignTop);
    inputContainer->addLayout(titleContainer);
    inputContainer->addWidget(calendar);
    inputContainer->addLayout(selectorContainer);
    inputContainer->addLayout(buttonBoxContainer);

    cardTitleEdit = new QLineEdit;


    titleEditContainer = new QHBoxLayout;

    QHBoxLayout *form = new QHBoxLayout;
    left = new QTimeEdit;
    right = new QTimeEdit;

    left->setStyleSheet(Qtimestyle);
    right->setStyleSheet(Qtimestyle);




    addBoxTitleButton = new QSvgButton(":/resc/resc/done_outline.svg", QSize(24,24));

    connect(addBoxTitleButton, &QSvgButton::clicked, this, &Shedule::onBoxTitleAdd);


    addBoxTitleButton->hide();
    cardTitleEdit->setStyleSheet(EDIT_TEXT);
    cardTitleEdit->setPlaceholderText("Дело...");

    connect(cardTitleEdit, &QLineEdit::textChanged, this, &Shedule::checkBoxTitle);


    form->addWidget(left);
    form->addWidget(cardTitleEdit);

    form->addWidget(right);


    titleEditContainer->addLayout(form);
    titleEditContainer->addWidget(addBoxTitleButton);

//        //стак для выбора контента


//        QVBoxLayout *day1Layout = new QVBoxLayout;

//        day1Layout->setAlignment(Qt::AlignTop);



    inputContainer->insertLayout(3,titleEditContainer);


    content->setAlignment(Qt::AlignTop);
    content->addLayout(inputContainer);

    mainHLayout->setAlignment(Qt::AlignTop);

    mainHLayout->addWidget(deskScrollArea);



    this->setLayout(mainHLayout);
    this->setStyleSheet(BACK_WHITE);
    this->setObjectName("fragment");


    networkManager = new QNetworkAccessManager();
    connect(networkManager, &QNetworkAccessManager::finished, this, &Shedule::onHttpResult);

    networkManagerSendShedule = new QNetworkAccessManager();
    connect(networkManagerSendShedule, &QNetworkAccessManager::finished, this, &Shedule::onHttpResultSendShedule);

    networkManageraddEvent = new QNetworkAccessManager();
    connect(networkManageraddEvent, &QNetworkAccessManager::finished, this, &Shedule::onHttpResultAddEvent);

    networkManagerDeleteEvent = new QNetworkAccessManager();
    connect(networkManagerDeleteEvent, &QNetworkAccessManager::finished, this, &Shedule::onHttpResultDeleteEvent);

    setButtonDate();


    loadSheduleFromDate();
    checkData();

   // qDebug() << "TTTILE EDIT COUNNTT  "<<  this->titleEditContainer->count() << endl;

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
    delete networkManager;
    delete networkManageraddEvent;
    delete networkManagerDeleteEvent;
    delete networkManagerSendShedule;
}

void Shedule::checkData() {

    if (titleList.size() != 0) {
          createButton_2->setStyleSheet(BUTTON_SOLID);
          createButton_2->setDisabled(false);

      } else {
          createButton_2->setStyleSheet(BUTTON_DISABLED);
           createButton_2->setDisabled(true);
      }

}

void Shedule::setData(BaseModel *model) {

}

void Shedule::onBackPressed() {
    back();
}

void Shedule::onCreatePressed() {
    if (titleEdit->text().length() > 2) {
        createButton_1->setDisabled(true);
        loading->show();
        createButton_2->setStyleSheet(BUTTON_DISABLED);
        createButton_2->setDisabled(true);
        loadingBox->show();
        createButton_2->setStyleSheet(BUTTON_DISABLED);

    }



}



void Shedule::onHttpResultDeleteEvent(QNetworkReply *reply) {

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

}

void Shedule::checkBoxTitle() {
    if (cardTitleEdit->text().length() >= 3 && cardTitleEdit->text().length() <= 30) {
        addBoxTitleButton->show();
    } else {
        addBoxTitleButton->hide();
    }
}


void Shedule::onBoxTitleAdd() {  // добавление ивента


    timeLabelTask = new QLabel;


    time_begin = left->time();
    time_end = right->time();

    time_begin_string = time_begin.toString("hh:mm");
    time_end_string = time_end.toString("hh:mm");


    deleteTaskButton = new QSvgButton(":/resc/resc/bin.svg", QSize(24,24));

    connect(deleteTaskButton, &QSvgButton::clicked, this, &Shedule::deleteButton_pressed);




    timeLabelTask->setText(QString("begin %1 \n end: %2.").arg(time_begin_string, time_end_string));

    titleList.append(cardTitleEdit->text());
    titleList.append(time_begin_string);
    titleList.append(time_end_string);


    boxTitleTask = new QLabel(cardTitleEdit->text());
    boxTitleTask->setStyleSheet(TASK_PADDING);

    mainImageTask = new QSvgWidget(":/resc/resc/done_outline.svg");
    mainImageTask->setMinimumSize(QSize(24,24));
    mainImageTask->setMaximumSize(QSize(24,24));


    task_container = new QHBoxLayout;

    //task_container->setAlignment(Qt::AlignCenter);

    task_container->addWidget(mainImageTask);
    task_container->addWidget(boxTitleTask);
    task_container->addWidget(timeLabelTask);

    task_container->addWidget(deleteTaskButton);
    task_container->setContentsMargins(125,0,0,0);

    inputContainer->insertLayout(3,task_container);

    deleteTaskButtonToLayoutMap.insert(deleteTaskButton,task_container);

    checkData();

    QJsonObject addEventJson;
    QJsonObject bodyJson;
    bodyJson.insert("user_id", "1");
    bodyJson.insert("event_name", cardTitleEdit->text());
    bodyJson.insert("event_date", dateToHTTP);
    bodyJson.insert("time_begin", time_begin_string);
    bodyJson.insert("time_end", time_end_string);
    bodyJson.insert("description", "q");


    QJsonArray eventArray;

    eventArray.push_back(bodyJson);



    addEventJson.insert("add_event", eventArray);

        qDebug() << "create request" << endl;



        QNetworkRequest request(QUrl(SERVER_URL + ""));
        request.setHeader(QNetworkRequest::ContentTypeHeader,
                          QStringLiteral("application/json;charset=utf-8"));

        request.setRawHeader("JSON_DATA", QJsonDocument(addEventJson).toJson(QJsonDocument::Compact));
        qDebug() << "request data"<< QJsonDocument(addEventJson).toJson(QJsonDocument::Compact) << endl;
        networkManageraddEvent->post(
            request,
            QJsonDocument(addEventJson).toJson(QJsonDocument::Compact)
        );
        qDebug() << "request send" << endl;



        cardTitleEdit->setText("");


}



void Shedule::onHttpResultAddEvent(QNetworkReply *reply) {

    qDebug() << "http finished" << endl;
    loading->stop();
    checkData();
    if(!reply->error()) {
        QByteArray resp = reply->readAll();
        qDebug() <<"ETO OTVET SERVERA ADD EVENT :  " + resp  << endl;
        QJsonDocument doc = QJsonDocument::fromJson(resp);
        QJsonObject obj;

        std::string str = resp.toStdString();

        std::cout << "str  " + str << std::endl;

        nlohmann::json j = nlohmann::json::parse(str);

        std::string add_event_result = j["add_event"].get<std::string>();

        if(add_event_result == "OK") {


            std::cout << "delete friebd: " << add_event_result << std::endl;

}

        } else {

        qDebug() << reply->errorString();

        qDebug() <<  reply->readAll() << endl;

        qDebug () << reply -> error ();

        QMessageBox::warning(this, "Ошибка",
            "При подключениии произошла ошибка.\n");
        // newRootScreen(MAIN_TAG);

}
    //newRootScreen(MAIN_TAG);
    reply->deleteLater();


     networkManageraddEvent->clearAccessCache();


}

void Shedule::deleteButton_pressed() {




    QPushButton *button = qobject_cast<QPushButton*>(sender());

    QHBoxLayout *layout = deleteTaskButtonToLayoutMap.take(button);

//    QWidget *event_name = layout->takeAt(1)->widget();

//    QLayout *times = layout->takeAt(2)->layout();

//    QWidget *time_begin = times->takeAt(0)->widget();

//    QWidget *time_end= times->takeAt(1)->widget();

//    QLabel* event_nameLabel = dynamic_cast<QLabel*>(event_name);

//    QLabel* time_begin_label = dynamic_cast<QLabel*>(time_begin);

//    QLabel* time_end_label = dynamic_cast<QLabel*>(time_end);


//    QString event_nameString = event_nameLabel->text();

//    QString time_beginString = time_begin_label->text();

//    QString time_endString = time_end_label->text();

//    qDebug() <<  event_nameString  << endl;

//    qDebug() <<  time_beginString  << endl;

//    qDebug() <<  time_endString  << endl;



//    QJsonObject deleteEventJson;
//    QJsonObject bodyJson;
//    bodyJson.insert("user_id", "1");
//    bodyJson.insert("event_name", cardTitleEdit->text());
//    bodyJson.insert("event_date", dateToHTTP);
//    //bodyJson.insert("time_begin", tmpItem->time_begin_string);
//    bodyJson.insert("time_end", time_end_string);
//    bodyJson.insert("description", "q");


//    QJsonArray eventArray;

//    eventArray.push_back(bodyJson);

//    deleteEventJson.insert("delete_event", eventArray);

//        qDebug() << "create request" << endl;



//        QNetworkRequest request(QUrl(SERVER_URL + ""));
//        request.setHeader(QNetworkRequest::ContentTypeHeader,
//                          QStringLiteral("application/json;charset=utf-8"));

//        request.setRawHeader("JSON_DATA", QJsonDocument(deleteEventJson).toJson(QJsonDocument::Compact));
//        qDebug() << "request data"<< QJsonDocument(deleteEventJson).toJson(QJsonDocument::Compact) << endl;
//        networkManageraddEvent->post(
//            request,
//            QJsonDocument(deleteEventJson).toJson(QJsonDocument::Compact)
//        );
//        qDebug() << "request send" << endl;


    while(QLayoutItem *tmpItem = layout->itemAt(0)) {
        layout->removeItem(tmpItem);
        layout->removeWidget(tmpItem->widget());
        delete tmpItem->widget();
        delete tmpItem;
    }
    layout->update();



    checkData();



   // titleWidgetList->update();



}









void Shedule::calendar_btn(const QDate &date) {



//        while(QLayoutItem *tmpItem = task_container->itemAt(0)) {
//            this->task_container->removeItem(tmpItem);
//            this->task_container->removeWidget(tmpItem->widget());
//            delete tmpItem->widget();
//            delete tmpItem;
//        }
//        this->task_container->update();
//        delete task_container;




      QString strdate = date.toString();
      dateTotask = date.toString("dd-MM-yy");

      dateToHTTP = date.toString("MM-dd-yyyy");

    if(!strDinamicckeck.contains(strdate) && date !=   QDate::currentDate()){




//        if(titleEditContainer->count() != 0){

//            while (titleEditContainer->count() != 0) {
////                QLayoutItem *item = titleEditContainer->takeAt(0);
////                delete item->widget();
//                //delete item;
//                delete titleEditContainer;
//            }
//        }

//          if(titleEditContainer->count() != 0){

//        QHBoxLayout *layout = titleEditContainer;

//        while(QLayoutItem *tmpItem = layout->itemAt(0)) {
//            layout->removeItem(tmpItem);
//            layout->removeWidget(tmpItem->widget());
//            delete tmpItem->widget();
//            delete tmpItem;
//        }
//        layout->update();

//        }



        // стак для дел

//        day1Layout->setContentsMargins(0,0,0,0);
//        day1Layout->addLayout(titleWidgetList);
//    day1Layout->addLayout(titleEditContainer);


    }



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


void Shedule::sendShedulePressed() {

//    QJsonObject loadSheduleJson;

//    QJsonObject Shedule;

//          QJsonObject SheduleTask;


//    for(int i = 0; i < titleList.size(); i=i+3 ){

//        QString s = QString::number(i);



//        SheduleTask.insert("taskTitle" + s , titleList[i]);
//        SheduleTask.insert("taskBegin" + s, titleList[i+1]);
//        SheduleTask.insert("taskEnd" + s, titleList[i+2]);


//         Shedule.insert("qq",SheduleTask);
//    }



//    Shedule.insert("date",dateTotask);







//    qDebug() << titleList.size() << endl;


//    loadSheduleJson.insert("sendSheduleFromDate", Shedule);

//        qDebug() << "create request" << endl;



//        QNetworkRequest request(QUrl(SERVER_URL + ""));
//        request.setHeader(QNetworkRequest::ContentTypeHeader,
//                          QStringLiteral("application/json;charset=utf-8"));
//        qDebug() << "request data"<< QJsonDocument(loadSheduleJson).toJson(QJsonDocument::Compact) << endl;
//        networkManagerSendShedule->post(
//            request,
//            QJsonDocument(loadSheduleJson).toJson(QJsonDocument::Compact)
//        );
//        qDebug() << "request send" << endl;
    }


void Shedule::onHttpResultSendShedule(QNetworkReply *reply){



}






void Shedule::loadSheduleFromDate() {



    QDate date = QDate::currentDate();
    QJsonObject loadSheduleJson;
    QJsonObject currentDate;
    currentDate.insert("event_date", date.toString("yyyy-MM-dd"));

    currentDate.insert("user_id", "1");

    loadSheduleJson.insert("get_events", currentDate);

        qDebug() << "create request" << endl;



        QNetworkRequest request(QUrl(SERVER_URL + ""));

        request.setRawHeader("JSON_DATA", QJsonDocument(loadSheduleJson).toJson(QJsonDocument::Compact));
        request.setHeader(QNetworkRequest::ContentTypeHeader,
                          QStringLiteral("application/json;charset=utf-8"));
        qDebug() << "request data"<< QJsonDocument(loadSheduleJson).toJson(QJsonDocument::Compact) << endl;
        networkManager->post(
            request,
            QJsonDocument(loadSheduleJson).toJson(QJsonDocument::Compact)
        );
        qDebug() << "request send" << endl;
    }


void Shedule::onHttpResult(QNetworkReply *reply) {


    qDebug() << "http finished" << endl;

    if(1) {  //!reply->error()
        QByteArray resp = reply->readAll();
        qDebug() <<"ETO OTVET SERVERA LOAD EVENTS :  " + resp  << endl;
        QJsonDocument doc = QJsonDocument::fromJson(resp);
        QJsonObject obj;

        std::string str = resp.toStdString();

        std::cout << "str  " + str << std::endl;
//        "{\"userID\":\"213564544\",\"Friends\":[\"Misha1991\", \"Igor\",  \"Alex\",  \"qwe\", \"piotr\"]}";

        std::string parser_str = "{\"get_events\":[{\"description\":\"breakfast\","
                                 " \"time_begin\":\"10:00\",""\"time_end\":\"10:45\"}, {\"description\":\"lansh\", \"time_begin\":"
                                          "\"19:00\", \"time_end\":\"20:00\"}]}";

        nlohmann::json j = nlohmann::json::parse(parser_str);

            nlohmann::json::iterator it = j.begin();

            nlohmann::json value = j[it.key()];

            for (auto& element : value)
            {

                std::string time_end_str;
                 std::string time_begin_str;
                  std::string description;


                if(element.contains("description"))
                {
                    description = element["description"].get<std::string>();

                    std::cout << description << std::endl;
                }


                if(element.contains("time_begin"))
                {
                     time_begin_str = element["time_begin"].get<std::string>();
                     std::cout << time_begin_str << std::endl;
                }

                if(element.contains("time_end"))
                {
                    time_end_str = element["time_end"].get<std::string>();

                     std::cout << time_end_str << std::endl;
                }


                timeLabelTask = new QLabel;



                time_begin_string = QString::fromUtf8(time_begin_str.c_str());
                time_end_string = QString::fromUtf8(time_end_str.c_str());


                deleteTaskButton = new QSvgButton(":/resc/resc/bin.svg", QSize(24,24));

                connect(deleteTaskButton, &QSvgButton::clicked, this, &Shedule::deleteButton_pressed);




                timeLabelTask->setText(QString("begin %1 \n end: %2.").arg(time_begin_string, time_end_string));


                QString titleEvent = QString::fromUtf8(description.c_str());
                titleList.append(titleEvent);
                titleList.append(time_begin_string);
                titleList.append(time_end_string);


                boxTitleTask = new QLabel(titleEvent);
                boxTitleTask->setStyleSheet(TASK_PADDING);

                mainImageTask = new QSvgWidget(":/resc/resc/done_outline.svg");
                mainImageTask->setMinimumSize(QSize(24,24));
                mainImageTask->setMaximumSize(QSize(24,24));


                task_container = new QHBoxLayout;

                //task_container->setAlignment(Qt::AlignCenter);

                task_container->addWidget(mainImageTask);
                task_container->addWidget(boxTitleTask);
                task_container->addWidget(timeLabelTask);

                task_container->addWidget(deleteTaskButton);
                task_container->setContentsMargins(125,0,0,0);

                inputContainer->insertLayout(3,task_container);

                deleteTaskButtonToLayoutMap.insert(deleteTaskButton,task_container);

             }

        } else {

        qDebug() << reply->errorString();

        qDebug() << "Server answer: " +  reply->readAll() << endl;

        qDebug () << reply -> error ();


}


    reply->deleteLater();

    networkManager->clearAccessCache();

       }











