#include "Shedule_generation.h"
#include "style/stylecontainer.h"
#include <ui/view/qsvgbutton.h>
#include <ui/view/waitingspinnerwidget.h>
using namespace styles;


#include <QLabel>
#include <cstring>
#include <QTimeEdit>
#include <QSettings>
#include <QDate>
#include <QVBoxLayout>
#include <QJsonObject>
#include <QJsonDocument>
#include <ui/view/qsvgbutton.h>
#include <ui/view/waitingspinnerwidget.h>
#include <QJsonArray>
#include <QMessageBox>
#include <QNetworkReply>
#include <QScrollArea>
#include <QScrollBar>
#include <QLine>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QSvgWidget>
#include <QStackedWidget>
#include <QCalendarWidget>

QDynamicButton::QDynamicButton(QWidget *parent) :
    QVBoxLayout(parent)
{


   QHBoxLayout *mainLayout = new QHBoxLayout;
    QVBoxLayout *inputContainer = new QVBoxLayout;

    QHBoxLayout *titleContainer = new QHBoxLayout;
    QSvgButton *backButton = new QSvgButton(":/resc/resc/arrow_back.svg", QSize(24,24));
    QLabel *titleLabel = new QLabel("Мое расписание");


    QCalendarWidget *calendar = new QCalendarWidget;


    calendar->setMinimumDate(QDate::currentDate());



    calendar->setGridVisible(0);



    calendar->setNavigationBarVisible(1);

    QHBoxLayout *buttoContainer = new QHBoxLayout;
    QHBoxLayout *buttonBoxContainer = new QHBoxLayout;
    QPushButton *createButton_1 = new QPushButton("Отправить расписание");
    QPushButton *createButton_2= new QPushButton("Отправить расписание");

    QFrame *loadingContaiter = new QFrame;
    WaitingSpinnerWidget *loading = new WaitingSpinnerWidget(loadingContaiter, true, false);
    loading->setColor(QT_COLOR_PRIMARY);
    loadingContaiter->setMinimumWidth(100);
    QFrame *loadingBoxContaiter = new QFrame;
    WaitingSpinnerWidget *loadingBox = new WaitingSpinnerWidget(loadingContaiter, true, false);
    loadingBox->setColor(QT_COLOR_PRIMARY);
    loadingBoxContaiter->setMinimumWidth(100);

    QLineEdit *titleEdit = new QLineEdit;
    QPlainTextEdit *descriptionEdit = new QPlainTextEdit;

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



    //стак для выбора контента
    QStackedWidget *stack = new QStackedWidget;

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


    // стак для деk
   cardTitleEdit = new QLineEdit;

    //connect(cardTitleEdit, &QLineEdit::textChanged, this, &QDynamicButton::checkBoxTitle);

    QHBoxLayout *titleEditContainer = new QHBoxLayout;

    QHBoxLayout *form = new QHBoxLayout;
    QTimeEdit *left = new QTimeEdit;
    QTimeEdit *right = new QTimeEdit;

    left->setStyleSheet(Qtimestyle);
    right->setStyleSheet(Qtimestyle);


    QSvgButton *addBoxTitleButton = new QSvgButton(":/resc/resc/done_outline.svg", QSize(24,24));
    QVBoxLayout *titleWidgetList = new QVBoxLayout;
    titleWidgetList->setAlignment(Qt::AlignTop);
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

    titleContainer->addWidget(backButton);
    titleContainer->addWidget(titleLabel);
    titleContainer->setContentsMargins(0,24,0,16);
    titleLabel->setContentsMargins(16,0,0,0);




    buttoContainer->setAlignment(Qt::AlignRight);

    createButton_2->setStyleSheet(BUTTON_SOLID);
    createButton_2->setMaximumWidth(335);
    createButton_2->setMinimumWidth(335);

    buttonBoxContainer->addWidget(loadingBoxContaiter);
    buttonBoxContainer->addWidget(createButton_2);
    buttonBoxContainer->setAlignment(Qt::AlignRight);




    inputContainer->setAlignment(Qt::AlignTop);
    inputContainer->addLayout(titleContainer);
    inputContainer->addWidget(calendar);
    inputContainer->addLayout(selectorContainer);
    inputContainer->addWidget(stack);

    content->addLayout(inputContainer);

    mainLayout->setAlignment(Qt::AlignHCenter);
    mainLayout->addWidget(deskScrollArea);


    this->addWidget(stack);



}

void QDynamicButton::checkData() {

    if (titleList.size() != 0) {
          createButton_2->setStyleSheet(BUTTON_SOLID);
      } else {
          createButton_2->setStyleSheet(BUTTON_DISABLED);
      }

}


void QDynamicButton::checkBoxTitle() {
    if (cardTitleEdit->text().length() >= 3 && cardTitleEdit->text().length() <= 30) {
        addBoxTitleButton->show();
    } else {
        addBoxTitleButton->hide();
    }
}

QDynamicButton::~QDynamicButton()
{

}

/* Метод для возврата значения номера кнопки
 * */
int QDynamicButton::getID()
{
    return buttonID;
}

/* Инициализация статической переменной класса.
 * Статическая переменная класса должна инициализироваться в обязательном порядке
 * */
int QDynamicButton::ResID = 0;
