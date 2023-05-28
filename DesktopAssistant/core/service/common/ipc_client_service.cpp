#include "ipc_client_service.h"

#include "base/exception/error.h"

namespace core {

IPCClientService::IPCClientService(base::MessageHandlerBase* pMsgHandler, QObject* parent) : base::ServiceThread(pMsgHandler, parent),
    m_ipc_client(nullptr)
{
    m_ipc_client = new base::LocalSocketClient(this);
    if (m_ipc_client) {
        connect(m_ipc_client, SIGNAL(socketConnected()), this, SLOT(onSocketConnected()) );
        connect(m_ipc_client, SIGNAL(socketDisConnected()), this, SLOT(onSocketDisConnected()) );
        connect(m_ipc_client, SIGNAL(socketDataRecv(QString)), this, SLOT(onSocketDataRecv(QString)) );
        connect(m_ipc_client, SIGNAL(socketStateChanged(int)), this, SLOT(onSocketStateChanged(int)) );
        connect(m_ipc_client, SIGNAL(socketExceptionError(int)), this, SLOT(onSocketExceptionError(int)) );

    }

}

IPCClientService::~IPCClientService() {
    if (m_ipc_client) {
        disconnect(m_ipc_client, SIGNAL(socketConnected()), this, SLOT(onSocketConnected()) );
        disconnect(m_ipc_client, SIGNAL(socketDisConnected()), this, SLOT(onSocketDisConnected()) );
        disconnect(m_ipc_client, SIGNAL(socketDataRecv(QString)), this, SLOT(onSocketDataRecv(QString)) );
        disconnect(m_ipc_client, SIGNAL(socketStateChanged(int)), this, SLOT(onSocketStateChanged(int)) );
        disconnect(m_ipc_client, SIGNAL(socketExceptionError(int)), this, SLOT(onSocketExceptionError(int)) );

        m_ipc_client->deleteLater();
    }
}

void IPCClientService::onSocketConnected() {
    emit selfSocketConnected();
}

void IPCClientService::onSocketDisConnected() {
    emit selfSocketDisConnected();
}

void IPCClientService::onSocketDataRecv(QString data) {
    emit selfSocketDataRecv(data);
}

void IPCClientService::onSocketStateChanged(int state) {
    emit selfSocketStateChanged(state);
}

void IPCClientService::onSocketExceptionError(int errorNo) {
    emit selfSocketExceptionError(errorNo);
}

int IPCClientService::connectTo(QString ipcServerName, int timeout) {
    if (ipcServerName.isEmpty()) {
        return ERROR_CODE_PARAM_ERROR;
    }
    if (!m_ipc_client) {
        return ERROR_CODE_INNER_ERROR;
    }
    return m_ipc_client->beginConnect(ipcServerName, timeout);
}

int IPCClientService::closeConnect() {
    if (m_ipc_client) {
        m_ipc_client->endConnect();
    }
    return 0;
}

int IPCClientService::send(const QString& data, int timeout) {
    if (!m_ipc_client) {
        return ERROR_CODE_INNER_ERROR;
    }
    if (data.isEmpty()) {
        return 0;
    }
    return m_ipc_client->sendMessage(data, timeout);
}

} // end namespace core
