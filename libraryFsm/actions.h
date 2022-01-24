#ifndef ACTIONS_H
#define ACTIONS_H

#include "libraryfsm.h"

#include <QString>
#include <QDebug>

class Actions : public QObject
{
    Q_OBJECT
    QString _name;
    QString _type;
    QMap<QString, QVariant> _map;

protected:
    LibraryFsm * _fsm = nullptr;

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

   void setFsm(LibraryFsm * fsm) {
        _fsm = fsm;
   }

   virtual QMap<QString, QVariant> getMap() {
       return _map;
   }


   virtual void setMap(QMap<QString, QVariant> newMap) {
       _map = newMap;
   }

   virtual void run() = 0;

   virtual void sendRequest(QString path) {
       qDebug() << "No GG " << getMap();
   }

   signals:
      void dirsAdded(const QString &);

};

    typedef Actions *(*CreateActionsFn)();

#endif // ACTIONS_H
