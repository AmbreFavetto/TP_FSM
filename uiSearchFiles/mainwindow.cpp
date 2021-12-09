#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMainWindow>
#include "myclient.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MinWIndow : public QMainWindow {
    Q_OBJECT
    myclient *_client = nullptr;
};

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

