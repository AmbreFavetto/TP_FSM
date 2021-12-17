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
    QString location = "C:/Users/Leval/TPDevLogicielAvance/";
    db->directoryIterator(location);
    return a.exec();
}
