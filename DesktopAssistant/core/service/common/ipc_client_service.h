#ifndef IPC_CLIENT_SERVICE_H
#define IPC_CLIENT_SERVICE_H

#include "base/message/ipc/local_socket_client.h"
#include "base/thread/service_thread.h"
#include "base/message/message_handler_base.h"

namespace core {


/*
 * ClassName: IPCClientService
 * Desc: IPC客户端服务类
 * Author: zfs
 * Date: 2023-05-28 08:59
 */
class IPCClientService : public base::ServiceThread
{
    Q_OBJECT
public:
    IPCClientService(base::MessageHandlerBase* pMsgHandler, QObject* parent = nullptr);
    virtual ~IPCClientService();

    /*
     * Func: connectTo
     * Desc: 连接到服务器
     * Author: zfs
     * Date: 2023-05-28 09:22
     * @ipcServerName: IPC服务器名称（内部用命名管道进行IPC通信）
     * @timeout: 超时时间，单位：毫秒
     */
    Q_INVOKABLE int connectTo(QString ipcServerName, int timeout = 5000);

    /*
     * Func: closeConnect
     * Desc: 关闭连接
     * Author: zfs
     * Date: 2023-05-28 09:29
     */
    Q_INVOKABLE int closeConnect();

    /*
     * Func: send
     * Desc: 发送数据
     * Author: zfs
     * Date: 2023-05-28 09:30
     * @data: 待发送的数据
     * @timeout: 发送超时时间
     * 返回值：成功返回发送的长度，失败返回错误码
     */
    Q_INVOKABLE int send(const QString& data, int timeout = 3000);


public slots:

    //
    // base::LocalSocketClient
    //
    void onSocketConnected();
    void onSocketDisConnected();
    void onSocketDataRecv(QString data);
    void onSocketStateChanged(int state);
    void onSocketExceptionError(int errorNo);

public:
signals:

    void selfSocketConnected();
    void selfSocketDisConnected();
    void selfSocketDataRecv(QString data);
    void selfSocketStateChanged(int state);
    void selfSocketExceptionError(int errorNo);

private:

    base::LocalSocketClient* m_ipc_client;

};

} // end namespace core

#endif // IPC_CLIENT_SERVICE_H
