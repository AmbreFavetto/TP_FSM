#include "mainwindow.h"

#include "bddrequest.h"
#include "helpwindow.h"


#include <QSqlQuery>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    /* Debut timer */
    //QElapsedTimer timer;
    //timer.start();

    //bddRequest * db = new bddRequest();
    //db->setupDatabase();
    //QString location = "C:/";
    //QString location = "C:/Users/Leval/TPDevLogicielAvance2";
    //db->directoryIterator(location);


    //qDebug() << timer.elapsed()/1000 << "seconde";

    //return 0;
    return a.exec();
}



