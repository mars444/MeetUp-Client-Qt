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

#include "Shedule_generation.h"
#include <models/deskmodel.h>

#include <ui/view/qsvgbutton.h>
#include <ui/view/waitingspinnerwidget.h>

class QDynamicButton : public QVBoxLayout
{
    Q_OBJECT
public:
    explicit QDynamicButton(QWidget *parent = 0);
    ~QDynamicButton();
    static int ResID;   // Статическая переменная, счетчик номеров кнопок
    int getID();        // Функция для возврата локального номера кнопки


public slots:

    void checkBoxTitle();
    void checkData();
private:
    int buttonID = 0;   // Локальная переменная, номер кнопки
    QLineEdit *cardTitleEdit;
    QSvgButton *addBoxTitleButton;
    QList<QString> titleList;
     QSvgButton *deleteTaskButton;
       QLabel *timeLabelTask;
        QLabel *boxTitleTask;
         QSvgWidget *mainImageTask;
         QHBoxLayout *task_container;
         QVBoxLayout *titleWidgetList;
         QTime *time_begin;
         QTime *time_end;

         QPushButton *createButton_2;


};

