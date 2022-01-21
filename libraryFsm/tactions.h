#ifndef TACTIONS_H
#define TACTIONS_H

#include "actions.h"

template <class T>
class TActions : public Actions
{

public:
    static Actions *create() {
        qDebug() << __FUNCTION__;
        return new T;
    }

};

class ActionException {
    QString m_msg;

  public:
    ActionException(QString msg) {
        m_msg = msg;
    }
    QString msg() const {
        return m_msg;
    }

    void setMsg(const QString &msg) {
        m_msg = msg;
    }
};


class CmdAdd : public TActions<CmdAdd> {

    void run() override {
        QMap<QString, QVariant> map = getMap();
        qDebug() << "TEST" << map;
    }
};

class CmdGet : public TActions<CmdGet> {

    void run() override {
        qDebug() << _fsm->getValue("cmd");
    }
};

class CmdPush : public TActions<CmdPush> {

    void run() override {
        qDebug() << _fsm->getValue("cmd");
    }
};

class CmdClear : public TActions<CmdClear> {

    void run() override {
        qDebug() << _fsm->getValue("cmd");
    }
};

class CmdSearch : public TActions<CmdSearch> {

    void run() override {
        qDebug() << _fsm->getValue("cmd");
    }

};

class CmdIndexer : public TActions<CmdIndexer> {

    void run() override {
        qDebug() << "COUCOU LES AMIS" << _fsm->getValue("cmd");
        QMap<QString, QVariant> map = getMap();
        auto mapIterator = map.find("action");
        if(mapIterator.value() == "STATUS") {
            qDebug() << "STATUS";
        } else if (mapIterator.value() == "START") {
            qDebug() << "START";
        } else if (mapIterator.value() == "STOP") {
            qDebug() << "STOP";
        } else if (mapIterator.value() == "PAUSE") {
            qDebug() << "PAUSE";
        } else if (mapIterator.value() == "RESUME") {
            qDebug() << "RESUME";
        }
    }

    void test() {
        qDebug() << "COUCOU LES POTES";
    }
};
#endif // TACTIONS_H
