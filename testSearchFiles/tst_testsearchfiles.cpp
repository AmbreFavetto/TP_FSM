#include <QMap>
#include <QtTest>
#include "../libraryFsm/libraryfsm.h"

// add necessary includes here

class testSearchFiles : public QObject
{
    Q_OBJECT
    QStringList listTokens;
    LibraryFsm * fsm;

public:
    testSearchFiles();
    ~testSearchFiles();

private slots:
    // Search
    void test_searchLastModifiedSimple();
    void test_searchLastModifiedSince();
    void test_searchLastModifiedAgo();
    void test_searchLastModifiedBetween();

    void test_searchCreatedSimple();
    void test_searchCreatedSince();
    void test_searchCreatedAgo();
    void test_searchCreatedBetween();



};

testSearchFiles::testSearchFiles()
{

}

testSearchFiles::~testSearchFiles()
{

}

void testSearchFiles::test_searchLastModifiedSimple()
{
    fsm = new LibraryFsm();
    fsm->stringToList("SEARCH xxx LAST_MODIFIED dd/mm/yyyy");

    // Result expected
    QMap<QString, QVariant> mapRef ;
    mapRef["cmd"] = "SEARCH";
    mapRef["filenamePart"] = "xxx";
    mapRef["option"] = "LAST_MODIFIED";
    mapRef["date"] = "dd/mm/yyyy";

    // wrong result
    QMap<QString, QVariant> wrongMap ;
    wrongMap["cmd"] = "coucou";
    wrongMap["filenamePart"] = "no";
    wrongMap["option"] = "stop";
    wrongMap["date"] = "test";

    listTokens = fsm->getListTokens();
    fsm->createMapping(listTokens);
    QMap<QString, QVariant> map = fsm->getValues();

    QCOMPARE(mapRef.values(), map.values());
    //QCOMPARE(wrongMap.values(), map.values());

}

void testSearchFiles::test_searchLastModifiedSince()
{
    fsm = new LibraryFsm();
    fsm->stringToList("SEARCH xxx LAST_MODIFIED SINCE LAST 3 DAYS");

    // Result expected
    QMap<QString, QVariant> mapRef ;
    mapRef["cmd"] = "SEARCH";
    mapRef["filenamePart"] = "xxx";
    mapRef["option"] = "LAST_MODIFIED";
    mapRef["since"] = "SINCE";
    mapRef["last"] = "LAST";
    mapRef["number"] = "3";
    mapRef["time"] = "DAYS";

    // wrong result
    QMap<QString, QVariant> wrongMap ;
    wrongMap["cmd"] = "coucou";
    wrongMap["filenamePart"] = "no";
    wrongMap["option"] = "stop";
    wrongMap["date"] = "test";

    listTokens = fsm->getListTokens();
    fsm->createMapping(listTokens);
    QMap<QString, QVariant> map = fsm->getValues();

    QCOMPARE(mapRef.values(), map.values());

}
void testSearchFiles::test_searchLastModifiedAgo()
{
    fsm = new LibraryFsm();
    fsm->stringToList("SEARCH xxx LAST_MODIFIED 3 DAYS AGO");

    // Result expected
    QMap<QString, QVariant> mapRef ;
    mapRef["cmd"] = "SEARCH";
    mapRef["filenamePart"] = "xxx";
    mapRef["option"] = "LAST_MODIFIED";
    mapRef["number"] = "3";
    mapRef["time"] = "DAYS";
    mapRef["ago"] = "AGO";

    // wrong result
    QMap<QString, QVariant> wrongMap ;
    wrongMap["cmd"] = "coucou";
    wrongMap["filenamePart"] = "no";
    wrongMap["option"] = "stop";
    wrongMap["date"] = "test";

    listTokens = fsm->getListTokens();
    fsm->createMapping(listTokens);
    QMap<QString, QVariant> map = fsm->getValues();

    QCOMPARE(mapRef.values(), map.values());
}
void testSearchFiles::test_searchLastModifiedBetween()
{

}
void testSearchFiles::test_searchCreatedSimple()
{

}
void testSearchFiles::test_searchCreatedSince()
{

}
void testSearchFiles::test_searchCreatedAgo()
{

}
void testSearchFiles::test_searchCreatedBetween()
{

}


QTEST_APPLESS_MAIN(testSearchFiles)

#include "tst_testsearchfiles.moc"
