#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "myclient.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
    myclient *_client = nullptr;

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow() override;

    private slots:
        //void on_btnConnect_clicked();
        //void on_btnDisconnect_clicked();
        //void on_pushButton_clicked();

    private :
        Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
