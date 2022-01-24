#include "bddrequest.h"
#include <QDirIterator>
#include <QList>
#include <QDateTime>
#include <QDate>
#include <QFuture>
#include <QSqlQueryModel>

bddRequest::bddRequest()
{
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
                                "flag STRING,"
                                "date_creation DATE,"
                                "date_modification DATE,"
                                "size INTEGER,"
                                "type STRING,"
                                "chemin STRING"
                                ")";

    /* Start base de donne */
    QSqlQuery query;
    //query.exec("DROP TABLE files");
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
    query.prepare("INSERT INTO files (name, flag, date_creation, date_modification, size, type, chemin)"
                          "VALUES(:name, :flag, :date_creation, :date_modification, :size, :type, :chemin)");

    /* Inserer dans la tables grace au query.prepare */
    query.bindValue(":name", data[0]);
    query.bindValue(":flag", "default");
    query.bindValue(":date_creation", data[1]);
    query.bindValue(":date_modification", data[2]);
    query.bindValue(":size", data[3].toInt());
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
    emit dirsAdded(file.absoluteFilePath());
    return a;
}


int bddRequest::directoryIterator(QString dirPathName){

    QFuture<void> future = QtConcurrent::run(&_pool, [this, dirPathName]() {
        //QElapsedTimer timer;
        //timer.start();
        setupDatabase();
        QString dir= dirPathName;
        QDirIterator it(dir, QDirIterator::Subdirectories);
        //db.open();
        db.transaction();
        while(it.hasNext()){
            QFile file(it.next());
            QFileInfo fileInfo(file);
            if(fileInfo.isFile()) {
                extractFileInfo(fileInfo);
            }
        }
        db.commit();

        //selectAllFilesFromDB();
        db.close();
        //qDebug() << timer.elapsed()/1000 << "seconde";
        return 0;
    });

    return 0;
}

int bddRequest::clear(QString flagToClear)
{
    setupDatabase();

    db.transaction();
    QSqlQuery query;
    qDebug() << "FLAG :" << flagToClear;
    QString queryPrepare = "DELETE FROM files WHERE flag='" + flagToClear +"'";
    qDebug() << queryPrepare;
    query.exec(queryPrepare);
    if(query.lastError().isValid()) {
        qDebug() << "err cmd clear";
        return -1;
    }
    db.commit();
    db.close();
    qDebug() << "good cmd clear";
    return 0;
}

int bddRequest::add(QString flagToAdd, QString files)
{
    QFuture<void> future = QtConcurrent::run(&_pool, [this, flagToAdd, files]() {
        setupDatabase();

        db.transaction();

        QSqlQuery query;
        QString queryPrepare = "UPDATE files SET flag = '" + flagToAdd + "' WHERE chemin = '" + files + "'";
        qDebug() << queryPrepare;
        query.exec(queryPrepare);
        if(query.lastError().isValid()) {
            qDebug() << query.lastError();
            qDebug() << "err cmd add";
            return -1;
        }
        db.commit();
        db.close();
        qDebug() << "good cmd add";
        return 0;
    });

    return 0;
}

int bddRequest::get(QString flagToGet)
{
    setupDatabase();

    QSqlQuery query;
    QString queryPrepare = "SELECT * FROM files WHERE flag = '" + flagToGet + "'";
    qDebug() << queryPrepare;
    query.exec(queryPrepare);
    if(query.lastError().isValid()) {
        qDebug() << "err cmd get";
        return -1;
    }
    db.close();
    qDebug() << "good cmd get";
    return 0;
}

// TODO Modif date
int bddRequest::searchLastModifiedSimple(QString fileNamePartToSearch, QString date)
{
    setupDatabase();

    db.transaction();
    QSqlQuery query;
    QString queryPrepare = "SELECT * FROM files WHERE name LIKE '" + fileNamePartToSearch + "' AND date_modification = '" + date + "'" ;
    qDebug() << queryPrepare;
    query.exec(queryPrepare);
    if(query.lastError().isValid()) {
        qDebug() << "err cmd search last modify simple";
        return -1;
    }
    db.commit();
    qDebug() << "good cmd search last modify simple";
    return 0;
}

int bddRequest::searchLastModifiedSinceLast(QString fileNamePartToSearch, QString date, QString TimeUnit)
{
    setupDatabase();

    db.transaction();
    QSqlQuery query;
    QString queryPrepare = "SELECT * FROM files WHERE name LIKE '" + fileNamePartToSearch + "' AND "; // date < date courrante
    qDebug() << queryPrepare;
    query.exec(queryPrepare);
    if(query.lastError().isValid()) {
        qDebug() << "err cmd search last modify since last";
        return -1;
    }
    db.commit();
    qDebug() << "good cmd search last modify since last";
    return 0;
}

