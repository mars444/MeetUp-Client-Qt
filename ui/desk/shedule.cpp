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

#include "mytimeedit.h"
#include <string>
#include <QCheckBox>





#include "ui/auth/user_data.h"

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

    std::string IDstd = GetId();

    ID_QSTRING = QString::fromUtf8(IDstd.c_str());






    mainHLayout = new QHBoxLayout;
    inputContainer = new QVBoxLayout;
    inputContainer->setAlignment(Qt::AlignTop);
    mainHLayout->setAlignment(Qt::AlignTop);

    QHBoxLayout *titleContainer = new QHBoxLayout;
    titleContainer->setAlignment(Qt::AlignTop);
    QSvgButton *backButton = new QSvgButton(":/resc/resc/arrow_back.svg", QSize(24,24));
    QLabel *titleLabel = new QLabel(tr("My Sheduleqqqqqqqqqqqq"));


    calendar = new QCalendarWidget;
    //calendar->setMinimumDate(QDate::currentDate());

    calendar->setStyleSheet(CALENDAR);


    calendar->hide();

    calendar->setMaximumHeight(250);
    calendar->setMinimumHeight(250);


    calendar->setGridVisible(0);





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

    QSvgButton *leftButton = new QSvgButton(":/resc/resc/chevron-left.svg", QSize(45,50));
    QSvgButton *rightButton = new QSvgButton(":/resc/resc/chevron-right.svg", QSize(45,50));

    leftButton->setStyleSheet("border-radius:25px;");
    rightButton->setStyleSheet("border-radius:25px;");

    connect(leftButton, &QPushButton::clicked, this, &Shedule::leftButtonClicked);
    connect(rightButton, &QPushButton::clicked, this, &Shedule::rightButtonClicked);

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

    selectorContainer->addWidget(leftButton);
    selectorContainer->addWidget(date1Button);
    selectorContainer->addWidget(date2Button);
    selectorContainer->addWidget(date3Button);
    selectorContainer->addWidget(date4Button);
    selectorContainer->addWidget(date5Button);
    selectorContainer->addWidget(date6Button);
    selectorContainer->addWidget(date7Button);
    selectorContainer->addWidget(rightButton);

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


    calendarOpen = new QSvgButton(":/resc/resc/calendar.svg", QSize(30,30));
    calendarClose = new QSvgButton(":/resc/resc/cross.svg", QSize(30,30));

    calendarClose->hide();

    calendarOpen->setStyleSheet("border-radius:15px;");
    calendarClose->setStyleSheet("border-radius:15px;");

    connect(calendarOpen, &QPushButton::clicked, this, &Shedule::calendarOpenClicked);
    connect(calendarClose, &QPushButton::clicked, this, &Shedule::calendarCloseClicked);


    titleContainer->addWidget(backButton);
    titleContainer->addWidget(titleLabel);
    titleContainer->addWidget(calendarClose);
    titleContainer->addWidget(calendarOpen);
    titleContainer->setContentsMargins(0,24,0,16);
    titleLabel->setContentsMargins(16,0,16,0);



    titleContainer->setAlignment(Qt::AlignCenter);




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

    cardDescriptionEdit = new QLineEdit;


    titleEditContainer = new QHBoxLayout;

    form = new QHBoxLayout;

    left = new TimeEdit;
    right = new TimeEdit;

    QTime defaultTime(0,15);

    right->setTime(defaultTime);

    connect(left, &QTimeEdit::timeChanged, this,&Shedule::setTimeRightTimeEdit);

    left->setStyleSheet(Qtimestyle);
    right->setStyleSheet(Qtimestyle);

    left->setMaximumWidth(100);
    right->setMaximumWidth(100);



    addBoxTitleButton = new QSvgButton(":/resc/resc/arrow_up.svg", QSize(50,50));

    addBoxTitleButton->setStyleSheet("border-radius:25px;");

    connect(addBoxTitleButton, &QSvgButton::clicked, this, &Shedule::onBoxTitleAdd);

    connect(addBoxTitleButton, &QSvgButton::clicked, this, &Shedule::setTimeLeftTimeEdit);



    addBoxTitleButton->hide();
    cardTitleEdit->setStyleSheet(EDIT_TEXT_EVENT_TITLE);
    cardTitleEdit->setMaximumWidth(200);
    cardTitleEdit->setPlaceholderText(tr("Task title..."));
    cardTitleEdit->setAlignment(Qt::AlignCenter);

    cardDescriptionEdit->setStyleSheet(EDIT_TEXT_SMALL);
    cardDescriptionEdit->setPlaceholderText(tr("Description..."));
    cardDescriptionEdit->setMaximumWidth(500);
    cardDescriptionEdit->setMinimumHeight(100);
    cardDescriptionEdit->setMaximumHeight(100);

    connect(cardTitleEdit, &QLineEdit::textChanged, this, &Shedule::checkBoxTitle);

    connect(cardDescriptionEdit, &QLineEdit::textChanged, this, &Shedule::checkBoxTitle);



    cardDescriptionEdit->setAlignment(Qt::AlignCenter);

    left->setAlignment(Qt::AlignCenter);
    right->setAlignment(Qt::AlignCenter);


    form->addWidget(cardTitleEdit);


    form->addWidget(cardDescriptionEdit);

    QHBoxLayout *timeInner = new QHBoxLayout;

    timeInner->addWidget(left);

    timeInner->addWidget(right);

    form->addLayout(timeInner);




    //form->setAlignment(Qt::AlignLeft);



    formFrame = new QFrame;

    formFrame->setStyleSheet(EVENT_STYLE);

    formFrame->setLayout(form);

    formFrame->setContentsMargins(57,0,57,0);




    titleEditContainer->addWidget(formFrame);



    titleEditContainer->setAlignment(Qt::AlignTop);


    titleEditContainer->addWidget(addBoxTitleButton);


