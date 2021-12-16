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
    values[key] = value;
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
        // Search

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
        // TODO - quoi mettre si c'est un fichier ??
        //checkState(AddEntity, AddEntityPath, currentToken, [=](){setValue("path", currentToken);});

        // Push
        checkState(CommandFound, Push, currentToken.toUpper()=="PUSH", [=](){setValue("cmd", currentToken.toUpper());});
        //checkState(Push, PushEntity, isFlag(currentToken.toUpper()), [=](){setValue("flag", currentToken.toUpper());});
        checkState(Push, PushEntity, currentToken.toUpper() == "WHITELIST", [=](){setValue("flag", currentToken.toUpper());});
        checkState(Push, PushEntity, currentToken.toUpper() == "BLACKLIST", [=](){setValue("flag", currentToken.toUpper());});
        checkState(Push, PushEntity, currentToken.toUpper() == "FILTERS", [=](){setValue("flag", currentToken.toUpper());});
        checkState(Push, PushEntity, currentToken.toUpper() == "SKIPPED_FILTERS", [=](){setValue("flag", currentToken.toUpper());});
        // TODO - quoi mettre si c'est un fichier ??
        //checkState(PushEntity, PushEntityPath, currentToken, [=](){setValue("path", currentToken);});
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
