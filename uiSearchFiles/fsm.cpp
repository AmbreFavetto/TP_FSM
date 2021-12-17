#include "fsm.h"

#include <QDebug>


Fsm::Fsm()
{

}


// Split the sentence written by the user into several tokens
void Fsm::stringToList(QString line)
{
    listTokens = line.split(" ");
}

const QMap<QString, QVariant> &Fsm::getValues() const
{
    return values;
}

void Fsm::setValues(const QMap<QString, QVariant> &newValues)
{
    values = newValues;
}


QVariant Fsm::getValue(QString key)
{
    return values[key];
}

void Fsm::setValue(QString key, QVariant value)
{
    //values[key] = value;
    values.insert(key, value);
}

// "ADD", "PUSH", "CLEAR", "GET", "SEARCH", "INDEXER"
bool Fsm::isAction(const QString &str)
{
    if(correctActions.contains(str)) return true;

    return false;

}

// "WHITELIST","BLACKLIST","FILTERS","SKIPPED_FILTERSADD"
bool Fsm::isFlag(const QString &str)
{
    if(correctFlags.contains(str)) return true;

    return false;
}

// "STATUS","START","STOP","PAUSE","RESUME"
bool Fsm::isOptions(const QString &str)
{
    if(correctOptions.contains(str)) return true;

    return false;
}