//        //стак для выбора контента


//        QVBoxLayout *day1Layout = new QVBoxLayout;

//        day1Layout->setAlignment(Qt::AlignTop);


//    QLabel *bgEvents = new QLabel("");
//    QPixmap profileImage(":/resc/resc/bg-events.png");
//    bgEvents->setPixmap(profileImage);


//    inputContainer->addWidget(bgEvents);

    inputContainer->addLayout(titleEditContainer);

    inputContainer->setAlignment(Qt::AlignTop);


    task_container_inner = new QVBoxLayout;
    task_container_inner->setAlignment(Qt::AlignTop);
    task_container_inner->setContentsMargins(0,20,0,0);

    inputContainer->addLayout(task_container_inner);



    content->setAlignment(Qt::AlignTop);
    content->addLayout(inputContainer);

    mainHLayout->setAlignment(Qt::AlignTop);

    mainHLayout->addWidget(deskScrollArea);



    this->setLayout(mainHLayout);
    this->setStyleSheet(BACK_WHITE);
    this->setObjectName("fragment");


    networkManagerGetEvents = new QNetworkAccessManager();
    connect(networkManagerGetEvents, &QNetworkAccessManager::finished, this, &Shedule::onHttpResultGetEvents);

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
    delete networkManagerGetEvents;
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

void Shedule::leftButtonClicked() {

    calendar->setSelectedDate (calendar->selectedDate().addDays(-1));
    setButtonDate();
    loadSheduleFromDate();
}

void Shedule::rightButtonClicked() {

    calendar->setSelectedDate (calendar->selectedDate().addDays(+1));
    setButtonDate();
    loadSheduleFromDate();
}

void Shedule::calendarOpenClicked() {


    calendarOpen->hide();
    calendarClose->show();
    calendar->show();


}

void Shedule::calendarCloseClicked() {

    calendarOpen->show();
    calendarClose->hide();
    calendar->hide();


}

void Shedule::doneButton_pressed() {


    QPushButton *button = qobject_cast<QPushButton*>(sender());

    button->hide();

    QPushButton *button1 = doneButtonToLayoutMap.value(button);
    button1->show();

}

void Shedule::doneButtonYes_pressed() {

    QPushButton *button = qobject_cast<QPushButton*>(sender());
    button->hide();

    QPushButton *button1 = doneButtonYesToLayoutMap.value(button);
    button1->show();

}



