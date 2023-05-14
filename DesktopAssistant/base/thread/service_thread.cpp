#include "service_thread.h"

#include "base/exception/error.h"

namespace base {

ServiceThread::ServiceThread(base::MessageHandlerBase* pMsgHandler, QObject* parent) : ThreadBase(parent),
    m_running(false), m_max_task_count(100), m_message_handler(pMsgHandler)
{
    Q_ASSERT(m_message_handler);
}

ServiceThread::~ServiceThread() {

}

bool ServiceThread::getRunning() const {
    return m_running;
}

void ServiceThread::setRunning(bool val) {
    m_running = val;
}

int ServiceThread::getMaxTaskCount() {
    return m_max_task_count;
}

void ServiceThread::setMaxTaskCount(int val) {
    m_max_task_count = val;
}

int ServiceThread::addTask(int type, QString data, QString owner, int timeout) {
    if (m_task_queue.getCount() >= m_max_task_count) {
        return ERROR_CODE_NO_RESOURCE;
    }
    if (timeout <= 0) {
        timeout = DEF_LOCK_TIMEOUT;
    }
    bool bret = false;
    if (m_mutex.tryLock(timeout)) {
        bret = m_task_queue.addItem(type, data, owner);
        m_mutex.unlock();
    }
    return bret ? ERROR_CODE_OK : ERROR_CODE_TIMEOUT;
}

void ServiceThread::run() {
    int ret = onWork();
}

int ServiceThread::onWork() {
    bool isNeedDelay = true;
    while(m_running) {
        // 加载待处理任务
        this->onLoadTask();

        // 处理需要加入下一轮的任务
        this->onLoadNextTask();

        if (!m_work_queue.isEmpty()) {
            this->onProcessWorkTask();
        }

        if (isNeedDelay) {
            QThread::msleep(100);
        }
    }
    return 0;
}

int ServiceThread::onLoadTask() {
    int count = 0;

    if (!m_task_queue.isEmpty()) {
        // 尝试加载
        //QMutexLocker lock(&m_mutex);
        if (m_mutex.tryLock(3000)) {
            count = m_task_queue.moveTo(m_work_queue);
            m_mutex.unlock();
        }
    }

    return count;
}

int ServiceThread::onLoadNextTask() {
    return 0;
}

int ServiceThread::onProcessWorkTask() {
    int count = 0;

    int ret = -1;
    base::MessageBase* pMsgNode = nullptr;
    while(!m_work_queue.isEmpty()) {
        ret = -1;
        pMsgNode = m_work_queue.getHeadItem(true);
        if (pMsgNode) {
            ret = m_message_handler->process(pMsgNode);
            if (ret == ERROR_CODE_OK) {
                count++;
            }
            else {

            }
        }
    }

    return count;
}

} // end namespace base
