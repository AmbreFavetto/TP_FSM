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

    void test_extComa();
    void test_extOr();

    void test_typeComa();
    void test_typeOr();

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
    fsm->stringToList("SEARCH xxx LAST_MODIFIED 06/12/2000");

    // Result expected
    QMap<QString, QVariant> mapRef ;
    mapRef["cmd"] = "SEARCH";
    mapRef["filenamePart"] = "xxx";
    mapRef["option"] = "LAST_MODIFIED";
    mapRef["date"] = "06/12/2000";

    listTokens = fsm->getListTokens();
    fsm->createMapping(listTokens);
    QMap<QString, QVariant> map = fsm->getValues();

    QCOMPARE(mapRef.values(), map.values());
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

    listTokens = fsm->getListTokens();
    fsm->createMapping(listTokens);
    QMap<QString, QVariant> map = fsm->getValues();

    QCOMPARE(mapRef.values(), map.values());
}

void testSearchFiles::test_searchLastModifiedBetween()
{
    fsm = new LibraryFsm();
    fsm->stringToList("SEARCH xxx LAST_MODIFIED BETWEEN 07/12/2000 AND 2021");

    // Result expected
    QMap<QString, QVariant> mapRef ;
    mapRef["cmd"] = "SEARCH";
    mapRef["filenamePart"] = "xxx";
    mapRef["option"] = "LAST_MODIFIED";
    mapRef["between"] = "BETWEEN";
    mapRef["date"] = "07/12/2000";
    mapRef["and"] = "AND";
    mapRef["date2"] = "2021";

    listTokens = fsm->getListTokens();
    fsm->createMapping(listTokens);
    QMap<QString, QVariant> map = fsm->getValues();

    QCOMPARE(mapRef.values(), map.values());
}
void testSearchFiles::test_searchCreatedSimple()
{
    fsm = new LibraryFsm();
    fsm->stringToList("SEARCH xxx CREATED 20/02/2004");

    // Result expected
    QMap<QString, QVariant> mapRef ;
    mapRef["cmd"] = "SEARCH";
    mapRef["filenamePart"] = "xxx";
    mapRef["option"] = "CREATED";
    mapRef["date"] = "20/02/2004";

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

    listTokens = fsm->getListTokens();
    fsm->createMapping(listTokens);
    QMap<QString, QVariant> map = fsm->getValues();

    QCOMPARE(mapRef.values(), map.values());
}

void testSearchFiles::test_searchCreatedBetween()
{
    fsm = new LibraryFsm();
    fsm->stringToList("SEARCH xxx CREATED BETWEEN 20/03/1999 AND 2025");

    // Result expected
    QMap<QString, QVariant> mapRef ;
    mapRef["cmd"] = "SEARCH";
    mapRef["filenamePart"] = "xxx";
    mapRef["option"] = "CREATED";
    mapRef["between"] = "BETWEEN";
    mapRef["date"] = "20/03/1999";
    mapRef["and"] = "AND";
    mapRef["date2"] = "2025";

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

    listTokens = fsm->getListTokens();
    fsm->createMapping(listTokens);
    QMap<QString, QVariant> map = fsm->getValues();

    QCOMPARE(mapRef.values(), map.values());
}

void testSearchFiles::test_extComa()
{
    fsm = new LibraryFsm();
    fsm->stringToList("SEARCH xxx EXT aaa, bbb, ccc");

    // list ext expected
    QStringList listRef;
    listRef << "aaa,"<< "bbb," << "ccc";

    // Result expected
    QMap<QString, QVariant> mapRef ;
    mapRef["cmd"] = "SEARCH";
    mapRef["filenamePart"] = "xxx";
    mapRef["option"] = "EXT";
    mapRef["ext"] = listRef;

    listTokens = fsm->getListTokens();
    fsm->createMapping(listTokens);
    QMap<QString, QVariant> map = fsm->getValues();

    QCOMPARE(mapRef.values(), map.values());
}

