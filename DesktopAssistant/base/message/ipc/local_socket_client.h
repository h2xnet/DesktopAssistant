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
    QString sendMessage(QString strMsg, int timeout = 15000);

    //
    // sendActiveMessage : 发送激活消息
    //
    QString sendActiveMessage();

public slots:

    void socketConnectedHandler();
    void socketDisConnectedHandler();
    void socketErrorHandler(QLocalSocket::LocalSocketError error);

public:
signals:

private:
    QLocalSocket* m_socket;
};

} // end namespace base

#endif // LOCAL_SOCKET_CLIENT_H
