#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDateTime>
#include <QDebug>
#include <QDesktopServices>
#include <QFileDialog>
#include "../libraryFsm/libraryfsm.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    // listview
    m_model = new QStringListModel(this);
    ui->listViewResults->setUniformItemSizes(true);
    ui->listViewResults->setModel(m_model);

    ui->listViewResults->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->listViewResults, &QListView::customContextMenuRequested, [this](QPoint pos) {
        QModelIndex index = ui->listViewResults->indexAt(pos);
        m_selected_entry  = index.data(Qt::DisplayRole).toString();
        QMenu *  menu     = new QMenu(this);
        QAction *explore  = new QAction("Open folder", this);
        explore->setStatusTip(QString("Open the folder containg %1 in explorer ").arg(m_selected_entry));
        connect(explore, &QAction::triggered, this, &MainWindow::onOpenFolder);
        menu->addAction(explore);

        QAction *launch = new QAction("Launch file with default application", this);
        launch->setStatusTip(QString("Launch %1 with default application").arg(m_selected_entry));
        connect(launch, &QAction::triggered, this, &MainWindow::onLaunchFile);
        menu->addAction(launch);

        menu->popup(ui->listViewResults->viewport()->mapToGlobal(pos));
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getUserPath(){
    path = ui->lineEditSearch->text();
}

void MainWindow::getUserCmd(){
    command = ui->lineEditSearch->text();
}

void MainWindow::on_btnBrowse_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), QString(),
                                                    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->lineEditSearch->setText(dir);
}


void MainWindow::on_btnSendCommand_clicked()
{
    QString line = ui->lineEditCommand->text();
        getUserPath();
        LibraryFsm *fsm = new LibraryFsm(path);
        fsm->stringToList(line);
        fsm->createMapping();
}


void MainWindow::on_btnInfos_clicked()
{
    helpWindow.show();
}

void MainWindow::onDirsAdded(const QString &list) {
    qDebug() << __FUNCTION__ << __LINE__ << list.size() << m_dirs.size();
    m_dirs << list;
    m_model->setStringList(m_dirs);
    ui->listViewResults->scrollToBottom();
    //updateStatusBar();
}




void MainWindow::onOpenFolder() {
    qDebug() << __FUNCTION__ << __LINE__ << m_selected_entry;

    QFileInfo fi(m_selected_entry);
    qDebug() << fi.absolutePath() << " fn=" << fi.fileName();
    QDesktopServices::openUrl(QUrl::fromLocalFile(fi.absolutePath()));
//    ui->lblOverview->setText(QString("Exploring %1").arg(fi.absolutePath()));
}

void MainWindow::onLaunchFile() {
    qDebug() << __FUNCTION__ << __LINE__ << m_selected_entry;
    QDesktopServices::openUrl(QUrl::fromLocalFile(m_selected_entry));
//    ui->lblOverview->setText(QString("Launching %1").arg(m_selected_entry));
}