void testSearchFiles::test_extOr()
{
    fsm = new LibraryFsm();
    fsm->stringToList("SEARCH xxx EXT aaa OR bbb OR ccc");

    // list ext expected
    QStringList listRef;
    listRef << "aaa"<< "bbb" << "ccc";

    // Result expected
    QMap<QString, QVariant> mapRef ;
    mapRef["cmd"] = "SEARCH";
    mapRef["filenamePart"] = "xxx";
    mapRef["option"] = "EXT";
    mapRef["ext"] = listRef;
    mapRef["or"] = "OR";

    listTokens = fsm->getListTokens();
    fsm->createMapping(listTokens);
    QMap<QString, QVariant> map = fsm->getValues();

    QCOMPARE(mapRef.values(), map.values());
}

void testSearchFiles::test_typeComa()
{
    fsm = new LibraryFsm();
    fsm->stringToList("SEARCH xxx TYPE aaa, bbb, ccc");

    // list ext expected
    QStringList listRef;
    listRef << "aaa,"<< "bbb," << "ccc";

    // Result expected
    QMap<QString, QVariant> mapRef ;
    mapRef["cmd"] = "SEARCH";
    mapRef["filenamePart"] = "xxx";
    mapRef["option"] = "TYPE";
    mapRef["type"] = listRef;

    listTokens = fsm->getListTokens();
    fsm->createMapping(listTokens);
    QMap<QString, QVariant> map = fsm->getValues();

    QCOMPARE(mapRef.values(), map.values());
}

void testSearchFiles::test_typeOr()
{
    fsm = new LibraryFsm();
    fsm->stringToList("SEARCH xxx TYPE aaa OR bbb OR ccc");

    // list ext expected
    QStringList listRef;
    listRef << "aaa"<< "bbb" << "ccc";

    // Result expected
    QMap<QString, QVariant> mapRef ;
    mapRef["cmd"] = "SEARCH";
    mapRef["filenamePart"] = "xxx";
    mapRef["option"] = "TYPE";
    mapRef["type"] = listRef;
    mapRef["or"] = "OR";

    listTokens = fsm->getListTokens();
    fsm->createMapping(listTokens);
    QMap<QString, QVariant> map = fsm->getValues();

    QCOMPARE(mapRef.values(), map.values());
}


void testSearchFiles::test_indexer()
{
    fsm = new LibraryFsm();
    fsm->stringToList("INDEXER STATUS");

    // Result expected
    QMap<QString, QVariant> mapRef ;
    mapRef["cmd"] = "INDEXER";
    mapRef["action"] = "STATUS";

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

    listTokens = fsm->getListTokens();
    fsm->createMapping(listTokens);
    QMap<QString, QVariant> map = fsm->getValues();

    QCOMPARE(mapRef.values(), map.values());
}

void testSearchFiles::test_push()
{
    fsm = new LibraryFsm();
    fsm->stringToList("PUSH WHITELIST C:/xxx/yyy D:/abc C:/abc/xxx DONE");

    // list ext expected
    QStringList listRef;
    listRef << "C:/xxx/yyy" << "D:/abc" << "C:/abc/xxx";

    // Result expected
    QMap<QString, QVariant> mapRef ;
    mapRef["cmd"] = "PUSH";
    mapRef["flag"] = "WHITELIST";
    mapRef["path"] = listRef;
    mapRef["done"] = "DONE";

    listTokens = fsm->getListTokens();
    fsm->createMapping(listTokens);
    QMap<QString, QVariant> map = fsm->getValues();

    QStringList listPath = fsm->getListElts();
    qDebug() << "REF 0" << listRef.value(0) << "REF 1" <<listRef.value(1) << "REF 2" <<listRef.value(2) ;
    qDebug() << "REAL 0" << listPath.value(0) << "REAL 1" <<listPath.value(1) << "REAL 2" <<listPath.value(2) ;
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

    listTokens = fsm->getListTokens();
    fsm->createMapping(listTokens);
    QMap<QString, QVariant> map = fsm->getValues();

    QCOMPARE(mapRef.values(), map.values());
}

QTEST_APPLESS_MAIN(testSearchFiles)

#include "tst_testsearchfiles.moc"
