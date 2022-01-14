#include "myclient.h"

myclient::myclient()
{

}

void myclient::setHost(const QString &host){
     _host = host;
}

void myclient::setPort(uint port) {
    _port = port;
}

void myclient::connect() {
    connectToHost(_host, quint16(_port));
    if (waitForConnected(2000)) {
        qDebug("Connected ! ");
        emit connected();
        return;
    }
    qDebug("Unable to connect !");
}

void myclient::disconnect() {
    disconnectFromHost();
    emit disconnected();
}
