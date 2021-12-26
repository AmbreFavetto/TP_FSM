#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

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

QString MainWindow::getPath()
{
    return ui->lineEditSearch->text();
}

QString MainWindow::getCmd()
{
    return ui->lineEditCommand->text();
}


void MainWindow::on_btnBrowse_clicked()
{

}


void MainWindow::on_btnSendCommand_clicked()
{
    qDebug() << "PATH" << getPath();
    qDebug() << "CMD" << getCmd();
}


void MainWindow::on_btnInfos_clicked()
{
    helpWindow.show();
}

