#include "libraryfsm.h"
#include <QDebug>
#include <QChar>

LibraryFsm::LibraryFsm()
{
}

// Split the sentence written by the user into several tokens
void LibraryFsm::stringToList(QString line)
{
    listTokens = line.split(" ");
}

const QMap<QString, QVariant> &LibraryFsm::getValues() const
{
    return values;
}

void LibraryFsm::setValues(const QMap<QString, QVariant> &newValues)
{
    values = newValues;
}


QVariant LibraryFsm::getValue(QString key)
{
    return values[key];
}

QStringList LibraryFsm::getListTokens()
{
    return listTokens;
}

void LibraryFsm::setValue(QString key, QVariant value)
{
    //values[key] = value;
    values.insert(key, value);
}


// "ADD", "PUSH", "CLEAR", "GET", "SEARCH", "INDEXER"
bool LibraryFsm::isCmd(const QString &str)
{
    if(correctCmd.contains(str)) return true;

    return false;

}

// "WHITELIST","BLACKLIST","FILTERS","SKIPPED_FILTERS"
bool LibraryFsm::isFlag(const QString &str)
{
    if(correctFlags.contains(str)) return true;

    return false;
}

// "INDEXING","READY","STOPPED","PAUSED","QUERYING", "RESULTS_AVAILABLE"
bool LibraryFsm::isStatus(const QString &str)
{
    if(correctStatus.contains(str)) return true;

    return false;
}

// "STATUS","START","STOP","PAUSE","RESUME"
bool LibraryFsm::isAction(const QString &str)
{
    if(correctActions.contains(str)) return true;

    return false;
}

bool LibraryFsm::isDate(const QString &str)
{
    if(str == "dd/mm/yyyy" || str == "yyyy") {
        return true;
    }
    return false;
}

bool LibraryFsm::isNumber(const QString &str)
{
    for (QChar c : str) {
        if(!c.isDigit()) {
            return false;
        }
    }
    return true;

}

bool LibraryFsm::isNumberType(const QString &str)
{
    if( str == "5M" || str == "6G") {
        return true;
    }
    return false;
}

bool LibraryFsm::isTime(const QString &str)
{
    if(correctTimes.contains(str)) {
        return true;
    }
    return false;
}

bool LibraryFsm::isExt(const QString &str)
{
    return false;
}

bool LibraryFsm::isType(const QString &str)
{
    return false;
}

