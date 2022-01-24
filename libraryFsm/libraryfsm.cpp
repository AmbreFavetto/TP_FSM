#include "libraryfsm.h"
#include <QDebug>
#include <QChar>
#include <QRegularExpression>
#include <QDir>
#include "actionfactory.h"

LibraryFsm::LibraryFsm(QString path)
{
    if(path.isEmpty()) {
            qDebug() << "cheh";
    } else {
        qDebug() << path;
        this->path = path;

    }
}

// Split the sentence written by the user into several tokens
void LibraryFsm::stringToList(QString line)
{
    listTokens = line.split(" ");
}

// For EXT and TYPE options
const QStringList &LibraryFsm::getListElts() const
{
    return listElts;
}

// For EXT and TYPE options
void LibraryFsm::setListElts(const QStringList &newListElts)
{
    listElts = newListElts;
}

// QMap contains all the tokens stored
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

void LibraryFsm::setValue(QString key, QVariant value)
{
    //values[key] = value;
    values.insert(key, value);
}

QStringList LibraryFsm::getListTokens()
{
    return listTokens;
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

// For LAST_MODIFIED and CREATED options
bool LibraryFsm::isDate(const QString &str)
{
    // for "dd/mm/yyyy" format
    QRegularExpression re1("^(\\d\\d)/(\\d\\d)/(\\d\\d\\d\\d)$");
    QRegularExpressionMatch match1 = re1.match(str);
    if (match1.hasMatch() && currentToken.length() == 10) {
        int day = match1.captured(1).toInt();
        int month = match1.captured(2).toInt();
        int year = match1.captured(3).toInt();
        if (month <= 0 || month > 12 || day <= 0 || day > 31)
        {
            return false;
        }

        switch (month) {
        case 4:
        case 6:
        case 9:
        case 11:
            if (day > 30)
                return false;
            return true;
        case 2:
            if (day > 29)
                return false;
            if (!((year % 4 == 0 && year % 100 != 0) || (year % 4 == 0 && year % 100 == 0 && year % 400 == 0)))
            {
                if (day > 28) // year is not bissextile
                    return false;
            }
            return true;
        default:
            return true;
        }
    }

    // for "mm/yyyy" format
    QRegularExpression re2("^(\\d\\d)/(\\d\\d\\d\\d)$");
    QRegularExpressionMatch match2 = re2.match(str);
    if (match2.hasMatch() && str.length() == 7)
    {
        int month = match2.captured(1).toInt();
        if (month <= 0 || month > 12)
        {
            return false;
        }
        return true;
    }

    // for "yyyy" and "yy" format
    QRegularExpression re3("^(\\d\\d\\d\\d)$");
    QRegularExpressionMatch match3 = re3.match(str);
    QRegularExpression re4("^(\\d\\d)$");
    QRegularExpressionMatch match4 = re4.match(str);
    if ((match3.hasMatch() && str.length() == 4) || (match4.hasMatch() && str.length() == 2))
    {
        return true;
    }
    return false;
}

bool LibraryFsm::isFileName(const QString &str)
{
    QRegularExpression re("[<>:\"/,|?*]");
    QRegularExpressionMatch match = re.match(str);

    if (match.hasMatch()) return false;
    if (str[str.length() - 1] == '.') return false;

    return true;
}

// for date with SINCE LAST and AGO
bool LibraryFsm::isNumber(const QString &str)
{
    for (QChar c : str) {
        if(!c.isDigit()) {
            return false;
        }
    }
    return true;
}

// For MAX_SIZE, MIN_SIZE and SIZE ~<number>K|M|G
bool LibraryFsm::isNumberType(const QString &str)
{
    QRegularExpression re("^(\\d+)[KMG]$");
    QRegularExpressionMatch match = re.match(str);
    if (match.hasMatch())
    {
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
    if(!str.isEmpty() && !str.endsWith(",") && !listElts.contains(str)) {
        return true;
    }
    return false;
}

bool LibraryFsm::isListExt(const QString &str)
{
    if(!str.isEmpty() && str.endsWith(",") && !listElts.contains(str)) {
        return true;
    }
    return false;
}


bool LibraryFsm::isType(const QString &str)
{
    if(!str.isEmpty() && !str.endsWith(",")) {
        return true;
    }
    return false;
}

bool LibraryFsm::isListType(const QString &str)
{
    if(!str.isEmpty() && str.endsWith(",") && !listElts.contains(str)) {
        return true;
    }
    return false;
}

bool LibraryFsm::isPath(const QString &str)
{
    if(!str.isEmpty()) return true;

    return false;
}

void LibraryFsm::addEltToList(const QString &str)
{
    if(!listElts.contains(str)) listElts << str;
}

void LibraryFsm::onDirsAddedFromTActions(const QString dirs)
{
    qDebug() << "yo les potes dirsAdded from tActions";
    emit dirsAdded(dirs);
}

void LibraryFsm::createMapping()
{
    ActionFactory *factory = new ActionFactory;
    auto listIterator = listTokens.begin();
    currentState = Initial;

    while(listIterator != listTokens.end()) {
        qDebug() << "create mapping" << currentToken << currentState;
        currentToken = *listIterator;

        checkState(Initial, CommandFound, isCmd(currentToken.toUpper()), [=](){});
        checkState(Initial, ErrUnknownCmd, !isCmd(currentToken.toUpper()), [=](){});
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
        //      ~EXT
        checkState(SearchFilenamePart, SearchOptionExt, currentToken.toUpper()=="EXT", [=](){setValue("option", currentToken.toUpper());});
        //          with ,
        checkState(SearchOptionExt, SearchOptionExtListExt, isListExt(currentToken), [=](){addEltToList(currentToken);});
        checkState(SearchOptionExtListExt, SearchOptionExtListExt, isListExt(currentToken), [=](){addEltToList(currentToken);});
        checkState(SearchOptionExtListExt, SearchOptionExtListExtFinal, isExt(currentToken), [=](){addEltToList(currentToken); setValue("ext", listElts); });
        //          with OR
        checkState(SearchOptionExt, SearchOptionExtExt, isExt(currentToken) && currentToken.toUpper() != "EXT" && currentToken.toUpper() != "OR", [=](){addEltToList(currentToken); setValue("ext", listElts);});
        checkState(SearchOptionExtExt, SearchOptionExtExtOr, currentToken.toUpper()=="OR", [=](){setValue("or", currentToken.toUpper());});
        checkState(SearchOptionExtExtOr, SearchOptionExtExt, isExt(currentToken) && currentToken.toUpper() != "OR", [=](){addEltToList(currentToken); setValue("ext", listElts);});
        //      ~TYPE
        checkState(SearchFilenamePart, SearchOptionType, currentToken.toUpper()=="TYPE", [=](){setValue("option", currentToken.toUpper());});
        //          with ,
        checkState(SearchOptionType, SearchOptionTypeListType, isListType(currentToken), [=](){addEltToList(currentToken);});
        checkState(SearchOptionTypeListType, SearchOptionTypeListType, isListType(currentToken), [=](){addEltToList(currentToken);});
        checkState(SearchOptionTypeListType, SearchOptionTypeListTypeFinal, isType(currentToken), [=](){addEltToList(currentToken); setValue("type", listElts); });
        //          with OR
        checkState(SearchOptionType, SearchOptionTypeType, isType(currentToken) && currentToken.toUpper() != "TYPE" && currentToken.toUpper() != "OR", [=](){addEltToList(currentToken); setValue("type", listElts);});
        checkState(SearchOptionTypeType, SearchOptionTypeTypeOr, currentToken.toUpper()=="OR", [=](){setValue("or", currentToken.toUpper());});
        checkState(SearchOptionTypeTypeOr, SearchOptionTypeType, isType(currentToken) && currentToken.toUpper() != "OR", [=](){addEltToList(currentToken); setValue("type", listElts);});
        // Indexer
        checkState(CommandFound, Indexer, currentToken.toUpper()=="INDEXER", [=](){setValue("cmd", currentToken.toUpper());});
        checkState(Indexer, IndexerCmd, isAction(currentToken.toUpper()), [=](){setValue("action", currentToken.toUpper());
            Actions *CmdIndexer = factory->create("CmdIndexer");
            CmdIndexer->setMap(values);
            connect(CmdIndexer, &CmdIndexer::dirsAdded, this, &LibraryFsm::onDirsAddedFromTActions);
            CmdIndexer->sendRequest(path);});
        // Clear
        checkState(CommandFound, Clear, currentToken.toUpper()=="CLEAR", [=](){setValue("cmd", currentToken.toUpper());});
        checkState(Clear, ClearEntity, isFlag(currentToken.toUpper()), [=](){setValue("flag", currentToken.toUpper()); });
        checkState(Clear, ErrUnknownEntity, !isFlag(currentToken.toUpper()) && currentToken != "CLEAR", [=](){}); // ADD ERR MESSAGE
        // Get
        checkState(CommandFound, Get, currentToken.toUpper()=="GET", [=](){setValue("cmd", currentToken.toUpper());});
        checkState(Get, GetEntity, isFlag(currentToken.toUpper()), [=](){setValue("flag", currentToken.toUpper());});
        checkState(Get, ErrUnknownEntity, !isFlag(currentToken.toUpper()) && currentToken != "GET", [=](){}); // ADD ERR MESSAGE
        // Add
        checkState(CommandFound, Add, currentToken.toUpper()=="ADD", [=](){setValue("cmd", currentToken.toUpper());});
        checkState(Add, AddEntity, isFlag(currentToken.toUpper()), [=](){setValue("flag", currentToken.toUpper());});
        checkState(Add, ErrUnknownEntity, !isFlag(currentToken.toUpper()) && currentToken != "ADD", [=](){});
        checkState(AddEntity, AddEntityPath, isPath(currentToken) && !isFlag(currentToken.toUpper()), [=](){setValue("path", currentToken);});
        checkState(AddEntity, ErrMissingOrBadPath, !isPath(currentToken) && !isFlag(currentToken.toUpper()), [=](){}); // ADD ERR MESSAGE
        // Push
        checkState(CommandFound, Push, currentToken.toUpper()=="PUSH", [=](){setValue("cmd", currentToken.toUpper());});
        checkState(Push, PushEntity, isFlag(currentToken.toUpper()), [=](){setValue("flag", currentToken.toUpper());});
        checkState(Push, ErrUnknownEntity, !isFlag(currentToken.toUpper()) && currentToken != "PUSH", [=](){}); // ADD ERR MESSAGE
        checkState(PushEntity, PushEntityPath, isPath(currentToken) && !isFlag(currentToken.toUpper()) && currentToken != "DONE", [=](){addEltToList(currentToken);});
        checkState(PushEntityPath, PushEntityPath, isPath(currentToken) && currentToken != "DONE", [=](){addEltToList(currentToken);});
        checkState(PushEntity, ErrMissingOrBadPath, !isPath(currentToken), [=](){addEltToList(currentToken);}); // ADD ERR MESSAGE
        checkState(PushEntityPath, PushDone, currentToken.toUpper() == "DONE", [=](){setValue("path", listElts); setValue("done", currentToken.toUpper());});

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
