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

class Add : public TActions<Add> {

    void run() override {
        qDebug() << _fsm->getValue("cmd");
    }
};

#endif // TACTIONS_H
