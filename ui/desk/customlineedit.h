#ifndef CUSTOMLINEEDIT_H
#define CUSTOMLINEEDIT_H

#include <QLineEdit>

class CustomLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit CustomLineEdit(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event);

signals:

public slots:
};

#endif // CUSTOMLINEEDIT_H
