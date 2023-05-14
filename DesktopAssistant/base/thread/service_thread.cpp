#include "service_thread.h"

namespace base {

ServiceThread::ServiceThread(QObject* parent) : ThreadBase(parent), m_running(false),
    m_max_task_count(100)
{

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

int ServiceThread::addTask(int type, QString data, QString owner) {
    if (m_task_queue.getCount() >= m_max_task_count) {

    }
    return 0;
}

void ServiceThread::run() {
    int ret = onWork();
}

int ServiceThread::onWork() {

    while(m_running) {
        QThread::msleep(100);
    }
    return 0;
}

} // end namespace base
