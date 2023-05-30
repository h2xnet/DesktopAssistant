#ifndef THREAD_BASE_H
#define THREAD_BASE_H

#include <QThread>
#include <QDebug>

namespace base {

// 默认加锁超时时间，单位：毫秒
#define DEF_LOCK_TIMEOUT    5000

/*
 * ClassName: ThreadBase
 * Desc: 线程基类，做为所有线程的接口
 * Author: zfs
 * Date: 2023-05-14 15:35
 */
class ThreadBase : public QThread
{
    Q_OBJECT
public:
    ThreadBase(QObject* parent = nullptr);
    virtual ~ThreadBase();

    virtual bool getRunning() const = 0;
    virtual void setRunning(bool val) = 0;

    virtual int getMaxTaskCount() = 0;
    virtual void setMaxTaskCount(int val) = 0;

    /*
     * Func: onWork
     * Desc: 线程工作函数
     * Author: zfs
     * Date: 2023-05-14 15:59
     */
    virtual int onWork() = 0;

protected:
    /*
     * Func: onLoadTask
     * Desc: 加载待处理任务到工作队列
     * Author: zfs
     * Date: 2023-05-15 06:59
     */
    virtual int onLoadTask() = 0;

    /*
     * Func: onLoadNextTask
     * Desc: 加载进入下轮循环的任务到工作队列
     * Author: zfs
     * Date: 2023-05-15 06:59
     */
    virtual int onLoadNextTask() {  return 0; }

    /*
     * Func: onProcessWorkTask
     * Desc: 处理工作队列中的任务
     * Author: zfs
     * Date: 2023-05-15 07:00
     */
    virtual int onProcessWorkTask() = 0;

    /*
     * Func: onRemoveCompletedTask
     * Desc: 移除完成任务
     * Author: zfs
     * Date: 2023-05-21 08:39
     */
    virtual int onRemoveCompletedTask() = 0;

};

} // end namespace base

#endif // THREAD_BASE_H