void LibraryFsm::createMapping(QStringList list)
{
    auto listIterator = list.begin();
    //currentToken = *listIterator;
    currentState = CommandFound;

    while(listIterator != list.end()) {
        qDebug() << "create mapping" << currentToken << currentState;
        currentToken = *listIterator;
        // SEARCH
        checkState(CommandFound, Search, currentToken.toUpper()=="SEARCH", [=](){setValue("cmd", currentToken.toUpper());});
        checkState(Search, SearchFilenamePart, !currentToken.isEmpty() && currentToken!="SEARCH", [=](){setValue("filenamePart", currentToken);});
        //      ~LAST_MODIFIED
        checkState(SearchFilenamePart, SearchOptionLastModified, currentToken.toUpper()=="LAST_MODIFIED", [=](){setValue("option", currentToken.toUpper());});
        checkState(SearchOptionLastModified, SearchOptionSimpleDate, isDate(currentToken), [=](){setValue("date", currentToken);});
        checkState(SearchOptionLastModified, SearchOptionSince, currentToken.toUpper()=="SINCE", [=](){setValue("since", currentToken.toUpper());});
        checkState(SearchOptionLastModified, SearchOptionNumber, isNumber(currentToken), [=](){setValue("number", currentToken);});
        checkState(SearchOptionLastModified, SearchOptionBetween, currentToken.toUpper()=="BETWEEN", [=](){setValue("between", currentToken.toUpper());});
        //      ~CREATED
        checkState(SearchFilenamePart, SearchOptionCreated, currentToken.toUpper()=="CREATED", [=](){setValue("option", currentToken.toUpper());});
        checkState(SearchOptionCreated, SearchOptionSimpleDate, isDate(currentToken), [=](){setValue("date", currentToken);});
        checkState(SearchOptionCreated, SearchOptionSince, currentToken.toUpper()=="SINCE", [=](){setValue("since", currentToken.toUpper());});
        checkState(SearchOptionCreated, SearchOptionNumber, isNumber(currentToken), [=](){setValue("number", currentToken);});
        checkState(SearchOptionCreated, SearchOptionBetween, currentToken.toUpper()=="BETWEEN", [=](){setValue("between", currentToken.toUpper());});
        //      ~LAST_MODIFIED & CREATED
        checkState(SearchOptionSince, SearchOptionSinceLast, currentToken.toUpper()=="LAST", [=](){setValue("last", currentToken.toUpper());});
        checkState(SearchOptionSinceLast, SearchOptionSinceLastNumber, isNumber(currentToken), [=](){setValue("number", currentToken);});
        checkState(SearchOptionSinceLastNumber, SearchOptionSinceLastNumberTime, isTime(currentToken.toUpper()), [=](){setValue("time", currentToken.toUpper());});
        checkState(SearchOptionNumber, SearchOptionNumberTime, isTime(currentToken), [=](){setValue("time", currentToken);});
        checkState(SearchOptionNumberTime, SearchOptionNumberTimeAgo, currentToken.toUpper()=="AGO", [=](){setValue("ago", currentToken.toUpper());});
        checkState(SearchOptionBetween, SearchOptionBetweenSimpleDate, isDate(currentToken), [=](){setValue("date", currentToken);});
        checkState(SearchOptionBetweenSimpleDate, SearchOptionBetweenSimpleDateAnd, currentToken.toUpper()=="AND", [=](){setValue("and", currentToken.toUpper());});
        checkState(SearchOptionBetweenSimpleDateAnd, SearchOptionBetweenSimpleDateAndSimpleDate, isDate(currentToken), [=](){setValue("date2", currentToken);});
        //      ~MAX_SIZE
        checkState(SearchFilenamePart, SearchOptionMaxSize, currentToken.toUpper()=="MAX_SIZE", [=](){setValue("option", currentToken.toUpper());});
        checkState(SearchOptionMaxSize, SearchOptionSizeNumberType, isNumberType(currentToken), [=](){setValue("number", currentToken);});
        //      ~MIN_SIZE
        checkState(SearchFilenamePart, SearchOptionMinSize, currentToken.toUpper()=="MIN_SIZE", [=](){setValue("option", currentToken.toUpper());});
        checkState(SearchOptionMinSize, SearchOptionSizeNumberType, isNumberType(currentToken), [=](){setValue("number", currentToken);});
        //      ~SIZE
        checkState(SearchFilenamePart, SearchOptionSize, currentToken.toUpper()=="SIZE", [=](){setValue("option", currentToken.toUpper());});
        checkState(SearchOptionSize, SearchOptionSizeNumberType, isNumberType(currentToken), [=](){setValue("number", currentToken);});

        checkState(SearchOptionSize, SearchOptionSizeBetween, currentToken.toUpper()=="BETWEEN", [=](){setValue("between", currentToken.toUpper());});
        checkState(SearchOptionSizeBetween, SearchOptionSizeBetweenNumberType, isNumberType(currentToken.toUpper()), [=](){setValue("numberType", currentToken.toUpper());});
        checkState(SearchOptionSizeBetweenNumberType, SearchOptionSizeBetweenNumberTypeAnd, currentToken.toUpper()=="AND", [=](){setValue("and", currentToken.toUpper());});
        checkState(SearchOptionSizeBetweenNumberTypeAnd, SearchOptionSizeBetweenNumberTypeAndNumberType, isNumberType(currentToken.toUpper()), [=](){setValue("numberType2", currentToken.toUpper());});
        //      ~EXT    ???
        checkState(SearchFilenamePart, SearchOptionExt, currentToken.toUpper()=="EXT", [=](){setValue("option", currentToken.toUpper());});
        checkState(SearchOptionExt, SearchOptionExtExt, isExt(currentToken), [=](){setValue("ext", currentToken);});
        checkState(SearchOptionExtExt, SearchOptionExtExt, isExt(currentToken), [=](){setValue("ext", currentToken);});
        checkState(SearchOptionExtExt, SearchOptionExtExtOr, currentToken.toUpper()=="OR", [=](){setValue("elt", currentToken.toUpper());});
        //      ~TYPE   ???
        checkState(SearchFilenamePart, SearchOptionType, currentToken.toUpper()=="TYPE", [=](){setValue("option", currentToken.toUpper());});
        checkState(SearchOptionType, SearchOptionTypeType, isType(currentToken), [=](){setValue("type", currentToken);});
        checkState(SearchOptionTypeType, SearchOptionTypeType, isType(currentToken), [=](){setValue("type", currentToken);});
        checkState(SearchOptionTypeType, SearchOptionTypeTypeOr, currentToken.toUpper()=="OR", [=](){setValue("elt", currentToken.toUpper());});
        // Status -- ???
        //checkState(CommandFound, Status, currentToken.toUpper()=="STATUS", [=](){setValue("cmd", currentToken.toUpper());});
        //checkState(Status, ServerStatus, isStatus(currentToken.toUpper()), [=](){setValue("serverStatus", currentToken.toUpper());});
        // Indexer
        checkState(CommandFound, Indexer, currentToken.toUpper()=="INDEXER", [=](){setValue("cmd", currentToken.toUpper());});
        checkState(Indexer, IndexerCmd, isAction(currentToken.toUpper()), [=](){setValue("action", currentToken.toUpper());});
        // Clear
        checkState(CommandFound, Clear, currentToken.toUpper()=="CLEAR", [=](){setValue("cmd", currentToken.toUpper());});
        checkState(Clear, ClearEntity, isFlag(currentToken.toUpper()), [=](){setValue("flag", currentToken.toUpper());});
        // Get
        checkState(CommandFound, Get, currentToken.toUpper()=="GET", [=](){setValue("cmd", currentToken.toUpper());});
        checkState(Get, GetEntity, isFlag(currentToken.toUpper()), [=](){setValue("flag", currentToken.toUpper());});
        // Add
        checkState(CommandFound, Add, currentToken.toUpper()=="ADD", [=](){setValue("cmd", currentToken.toUpper());});
        checkState(Add, AddEntity, isFlag(currentToken.toUpper()), [=](){setValue("flag", currentToken.toUpper());});
        checkState(AddEntity, AddEntityPath, !currentToken.isEmpty() && !isFlag(currentToken), [=](){setValue("path", currentToken);});
        // Push     ???
        checkState(CommandFound, Push, currentToken.toUpper()=="PUSH", [=](){setValue("cmd", currentToken.toUpper());});
        checkState(Push, PushEntity, isFlag(currentToken.toUpper()), [=](){setValue("flag", currentToken.toUpper());});
        checkState(PushEntity, PushEntityPath, !currentToken.isEmpty() && !isFlag(currentToken), [=](){setValue("path", currentToken);});
        checkState(PushEntityPath, PushEntityPath, !currentToken.isEmpty()  && !isFlag(currentToken) && currentToken != "DONE", [=](){setValue("path", currentToken);});
        checkState(PushEntityPath, PushDone, currentToken.toUpper() == "DONE", [=](){setValue("done", currentToken.toUpper());});

        listIterator ++;

    }
}

void LibraryFsm::checkState(states previousState, states nextState, bool condition, stateFn fn)
{
    //qDebug() << __FUNCTION__ << currentToken << currentState ;
    if(currentState==previousState && condition) {
        currentState=nextState;
        fn();
    }
}
