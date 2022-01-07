#include "mainwindow.h"

#include <QApplication>
#include "nlohmann/json.hpp"
#include <iostream>
#include <set>

#include <iostream>
#include <fstream>
#include <string>
#include <QInputDialog>


#include <QTranslator>
#include <QLibraryInfo>


int main(int argc, char *argv[])
{

   qDebug("Start programm");

    //Поддержка HighDpi в проекте.
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);
    QApplication a(argc, argv);

//Установка русского языка

    QTranslator qtLanguageTranslator;

    QStringList languages;

    languages<< "English" << "Русский";

    QString lang = QInputDialog::getItem
            (NULL,"Please select Language", "Language", languages);

    if( lang == "Русский"){
        qtLanguageTranslator.load(":/resc/resc/QtLanguage_ru.qm");
    }

    qApp->installTranslator(&qtLanguageTranslator);

//Установка русского языка

    MainWindow w;
    w.show();


    return a.exec();
}
