#ifndef ACTIONFACTORY_H
#define ACTIONFACTORY_H

#include "tactions.h"

class ActionFactory
{
    QMap<QString, CreateActionsFn> m_factoryMap;
    QList<Actions *>               actionsList;

public:
    ActionFactory();
    ~ActionFactory();

    void Register(QString actionName, CreateActionsFn fn);
    Actions* create(QString actionName);
    QMap<QString, CreateActionsFn> &factoryMap();
    void setFactoryMap(QMap<QString, CreateActionsFn> &newFactoryMap);
};


#endif // ACTIONFACTORY_H
