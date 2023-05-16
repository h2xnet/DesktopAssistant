#include "local_socket_server.h"

#include "base/define.h"
#include <QLocalSocket>

namespace base {

LocalSocketServer::LocalSocketServer(QObject* parent) : QObject(parent), m_server(nullptr)
{
    m_server = new QLocalServer(this);
    if (m_server) {
        connect(m_server, SIGNAL(newConnection()), this, SLOT(newConnectHandler()));
    }
}

LocalSocketServer::~LocalSocketServer() {
    if (m_server) {
        disconnect(m_server, SIGNAL(newConnection), this, SLOT(newConnectHandler()));
        //if (m_server->isListening()) {
        //    m_server->close();
        //}
        m_server->close();
        delete m_server;
        m_server = nullptr;
    }
}

int LocalSocketServer::beginListen(QString serverName) {
    if (serverName.isEmpty()) {
        serverName = DEF_LOCAL_SOCKET_SERVER_NAME;
    }

    m_server_name = QString("%1").arg(serverName);

    QLocalServer::removeServer(serverName);
    bool bret = m_server->listen(serverName);
    qInfo() << "LocalSocketServer::beginListen listen status:" << bret  \
            << ", serverName:" << serverName    \
            << ", errmsg:" << m_server->errorString();

    return bret ? 0 : -2;
}

void LocalSocketServer::endListen() {
    qInfo() << "LocalSocketServer::endListen";
    if (m_server) {

        //if (m_server->isListening()) {
        //    m_server->close();
        //    qInfo() << "LocalSocketServer::endListen close";
        //}

        m_server->close();

        QLocalServer::removeServer(m_server_name);

    }
}

void LocalSocketServer::newConnectHandler() {
    qInfo() << "LocalSocketServer New Connection, listen:" << m_server->serverName();

    QLocalSocket* socket = m_server->nextPendingConnection();
    connect(socket, SIGNAL(readyRead()), this, SLOT(socketReadyReadHandler()));
    connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()));

}

void LocalSocketServer::socketReadyReadHandler() {
    QLocalSocket* socket = static_cast<QLocalSocket*>(sender());
    if (socket) {
        QTextStream stream(socket);
        QString strData = stream.readAll();
        qDebug() << "LocalSocketServer Read Data From Client:" << strData;

        emit localSocketServerRecv(strData);

        QString response = onGetAckMessage();
        socket->write(response.toUtf8());
        socket->flush();
        qDebug() << "LocalSocketServer response:" << response;
    }
    // 返回到客户端的void sendMessage 方法，m_socket->waitForReadyRead()之后的操作

}

QString LocalSocketServer::onGetAckMessage() {
    QString strMsg = "{\"code\":200, \"msg\":\"ok\"}";
    return strMsg;
}

} // end namespace base