int bddRequest::searchLastModifiedBetween(QString fileNamePartToSearch, QString date1, QString date2)
{
    setupDatabase();

    db.transaction();
    QSqlQuery query;
    QString queryPrepare = "SELECT * FROM files WHERE name LIKE '" + fileNamePartToSearch + "' AND date_modification BETWEEN '" + date1 + "' AND '" + date2 + "'";
    qDebug() << queryPrepare;
    query.exec(queryPrepare);
    if(query.lastError().isValid()) {
        qDebug() << "err cmd search last modify between";
        return -1;
    }
    db.commit();
    qDebug() << "good cmd search last modify between";
    return 0;
}

int bddRequest::searchCreateSimple(QString fileNamePartToSearch, QString date)
{
    setupDatabase();

    db.transaction();
    QSqlQuery query;
    QString queryPrepare = "SELECT * FROM files WHERE name LIKE '" + fileNamePartToSearch + "' AND date_creation = '" + date + "'";
    qDebug() << queryPrepare;
    query.exec(queryPrepare);
    if(query.lastError().isValid()) {
        qDebug() << "err cmd search create simple";
        return -1;
    }
    db.commit();
    qDebug() << "good cmd search create simple";
    return 0;
}

int bddRequest::searchCreateSinceLast(QString fileNamePartToSearch, QString date, QString TimeUnit)
{
    setupDatabase();

    db.transaction();
    QSqlQuery query;
    QString queryPrepare = "SELECT * FROM files WHERE name LIKE '" + fileNamePartToSearch + "' AND "; // date < date courrante
    qDebug() << queryPrepare;
    query.exec(queryPrepare);
    if(query.lastError().isValid()) {
        qDebug() << "err cmd search create since last";
        return -1;
    }
    db.commit();
    qDebug() << "good cmd search create since last";
    return 0;
}

int bddRequest::searchCreateBetween(QString fileNamePartToSearch, QString date1, QString date2)
{
    setupDatabase();

    db.transaction();
    QSqlQuery query;
    QString queryPrepare = "SELECT * FROM files WHERE name LIKE '" + fileNamePartToSearch + "' AND date_creation BETWEEN '" + date1 + "' AND '" + date2 + "'";
    qDebug() << queryPrepare;
    query.exec(queryPrepare);
    if(query.lastError().isValid()) {
        qDebug() << "err cmd search create between";
        return -1;
    }
    db.commit();
    qDebug() << "good cmd search create between";
    return 0;
}

int bddRequest::searchMaxSize(QString fileNamePartToSearch, QString size)
{
    setupDatabase();

    db.transaction();
    QSqlQuery query;
    QString queryPrepare = "SELECT * FROM files WHERE name LIKE '" + fileNamePartToSearch + "' AND WHERE size <'" + size + "'";
    qDebug() << queryPrepare;
    query.exec(queryPrepare);
    if(query.lastError().isValid()) {
        qDebug() << "err cmd search max size";
        return -1;
    }
    db.commit();
    qDebug() << "good cmd search max size";
    return 0;
}

int bddRequest::searchMinSize(QString fileNamePartToSearch, QString size)
{
    setupDatabase();

    db.transaction();
    QSqlQuery query;
    QString queryPrepare = "SELECT * FROM files WHERE name LIKE '" + fileNamePartToSearch + "' AND WHERE size >'" + size + "'";
    qDebug() << queryPrepare;
    query.exec(queryPrepare);
    if(query.lastError().isValid()) {
        qDebug() << "err cmd search min size";
        return -1;
    }
    db.commit();
    qDebug() << "good cmd search min size";
    return 0;
}

int bddRequest::searchSize(QString fileNamePartToSearch, QString size)
{
    setupDatabase();

    db.transaction();
    QSqlQuery query;
    QString queryPrepare = "SELECT * FROM files WHERE name LIKE '" + fileNamePartToSearch + "' AND WHERE size ='" + size + "'";
    qDebug() << queryPrepare;
    query.exec(queryPrepare);
    if(query.lastError().isValid()) {
        qDebug() << "err cmd search size";
        return -1;
    }
    db.commit();
    qDebug() << "good cmd search size";
    return 0;
}

int bddRequest::searchSizeBetween(QString fileNamePartToSearch, QString size1, QString size2)
{
    setupDatabase();

    db.transaction();
    QSqlQuery query;
    QString queryPrepare = "SELECT * FROM files WHERE name LIKE '" + fileNamePartToSearch + "' AND WHERE size BETWEEN '" + size1 + "' AND '" + size2 + "'";
    qDebug() << queryPrepare;
    query.exec(queryPrepare);
    if(query.lastError().isValid()) {
        qDebug() << "err cmd search size between";
        return -1;
    }
    db.commit();
    qDebug() << "good cmd search size between";
    return 0;
}

void bddRequest::selectAllFilesFromDB() {
    QSqlQuery query;
    query.exec(QString("SELECT * FROM files"));

    while (query.next()) {
        qDebug() << "TEST" << query.value(6).toString();
        emit dirsAdded(query.value(6).toString());
    }
    qDebug() << __LINE__ << __FUNCTION__ << "EMIT";
}
