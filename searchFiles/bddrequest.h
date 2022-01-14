#ifndef BDDREQUEST_H
#define BDDREQUEST_H
#include <QString>
#include <QStringList>
#include <QThread>
#include <QSqlDatabase>
#include <QSqlError>
#include <QStandardPaths>
#include <QDebug>
#include <QString>
#include <QDir>
#include <QSqlQuery>
#include <QElapsedTimer>
#include <QThreadPool>
#include <QtConcurrent>

class bddRequest
{
    QThreadPool _pool;
public:
    /* Constructeur */
    bddRequest();

    /* Base de donnees */
    QSqlDatabase db;

    /* Chemin vers le dossier ../AppData/Roaming/contacts pour stock toutes les données relatives au TP */
    QString appDataLocation;

    /* Fonction qui créé la base de données pour préparer son utilisation */
    int setupDatabase();

    /* Fonction permettant l'ajout de nouvelles données dans la table, prend en parametre  une liste des données d'une ligne sous la forme
    {"id","name","date_creation","date_modification","size","type"} renvoye 0 si l'ajout est passé -1 sinon*/
    int addRow(QStringList data);

    int extractFileInfo(QFileInfo file);

    int directoryIterator(QString dirPathName);

};

#endif // BDDREQUEST_H
