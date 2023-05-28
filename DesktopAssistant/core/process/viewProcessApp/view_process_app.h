#ifndef VIEW_PROCESS_APP_H
#define VIEW_PROCESS_APP_H

#include "base/childProcess/child_process_app.h"
#include "base/util/command_line.h"
#include "core/service/common/ipc_client_service.h"
#include "core/message/default_message_handler.h"

#include <QObject>
#include <QProcess>
#include <QSocketNotifier>
#include <QFile>

namespace core {

/*
 * ClassName: ViewProcessApp
 * Desc: 页面进程应用类
 * Author: zfs
 * Date: 2023-05-20 20:32
 */
class ViewProcessApp : public QObject, public base::ChildProcessApp, public core::DefaultMessageHandler
{
    Q_OBJECT
public:
    ViewProcessApp();
    virtual ~ViewProcessApp();

    //
    // base::ChildProcessApp
    //
    virtual int init(int argc, char* argv[], void* owner = nullptr) override;
    virtual int exec() override;
    virtual int quit(int exitCode) override;

    //
    // core::DefaultMessageHandler
    //
    virtual int process(base::MessageBase* pMsg) override;


public slots:

    //
    // core::IPCClientService
    //
    void onSelfSocketConnected();
    void onSelfSocketDisConnected();
    void onSelfSocketDataRecv(QString data);
    void onSelfSocketStateChanged(int state);
    void onSelfSocketExceptionError(int errorNo);


public:
signals:



private:
    //
    // onProcessWelcome : 处理欢迎消息
    //
    int onProcessWelcome(base::MessageBase* pMsg);

    bool m_running;
    int m_exit_code;

    base::CommandLine* m_command_line; // 传递进来的命令行参数指针

    // ipc
    core::IPCClientService* m_ipc_service;

    // 进程节点信息
    base::IPC_NODE_INFO m_node_info;

};

} // end namespace core

#endif // VIEW_PROCESS_APP_H
