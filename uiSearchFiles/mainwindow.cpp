#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "fsm.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnSendCommand_clicked()
{
    QString line = ui->lineEditCommand->text();
    Fsm *fsm = new Fsm();
    fsm->stringToList(line);



    delete fsm;
}

