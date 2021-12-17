#include "mainwindow.h"
#include "bddrequest.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    bddRequest * db = new bddRequest();

    db->setupDatabase();
    QString location = "C:/Users/Leval/TPDevLogicielAvance2";
    db->directoryIterator(location);
    return a.exec();
}
