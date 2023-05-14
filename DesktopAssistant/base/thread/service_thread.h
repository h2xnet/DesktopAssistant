#ifndef SERVICE_THREAD_H
#define SERVICE_THREAD_H

#include "base/thread/thread_base.h"
#include "base/message/message_queue.h"

#include <QMutex>

namespace base {

class ServiceThread : public ThreadBase
{
    Q_OBJECT
public:
    ServiceThread(QObject* parent = nullptr);
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
    Q_INVOKABLE int addTask(int type, QString data, QString owner);


public slots:


public:
signals:



protected:
    virtual void run() override;

private:
    bool m_running;

    int m_max_task_count;

    QMutex m_mutex;
    MessageQueue m_task_queue; // 任务队列
    MessageQueue m_work_queue; // 当前工作队列

};

} // end namespace base

#endif // SERVICE_THREAD_H
