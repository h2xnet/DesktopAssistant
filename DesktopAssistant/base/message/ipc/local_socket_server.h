#ifndef LOCAL_SOCKET_SERVER_H
#define LOCAL_SOCKET_SERVER_H

#include <QObject>
#include <QLocalServer>

namespace base {

/*
 * ClassName: LocalSocketServer
 * Desc: IPC服务端
 * Author: zfs
 * Date: 2023-05-16 20:43
 */
class LocalSocketServer : public QObject
{
    Q_OBJECT
public:
    LocalSocketServer(QObject* parent = nullptr);

    virtual ~LocalSocketServer();

    Q_INVOKABLE int beginListen(QString serverName);

    Q_INVOKABLE void endListen();

public slots:

    void newConnectHandler();

    void socketReadyReadHandler();

public:
signals:

    //
    // localSocketServerRecv : 接收到的消息
    //
    void localSocketServerRecv(QString data);

private:

    QString onGetAckMessage();

    QLocalServer* m_server;

    QString m_server_name;
};


} // end namespace base

#endif // LOCAL_SOCKET_SERVER_H
