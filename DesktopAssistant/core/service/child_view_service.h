#ifndef CHILD_PROCESS_SERVICE_H
#define CHILD_PROCESS_SERVICE_H

#include "base/thread/service_thread.h"
#include "core/message/default_message_handler.h"
#include "core/service/common/ipc_server_service.h"

#include <QMap>
#include <QProcess>

#include <QMutex>
#include <QMutexLocker>

namespace core {

/*
 * ClassName: ChildViewService
 * Desc: 子页面管理服务类，主要负责子页面的创建、销毁、消息处理等，它跟子页面进程之间用IPC通信
 *        这类页面的特点是一个页面，对应一个子进行，进程ID就是页面ID
 * Author: zfs
 * Date: 2023-05-16 21:04
 */
class ChildViewService : public base::ServiceThread, public core::DefaultMessageHandler
{
    Q_OBJECT
public:
    //
    // CHILD_VIEW_SESSION_ : 定义页面会话信息
    //
    typedef struct VIEW_SESSION_ {
        VIEW_SESSION_() {
            process = nullptr;
            createTime = 0;
            modifyTime = 0;
        }

        ~VIEW_SESSION_() {
            process = nullptr;
        }

        QString viewId; // 页面ID，也是页面进程ID
        QString sessionId; // 会话ID
        QProcess* process; // 页面进程指针，不进行信号绑定，消息通过专有IPC进行通信
        qint64 createTime; // 创建时间
        qint64 modifyTime; // 最后修改时间
        QString title; // 页面标题
        QString owner; // 页面自定义参数
    } VIEW_SESSION, *LPVIEW_SESSION;

    // 页面会话信息列表
    // typedef QMap<viewId, VIEW_SESSION*>
    typedef QMap<QString, VIEW_SESSION*> ViewSessionMap;

    // typedef QMap<sessionId, viewId>
    typedef QMap<QString, QString> SessionToViewMap;

    ChildViewService(QObject* parent = nullptr);
    virtual ~ChildViewService();

    //
    // core::DefaultMessageHandler
    //
    virtual int write(const base::MessageBase* pMsg) override;
    //virtual int read(base::MessageBase* pMsg) override;
    virtual int process(base::MessageBase* pMsg) override;


    /*
     * Func: addView
     * Desc: 添加一个页面
     * Author: zfs
     * Date: 2023-05-21 16:19
     * @title: 页面标题
     * @owner: 页面参数，允许添加一个页面自定义参数
     * 返回值：成功返回0
     */
    Q_INVOKABLE int addView(QString title, QString owner);

public slots:

    //
    // core::IPCServerService
    //
    void onClientSocketConnectedHandler(QString strSessionId);
    void onClientSocketDisConnectedHandler(QString strSessionId);
    void onClientSocketDataRecvHandler(QString strSessionId, QString data);
    void onClientSocketStateChangedHandler(QString strSessionId, int state);
    void onClientSocketExceptionErrorHandler(QString strSessionId, int errorNo);


public:
signals:

    //void clientView

protected:


private:
    //
    // onAddSession : 添加会话
    //
    bool onAddSession(QProcess* process, const QString& title, const QString& owner);

    //
    // onRemoveSession : 移除会话
    //
    bool onRemoveSession(const QString& strSessionId);

    //
    // onModifySession : 修改会话信息
    //
    bool onModifySession(const QString& viewId, const QString& strSessionId);

    // IPC 服务端对象
    core::IPCServerService* m_ipc_server;

    // 页面会话信息
    ViewSessionMap m_session_map;
    SessionToViewMap m_session_to_view_map;
    QMutex m_session_mutex;

};

} // end namespace core

#endif // CHILD_PROCESS_SERVICE_H
