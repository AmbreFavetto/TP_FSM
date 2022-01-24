#ifndef LIBRARYFSM_H
#define LIBRARYFSM_H

#include <QtWidgets/QMainWindow>
#include <QDebug>
#include <QList>
#include "libraryFsm_global.h"

typedef std::function<void()> stateFn;
class LIBRARYFSM_EXPORT LibraryFsm
{
    //Q_OBJECT

    // differents states of the fsm
    enum states {
        Initial,
        CommandFound,
        // Errors
        ErrUnknownCmd,

        // Search
        Search,
        SearchFilenamePart,
        SearchOptionLastModified,
        SearchOptionCreated,

        SearchOptionSimpleDate,
        SearchOptionSince,
        SearchOptionSinceLast,
        SearchOptionSinceLastNumber,
        SearchOptionSinceLastNumberTime,
        SearchOptionNumber,
        SearchOptionNumberTime,
        SearchOptionNumberTimeAgo,
        SearchOptionBetween,
        SearchOptionBetweenSimpleDate,
        SearchOptionBetweenSimpleDateAnd,
        SearchOptionBetweenSimpleDateAndSimpleDate,

        SearchOptionMaxSize,
        SearchOptionMinSize,
        SearchOptionSize,
        SearchOptionSizeNumberType,
        SearchOptionSizeBetween,
        SearchOptionSizeBetweenNumberType,
        SearchOptionSizeBetweenNumberTypeAnd,
        SearchOptionSizeBetweenNumberTypeAndNumberType,

        SearchOptionExt,
        SearchOptionExtListExt,
        SearchOptionExtExt,
        SearchOptionExtExtOr,
        SearchOptionExtListExtFinal,

        SearchOptionType,
        SearchOptionTypeListType,
        SearchOptionTypeType,
        SearchOptionTypeTypeOr,
        SearchOptionTypeListTypeFinal,

        // Errors
        ErrBadFilenamePart,
        ErrUnknownSearchOption,

        // Status
        Status,
        ServerStatus,
        // Errors
        ErrUnknownServerStatus,

        // Indexer
        Indexer,
        IndexerCmd,
        // Errors
        ErrUnknownIndexerCmd,

        // Clear
        Clear,
        ClearEntity,

        // Get
        Get,
        GetEntity,

        // Add
        Add,
        AddEntity,
        AddEntityPath,
        // Errors
        ErrUnknownEntity,

        // Push
        Push,
        PushEntity,
        PushEntityPath,
        PushEntityDone,
        PushDone,
        // Errors
        ErrMissingOrBadPath

    };


    QStringList listTokens;
    QString currentToken;
    states currentState;
    QStringList listElts;

    QStringList correctCmd = { "ADD", "PUSH", "CLEAR", "GET", "SEARCH", "INDEXER"};
    QStringList correctFlags = { "WHITELIST","BLACKLIST","FILTERS","SKIPPED_FILTERS"};
    QStringList correctStatus = { "INDEXING","READY","STOPPED","PAUSED","QUERYING", "RESULTS_AVAILABLE"};
    QStringList correctActions = { "STATUS","START","STOP","PAUSE","RESUME"};
    QStringList correctTimes = {"MINUTES","HOURS","DAYS","MONTHS","YEAR"};

    QMap<QString, QVariant> values;
    QString path;

    public:
        LibraryFsm(QString path);

        void stringToList(QString line);

        bool isCmd(QString const& str);
        bool isFlag(QString const& str);
        bool isStatus(QString const& str);
        bool isAction(QString const& str);

        bool isDate(QString const& str);
        bool isFileName(const QString &str);
        bool isNumber(QString const& str);
        bool isNumberType(QString const& str);
        bool isTime(QString const& str);
        bool isExt(QString const& str);
        bool isListExt(QString const& str);
        bool isType(QString const& str);
        bool isListType(QString const& str);
        bool isPath(QString const& str);

        void addEltToList(QString const& str);

        void createMapping();
        void checkState(states previousState, states nextState, bool condition, stateFn fn);

        const QMap<QString, QVariant> &getValues() const;
        void setValues(const QMap<QString, QVariant> &newValues);

        void setValue(QString key, QVariant value);
        QVariant getValue(QString key);

        QStringList getListTokens();
        const QStringList &getListElts() const;
        void setListElts(const QStringList &newListElts);
};

#endif // LIBRARYFSM_H
