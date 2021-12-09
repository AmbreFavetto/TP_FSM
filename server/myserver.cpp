#include "myserver.h"

myserver::myserver()
{

}

bool myserver::start() {
    _server = new QTcpServer;
    if (!_server->listen(QHostAddress::Any, 8080)) {
        qCritical() << "Unable to start server" << _server->serverAddress() << _server->serverPort();
        return false;
    }
    qInfo() << "Server started" << _server->serverAddress() << _server->serverPort();
    connect(_server, &QTcpServer::newConnection, this, &myserver::onNewConnection);
    emit started();
    return true;
}

void myserver::stop() {
    qDebug() << __FUNCTION__;
    _server->close();
    _server->deleteLater();
    emit stopped();
}

void myserver::onNewConnection() {
    qDebug() << __FUNCTION__;
    QTcpSocket *_client = _server->nextPendingConnection();
    qDebug() << "Client connected" << _client->peerAddress() << _client->peerPort();
    connect(_client, &QTcpSocket::readyRead, this, &myserver::onReadyRead, Qt::QueuedConnection);
}

void myserver::onReadyRead() {
    QTcpSocket *_client = static_cast<QTcpSocket *>(sender());

    QByteArray _data = _client->readAll();
    qDebug() << "Data received" << _data;
    _client->write(_data);
    _client->waitForBytesWritten();
    _client->disconnectFromHost();
    _client->deleteLater();
}