void Fsm::createMapping(QStringList list)
{
    auto listIterator = list.begin();
    currentToken = *listIterator;
    while(listIterator != list.end()) {
        currentToken = *listIterator;

        // SEARCH
        checkState(CommandFound, Search, currentToken.toUpper()=="SEARCH", [=](){setValue("cmd", currentToken.toUpper());});
        checkState(Search, SearchFilenamePart, !currentToken.isEmpty(), [=](){setValue("filenamePart", currentToken);});
        //      ~LAST_MODIFIED
        checkState(SearchFilenamePart, SearchOptionLastModified, currentToken.toUpper()=="LAST_MODIFIED", [=](){setValue("option", currentToken.toUpper());});
        checkState(SearchOptionLastModified, SearchOptionSimpleDate, isDate(currentToken), [=](){setValue("date", currentToken);});
        checkState(SearchOptionLastModified, SearchOptionSince, currentToken.toUpper()=="SINCE", [=](){setValue("elt", currentToken.toUpper());});
        checkState(SearchOptionLastModified, SearchOptionNumber, isNumber(currentToken), [=](){setValue("number", currentToken);});
        checkState(SearchOptionLastModified, SearchOptionBetween, currentToken.toUpper()=="BETWEEN", [=](){setValue("elt", currentToken.toUpper());});
        //      ~CREATED
        checkState(SearchFilenamePart, SearchOptionCreated, currentToken.toUpper()=="CREATED", [=](){setValue("option", currentToken.toUpper());});
        checkState(SearchOptionCreated, SearchOptionSimpleDate, isDate(currentToken), [=](){setValue("date", currentToken);});
        checkState(SearchOptionCreated, SearchOptionSince, currentToken.toUpper()=="SINCE", [=](){setValue("elt", currentToken.toUpper());});
        checkState(SearchOptionCreated, SearchOptionNumber, isNumber(currentToken), [=](){setValue("number", currentToken);});
        checkState(SearchOptionCreated, SearchOptionBetween, currentToken.toUpper()=="BETWEEN", [=](){setValue("elt", currentToken.toUpper());});
        //      ~LAST_MODIFIED & CREATED
        checkState(SearchOptionSince, SearchOptionSinceLast, currentToken.toUpper()=="LAST", [=](){setValue("elt", currentToken.toUpper());});
        checkState(SearchOptionSinceLast, SearchOptionSinceLastNumber, isNumber(currentToken), [=](){setValue("number", currentToken);});
        checkState(SearchOptionSinceLastNumber, SearchOptionSinceLastNumberTime, isTime(currentToken.toUpper()), [=](){setValue("time", currentToken.toUpper());});
        checkState(SearchOptionNumber, SearchOptionNumberTime, isTime(currentToken), [=](){setValue("time", currentToken);});
        checkState(SearchOptionNumberTime, SearchOptionNumberTimeAgo, currentToken.toUpper()=="AGO", [=](){setValue("elt", currentToken.toUpper());});
        checkState(SearchOptionBetween, SearchOptionBetweenSimpleDate, isDate(currentToken), [=](){setValue("date", currentToken);});
        checkState(SearchOptionBetweenSimpleDate, SearchOptionBetweenSimpleDateAnd, currentToken.toUpper()=="AND", [=](){setValue("elt", currentToken.toUpper());});
        checkState(SearchOptionBetweenSimpleDateAnd, SearchOptionBetweenSimpleDateAndSimpleDate, isDate(currentToken), [=](){setValue("date", currentToken);});
        //      ~MAX_SIZE
        checkState(SearchFilenamePart, SearchOptionMaxSize, currentToken.toUpper()=="MAX_SIZE", [=](){setValue("option", currentToken.toUpper());});
        checkState(SearchOptionMaxSize, SearchOptionSizeNumber, isNumber(currentToken), [=](){setValue("number", currentToken);});
        //      ~MIN_SIZE
        checkState(SearchFilenamePart, SearchOptionMinSize, currentToken.toUpper()=="MIN_SIZE", [=](){setValue("option", currentToken.toUpper());});
        checkState(SearchOptionMinSize, SearchOptionSizeNumber, isNumber(currentToken), [=](){setValue("number", currentToken);});
        //      ~SIZE
        checkState(SearchOptionSize, SearchOptionSizeBetween, currentToken.toUpper()=="BETWEEN", [=](){setValue("elt", currentToken.toUpper());});
        checkState(SearchOptionSizeBetween, SearchOptionSizeBetweenNumber, isNumber(currentToken), [=](){setValue("number", currentToken);});
        checkState(SearchOptionSizeBetweenNumber, SearchOptionSizeBetweenNumberType, isType(currentToken.toUpper()), [=](){setValue("type", currentToken.toUpper());});
        checkState(SearchOptionSizeBetweenNumberType, SearchOptionSizeBetweenNumberTypeAnd, currentToken.toUpper()=="AND", [=](){setValue("elt", currentToken.toUpper());});
        checkState(SearchOptionSizeBetweenNumberTypeAnd, SearchOptionSizeBetweenNumberTypeAndNumber, isNumber(currentToken), [=](){setValue("number", currentToken);});
        checkState(SearchOptionSizeBetweenNumberTypeAndNumber, SearchOptionSizeBetweenNumberTypeAndNumberType, isType(currentToken.toUpper()), [=](){setValue("type", currentToken.toUpper());});
        //      ~SIZE & MAX_SIZE & MIN_SIZE
        checkState(SearchFilenamePart, SearchOptionSize, currentToken.toUpper()=="SIZE", [=](){setValue("option", currentToken.toUpper());});
        checkState(SearchOptionSize, SearchOptionSizeNumber, isNumber(currentToken), [=](){setValue("number", currentToken);});
        checkState(SearchOptionSizeNumber, SearchOptionSizeNumberType, isType(currentToken), [=](){setValue("type", currentToken);});
        //      ~EXT
        checkState(SearchFilenamePart, SearchOptionExt, currentToken.toUpper()=="EXT", [=](){setValue("option", currentToken.toUpper());});
        checkState(SearchOptionExt, SearchOptionExtExt, isExt(currentToken), [=](){setValue("ext", currentToken);});
        checkState(SearchOptionExtExt, SearchOptionExtExt, isExt(currentToken), [=](){setValue("ext", currentToken);});
        checkState(SearchOptionExtExt, SearchOptionExtExtOr, currentToken.toUpper()=="OR", [=](){setValue("elt", currentToken.toUpper());});
        //      ~TYPE
        checkState(SearchFilenamePart, SearchOptionType, currentToken.toUpper()=="TYPE", [=](){setValue("option", currentToken.toUpper());});
        checkState(SearchOptionType, SearchOptionTypeType, isType(currentToken), [=](){setValue("type", currentToken);});
        checkState(SearchOptionTypeType, SearchOptionTypeType, isType(currentToken), [=](){setValue("type", currentToken);});
        checkState(SearchOptionTypeType, SearchOptionTypeTypeOr, currentToken.toUpper()=="OR", [=](){setValue("elt", currentToken.toUpper());});
        // Status
        checkState(CommandFound, Status, currentToken.toUpper()=="STATUS", [=](){setValue("cmd", currentToken.toUpper());});
        checkState(Status, ServerStatus, currentToken.toUpper()=="INDEXING", [=](){setValue("serverStatus", currentToken.toUpper());});
        checkState(Status, ServerStatus, currentToken.toUpper()=="READY", [=](){setValue("serverStatus", currentToken.toUpper());});
        checkState(Status, ServerStatus, currentToken.toUpper()=="STOPPED", [=](){setValue("serverStatus", currentToken.toUpper());});
        checkState(Status, ServerStatus, currentToken.toUpper()=="PAUSED", [=](){setValue("serverStatus", currentToken.toUpper());});
        checkState(Status, ServerStatus, currentToken.toUpper()=="QUERYING", [=](){setValue("serverStatus", currentToken.toUpper());});
        checkState(Status, ServerStatus, currentToken.toUpper()=="RESULTS_AVAILABLE", [=](){setValue("serverStatus", currentToken.toUpper());});
        // Indexer
        checkState(CommandFound, Indexer, currentToken.toUpper()=="INDEXER", [=](){setValue("cmd", currentToken.toUpper());});
        //checkState(Indexer, IndexerCmd, isFlag(currentToken.toUpper()), [=](){setValue("flag", currentToken.toUpper());});
        checkState(Indexer, IndexerCmd, currentToken.toUpper() == "STATUS", [=](){setValue("indexerCmd", currentToken.toUpper());});
        checkState(Indexer, IndexerCmd, currentToken.toUpper() == "START", [=](){setValue("indexerCmd", currentToken.toUpper());});
        checkState(Indexer, IndexerCmd, currentToken.toUpper() == "STOP", [=](){setValue("indexerCmd", currentToken.toUpper());});
        checkState(Indexer, IndexerCmd, currentToken.toUpper() == "PAUSE", [=](){setValue("indexerCmd", currentToken.toUpper());});
        checkState(Indexer, IndexerCmd, currentToken.toUpper() == "RESUME", [=](){setValue("indexerCmd", currentToken.toUpper());});
        // Clear
        checkState(CommandFound, Clear, currentToken.toUpper()=="CLEAR", [=](){setValue("cmd", currentToken.toUpper());});
        //checkState(Clear, ClearEntity, isFlag(currentToken.toUpper()), [=](){setValue("flag", currentToken.toUpper());});
        checkState(Clear, ClearEntity, currentToken.toUpper() == "WHITELIST", [=](){setValue("flag", currentToken.toUpper());});
        checkState(Clear, ClearEntity, currentToken.toUpper() == "BLACKLIST", [=](){setValue("flag", currentToken.toUpper());});
        checkState(Clear, ClearEntity, currentToken.toUpper() == "FILTERS", [=](){setValue("flag", currentToken.toUpper());});
        checkState(Clear, ClearEntity, currentToken.toUpper() == "SKIPPED_FILTERS", [=](){setValue("flag", currentToken.toUpper());});
        // Get
        checkState(CommandFound, Get, currentToken.toUpper()=="GET", [=](){setValue("cmd", currentToken.toUpper());});
        //checkState(Get, GetEntity, isFlag(currentToken.toUpper()), [=](){setValue("flag", currentToken.toUpper());});
        checkState(Get, GetEntity, currentToken.toUpper() == "WHITELIST", [=](){setValue("flag", currentToken.toUpper());});
        checkState(Get, GetEntity, currentToken.toUpper() == "BLACKLIST", [=](){setValue("flag", currentToken.toUpper());});
        checkState(Get, GetEntity, currentToken.toUpper() == "FILTERS", [=](){setValue("flag", currentToken.toUpper());});
        checkState(Get, GetEntity, currentToken.toUpper() == "SKIPPED_FILTERS", [=](){setValue("flag", currentToken.toUpper());});
        // Add
        checkState(CommandFound, Add, currentToken.toUpper()=="ADD", [=](){setValue("cmd", currentToken.toUpper());});
        //checkState(Add, AddEntity, isFlag(currentToken.toUpper()), [=](){setValue("flag", currentToken.toUpper());});
        checkState(Add, AddEntity, currentToken.toUpper() == "WHITELIST", [=](){setValue("flag", currentToken.toUpper());});
        checkState(Add, AddEntity, currentToken.toUpper() == "BLACKLIST", [=](){setValue("flag", currentToken.toUpper());});
        checkState(Add, AddEntity, currentToken.toUpper() == "FILTERS", [=](){setValue("flag", currentToken.toUpper());});
        checkState(Add, AddEntity, currentToken.toUpper() == "SKIPPED_FILTERS", [=](){setValue("flag", currentToken.toUpper());});
        checkState(AddEntity, AddEntityPath, !currentToken.isEmpty(), [=](){setValue("path", currentToken);});

        // Push
        checkState(CommandFound, Push, currentToken.toUpper()=="PUSH", [=](){setValue("cmd", currentToken.toUpper());});
        //checkState(Push, PushEntity, isFlag(currentToken.toUpper()), [=](){setValue("flag", currentToken.toUpper());});
        checkState(Push, PushEntity, currentToken.toUpper() == "WHITELIST", [=](){setValue("flag", currentToken.toUpper());});
        checkState(Push, PushEntity, currentToken.toUpper() == "BLACKLIST", [=](){setValue("flag", currentToken.toUpper());});
        checkState(Push, PushEntity, currentToken.toUpper() == "FILTERS", [=](){setValue("flag", currentToken.toUpper());});
        checkState(Push, PushEntity, currentToken.toUpper() == "SKIPPED_FILTERS", [=](){setValue("flag", currentToken.toUpper());});
        checkState(PushEntity, PushEntityPath, !currentToken.isEmpty(), [=](){setValue("path", currentToken);});
        checkState(PushEntityPath, PushDone, currentToken.toUpper() == "DONE", [=](){setValue("end", currentToken.toUpper());});

        listIterator ++;

    }
}

void Fsm::checkState(states previousState, states nextState, bool condition, stateFn fn)
{
    qDebug() << __FUNCTION__ << currentState ;
    if(currentState==previousState && condition) {
        currentState=nextState;
        fn();
    }
}
