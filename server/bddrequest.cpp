#include "bddrequest.h"
#include <QDirIterator>
#include <QList>
#include <QDateTime>
#include <QDate>

bddRequest::bddRequest()
{

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
                                "type STRING"
                                ")";

    /* Start base de donne */
    QSqlQuery query;
    query.exec("DROP TABLE tableFilesCreate");
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
    db.open();
    db.transaction();
    QSqlQuery query;
    query.prepare("INSERT INTO tableFilesCreate (name, date_creation, date_modification, size, type)"
                          "VALUES(:name, :date_creation, :date_modification, :size, :type)");

    /* Debut timer */
    QElapsedTimer timer;
    timer.start();

    /* Inserer dans la tables grace au query.prepare */
    query.bindValue(":name", data[0]);
    query.bindValue(":date_creation", data[1]);
    query.bindValue(":date_modification", data[2]);
    query.bindValue(":size", data[3]);
    query.bindValue(":type", data[4]);
    query.exec();
    if (query.lastError().isValid()){
        qWarning() << "INSERT" << query.lastError().text();
        return -1;
    }

    db.commit();
    qDebug() << timer.elapsed()/1000 << "seconde";
    return 0;
}


int bddRequest::extractFileInfo(QFileInfo file) {
    QStringList fileInfos;
    fileInfos[0]= file.fileName(); //QString
    fileInfos[1]= file.birthTime().date().toString(); //QDateTime to QDate to QString
    fileInfos[2]= file.lastModified().date().toString(); //QDateTime to QDate to QString
    fileInfos[3]= QString::number(file.size()); //qint64 to QString
    fileInfos[4]= file.suffix(); //QString
    int a = addRow(fileInfos);
    return a;
}


int bddRequest::directoryIterator(QString dirPathName){
    QString name;
    //qDebug() << dirPathName;
    QDir dir(dirPathName);
    //qDebug() << dir.dirName();
    QDirIterator it(dir);
    //qDebug() << it.fileName();
    //qDebug() << "coucou5";
    while(it.hasNext()){
        //qDebug() << "coucou6";
        QFile file(it.next());
        //qDebug() << name;//ou .path();
        //qDebug() << "coucou7";
        //QFile file(name); //QString to QFile
        QFileInfo fileInfo(file); //QFile to QFileInfo
        qDebug() << fileInfo.fileName();
        if(fileInfo.isFile()){
           extractFileInfo(fileInfo);
        }
        else directoryIterator(name);
    }
    return 0;
}
