#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "helpwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();    
    HelpWindow helpWindow;

    QString getPath();
    QString getCmd();

private slots:
    void on_btnBrowse_clicked();
    void on_btnSendCommand_clicked();
    void on_btnInfos_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
