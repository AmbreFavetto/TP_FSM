#ifndef FSM_H
#define FSM_H

#include <QtWidgets/QMainWindow>
#include <QDebug>
#include <QList>

#include "parser.h"

typedef std::function<void()> stateFn;
class Fsm
        //:public QMainWindow
{
    Q_OBJECT

    // differents states of the fsm
    enum states {
        Initial,
        CommandFound,
        // Errors
        ErrUnknownCmd,

        // Search
        Search,
        SearchFilenamePart,
        SearchOptions,
        SearchOptionLastModified,
        SearchOptionCreated,
        SearchOptionMaxSize,
        SearchOptionMinSize,
        SearchOptionSize,
        SearchOptionExt,
        SearchOptionType,
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
    QStringList correctOptions = { "STATUS","START","STOP","PAUSE","RESUME"};

    QMap<QString, QVariant> values;

    public:
        Fsm();


        //bool isNumber(QString const& str);
        //bool isOperator(QString const& str);
        //bool isWord(QString const& str);

        void stringToList(QString line);

        //int current_state() const;

        //bool CheckState(int from, int to, bool condition);

        bool isAction(QString const& str);
        bool isFlag(QString const& str);
        bool isOptions(QString const& str);

        void createMapping(QStringList list);
        void checkState(states previousState, states nextState, bool condition, stateFn fn);

        const QMap<QString, QVariant> &getValues() const;
        void setValues(const QMap<QString, QVariant> &newValues);

        void setValue(QString key, QVariant value);
        QVariant getValue(QString key);
};

#endif // FSM_H
