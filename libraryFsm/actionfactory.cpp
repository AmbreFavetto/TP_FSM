#include "actionfactory.h"

QMap<QString, CreateActionsFn> &ActionFactory::factoryMap()
{
    return m_factoryMap;
}

void ActionFactory::setFactoryMap(QMap<QString, CreateActionsFn> &newFactoryMap)
{
    m_factoryMap = newFactoryMap;
}

ActionFactory::ActionFactory()
{
    Register("CmdAdd", &CmdAdd::create);
    Register("CmdGet", &CmdGet::create);
    Register("CmdPush", &CmdPush::create);
    Register("CmdClear", &CmdClear::create);
    Register("CmdSearch", &CmdSearch::create);
    Register("CmdIndexer", &CmdIndexer::create);
}

ActionFactory::~ActionFactory() {
        foreach (auto action, actionsList) { delete action; }
    }


void ActionFactory::Register(QString actionName, CreateActionsFn fn) {
    qDebug() << __FUNCTION__ << actionName << fn;
    m_factoryMap[actionName] = fn;
}

Actions* ActionFactory::create(QString actionName) {
        qDebug() << __FUNCTION__ << actionName;

        // on recupere le pointeur sur fonction de la Map
        CreateActionsFn fn = m_factoryMap[actionName];
        if (fn == nullptr) {
            throw ActionException("Unable to create " + actionName);
        }
        // on appel la fonction désignée par le pointeur 'fn'
        Actions *action = fn();

        // on assigne le type et on nomme l'objet
        action->setType(actionName);
        action->setName(QString(actionName + " #%1").arg(actionsList.size()));

        // on le rajoute à la liste des objets de la Factory
        actionsList.append(action);
        return action;
    }


