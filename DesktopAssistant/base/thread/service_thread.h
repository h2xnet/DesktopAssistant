#ifndef SERVICE_THREAD_H
#define SERVICE_THREAD_H

#include "base/thread/thread_base.h"
#include "base/message/message_queue.h"
#include "base/message/message_handler_base.h"

#include <QMutex>
#include <QMutexLocker>
#include <QList>

namespace base {

class ServiceThread : public ThreadBase
{
    Q_OBJECT
public:
    typedef QList<MessageBase*> MessageList;

    ServiceThread(base::MessageHandlerBase* pMsgHandler, QObject* parent = nullptr);
    virtual ~ServiceThread();

    //
    // ThreadBase
    //
    virtual bool getRunning() const override;
    virtual void setRunning(bool val) override;

    virtual int getMaxTaskCount() override;
    virtual void setMaxTaskCount(int val) override;

    virtual int onWork() override;

    /*
     * Func: addTask
     * Desc: 添加新任务
     * Author: zfs
     * Date: 2023-05-14 17:44
     * @type: 任务类型，在 MessageBase::eMessageType 中定义
     * @data: 任务请求数据，主要是请求参数，可以为空
     * @owner: 传递的自定义数据，可以为空
     */
    Q_INVOKABLE int addTask(int type, QString data, QString owner, QString sender, QString reciver, int timeout = DEF_LOCK_TIMEOUT);

    /*
     * Func: addTask
     * Desc: 添加新任务
     * Author: zfs
     * Date: 2023-05-25 07:05
     */
    int addTask(base::MessageBase* pMsg, int timeout = DEF_LOCK_TIMEOUT);


public slots:


public:
signals:



protected:
    //
    // QThread
    //
    virtual void run() override;


protected:
    //
    // ThreadBase
    //
    virtual int onLoadTask() override;
    virtual int onLoadNextTask() override;
    virtual int onProcessWorkTask() override;
    virtual int onRemoveCompletedTask() override;

private:
    bool m_running;

    int m_max_task_count;

    QMutex m_mutex;
    MessageQueue m_task_queue; // 任务队列
    MessageQueue m_work_queue; // 当前工作队列

    MessageList m_completed_list; // 任务执行完成列表
    MessageList m_next_list; // 下一轮循环列表

    base::MessageHandlerBase* m_message_handler; // 消息处理器

};

} // end namespace base

#endif // SERVICE_THREAD_H
