#include "child_view_service.h"

#include "app.h"
#include "base/exception/error.h"
#include "base/util/tool_util.h"
#include "core/message/child_view_message.h"
#include "sdk/message_package.h"

#include <QDateTime>
#include <QJsonObject>
#include <QJsonArray>

using namespace base;

namespace core {

ChildViewService::ChildViewService(QObject* parent) : base::ServiceThread(this, parent), m_ipc_server(nullptr)
{
    // IPC
    m_ipc_server = new base::LocalSocketServer(this);
    if (m_ipc_server) {
        connect(m_ipc_server, SIGNAL(socketConnected(QString)), this, SLOT(onClientSocketConnected(QString)));
        connect(m_ipc_server, SIGNAL(socketDisConnected(QString)), this, SLOT(onClientSocketDisConnected(QString)));
        connect(m_ipc_server, SIGNAL(socketDataRecv(QString, QString)), this, SLOT(onClientSocketDataRecv(QString, QString)));
        connect(m_ipc_server, SIGNAL(socketStateChanged(QString, int)), this, SLOT(onClientSocketStateChanged(QString, int)));
        connect(m_ipc_server, SIGNAL(socketExceptionError(QString, int)), this, SLOT(onClientSocketExceptionError(QString, int)));
    }

}

ChildViewService::~ChildViewService() {

    if (m_ipc_server) {
        disconnect(m_ipc_server, SIGNAL(socketConnected(QString)), this, SLOT(onClientSocketConnected(QString)));
        disconnect(m_ipc_server, SIGNAL(socketDisConnected(QString)), this, SLOT(onClientSocketDisConnected(QString)));
        disconnect(m_ipc_server, SIGNAL(socketDataRecv(QString, QString)), this, SLOT(onClientSocketDataRecv(QString, QString)));
        disconnect(m_ipc_server, SIGNAL(socketStateChanged(QString, int)), this, SLOT(onClientSocketStateChanged(QString, int)));
        disconnect(m_ipc_server, SIGNAL(socketExceptionError(QString, int)), this, SLOT(onClientSocketExceptionError(QString, int)));

        m_ipc_server->deleteLater();
    }

}

void ChildViewService::onClientSocketConnected(QString strSessionId) {
    qDebug() << "ChildViewService::onClientSocketConnected sessionId:" << strSessionId;

    int ret = -1;
    // 有用户连接，发送欢迎消息
    QString strWelcome = hxxda::getIPCWelcomeMessage("欢迎用户连接到页面服务器!");
    if (m_ipc_server) {
        ret = m_ipc_server->write(strSessionId, strWelcome, 3000);
        qDebug() << "ChildViewService::onClientSocketConnected sedn welcome, status:" << ret    \
                 << ", welcome:" << strWelcome;
    }

}

void ChildViewService::onClientSocketDisConnected(QString strSessionId) {
    bool bret = this->onRemoveSession(strSessionId);
    qDebug() << "ChildViewService::onClientSocketDisConnected sessionId:" << strSessionId    \
             << ", onRemoveSession status:" << bret;

}

void ChildViewService::onClientSocketDataRecv(QString strSessionId, QString data) {
    // 解析接收到的IPC数据，以消息的方式放入处理队列
    base::MessageBase msg;
    if (msg.deserialize(data)) {
        this->addTask(msg.type, msg.data, msg.owner, msg.sender, msg.reciver, strSessionId);
    }
}

void ChildViewService::onClientSocketStateChanged(QString strSessionId, int state) {

}

void ChildViewService::onClientSocketExceptionError(QString strSessionId, int errorNo) {

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

int ChildViewService::beginRun(QString ipcServerName) {
    if (ipcServerName.isEmpty()) {
        ipcServerName = CHILD_VIEW_SERVICE_SERVER_NAME;
    }

    if (!m_ipc_server) {
        qInfo() << "ChildViewService::beginRun ipc server object pointer isNull";
        return -2;
    }

    int ret = -1;

    try {
        ret = m_ipc_server->beginRun(ipcServerName);
        qInfo() << "ChildViewService::beginRun ipc server beginRun status:" << ret;

        if (ret != 0) {
            return ret;
        }

        this->setRunning(true);
        this->start();
        ret = 0;
    }
    catch(...) {
        qInfo() << "ChildViewService::beginRun exception";
        ret = -3;
    }

    return ret;
}

int ChildViewService::write(const base::MessageBase* pMsg) {
    return 0;
}

//int ChildViewService::read(base::MessageBase* pMsg) {
//    return 0;
//}

int ChildViewService::process(base::MessageBase* pMsg) {
    if (!pMsg) {
        qInfo() << "ChildViewService::process params error";
        return ERROR_CODE_OK;
    }
    qDebug() << "ChildViewService::process params, type:" << pMsg->type \
             << ", data:" << pMsg->data \
             << ", sequeNo:" << pMsg->sequeNo   \
             << ", sender:" << pMsg->sender \
             << ", reciver:" << pMsg->reciver   \
             << ", owner:" << pMsg->owner;

    int status = ERROR_CODE_FAIL;
    int ret = ERROR_CODE_OK;
    switch (pMsg->type) {
    case CHILD_VIEW_MESSAGE_ADD_VIEW_REQUEST: {
        // 添加页面请求
        status = this->onProcessAddView(pMsg);
        ret = ERROR_CODE_OK;
    }break;
    case PUBLIC_MESSAGE_NODE_RESPONSE: {
        // 子进程上报节点信息消息
        status = this->onProcessNodeResponse(pMsg);
        ret = ERROR_CODE_OK;
    }break;
    default: {
        ret = ERROR_CODE_OK;
    }break;
    }
    return ret;
}

int ChildViewService::addView(QString title, QString owner) {
    if (title.isEmpty()) {
        title = "新标签页";
    }

    // 创建子页面请求消息
    ChildViewMessage* pMsg = new ChildViewMessage();
    if (pMsg) {
        pMsg->type = CHILD_VIEW_MESSAGE_ADD_VIEW_REQUEST;
        pMsg->owner = QString("%1").arg(owner);

        QJsonObject dataObj;
        dataObj.insert("title", title);

        pMsg->data = QString("%1").arg(base::MessageBase::buildMessage(ERROR_CODE_DATA_OK, "ok", dataObj));
    }

    return this->addTask(pMsg);
}

int ChildViewService::onProcessAddView(base::MessageBase* pMsg) {
    if (pMsg->type != CHILD_VIEW_MESSAGE_ADD_VIEW_REQUEST) {
        return ERROR_CODE_PARAM_ERROR;
    }

    int ret = ERROR_CODE_FAIL;
    QString strTitle("");
    QString strViewId("");

    QJsonObject obj = base::ToolUtil::qstringToQjsonobject(pMsg->data);
    if (obj.contains("code")) {
        int code = obj.value("code").toInt();
        if (code == ERROR_CODE_DATA_OK) {
            QJsonObject dataObj = obj.value("data").toObject();
            if (dataObj.contains("title")) {
                strTitle = dataObj.value("title").toString();
            }
        }
    }

    qDebug() << "ChildViewService::onProcessAddView params, title:" << strTitle \
             << ", owner:" << pMsg->owner;

    int timeout = 5000;

    // 启动页面子进程
    QProcess* process = getApp().getStartup()->startViewChildProcess(timeout);
    if (process) {
        strViewId = QString::number(process->processId());
        if (this->onAddSession(process, strTitle, pMsg->owner)) {
            ret = ERROR_CODE_OK;
        }
    }

    QJsonObject replayObj;
    if (ret == ERROR_CODE_OK) {
        // 成功
        replayObj.insert("code", ERROR_CODE_DATA_OK);
        replayObj.insert("msg", "成功");

        QJsonObject dataObj;
        dataObj.insert("viewId", strViewId);
        dataObj.insert("viewTitle", strTitle);

        replayObj.insert("data", dataObj);
    }
    else {
        // 失败
        if (process) {
            process->close();
            process->deleteLater();
        }
        if (!strViewId.isEmpty()) {
            strViewId = "";
        }

        replayObj.insert("code", ERROR_CODE_FAIL);
        replayObj.insert("msg", "失败");
    }

    emit childViewResponseEvent(CHILD_VIEW_MESSAGE_ADD_VIEW_RESPONSE, ret, replayObj, pMsg->owner);

    return ERROR_CODE_OK;
}

int ChildViewService::onProcessNodeResponse(base::MessageBase* pMsg) {
    qDebug() << "ChildViewService::onProcessNodeResponse params, type:" << pMsg->type   \
             << ", sender:" << pMsg->sender \
             << ", reciver:" << pMsg->reciver   \
             << ", data:" << pMsg->data\
             << ", owner:" << pMsg->owner   \
             << ", sequeNo:" << pMsg->sequeNo;

    // 更新会话信息(主要更新viewID，目前用子进程ID作为viewID)
    this->onModifySession(pMsg->sender, pMsg->sessionId);

    // 发送通知消息
    QJsonObject dataObj;
    dataObj.insert("viewId", pMsg->sender);
    dataObj.insert("sessionId", pMsg->sessionId);

    QJsonObject replayObj;
    replayObj.insert("code", ERROR_CODE_DATA_OK);
    replayObj.insert("msg", "成功");
    replayObj.insert("data", dataObj);

    emit childViewResponseEvent(PUBLIC_MESSAGE_NODE_RESPONSE, ERROR_CODE_OK, replayObj, pMsg->owner);

    return ERROR_CODE_OK;
}


} // end namespace core
