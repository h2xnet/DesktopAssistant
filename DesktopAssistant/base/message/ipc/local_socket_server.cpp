#include "local_socket_server.h"

#include "base/define.h"
#include "base/util/tool_util.h"

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

int LocalSocketServer::beginRun(QString serverName) {
    if (serverName.isEmpty()) {
        serverName = DEF_LOCAL_SOCKET_SERVER_NAME;
    }

    m_server_name = QString("%1").arg(serverName);

    QLocalServer::removeServer(serverName);
    bool bret = m_server->listen(serverName);
    qInfo() << "LocalSocketServer::beginRun listen status:" << bret  \
            << ", serverName:" << serverName    \
            << ", errmsg:" << m_server->errorString();

    return bret ? 0 : -2;
}

void LocalSocketServer::endRun() {
    qInfo() << "LocalSocketServer::endRun";
    if (m_server) {

        // 结束所有会话
        this->onEndAllSocket();

        m_server->close();

        QLocalServer::removeServer(m_server_name);

    }
}

int LocalSocketServer::write(const QString& strSessionId, const QString& data, int timeout) {
    if (strSessionId.isEmpty() || data.isEmpty()) {
        return -1;
    }
    int ret = -1;
    bool bret = false;
    QLocalSocket* pSocket = this->onGetSocket(strSessionId);
    if (pSocket) {
        bret = true;
        ret = pSocket->write(data.toUtf8().data(), data.toUtf8().size());
        pSocket->flush();
        if (timeout > 0) {
            bret = pSocket->waitForReadyRead(timeout);
        }
    }
    return bret ? ret : 0;
}

void LocalSocketServer::newConnectHandler() {
    qInfo() << "LocalSocketServer New Connection, listen:" << m_server->serverName();

    // 创建会话socket
    QLocalSocket* socket = m_server->nextPendingConnection();
    if (socket) {
        connect(socket, SIGNAL(connected()), this, SLOT(onSocketConnected()));
        connect(socket, SIGNAL(disconnected()), this, SLOT(onSocketDisConnected()));
        connect(socket, SIGNAL(error(QLocalSocket::LocalSocketError)), this, SLOT(onSocketError(QLocalSocket::LocalSocketError)));
        connect(socket, SIGNAL(readyRead()), this, SLOT(onSocketReadyRead()));
        connect(socket, SIGNAL(stateChanged(QLocalSocket::LocalSocketState)), this, SLOT(onSocketStateChanged(QLocalSocket::LocalSocketState)));
    }
}

void LocalSocketServer::onSocketConnected() {
    QLocalSocket* socket = static_cast<QLocalSocket*>(sender());

    if (socket) {
        // 生成唯一会话ID
        QString strSessionId = base::ToolUtil::getUuid();

        {
            QMutexLocker lock(&m_mutex);
            // 保存缓存
            session_to_socket[strSessionId] = socket;
            socket_to_session[socket] = strSessionId;
        }

        // 发送通知
        emit socketConnected(strSessionId);
    }

}

void LocalSocketServer::onSocketDisConnected() {
    QLocalSocket* socket = static_cast<QLocalSocket*>(sender());
    if (socket) {
        QString strSessionId = onGetSessionId(socket);
        this->onRemoveSessionId(strSessionId);
        this->onRemoveSocket(socket);

        socket->deleteLater();

        if (!strSessionId.isEmpty()) {
            emit socketDisConnected(strSessionId);
        }
    }
}

void LocalSocketServer::onSocketError(QLocalSocket::LocalSocketError socketError) {
    QLocalSocket* socket = static_cast<QLocalSocket*>(sender());
    if (socket) {
        QString strSessionId = onGetSessionId(socket);
        if (!strSessionId.isEmpty()) {
            emit socketExceptionError(strSessionId, socketError);
        }
    }

}

void LocalSocketServer::onSocketReadyRead() {
    QLocalSocket* socket = static_cast<QLocalSocket*>(sender());
    if (socket) {
        // 获取会话ID
        QString strSessionId = onGetSessionId(socket);
        if (strSessionId.isEmpty()) {
            // 无效会话不处理
            return;
        }

        QTextStream stream(socket);
        QString strData = stream.readAll();
        qDebug() << "LocalSocketServer::onSocketReadyRead Read Data From Client:" << strData;

        emit socketDataRecv(strSessionId, strData);

        //QString response = onGetAckMessage();
        //socket->write(response.toUtf8());
        //socket->flush();
        //qDebug() << "LocalSocketServer response:" << response;
    }
    // 返回到客户端的void sendMessage 方法，m_socket->waitForReadyRead()之后的操作

}

void LocalSocketServer::onSocketStateChanged(QLocalSocket::LocalSocketState socketState) {
    QLocalSocket* socket = static_cast<QLocalSocket*>(sender());
    if (socket) {
        QString strSessionId = onGetSessionId(socket);
        if (!strSessionId.isEmpty()) {
            emit socketStateChanged(strSessionId, socketState);
        }
    }

}

QString LocalSocketServer::onGetSessionId(const QLocalSocket* socket) {
    QString strSessionId("");
    if (socket && socket_to_session.contains(socket)) {
        QMutexLocker lock(&m_mutex);
        strSessionId = socket_to_session.value(socket, "");
    }

    return strSessionId;
}

QLocalSocket* LocalSocketServer::onGetSocket(const QString& strSessionId) {
    QLocalSocket* socket = nullptr;

    if (!strSessionId.isEmpty() && session_to_socket.contains(strSessionId)) {
        QMutexLocker lock(&m_mutex);
        socket = (QLocalSocket*)session_to_socket.value(strSessionId, nullptr);
    }

    return socket;
}

bool LocalSocketServer::onRemoveSessionId(const QString& strSessionId) {
    if (!strSessionId.isEmpty() && session_to_socket.contains(strSessionId)) {
        QMutexLocker lock(&m_mutex);
        session_to_socket.remove(strSessionId);
        return true;
    }

    return false;
}

bool LocalSocketServer::onRemoveSocket(const QLocalSocket* socket) {
    if (socket && socket_to_session.contains(socket)) {
        QMutexLocker lock(&m_mutex);
        socket_to_session.remove(socket);
        return true;
    }
    return false;
}

void LocalSocketServer::onEndAllSocket() {
    if (!socket_to_session.isEmpty()) {
        QString strQuitMsg = this->onGetQuitMessage();
        QLocalSocket* pSocket = nullptr;
        QMutexLocker lock(&m_mutex);
        for(auto it = socket_to_session.begin(); it != socket_to_session.end(); it++) {
            pSocket = (QLocalSocket*)it.key();
            if (pSocket) {
                pSocket->write(strQuitMsg.toUtf8().data(), strQuitMsg.toUtf8().size());

                pSocket->deleteLater();
            }
        }

        socket_to_session.clear();
        session_to_socket.clear();
    }
}

QString LocalSocketServer::onGetAckMessage() {
    QString strMsg = "{\"code\":200, \"msg\":\"ok\"}";
    return strMsg;
}

QString LocalSocketServer::onGetQuitMessage() {
    QString strMsg = "{\"code\":200, \"msg\":\"ok\", \"cmd\":\"quit\"}";
    return strMsg;
}

} // end namespace base
