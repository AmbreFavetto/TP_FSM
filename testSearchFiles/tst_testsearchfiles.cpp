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

    void test_maxSize();
    void test_minSize();
    void test_sizeSimple();
    void test_sizeSpecial();

    // INDEXER
    void test_indexer();
    // GET
    void test_get();
    // ADD
    void test_add();
    // PUSH
    void test_push();
    // CLEAR
    void test_clear();


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
    fsm = new LibraryFsm();
    fsm->stringToList("SEARCH xxx LAST_MODIFIED BETWEEN dd/mm/yyyy AND yyyy");

    // Result expected
    QMap<QString, QVariant> mapRef ;
    mapRef["cmd"] = "SEARCH";
    mapRef["filenamePart"] = "xxx";
    mapRef["option"] = "LAST_MODIFIED";
    mapRef["between"] = "BETWEEN";
    mapRef["date"] = "dd/mm/yyyy";
    mapRef["and"] = "AND";
    mapRef["date2"] = "yyyy";

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
void testSearchFiles::test_searchCreatedSimple()
{
    fsm = new LibraryFsm();
    fsm->stringToList("SEARCH xxx CREATED dd/mm/yyyy");

    // Result expected
    QMap<QString, QVariant> mapRef ;
    mapRef["cmd"] = "SEARCH";
    mapRef["filenamePart"] = "xxx";
    mapRef["option"] = "CREATED";
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
}

void testSearchFiles::test_searchCreatedSince()
{
    fsm = new LibraryFsm();
    fsm->stringToList("SEARCH xxx CREATED SINCE LAST 3 DAYS");

    // Result expected
    QMap<QString, QVariant> mapRef ;
    mapRef["cmd"] = "SEARCH";
    mapRef["filenamePart"] = "xxx";
    mapRef["option"] = "CREATED";
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

void testSearchFiles::test_searchCreatedAgo()
{
    fsm = new LibraryFsm();
    fsm->stringToList("SEARCH xxx CREATED 3 DAYS AGO");

    // Result expected
    QMap<QString, QVariant> mapRef ;
    mapRef["cmd"] = "SEARCH";
    mapRef["filenamePart"] = "xxx";
    mapRef["option"] = "CREATED";
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

void testSearchFiles::test_searchCreatedBetween()
{
    fsm = new LibraryFsm();
    fsm->stringToList("SEARCH xxx CREATED BETWEEN dd/mm/yyyy AND yyyy");

    // Result expected
    QMap<QString, QVariant> mapRef ;
    mapRef["cmd"] = "SEARCH";
    mapRef["filenamePart"] = "xxx";
    mapRef["option"] = "CREATED";
    mapRef["between"] = "BETWEEN";
    mapRef["date"] = "dd/mm/yyyy";
    mapRef["and"] = "AND";
    mapRef["date2"] = "yyyy";

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

void testSearchFiles::test_maxSize()
{
    fsm = new LibraryFsm();
    fsm->stringToList("SEARCH xxx MAX_SIZE 5M");

    // Result expected
    QMap<QString, QVariant> mapRef ;
    mapRef["cmd"] = "SEARCH";
    mapRef["filenamePart"] = "xxx";
    mapRef["option"] = "MAX_SIZE";
    mapRef["number"] = "5M";

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

void testSearchFiles::test_minSize()
{
    fsm = new LibraryFsm();
    fsm->stringToList("SEARCH xxx MIN_SIZE 5M");

    // Result expected
    QMap<QString, QVariant> mapRef ;
    mapRef["cmd"] = "SEARCH";
    mapRef["filenamePart"] = "xxx";
    mapRef["option"] = "MIN_SIZE";
    mapRef["number"] = "5M";

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

void testSearchFiles::test_sizeSimple()
{
    fsm = new LibraryFsm();
    fsm->stringToList("SEARCH xxx SIZE 5M");

    // Result expected
    QMap<QString, QVariant> mapRef ;
    mapRef["cmd"] = "SEARCH";
    mapRef["filenamePart"] = "xxx";
    mapRef["option"] = "SIZE";
    mapRef["number"] = "5M";

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

void testSearchFiles::test_sizeSpecial()
{
    fsm = new LibraryFsm();
    fsm->stringToList("SEARCH xxx SIZE BETWEEN 5M AND 6G");

    // Result expected
    QMap<QString, QVariant> mapRef ;
    mapRef["cmd"] = "SEARCH";
    mapRef["filenamePart"] = "xxx";
    mapRef["option"] = "SIZE";
    mapRef["between"] = "BETWEEN";
    mapRef["numberType"] = "5M";
    mapRef["and"] = "AND";
    mapRef["numberType2"] = "6G";

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

// TODO LIST EXT AND TYPE ???

void testSearchFiles::test_indexer()
{
    fsm = new LibraryFsm();
    fsm->stringToList("INDEXER STATUS");

    // Result expected
    QMap<QString, QVariant> mapRef ;
    mapRef["cmd"] = "INDEXER";
    mapRef["action"] = "STATUS";

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

void testSearchFiles::test_get()
{
    fsm = new LibraryFsm();
    fsm->stringToList("GET WHITELIST");

    // Result expected
    QMap<QString, QVariant> mapRef ;
    mapRef["cmd"] = "GET";
    mapRef["flag"] = "WHITELIST";

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

void testSearchFiles::test_add()
{
    fsm = new LibraryFsm();
    fsm->stringToList("ADD WHITELIST xxx");

    // Result expected
    QMap<QString, QVariant> mapRef ;
    mapRef["cmd"] = "ADD";
    mapRef["flag"] = "WHITELIST";
    mapRef["path"] = "xxx";

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

// TODO régler pb plusieurs fichiers
void testSearchFiles::test_push()
{
    fsm = new LibraryFsm();
    fsm->stringToList("PUSH WHITELIST xxx DONE");

    // Result expected
    QMap<QString, QVariant> mapRef ;
    mapRef["cmd"] = "PUSH";
    mapRef["flag"] = "WHITELIST";
    mapRef["path"] = "xxx";
    mapRef["done"] = "DONE";

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

void testSearchFiles::test_clear()
{
    fsm = new LibraryFsm();
    fsm->stringToList("CLEAR WHITELIST");

    // Result expected
    QMap<QString, QVariant> mapRef ;
    mapRef["cmd"] = "CLEAR";
    mapRef["flag"] = "WHITELIST";

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

QTEST_APPLESS_MAIN(testSearchFiles)

#include "tst_testsearchfiles.moc"
