#ifndef LOCAL_SOCKET_CLIENT_H
#define LOCAL_SOCKET_CLIENT_H

#include <QLocalSocket>
#include <QObject>

namespace base {

/*
 * ClassName: LocalSocketClient
 * Desc: IPC客户端
 * Author: zfs
 * Date: 2023-05-16 20:46
 */
class LocalSocketClient : public QObject
{
    Q_OBJECT
public:
    LocalSocketClient(QObject* parent = nullptr);
    virtual ~LocalSocketClient();

    int beginConnect(QString serverName, int timeout = 5000);

    void endConnect();

    //
    // sendMessage : 发送消息
    //
    int sendMessage(QString strMsg, int timeout = 15000);

    //
    // sendActiveMessage : 发送激活消息
    //
    int sendActiveMessage();

public slots:

    void onSocketConnected();
    void onSocketDisConnected();
    void onSocketError(QLocalSocket::LocalSocketError error);
    void onStateChanged(QLocalSocket::LocalSocketState socketState);
    void onSocketReadyRead();

public:
signals:

    //
    // socketConnected : 会话建议成功
    //
    void socketConnected();

    //
    // socketDisConnected : 会话已经断开
    //
    void socketDisConnected();

    //
    // socketDataRecv : 会话数据接收
    //
    void socketDataRecv(QString data);

    //
    // socketStateChanged : 会话状态改变
    //
    void socketStateChanged(int state);

    //
    // socketExceptionError : 会话发生错误
    //
    void socketExceptionError(int errorNo);

private:
    QLocalSocket* m_socket;
};

} // end namespace base

#endif // LOCAL_SOCKET_CLIENT_H
