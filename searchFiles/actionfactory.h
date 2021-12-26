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
};

#endif // ACTIONFACTORY_H
