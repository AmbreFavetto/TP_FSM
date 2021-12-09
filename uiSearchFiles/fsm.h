#ifndef FSM_H
#define FSM_H

#include <QtWidgets/QMainWindow>
#include <QDebug>

class fsm: public QMainWindow
{
    Q_OBJECT

    int m_current_state = 0;

    enum Actions {
        ADD     = 0,
        PUSH    = 1,
        CLEAR   = 2,
        GET     = 3,
        SEARCH  = 4,
        INDEXER = 5,
        UNDEFINED = 6
    };

    public:
        fsm();

        //Flags isFlag(QString const& str);
        Actions isAction(QString const& str);
        bool isNumber(QString const& str);
        bool isOperator(QString const& str);
        bool isWord(QString const& str);

        QStringList stringToList(QString line);

        int current_state() const;

        bool CheckState(int from, int to, bool condition);


    };

#endif // FSM_H
