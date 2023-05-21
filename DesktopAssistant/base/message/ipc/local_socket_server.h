#ifndef LOCAL_SOCKET_SERVER_H
#define LOCAL_SOCKET_SERVER_H

#include <QObject>
#include <QLocalServer>
#include <QLocalSocket>
#include <QString>
#include <QMap>

#include <QMutex>
#include <QMutexLocker>

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
    typedef QMap<QString, const QLocalSocket*> SessionToSocketMap;
    typedef QMap<const QLocalSocket*, QString> SocketToSessionMap;

    LocalSocketServer(QObject* parent = nullptr);

    virtual ~LocalSocketServer();

    Q_INVOKABLE int beginRun(QString serverName);

    Q_INVOKABLE void endRun();

    Q_INVOKABLE int write(const QString& strSessionId, const QString& data, int timeout = 5000);

public slots:

    //
    // 连接请求
    //
    void newConnectHandler();

    //
    // onSocketConnected : 会话建立成功
    //
    void onSocketConnected();

    //
    // onSocketDisConnected : 会话断开
    //
    void onSocketDisConnected();

    //
    // onSocketError : 会话发生错误
    //
    void onSocketError(QLocalSocket::LocalSocketError socketError);

    //
    // onSocketReadyRead : 会话接收数据
    //
    void onSocketReadyRead();

    //
    // onSocketStateChanged : 会话状态改变
    //
    void onSocketStateChanged(QLocalSocket::LocalSocketState socketState);

public:
signals:

    //
    // socketConnected : 会话建议成功
    //
    void socketConnected(QString strSessionId);

    //
    // socketDisConnected : 会话已经断开
    //
    void socketDisConnected(QString strSessionId);

    //
    // socketDataRecv : 会话数据接收
    //
    void socketDataRecv(QString strSessionId, QString data);

    //
    // socketStateChanged : 会话状态改变
    //
    void socketStateChanged(QString strSessionId, int state);

    //
    // socketExceptionError : 会话发生错误
    //
    void socketExceptionError(QString strSessionId, int errorNo);

private:

    QString onGetSessionId(const QLocalSocket* socket);
    QLocalSocket* onGetSocket(const QString& strSessionId);

    bool onRemoveSessionId(const QString& strSessionId);
    bool onRemoveSocket(const QLocalSocket* socket);

    //
    // onEndAllSocket : 结束所有会话
    //
    void onEndAllSocket();

    QString onGetAckMessage();
    QString onGetQuitMessage();

    QLocalServer* m_server; // 服务对象

    QString m_server_name; // 服务名称（命名管道名称）

    // 缓存列表
    SessionToSocketMap session_to_socket;
    SocketToSessionMap socket_to_session;
    QMutex m_mutex; // 缓存锁
};


} // end namespace base

#endif // LOCAL_SOCKET_SERVER_H
