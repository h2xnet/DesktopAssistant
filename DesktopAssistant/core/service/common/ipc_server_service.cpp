#include "ipc_server_service.h"
#include "base/exception/error.h"

namespace core {

IPCServerService::IPCServerService() : base::ServiceThread(this, this), m_ipc_server(nullptr)
{
    m_ipc_server = new base::LocalSocketServer(this);
    if (m_ipc_server) {
        connect(m_ipc_server, SIGNAL(socketConnected(QString)), this, SLOT(onClientSocketConnected(QString)));
        connect(m_ipc_server, SIGNAL(socketDisConnected(QString)), this, SLOT(onClientSocketDisConnected(QString)));
        connect(m_ipc_server, SIGNAL(socketDataRecv(QString, QString)), this, SLOT(onClientSocketDataRecv(QString, QString)));
        connect(m_ipc_server, SIGNAL(socketStateChanged(QString, int)), this, SLOT(onClientSocketStateChanged(QString, int)));
        connect(m_ipc_server, SIGNAL(socketExceptionError(QString, int)), this, SLOT(onClientSocketExceptionError(QString, int)));

    }
}

IPCServerService::~IPCServerService() {
    if (m_ipc_server) {
        disconnect(m_ipc_server, SIGNAL(socketConnected(QString)), this, SLOT(onClientSocketConnected(QString)));
        disconnect(m_ipc_server, SIGNAL(socketDisConnected(QString)), this, SLOT(onClientSocketDisConnected(QString)));
        disconnect(m_ipc_server, SIGNAL(socketDataRecv(QString, QString)), this, SLOT(onClientSocketDataRecv(QString, QString)));
        disconnect(m_ipc_server, SIGNAL(socketStateChanged(QString, int)), this, SLOT(onClientSocketStateChanged(QString, int)));
        disconnect(m_ipc_server, SIGNAL(socketExceptionError(QString, int)), this, SLOT(onClientSocketExceptionError(QString, int)));

        m_ipc_server->deleteLater();
    }
}

int IPCServerService::init(QString ipcServerName) {
    return 0;
}

int IPCServerService::write(QString strSessionId, QString data, int timeout) {
    int ret = -1;
    if (m_ipc_server) {
        ret = m_ipc_server->write(strSessionId, data, timeout);
    }
    return ret;
}

void IPCServerService::onClientSocketConnected(QString strSessionId) {
    emit clientSocketConnectedHandler(strSessionId);

}

void IPCServerService::onClientSocketDisConnected(QString strSessionId) {
    emit clientSocketDisConnectedHandler(strSessionId);

}

void IPCServerService::onClientSocketDataRecv(QString strSessionId, QString data) {
    emit clientSocketDataRecvHandler(strSessionId, data);

}

void IPCServerService::onClientSocketStateChanged(QString strSessionId, int state) {
    emit clientSocketStateChangedHandler(strSessionId, state);

}

void IPCServerService::onClientSocketExceptionError(QString strSessionId, int errorNo) {
    emit clientSocketExceptionErrorHandler(strSessionId, errorNo);

}

int IPCServerService::write(const base::MessageBase* pMsg) {
    return 0;
}

int IPCServerService::read(base::MessageBase* pMsg) {
    return 0;
}

bool IPCServerService::serialize(const base::MessageBase* pMsg, base::Buffer* pBuffer) {
    return true;
}

bool IPCServerService::deserialize(const base::Buffer* pBuffer, base::MessageBase* pMsg) {
    return true;
}

int IPCServerService::process(base::MessageBase* pMsg) {
    return ERROR_CODE_OK;
}


} // end namespace core