void Shedule::setData(BaseModel *model) {

}


void Shedule::setTimeRightTimeEdit(const QTime &time) {

    QTime finalTime(23,45);

    if(time == finalTime) {
        right->setTime(time.addSecs(899));

    } else {
        right->setTime(time.addSecs(900));
    }

}


void Shedule::setTimeLeftTimeEdit() {


        left->setTime(right->time());
}

void Shedule::onBackPressed() {
    back();
}

void Shedule::onCreatePressed() {
    if (titleEdit->text().length() > 2 ) {
        createButton_1->setDisabled(true);
        loading->show();
        createButton_2->setStyleSheet(BUTTON_DISABLED);
        createButton_2->setDisabled(true);
        loadingBox->show();
        createButton_2->setStyleSheet(BUTTON_DISABLED);

    }

}



void Shedule::onHttpResultDeleteEvent(QNetworkReply *reply) {


    qDebug() << "http finished" << endl;

    if(!reply->error()) {
        QByteArray resp = reply->readAll();
        qDebug() <<"ETO OTVET SERVERA DELETE EVENT :  " + resp  << endl;
        QJsonDocument doc = QJsonDocument::fromJson(resp);
        QJsonObject obj;

        std::string str = resp.toStdString();

        std::cout << "str  " + str << std::endl;

        nlohmann::json j = nlohmann::json::parse(str);

        std::string delete_event_result = j["delete_event"].get<std::string>();

        if(delete_event_result == "OK") {


            std::cout << "delete event okkk: " << delete_event_result << std::endl;

}

        } else {

        qDebug() << reply->errorString();

        qDebug() <<  reply->readAll() << endl;

        qDebug () << reply -> error ();

        QMessageBox::warning(this, tr("Error"),
            "Connection ERROR!\n");

}

    reply->deleteLater();


     networkManagerDeleteEvent->clearAccessCache();

}



void Shedule::day_btn_1() {
    calendar->setSelectedDate(date1);
    loadSheduleFromDate();
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
    loadSheduleFromDate();
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
    loadSheduleFromDate();
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
    loadSheduleFromDate();
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
    loadSheduleFromDate();
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
    loadSheduleFromDate();
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
    loadSheduleFromDate();

    date7Button->setStyleSheet(BUTTON_SOLID);
    date1Button->setStyleSheet(BUTTON_DISABLED);
    date2Button->setStyleSheet(BUTTON_DISABLED);
    date3Button->setStyleSheet(BUTTON_DISABLED);
    date4Button->setStyleSheet(BUTTON_DISABLED);
    date5Button->setStyleSheet(BUTTON_DISABLED);
    date6Button->setStyleSheet(BUTTON_DISABLED);

}

void Shedule::checkBoxTitle() {
    if (cardTitleEdit->text().length() >= 3 && cardTitleEdit->text().length() <= 30 && cardDescriptionEdit->text().length() >10) {
        addBoxTitleButton->show();
        formFrame->setContentsMargins(57,0,0,0);
    } else {
        addBoxTitleButton->hide();
        formFrame->setContentsMargins(57,0,57,0);
    }
}

void Shedule::clearTasks() {


   QVBoxLayout *layout_inner = task_container_inner;


   // layout_inner - слой со слоями


//   while(QLayoutItem *layout = layout_inner->takeAt(0)){


//       // layout - слой с виджетами уже

//        while(QLayoutItem *tmpItem = layout->takeAt(0)) {
//            layout->removeItem(tmpItem);
//            layout->removeWidget(tmpItem->widget());
//            delete tmpItem->widget();
//            delete tmpItem;
//        }



//   }





}


