#include "child_view_service.h"

#include "base/exception/error.h"
#include "core/message/child_view_message.h"
#include "app.h"

#include <QDateTime>
#include <QJsonObject>
#include <QJsonArray>

namespace core {

ChildViewService::ChildViewService(QObject* parent) : base::ServiceThread(this, parent), m_ipc_server(nullptr)
{
    // IPC
    m_ipc_server = new IPCServerService();
    if (m_ipc_server) {

        connect(m_ipc_server, SIGNAL(clientSocketConnectedHandler(QString)),
                this, SLOT(onClientSocketConnectedHandler(QString)));

        connect(m_ipc_server, SIGNAL(clientSocketDisConnectedHandler(QString)),
                this, SLOT(onClientSocketDisConnectedHandler(QString)));

        connect(m_ipc_server, SIGNAL(clientSocketDataRecvHandler(QString, QString)),
                this, SLOT(onClientSocketDataRecvHandler(QString, QString)));

        connect(m_ipc_server, SIGNAL(clientSocketStateChangedHandler(QString, int)),
                this, SLOT(onClientSocketStateChangedHandler(QString, int)));

        connect(m_ipc_server, SIGNAL(clientSocketExceptionErrorHandler(QString, int)),
                this, SLOT(onClientSocketExceptionErrorHandler(QString, int)));


    }

}

ChildViewService::~ChildViewService() {

    if (m_ipc_server) {
        disconnect(m_ipc_server, SIGNAL(clientSocketConnectedHandler(QString)),
                this, SLOT(onClientSocketConnectedHandler(QString)));

        disconnect(m_ipc_server, SIGNAL(clientSocketDisConnectedHandler(QString)),
                this, SLOT(onClientSocketDisConnectedHandler(QString)));

        disconnect(m_ipc_server, SIGNAL(clientSocketDataRecvHandler(QString, QString)),
                this, SLOT(onClientSocketDataRecvHandler(QString, QString)));

        disconnect(m_ipc_server, SIGNAL(clientSocketStateChangedHandler(QString, int)),
                this, SLOT(onClientSocketStateChangedHandler(QString, int)));

        disconnect(m_ipc_server, SIGNAL(clientSocketExceptionErrorHandler(QString, int)),
                this, SLOT(onClientSocketExceptionErrorHandler(QString, int)));

        delete m_ipc_server;
        m_ipc_server = nullptr;
    }

}

void ChildViewService::onClientSocketConnectedHandler(QString strSessionId) {
    qDebug() << "ChildViewService::onClientSocketConnectedHandler sessionId:" << strSessionId;

}

void ChildViewService::onClientSocketDisConnectedHandler(QString strSessionId) {
    bool bret = this->onRemoveSession(strSessionId);
    qDebug() << "ChildViewService::onClientSocketDisConnectedHandler sessionId:" << strSessionId    \
             << ", onRemoveSession status:" << bret;

}

void ChildViewService::onClientSocketDataRecvHandler(QString strSessionId, QString data) {
    // 解析接收到的IPC数据，以消息的方式放入处理队列

}

void ChildViewService::onClientSocketStateChangedHandler(QString strSessionId, int state) {

}

void ChildViewService::onClientSocketExceptionErrorHandler(QString strSessionId, int errorNo) {

}

int ChildViewService::write(const base::MessageBase* pMsg) {
    return 0;
}

//int ChildViewService::read(base::MessageBase* pMsg) {
//    return 0;
//}

int ChildViewService::process(base::MessageBase* pMsg) {
    return 0;
}

int ChildViewService::addView(QString title, QString owner) {
    if (title.isEmpty()) {
        title = "新标签页";
    }

    // 创建子页面请求消息
    ChildViewMessage* pMsg = new ChildViewMessage();
    if (pMsg) {
        pMsg->type = pMsg->getRequestTypeValue(ChildViewMessage::ChildViewMessageType::eAddViewTypeIndex);
        pMsg->owner = QString("%1").arg(owner);

        QJsonObject dataObj;
        dataObj.insert("title", title);

        pMsg->data = QString("%1").arg(base::MessageBase::buildMessage(ERROR_CODE_DATA_OK, "ok", dataObj));
    }

    return this->addTask(pMsg);

    /*int timeout = 5000;
    // 启动页面子进程
    QProcess* process = getApp().getStartup()->startViewChildProcess(timeout);
    if (!process) {
        // 启动失败
        qInfo() << "ChildViewService::addView startViewChildProcess fail, title:" << title;
        delete process;
        process = nullptr;
        return QString("");
    }

    // start方式启动的时间才有效
    QString viewId = QString::number(process->processId());

    // 保存会话信息
    if (!this->onAddSession(process, title, owner)) {
        qInfo() << "ChildViewService::addView onAddSession fail, title:" << title;
        // 关闭进程
        process->close();
        process->deleteLater();
        return QString("");
    }

    return viewId;*/
}

bool ChildViewService::onAddSession(QProcess* process, const QString& title, const QString& owner) {
    if (!process) {
        return false;
    }

    VIEW_SESSION* pSession = new VIEW_SESSION();

    pSession->viewId = QString::number(process->processId());
    pSession->process = process;
    pSession->title = QString("%1").arg(title);
    pSession->owner = QString("%1").arg(owner);
    pSession->createTime = QDateTime::currentMSecsSinceEpoch();
    pSession->modifyTime = pSession->createTime;

    QMutexLocker lock(&m_session_mutex);
    m_session_map[pSession->viewId] = pSession;

    return true;
}

bool ChildViewService::onRemoveSession(const QString& strSessionId) {
    bool bret = false;
    if (!strSessionId.isEmpty() && m_session_to_view_map.contains(strSessionId)) {
        if (m_session_mutex.tryLock(3000)) {
            QString strViewId = m_session_to_view_map.value(strSessionId, "");
            if (!strViewId.isEmpty()) {
                auto it = m_session_map.find(strViewId);
                if (it != m_session_map.end()) {
                    VIEW_SESSION* pSession = it.value();
                    if (pSession) {
                        if (pSession->process != nullptr) {
                            pSession->process->deleteLater();
                        }
                        delete pSession;
                        pSession = nullptr;
                    }
                    m_session_map.erase(it);
                    m_session_to_view_map.remove(strSessionId);
                    bret = true;
                }
            }

            m_session_mutex.unlock();
        }
    }
    return bret;
}

bool ChildViewService::onModifySession(const QString& viewId, const QString& strSessionId) {
    if (!viewId.isEmpty()) {
        QMutexLocker lock(&m_session_mutex);
        if (m_session_map.contains(viewId)) {
            VIEW_SESSION* pSession = m_session_map.value(viewId, nullptr);
            if (pSession) {
                pSession->sessionId = QString("%1").arg(strSessionId);
                pSession->modifyTime = QDateTime::currentMSecsSinceEpoch();
                return true;
            }
        }
    }
    return false;
}


} // end namespace core
