#include "bddrequest.h"
#include <QDirIterator>
#include <QList>
#include <QDateTime>
#include <QDate>
#include <QFuture>
#include <QSqlQueryModel>
#include <QTableView>
bddRequest::bddRequest()
{
    //setupDatabase();
    _pool.setMaxThreadCount(1);
}

int bddRequest::setupDatabase(){

    /* Base de données */
    db = QSqlDatabase::addDatabase("QSQLITE");
    if(db.lastError().isValid()){
        qCritical() << "addDatabase" << db.lastError().text();
        return -1;
    }

    /* Init de la base de donnees */
    appDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(appDataLocation); // Creation du repertoire s'il existe pas et ouverture
    if(!dir.exists()){
        dir.mkdir(appDataLocation);
        qDebug() << "mkdir" << appDataLocation;
    }

    /* Creation fichiers base de donnee */
    QString dbPath = appDataLocation+"/testDbFsm.db";
    qDebug() <<"dbPath" << dbPath;
    db.setDatabaseName(dbPath);
    if(!db.open()){
        qCritical() << "Unable to open db" << db.lastError().text() << dbPath;
        return -2;
    }

    /* Creation table files */
    QString tableFilesCreate = "CREATE TABLE IF NOT EXISTS files("
                                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                "name STRING,"
                                "date_creation DATE,"
                                "date_modification DATE,"
                                "size STRING,"
                                "type STRING,"
                                "chemin STRING"
                                ")";

    /* Start base de donne */
    QSqlQuery query;
    query.exec("DROP TABLE files");
    query.exec(tableFilesCreate);
    query.exec("pragma temp_store = memory");
    query.exec("PRAGMA synchronous = normal");
    query.exec("pragma mmap_size = 30000000000");
    query.exec("PRAGMA journal_mode = wal");
    if(query.lastError().isValid()){
        qWarning() << "CREATE TABLE" << query.lastError().text();
        return -3;
    }

    return 0;
}


int bddRequest::addRow(QStringList data){
    /* Preparation pour modif */
    db.transaction();
    QSqlQuery query;
    query.prepare("INSERT INTO files (name, date_creation, date_modification, size, type, chemin)"
                          "VALUES(:name, :date_creation, :date_modification, :size, :type, :chemin)");

    /* Inserer dans la tables grace au query.prepare */
    query.bindValue(":name", data[0]);
    query.bindValue(":date_creation", data[1]);
    query.bindValue(":date_modification", data[2]);
    query.bindValue(":size", data[3]);
    query.bindValue(":type", data[4]);
    query.bindValue(":chemin", data[5]);
    query.exec();
    if (query.lastError().isValid()){
        qWarning() << "INSERT" << query.lastError().text();
        return -1;
    }
    return 0;
}


int bddRequest::extractFileInfo(QFileInfo file) {

    QStringList fileInfos;
    fileInfos.append(file.fileName()); //QString
    fileInfos.append(file.birthTime().date().toString()); //QDateTime to QDate to QString
    fileInfos.append(file.lastModified().date().toString()); //QDateTime to QDate to QString
    fileInfos.append(QString::number(file.size())); //qint64 to QString
    fileInfos.append(file.suffix()); //QString
    fileInfos.append(file.absoluteFilePath()); //QString
    int a = addRow(fileInfos);
    return a;
}


int bddRequest::directoryIterator(QString dirPathName){


    QFuture<void> future = QtConcurrent::run(&_pool, [this, dirPathName]() {
        //QElapsedTimer timer;
        //timer.start();
        setupDatabase();
        QString dir= dirPathName;
        QDirIterator it(dir, QDirIterator::Subdirectories);
        db.open();
        db.transaction();
        while(it.hasNext()){
            QFile file(it.next());
            QFileInfo fileInfo(file);
            if(fileInfo.isFile()) extractFileInfo(fileInfo);
        }
        db.commit();

        selectAllFilesFromDB();
        db.close();
        //qDebug() << timer.elapsed()/1000 << "seconde";
        return 0;
    });

    return 0;
}

void bddRequest::selectAllFilesFromDB() {
    QSqlQuery query;
    query.exec(QString("SELECT * FROM files"));

    QStringList fileNameList;

    while (query.next()) {
        QStringList valuesList;
        fileNameList.append(query.value(6).toString());
    }
    emit dirsAdded(fileNameList);
    qDebug() << __LINE__ << __FUNCTION__ << "EMIT";
}
