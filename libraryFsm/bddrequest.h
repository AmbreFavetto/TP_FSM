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

class bddRequest : public QObject
{
    Q_OBJECT
    QThreadPool _pool;
public:
    /* Constructeur */
    bddRequest();

    /* Base de donnees */
    QSqlDatabase db;

    /* Chemin vers le dossier ../AppData/Roaming/contacts pour stock toutes les données relatives au TP */
    QString appDataLocation;

    /* Fonction qui crée la base de données pour préparer son utilisation */
    int setupDatabase();

    /* Fonction permettant l'ajout de nouvelles données dans la table, prend en parametre une liste de données d'une ligne sous la forme
    {"id","name", "flag", "date_creation","date_modification","size","type"} renvoie 0 si l'ajout est passé -1 sinon */
    int addRow(QStringList data);
    int extractFileInfo(QFileInfo file);
    // Methodes permettant d'appeler les requetes sql correspondantes aux commandes entrées par l'utilisateur
    int directoryIterator(QString dirPathName);   
    int clear(QString flagToClear);
    int add(QString flagToAdd, QString files);
    int get(QString flagToGet);
    int searchLastModifiedSimple(QString fileNamePartToSearch, QString date);
    int searchLastModifiedSinceLast(QString fileNamePartToSearch, QString date, QString TimeUnit);
    int searchLastModifiedBetween(QString fileNamePartToSearch, QString date1, QString date2);
    int searchCreateSimple(QString fileNamePartToSearch, QString date);
    int searchCreateSinceLast(QString fileNamePartToSearch, QString date, QString TimeUnit);
    int searchCreateBetween(QString fileNamePartToSearch, QString date1, QString date2);
    int searchMaxSize(QString fileNamePartToSearch, QString size);
    int searchMinSize(QString fileNamePartToSearch, QString size);
    int searchSize(QString fileNamePartToSearch, QString size);
    int searchSizeBetween(QString fileNamePartToSearch, QString size1, QString size2);

    // Affiche tous les fichiers présents en bd
    void selectAllFilesFromDB();

signals:
    void dirsAdded(const QString &);
};

#endif // BDDREQUEST_H
