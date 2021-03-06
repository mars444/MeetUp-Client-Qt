#ifndef BASEFRAGMENT_H
#define BASEFRAGMENT_H

#include <QFrame>
#include <QVBoxLayout>
#include <QWidget>

#include <models/basemodel.h>
/**
 * @brief The BaseFragment class
 *
 * Базовый фрагмент приложения.
 */
class BaseFragment: public QFrame {
    Q_OBJECT

signals:
    void back();
    void backWhithData(BaseModel* model);

    void navigateTo(QString tag);
    void navigateWhithData(QString tag, BaseModel* model);

    void newRootScreen(QString tag);
    void replace(QString tag);

protected:
    void clearList(QLayout *list);
public:
    BaseFragment();
    ~BaseFragment();

    virtual void onPause();
    virtual void onResume();
    virtual void setData(BaseModel* model);
};

#endif // BASEFRAGMENT_H
