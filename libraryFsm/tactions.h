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

#endif // TACTIONS_H
