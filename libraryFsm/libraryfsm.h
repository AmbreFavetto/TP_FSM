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
        SearchOptionExtExt,
        SearchOptionExtExtOr,

        SearchOptionType,
        SearchOptionTypeType,
        SearchOptionTypeTypeOr,

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

    QStringList correctActions = { "ADD", "PUSH", "CLEAR", "GET", "SEARCH", "INDEXER"};
    QStringList correctFlags = { "WHITELIST","BLACKLIST","FILTERS","SKIPPED_FILTERSADD"};
    QStringList correctStatus = { "INDEXING","READY","STOPPED","PAUSED","QUERYING", "RESULTS_AVAILABLE"};
    QStringList correctOptions = { "STATUS","START","STOP","PAUSE","RESUME"};

    QStringList correctTimes = {"MINUTES","HOURS","DAYS","MONTHS","YEAR"};
    QMap<QString, QVariant> values;

    public:
        LibraryFsm();

        void stringToList(QString line);

        bool isAction(QString const& str);
        bool isFlag(QString const& str);
        bool isStatus(QString const& str);
        bool isOption(QString const& str);

        bool isDate(QString const& str);
        bool isNumber(QString const& str);
        bool isNumberType(QString const& str);
        bool isTime(QString const& str);
        bool isExt(QString const& str);
        bool isType(QString const& str);

        void createMapping(QStringList list);
        void checkState(states previousState, states nextState, bool condition, stateFn fn);

        const QMap<QString, QVariant> &getValues() const;
        void setValues(const QMap<QString, QVariant> &newValues);

        void setValue(QString key, QVariant value);
        QVariant getValue(QString key);

        QStringList getListTokens();
};

#endif // LIBRARYFSM_H
