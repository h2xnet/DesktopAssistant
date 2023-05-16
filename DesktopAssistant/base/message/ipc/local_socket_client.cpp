#include "local_socket_client.h"

#include "base/define.h"

namespace base {

LocalSocketClient::LocalSocketClient(QObject* parent) : QObject(parent), m_socket(nullptr)
{
    m_socket = new QLocalSocket(this);
    if (m_socket) {
        connect(m_socket, SIGNAL(connected()), this, SLOT(socketConnectedHandler()));
        connect(m_socket, SIGNAL(disconnected()), this, SLOT(socketDisConnectedHandler()));
        connect(m_socket, SIGNAL(error(QLocalSocket::LocalSocketError)), this, SLOT(socketErrorHandler(QLocalSocket::LocalSocketError)));
    }
}

LocalSocketClient::~LocalSocketClient() {
    if (m_socket) {
        disconnect(m_socket, SIGNAL(connected()), this, SLOT(socketConnectedHandler()));
        disconnect(m_socket, SIGNAL(disconnected()), this, SLOT(socketDisConnectedHandler()));
        disconnect(m_socket, SIGNAL(error(QLocalSocket::LocalSocketError)), this, SLOT(socketErrorHandler(QLocalSocket::LocalSocketError)));
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

QString LocalSocketClient::sendMessage(QString strMsg, int timeout) {
    if (strMsg.isEmpty()) {
        return QString("");
    }

    m_socket->write(strMsg.toStdString().c_str());
    m_socket->flush();

    if (!m_socket->bytesAvailable())
        m_socket->waitForReadyRead(timeout);

    QTextStream stream(m_socket);
    QString respond = stream.readAll();
    //qDebug() << "Read Data From Server:" << respond;
    return respond;
}

void LocalSocketClient::socketConnectedHandler() {

}

void LocalSocketClient::socketDisConnectedHandler() {

}

void LocalSocketClient::socketErrorHandler(QLocalSocket::LocalSocketError error) {
    qInfo() << "LocalSocketClient::socketErrorHandler errno:" << error;
}

QString LocalSocketClient::sendActiveMessage() {
    QString strMsg = "{\"code\":200,\"cmd\":\"active\"}";
    return this->sendMessage(strMsg, 10000);
}

} // end namespace base
