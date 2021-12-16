#include "parser.h"
#include <QDebug>

// Va voir si il a une classe héritant d'action qui est donc une action correcte
// ADD, PUSH, GET, CLEAR, INDEXER, STATUS, SEARCH

parser::parser()
{

}

bool parser::isAction(const QString &str)
{
    if(correctActions.contains(str)) return true;

    return false;

}

bool parser::isFlag(const QString &str)
{
    if(correctFlags.contains(str)) return true;

    return false;
}

bool parser::isOptions(const QString &str)
{
    if(correctOptions.contains(str)) return true;

    return false;
}

void parser::createMapping(QStringList list)
{
    auto listIterator = list.begin();
    currentToken = *listIterator;
    while(listIterator != list.end()) {
        currentToken = *listIterator;

        // premier passage
        if(isAction(currentToken) && mapTokens.isEmpty()) {
            mapTokens.insert("Action", currentToken);
        } else {
            qDebug() << "First token isn't an Action";
            break;
        }

        //tous les autres passages


        listIterator ++;

    }
}
