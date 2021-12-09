#ifndef MYSERVER_H
#define MYSERVER_H


#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QTcpServer>

class myserver : public QObject {
    Q_OBJECT
    QTcpServer *_server = nullptr;

    public:
        myserver();
        bool start();
        void stop();
    public slots:
        void onNewConnection();
        void onReadyRead();
    signals:
        void started();
        void stopped();
};
#endif // MYSERVER_H
