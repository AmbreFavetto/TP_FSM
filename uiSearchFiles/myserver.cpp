#include "myserver.h"
#include <QTcpSocket>

myserver::myserver()
{

}

bool myserver::start() {
    _server = new QTcpServer;
    if (!_server->listen(QHostAddress::Any, 8080)) {
        qCritical() << "Unable to start server" << _server->serverAdress() << _server->serverPort();
        return false;
    }

}
