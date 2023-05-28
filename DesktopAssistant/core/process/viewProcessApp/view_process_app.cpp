#include "view_process_app.h"

#include "base/exception/error.h"
#include "sdk/dasdk.h"
#include "sdk/message_package.h"

#include <QApplication>

namespace core {

ViewProcessApp::ViewProcessApp() : QObject(nullptr), m_running(true), m_exit_code(0),
    m_command_line(nullptr), m_ipc_service(nullptr)
{

    m_ipc_service = new core::IPCClientService(this, this);
    if (m_ipc_service) {
        connect(m_ipc_service, SIGNAL(selfSocketConnected()), this, SLOT(onSelfSocketConnected()) );
        connect(m_ipc_service, SIGNAL(selfSocketDisConnected()), this, SLOT(onSelfSocketDisConnected()) );
        connect(m_ipc_service, SIGNAL(selfSocketDataRecv(QString)), this, SLOT(onSelfSocketDataRecv(QString)) );
        connect(m_ipc_service, SIGNAL(selfSocketStateChanged(int)), this, SLOT(onSelfSocketStateChanged(int)) );
        connect(m_ipc_service, SIGNAL(selfSocketExceptionError(int)), this, SLOT(onSelfSocketExceptionError(int)) );

    }

    // 初始化自身节点信息
    m_node_info.selfPID = QString::number(QApplication::applicationPid());

}

ViewProcessApp::~ViewProcessApp() {

    if (m_ipc_service) {
        disconnect(m_ipc_service, SIGNAL(selfSocketConnected()), this, SLOT(onSelfSocketConnected()) );
        disconnect(m_ipc_service, SIGNAL(selfSocketDisConnected()), this, SLOT(onSelfSocketDisConnected()) );
        disconnect(m_ipc_service, SIGNAL(selfSocketDataRecv(QString)), this, SLOT(onSelfSocketDataRecv(QString)) );
        disconnect(m_ipc_service, SIGNAL(selfSocketStateChanged(int)), this, SLOT(onSelfSocketStateChanged(int)) );
        disconnect(m_ipc_service, SIGNAL(selfSocketExceptionError(int)), this, SLOT(onSelfSocketExceptionError(int)) );


        m_ipc_service->deleteLater();
    }

}

int ViewProcessApp::init(int argc, char* argv[], void* owner) {
    if (owner) {
        m_command_line = (base::CommandLine*)owner;
    }
    else {
        m_command_line = hxxda::getCommandLine();
    }

    int ret = -1;
    // 根据参数，解析IPC管道名称，连接父进程管道服务
    QString ipcServerName;
    if (m_command_line->contain(base::CommandLine::getViewIPCServerNameKey())) {
        ipcServerName = m_command_line->getItemValue(base::CommandLine::getViewIPCServerNameKey());
    }
    if (ipcServerName.isEmpty()) {
        ipcServerName = CHILD_VIEW_SERVICE_SERVER_NAME;
    }

    // 连接ipc服务器
    ret = m_ipc_service->connectTo(ipcServerName, 5000);

    return ret;
}

int ViewProcessApp::quit(int exitCode) {
    m_exit_code = exitCode;
    if (m_running) {
        m_running = false;
    }
    return 0;
}

int ViewProcessApp::exec() {
    int ret = -1;
    while(m_running) {
        QThread::msleep(1000);
    }
    return ret;
}

void ViewProcessApp::onSelfSocketConnected() {

}

void ViewProcessApp::onSelfSocketDisConnected() {

}

void ViewProcessApp::onSelfSocketDataRecv(QString data) {
    //
    // data => base::MessageBase
    //
    if (m_ipc_service) {
        int ret = -1;
        base::MessageBase msg;
        if (msg.deserialize(data)) {
            ret = m_ipc_service->addTask(msg.type, msg.data, msg.owner, msg.sender, msg.reciver);
        }

    }
}

void ViewProcessApp::onSelfSocketStateChanged(int state) {

}

void ViewProcessApp::onSelfSocketExceptionError(int errorNo) {

}

int ViewProcessApp::process(base::MessageBase* pMsg) {
    int ret = 0;
    switch (pMsg->type) {
    case PUBLIC_MESSAGE_WELCOME_REQUEST: {
        // 欢迎消息
        ret = this->onProcessWelcome(pMsg);
        ret = ERROR_CODE_OK;
    }break;
    }
    return ret;
}

int ViewProcessApp::onProcessWelcome(base::MessageBase* pMsg) {
    // 保存主进程ID
    m_node_info.mainPID = QString("%1").arg(pMsg->sender);

    // 发送自己节点信息
    QString strNodeMsg = hxxda::getIPCNodeResponseMessage(m_node_info.selfPID, m_node_info.mainPID, "");
    int ret = m_ipc_service->send(strNodeMsg);
    return ret;
}


} // end namespace core
