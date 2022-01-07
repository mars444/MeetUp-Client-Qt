#ifndef STARTFRAGMENT_H
#define STARTFRAGMENT_H

#include <common/base/basefragment.h>

#include <QTranslator>
#include <QEvent>



class StartFragment: public BaseFragment {
    Q_OBJECT
public:
    StartFragment();
    ~StartFragment();

protected:
    // Метод получения событий в главном окне приложения
    // В нём будет производиться проверка события смены перевода приложения
    void changeEvent(QEvent * event) override;

private:
    QTranslator qtLanguageTranslator;   // Выделяем перевод в отдельном поле, иначе ничего работать не будет

public slots:
    void openLogin();
    void openRegistration();
};

#endif // STARTFRAGMENT_H
