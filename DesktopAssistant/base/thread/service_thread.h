#ifndef SERVICE_THREAD_H
#define SERVICE_THREAD_H

#include "base/thread/thread_base.h"

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


public slots:


public:
signals:



protected:
    virtual void run() override;

private:
    bool m_running;

    int m_max_task_count;

};

#endif // SERVICE_THREAD_H
