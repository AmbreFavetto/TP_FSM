#ifndef MYCLIENT_H
#define MYCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
class myclient : public QTcpSocket {
    Q_OBJECT
    QString _host;
    uint    _port;

public:
    myclient();
    void setHost(const QString & host);
    void setPort(uint port);
    void connect();
    void disconnect();
};

#endif // MYCLIENT_H
