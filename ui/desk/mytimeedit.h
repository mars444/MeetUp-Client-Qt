#ifndef MYTIMEEDIT_H
#define MYTIMEEDIT_H

#include <QTimeEdit>


class TimeEdit: public QTimeEdit
{
public:
    using QTimeEdit::QTimeEdit;
    void stepBy(int steps) override{
        if(currentSection() == MinuteSection){
            setTime(time().addSecs(steps*900));  //15*60 сек
            return;
        }
        QTimeEdit::stepBy(steps);
    }
};
#endif // MYTIMEEDIT_H
