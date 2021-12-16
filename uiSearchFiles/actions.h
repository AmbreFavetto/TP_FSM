#ifndef ACTIONS_H
#define ACTIONS_H

#include "fsm.h"

#include <QString>
#include <QDebug>

class Actions
{
    QString _name;
    QString _type;

protected:
    Fsm * _fsm = nullptr;

public:
    Actions() {

    }

    virtual ~Actions() {
           qDebug() << __FUNCTION__ << type() << name();
    }
   virtual QString name() {
       return _name;
   }
   virtual void setName(QString name) {
       _name = name;
   }

   QString type() const {
       return _type;
   }

   void setType(const QString &type) {
       _type = type;
   }

   void setFsm(Fsm * fsm) {
        _fsm = fsm;
   }

   virtual void run() = 0;

};

    typedef Actions *(*CreateActionsFn)();

#endif // ACTIONS_H
