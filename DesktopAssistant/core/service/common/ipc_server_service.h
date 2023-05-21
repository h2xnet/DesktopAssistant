#ifndef IPC_SERVER_SERVICE_H
#define IPC_SERVER_SERVICE_H

#include "base/message/ipc/local_socket_server.h"
#include "base/thread/service_thread.h"
#include "core/message/default_message_handler.h"

namespace core {

/*
 * ClassName: IPCServerService
 * Desc: 进程间通信服务类
 * Author: zfs
 * Date: 2023-05-21 08:24
 */
class IPCServerService : public base::ServiceThread, public core::DefaultMessageHandler
{
    Q_OBJECT
public:
    IPCServerService();
    virtual ~IPCServerService();

    /*
     * Func: init
     * Desc: IPC服务初始化
     * Author: zfs
     * Date: 2023-05-21 08:54
     * @ipcServerName: IPC服务名称，当前IPC内部使用命名管道进行通信
     */
    Q_INVOKABLE int init(QString ipcServerName);

    Q_INVOKABLE int write(QString strSessionId, QString data, int timeout = 5000);

    //
    // base::ServiceThread
    //


    //
    // core::DefaultMessageHandler
    //
    virtual int write(const base::MessageBase* pMsg) override;
    virtual int read(base::MessageBase* pMsg) override;
    virtual bool serialize(const base::MessageBase* pMsg, base::Buffer* pBuffer) override;
    virtual bool deserialize(const base::Buffer* pBuffer, base::MessageBase* pMsg) override;
    virtual int process(base::MessageBase* pMsg) override;

public slots:

    //
    // 客户IPC会话事件
    //
    void onClientSocketConnected(QString strSessionId);
    void onClientSocketDisConnected(QString strSessionId);
    void onClientSocketDataRecv(QString strSessionId, QString data);
    void onClientSocketStateChanged(QString strSessionId, int state);
    void onClientSocketExceptionError(QString strSessionId, int errorNo);

public:
signals:

    void clientSocketConnectedHandler(QString strSessionId);
    void clientSocketDisConnectedHandler(QString strSessionId);
    void clientSocketDataRecvHandler(QString strSessionId, QString data);
    void clientSocketStateChangedHandler(QString strSessionId, int state);
    void clientSocketExceptionErrorHandler(QString strSessionId, int errorNo);

private:

    // ipc服务对象
    base::LocalSocketServer* m_ipc_server;


};

} // end namespace core

#endif // IPC_SERVER_SERVICE_H
