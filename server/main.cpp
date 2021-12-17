#include "mainwindow.h"
#include "bddrequest.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
qDebug() << "coucou";
    bddRequest * db = new bddRequest();

    db->setupDatabase();
    QString location = "D:/Ynov/DevLogiciel/TP2_Research_test/";
    db->directoryIterator(location);
    return a.exec();
}