void Shedule::onBoxTitleAdd() {  // добавление ивента




    deleteTaskButton = new QSvgButton(":/resc/resc/cross.svg", QSize(25,25));
    deleteTaskButton->setStyleSheet("border-radius:5px;");
    connect(deleteTaskButton, &QSvgButton::clicked, this, &Shedule::deleteButton_pressed);


    updateTaskButton = new QSvgButton(":/resc/resc/arrow_up.svg", QSize(40,40));
    updateTaskButton->setStyleSheet("border-radius:20px;");
    connect(updateTaskButton, &QSvgButton::clicked, this, &Shedule::updateTaskButton_pressed);

    doneButtonYes = new QSvgButton(":/resc/resc/checkbox-checked.svg", QSize(30,30));
    doneButtonYes->hide();
    doneButtonYes->setStyleSheet("border-radius:5px;");
    connect(doneButtonYes, &QSvgButton::clicked, this, &Shedule::doneButtonYes_pressed);

    doneButton = new QSvgButton(":/resc/resc/checkbox-unchecked.svg", QSize(30,30));
    doneButton->setStyleSheet("border-radius:5px;");
    connect(doneButton, &QSvgButton::clicked, this, &Shedule::doneButton_pressed);



    QLabel *idLabel  = new QLabel("id event");

    idLabel->hide();

    QLineEdit *cardTitleEditAdd = new QLineEdit;

     QLineEdit *cardDescriptionEditAdd = new QLineEdit;

    //QHBoxLayout *titleEditContainerLoad = new QHBoxLayout;

    QHBoxLayout *form = new QHBoxLayout;

    TimeEdit *leftAdd = new TimeEdit;
    TimeEdit *rightAdd = new TimeEdit;


    leftAdd->setTime(left->time());
    rightAdd->setTime(right->time());

    leftAdd->setStyleSheet(Qtimestyle);
    rightAdd->setStyleSheet(Qtimestyle);

    leftAdd->setMaximumWidth(100);
    rightAdd->setMaximumWidth(100);

    cardTitleEditAdd->setStyleSheet(EDIT_TEXT_EVENT_TITLE);
    cardTitleEditAdd->setMaximumWidth(200);
    cardTitleEditAdd->setText(cardTitleEdit->text());
    cardTitleEditAdd->setAlignment(Qt::AlignCenter);

    cardDescriptionEditAdd->setStyleSheet(EDIT_TEXT_SMALL);
    cardDescriptionEditAdd->setText(cardDescriptionEdit->text());
    cardDescriptionEditAdd->setMaximumWidth(500);
    cardDescriptionEditAdd->setMinimumHeight(50);
    cardDescriptionEditAdd->setMaximumHeight(50);

    cardDescriptionEditAdd->setAlignment(Qt::AlignCenter);

    leftAdd->setAlignment(Qt::AlignCenter);
    rightAdd->setAlignment(Qt::AlignCenter);

    QHBoxLayout *timeInner = new QHBoxLayout;

    timeInner->addWidget(leftAdd);

    timeInner->addWidget(rightAdd);

    form->addWidget(doneButtonYes);  //0

    form->addWidget(doneButton);   //1

    form->addWidget(idLabel);   //2

    form->addWidget(cardTitleEditAdd);   //3

    form->addWidget(cardDescriptionEditAdd);   //4

    form->addLayout(timeInner);  //5

    form->addWidget(updateTaskButton);   //6

    form->addWidget(deleteTaskButton);   //7

    QFrame *formFrame = new QFrame;

    formFrame->setStyleSheet(EVENT_STYLE_LOAD);

    formFrame->setLayout(form);




    task_container_inner->addWidget(formFrame);

    deleteTaskButtonToLayoutMap.insert(deleteTaskButton,task_container);
    doneButtonToLayoutMap.insert(doneButton,doneButtonYes);

    doneButtonYesToLayoutMap.insert(doneButtonYes,doneButton);

    checkData();


    dateToHTTP = calendar->selectedDate().toString("MM-dd-yyyy");

    QJsonObject addEventJson;
    QJsonObject bodyJson;
    bodyJson.insert("user_id", ID_QSTRING);
    bodyJson.insert("event_name", cardTitleEdit->text());
    bodyJson.insert("event_date", dateToHTTP);
    bodyJson.insert("time_begin", time_begin_string);
    bodyJson.insert("time_end", time_end_string);
    bodyJson.insert("description", cardTitleEdit->text());


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
        cardDescriptionEdit->setText("");


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

        QMessageBox::warning(this, tr("Error"),
            "Connection ERROR!\n");

}

    reply->deleteLater();


     networkManageraddEvent->clearAccessCache();


}


