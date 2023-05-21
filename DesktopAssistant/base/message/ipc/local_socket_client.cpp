#include "local_socket_client.h"

#include "base/define.h"

namespace base {

LocalSocketClient::LocalSocketClient(QObject* parent) : QObject(parent), m_socket(nullptr)
{
    m_socket = new QLocalSocket(this);
    if (m_socket) {
        connect(m_socket, SIGNAL(connected()), this, SLOT(onSocketConnected()));
        connect(m_socket, SIGNAL(disconnected()), this, SLOT(onSocketDisConnected()));
        connect(m_socket, SIGNAL(error(QLocalSocket::LocalSocketError)), this, SLOT(onSocketError(QLocalSocket::LocalSocketError)));
        connect(m_socket, SIGNAL(stateChanged(QLocalSocket::LocalSocketState)), this, SLOT(onStateChanged(QLocalSocket::LocalSocketState)));
        connect(m_socket, SIGNAL(readyRead()), this, SLOT(onSocketReadyRead()));

    }
}

LocalSocketClient::~LocalSocketClient() {
    if (m_socket) {
        disconnect(m_socket, SIGNAL(connected()), this, SLOT(onSocketConnected()));
        disconnect(m_socket, SIGNAL(disconnected()), this, SLOT(onSocketDisConnected()));
        disconnect(m_socket, SIGNAL(error(QLocalSocket::LocalSocketError)), this, SLOT(onSocketError(QLocalSocket::LocalSocketError)));
        disconnect(m_socket, SIGNAL(stateChanged(QLocalSocket::LocalSocketState)), this, SLOT(onStateChanged(QLocalSocket::LocalSocketState)));
        disconnect(m_socket, SIGNAL(readyRead()), this, SLOT(onSocketReadyRead()));

        if (m_socket->isOpen()) {
            m_socket->abort();
            m_socket->close();
        }
        delete m_socket;
        m_socket = nullptr;
    }
}

int LocalSocketClient::beginConnect(QString serverName, int timeout) {
    if (serverName.isEmpty()) {
        serverName = DEF_LOCAL_SOCKET_SERVER_NAME;
    }
    m_socket->connectToServer(serverName);
    bool bret = m_socket->waitForConnected(timeout);
    qInfo() << "LocalSocketClient::beginConnect connectToServer status:" << bret    \
            << ", serverName:" << serverName    \
            << ", errmsg:" << m_socket->errorString();
    return bret ? 0 : -2;
}

void LocalSocketClient::endConnect() {
    if (m_socket) {
        m_socket->close();
    }
}

int LocalSocketClient::sendMessage(QString strMsg, int timeout) {
    if (strMsg.isEmpty()) {
        return -1;
    }

    m_socket->write(strMsg.toUtf8().data(), strMsg.toUtf8().size());
    m_socket->flush();

    bool bret = false;
    if (!m_socket->bytesAvailable()) {
        bret = m_socket->waitForReadyRead(timeout);
    }

    return !bret ? 0 : strMsg.size();

    //QTextStream stream(m_socket);
    //QString respond = stream.readAll();
    //qDebug() << "Read Data From Server:" << respond;
    //return respond;
}

void LocalSocketClient::onSocketConnected() {
    emit socketConnected();
}

void LocalSocketClient::onSocketDisConnected() {
    emit socketDisConnected();
}

void LocalSocketClient::onSocketError(QLocalSocket::LocalSocketError error) {
    qInfo() << "LocalSocketClient::onSocketError errno:" << error;
    emit socketExceptionError(error);
}

void LocalSocketClient::onStateChanged(QLocalSocket::LocalSocketState socketState) {
    emit socketStateChanged(socketState);
}

void LocalSocketClient::onSocketReadyRead() {
    if (m_socket) {
        QString strMsg = m_socket->readAll();
        emit socketDataRecv(strMsg);
    }
}

int LocalSocketClient::sendActiveMessage() {
    QString strMsg = "{\"code\":200,\"cmd\":\"active\"}";
    return this->sendMessage(strMsg, 10000);
}

} // end namespace base
