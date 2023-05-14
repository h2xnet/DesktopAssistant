#ifndef THREAD_BASE_H
#define THREAD_BASE_H

#include <QThread>

namespace base {

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

    //
    // onWork : 线程工作函数
    //
    virtual int onWork() = 0;

};

} // end namespace base

#endif // THREAD_BASE_H