void Shedule::updateTaskButton_pressed() {



}

void Shedule::deleteButton_pressed() {




    QPushButton *button = qobject_cast<QPushButton*>(sender());

    QHBoxLayout *layout = deleteTaskButtonToLayoutMap.take(button);


    ////////////////////////////////////////////

//    task_container->addWidget(mainImageTask);       изображение      0000
//    task_container->addWidget(timeLabelTask);         время       1111111    qlabel
//    task_container->addWidget(boxTitleTask);          евент наэйм  222222222    qlabel
//    task_container->addWidget(deleteTaskButton);  к





    QWidget *event_name = layout->takeAt(4)->widget();
    QLabel* event_nameLabel = dynamic_cast<QLabel*>(event_name);
    QString event_nameString = event_nameLabel->text();
    qDebug() <<"deleteeeeeee event"  <<  event_nameString  << endl;



    QWidget *time = layout->takeAt(3)->widget();
    QLabel* timeLabel = dynamic_cast<QLabel*>(time);
    QString timeString = timeLabel->text();
    qDebug() <<"Time===  "  <<  timeString  << endl;

    std::string time_begin = timeString.toStdString().substr(0,5);

    std::string time_end = timeString.toStdString().substr(9,13);

    QString begin_str = QString::fromStdString(time_begin);

    QString end_str = QString::fromStdString(time_end);

    qDebug() <<"timeeeeee  begin  "  <<  begin_str  << endl;

    qDebug() <<"timeeeeee  end  "  <<  end_str  << endl;

    QWidget *event_id = layout->takeAt(2)->widget();
    QLabel* event_idLabel = dynamic_cast<QLabel*>(event_id);
    QString event_idString = event_idLabel->text();
    qDebug() <<"Event ID===  "  <<  event_idString  << endl;


    dateToHTTP = calendar->selectedDate().toString("MM-dd-yyyy");

    QJsonObject deleteEventJson;
    QJsonObject bodyJson;
    bodyJson.insert("user_id", ID_QSTRING);
    bodyJson.insert("event_name", event_nameString);
    //bodyJson.insert("event_id", event_idString);
    bodyJson.insert("event_date", dateToHTTP);
    bodyJson.insert("time_begin", begin_str);
    bodyJson.insert("time_end", end_str);
    bodyJson.insert("description", event_nameString);


    QJsonArray eventArray;

    eventArray.push_back(bodyJson);

    deleteEventJson.insert("delete_event", eventArray);

        qDebug() << "create request" << endl;



        QNetworkRequest request(QUrl(SERVER_URL + ""));
        request.setHeader(QNetworkRequest::ContentTypeHeader,
                          QStringLiteral("application/json;charset=utf-8"));

        request.setRawHeader("JSON_DATA", QJsonDocument(deleteEventJson).toJson(QJsonDocument::Compact));
        qDebug() << "request data"<< QJsonDocument(deleteEventJson).toJson(QJsonDocument::Compact) << endl;
        networkManagerDeleteEvent->post(
            request,
            QJsonDocument(deleteEventJson).toJson(QJsonDocument::Compact)
        );
        qDebug() << "request send" << endl;


    while(QLayoutItem *tmpItem = layout->itemAt(0)) {
        layout->removeItem(tmpItem);
        layout->removeWidget(tmpItem->widget());
        delete tmpItem->widget();
        delete tmpItem;
    }
    layout->update();

    delete event_nameLabel;

    delete timeLabel;

    delete event_id;



    checkData();



   // titleWidgetList->update();



}

