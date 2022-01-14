#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bddrequest.h"
#include "fsm.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::getUserPath(){
    path = ui->lineEditSearch->text();
}

void MainWindow::getUserCmd(){
    command = ui->lineEditSearch->text();
}


//"C:/Users/Leval/AppData/Roaming/"
void MainWindow::on_btnSendCommand_clicked() {
    //QString line = ui->lineEditCommand->text();
    //Fsm *fsm = new Fsm();
    //fsm->stringToList(line);

    bddRequest* db = new bddRequest();
    db->setupDatabase();
    getUserPath();
    QDir d(path);
    if (d.exists()){
        qDebug() << "good";
        db->directoryIterator(path);
    }


    //delete fsm;
}
