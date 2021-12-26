#include "mainwindow.h"
#include "bddrequest.h"
#include "helpwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();


    // !bddRequest * db = new bddRequest();

    // db->directoryIterator(location);
    return a.exec();
}