void Shedule::calendar_btn(const QDate &date) {


    clearTasks();

    loadSheduleFromDate();



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


    if(!strDinamicckeck.contains(strdate) && date !=   calendar->selectedDate()){




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


    for (int i = 0; i < task_container_inner->count();)
      {
        QLayoutItem *item = task_container_inner->itemAt(i);
        if (item->layout() != nullptr)     // Check whether item contains a layout
            delete task_container_inner->takeAt(i);  // Delete item with layout on it
        else i++;
      }


    QDate date =   calendar->selectedDate();

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

                  date1 = date.addDays(-5);
                  date2 = date.addDays(-4);
                  date3 = date.addDays(-3);
                  date4 = date.addDays(-2);
                  date5 = date.addDays(-1);
                  date6 = date;
                  date7 = date.addDays(1);
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

     qDebug() << "this id.........." << ID_QSTRING;

    QDate date = calendar->selectedDate();
    QJsonObject loadSheduleJson;
    QJsonObject currentDate;

    currentDate.insert("event_date", date.toString("yyyy-MM-dd"));
    currentDate.insert("user_id", ID_QSTRING);

    QJsonArray data;

    data.push_back(currentDate);

    loadSheduleJson.insert("get_events", data);

        qDebug() << "create request" << endl;



        QNetworkRequest request(QUrl(SERVER_URL + ""));

        request.setRawHeader("JSON_DATA", QJsonDocument(loadSheduleJson).toJson(QJsonDocument::Compact));

        request.setHeader(QNetworkRequest::ContentTypeHeader,
                          QStringLiteral("application/json;charset=utf-8"));
        qDebug() << "request data"<< QJsonDocument(loadSheduleJson).toJson(QJsonDocument::Compact) << endl;
        networkManagerGetEvents->post(
            request,
            QJsonDocument(loadSheduleJson).toJson(QJsonDocument::Compact)
        );
        qDebug() << "request send" << endl;
    }


void Shedule::onHttpResultGetEvents(QNetworkReply *reply) {


    qDebug() << "http finished" << endl;

    if(!reply->error()) {
        QByteArray resp = reply->readAll();
        qDebug() <<"ETO OTVET SERVERA LOAD EVENTS :  " + resp  << endl;
        QJsonDocument doc = QJsonDocument::fromJson(resp);
        QJsonObject obj;

        std::string str = resp.toStdString();

        std::cout << "str  " + str << std::endl;
//        "{\"userID\":\"213564544\",\"Friends\":[\"Misha1991\", \"Igor\",  \"Alex\",  \"qwe\", \"piotr\"]}";

        //std::string parser_str = "{\"get_events\":[{\"description\":\"breakfast\","
                                 " \"time_begin\":\"10:00\",""\"time_end\":\"10:45\"}, {\"description\":\"lansh\", \"time_begin\":"
                                          "\"19:00\", \"time_end\":\"20:00\"}]}";


        nlohmann::json j = nlohmann::json::parse(str);




        if(j["get_events"] != "Not found events"){

            nlohmann::json::iterator it = j.begin();

            nlohmann::json value = j[it.key()];

            for (auto& element : value)
            {

                std::string time_end_str;
                 std::string time_begin_str;
                  std::string event_name;
                  std::string event_description;


                if(element.contains("event_name"))
                {
                    event_name = element["event_name"].get<std::string>();

                    std::cout << event_name << std::endl;
                }

                if(element.contains("description"))
                {
                    event_description = element["description"].get<std::string>();

                    std::cout << event_name << std::endl;
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

                deleteTaskButton = new QSvgButton(":/resc/resc/cross.svg", QSize(25,25));
                deleteTaskButton->setStyleSheet("border-radius:5px;");
                connect(deleteTaskButton, &QSvgButton::clicked, this, &Shedule::deleteButton_pressed);


                updateTaskButton = new QSvgButton(":/resc/resc/arrow_up.svg", QSize(40,40));
                updateTaskButton->setStyleSheet("border-radius:20px;");
                connect(updateTaskButton, &QSvgButton::clicked, this, &Shedule::updateTaskButton_pressed);

                doneButtonYes = new QSvgButton(":/resc/resc/checkbox-checked.svg", QSize(30,30));
                doneButtonYes->hide();
                doneButtonYes->setStyleSheet("border-radius:5px;");
                connect(doneButtonYes, &QSvgButton::clicked, this, &Shedule::doneButtonYes_pressed);

                doneButton = new QSvgButton(":/resc/resc/checkbox-unchecked.svg", QSize(30,30));
                doneButton->setStyleSheet("border-radius:5px;");
                connect(doneButton, &QSvgButton::clicked, this, &Shedule::doneButton_pressed);

//                timeLabelTask = new QLabel;
//                timeLabelTask->setStyleSheet("QFrame {""background: transparent""}");
//                timeLabelTask->setAlignment(Qt::AlignCenter);
//                timeLabelTask->setAlignment(Qt::AlignVCenter);
//                timeLabelTask->setContentsMargins(0,15,0,0);


                time_begin_string = QString::fromUtf8(time_begin_str.c_str());
                time_end_string = QString::fromUtf8(time_end_str.c_str());

                std::string time_begin_hours = time_begin_string.toStdString().substr(0,2);
                std::string time_begin_minuts = time_begin_string.toStdString().substr(3,4);

                int time_begin_hours_int =  std::stoi( time_begin_hours );
                int time_begin_minuts_int =  std::stoi( time_begin_minuts );

                std::string time_end_hours = time_end_string.toStdString().substr(0,2);
                std::string time_end_minuts = time_end_string.toStdString().substr(3,4);

                int time_end_hours_int =  std::stoi( time_end_hours );
                int time_end_minuts_int =  std::stoi( time_end_minuts );



                QString titleEvent = QString::fromUtf8(event_name.c_str());
                QString descriptionEvent = "Hellow";

                QLabel *idLabel  = new QLabel("");

                idLabel->setText(titleEvent);
                idLabel->hide();

                QLineEdit *cardTitleEdit = new QLineEdit;

                 QLineEdit *cardDescriptionEdit = new QLineEdit;

                //QHBoxLayout *titleEditContainerLoad = new QHBoxLayout;

                QHBoxLayout *form = new QHBoxLayout;

                TimeEdit *left = new TimeEdit;
                TimeEdit *right = new TimeEdit;


                QTime leftTime(time_begin_hours_int,time_begin_minuts_int);
                QTime rightTime(time_end_hours_int,time_end_minuts_int);

                left->setTime(leftTime);
                right->setTime(rightTime);

                left->setStyleSheet(Qtimestyle);
                right->setStyleSheet(Qtimestyle);

                left->setMaximumWidth(100);
                right->setMaximumWidth(100);

                cardTitleEdit->setStyleSheet(EDIT_TEXT_EVENT_TITLE);
                cardTitleEdit->setMaximumWidth(200);
                cardTitleEdit->setText(titleEvent);
                cardTitleEdit->setAlignment(Qt::AlignCenter);

                cardDescriptionEdit->setStyleSheet(EDIT_TEXT_SMALL);
                cardDescriptionEdit->setText(descriptionEvent);
                cardDescriptionEdit->setMaximumWidth(500);
                cardDescriptionEdit->setMinimumHeight(50);
                cardDescriptionEdit->setMaximumHeight(50);

                cardDescriptionEdit->setAlignment(Qt::AlignCenter);

                left->setAlignment(Qt::AlignCenter);
                right->setAlignment(Qt::AlignCenter);

                QHBoxLayout *timeInner = new QHBoxLayout;

                timeInner->addWidget(left);

                timeInner->addWidget(right);

                form->addWidget(doneButtonYes);  //0

                form->addWidget(doneButton);   //1

                form->addWidget(idLabel);   //2

                form->addWidget(cardTitleEdit);   //3

                form->addWidget(cardDescriptionEdit);   //4

                form->addLayout(timeInner);  //5

                form->addWidget(updateTaskButton);   //6

                form->addWidget(deleteTaskButton);   //7

                QFrame *formFrame = new QFrame;

                formFrame->setStyleSheet(EVENT_STYLE_LOAD);

                formFrame->setLayout(form);




                task_container_inner->addWidget(formFrame);

                deleteTaskButtonToLayoutMap.insert(deleteTaskButton,task_container);
                doneButtonToLayoutMap.insert(doneButton,doneButtonYes);

                doneButtonYesToLayoutMap.insert(doneButtonYes,doneButton);



             }

        }



        } else {




}

    qDebug() << reply->errorString();

    qDebug() << "Server answer: " +  reply->readAll() << endl;

    qDebug () << reply -> error ();


    reply->deleteLater();

    networkManagerGetEvents->clearAccessCache();

}
