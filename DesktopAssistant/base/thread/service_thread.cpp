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

int ServiceThread::addTask(int type, QString data, QString owner, QString sender, QString reciver, int timeout) {
    if (m_task_queue.getCount() >= m_max_task_count) {
        return ERROR_CODE_NO_RESOURCE;
    }
    if (timeout <= 0) {
        timeout = DEF_LOCK_TIMEOUT;
    }
    bool bret = false;
    if (m_mutex.tryLock(timeout)) {
        bret = m_task_queue.addItem(type, data, owner, sender, reciver);
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

        // 移除已完成任务
        this->onRemoveCompletedTask();

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
    int count = 0;
    if (!m_next_list.isEmpty()) {
        for(int i = 0; i < m_next_list.size(); i++) {
            if (m_work_queue.addItem(m_next_list.at(i))) {
                count++;
            }
        }
    }
    return count;
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

            // 保存执行结果
            pMsgNode->code = ret;

            if (ret == ERROR_CODE_NEXT) {
                // 加载到下一轮
                m_next_list.push_back(pMsgNode);
            }
            else {
                // 执行完成，可能成功，也可能失败
                m_completed_list.push_back(pMsgNode);

                if (ret == ERROR_CODE_OK) {
                    // 成功完成
                    count++;
                }
            }
        }
    }

    return count;
}

int ServiceThread::onRemoveCompletedTask() {
    int count = 0;
    if (!m_completed_list.isEmpty()) {
        base::MessageBase* pMsg = nullptr;
        for(int i = 0; i < m_completed_list.size(); i++) {
            pMsg = m_completed_list.at(i);
            if (pMsg) {
                delete pMsg;
                pMsg = nullptr;
            }
        }
        m_completed_list.clear();
    }
    return count;
}

} // end namespace base
