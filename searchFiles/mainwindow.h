#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include "helpwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QStringListModel *m_model = nullptr;
    QString           m_selected_entry = "";
    QStringList       m_dirs;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();    
    HelpWindow helpWindow;
    QString path;
    QString command;
    void getUserPath();
    void getUserCmd();
    //void updateStatusBar();
    const QString &getPath() const;
    void setPath(const QString &newPath);
public slots:
    void onDirsAddedFromFsm(const QString &);
private slots:
    void on_btnBrowse_clicked();
    void on_btnSendCommand_clicked();
    void on_btnInfos_clicked();
    void onOpenFolder();
    void onLaunchFile();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
