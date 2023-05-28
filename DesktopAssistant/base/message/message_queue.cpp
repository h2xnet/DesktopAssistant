#include "message_queue.h"

namespace base {

MessageQueue::MessageQueue() : m_running(true), m_max_count(100)
{

}

MessageQueue::~MessageQueue() {
    this->clear();
}

bool MessageQueue::addItem(int type, QString data, QString owner, QString sender,
                           QString reciver, QString sessionId, int sequeNo) {
    if (sequeNo == 0) {
        sequeNo = MessageBase::getSequeCount();
    }

    bool bret = false;
    try {

        base::MessageBase* pNode = new base::MessageBase();
        pNode->sequeNo = sequeNo;
        pNode->type = type;
        if (!data.isEmpty()) {
            pNode->data = QString("%1").arg(data);
        }
        if (!owner.isEmpty()) {
            pNode->owner = QString("%1").arg(owner);
        }
        if (!sender.isEmpty()) {
            pNode->sender = QString("%1").arg(sender);
        }
        if (!reciver.isEmpty()) {
            pNode->reciver = QString("%1").arg(reciver);
        }
        if (!sessionId.isEmpty()) {
            pNode->sessionId = QString("%1").arg(sessionId);
        }
        bret = this->addItem(pNode);
    }
    catch (...) {
        return false;
    }
    return bret;
}

bool MessageQueue::addItem(base::MessageBase* pMsg) {
    if (!pMsg) {
        return false;
    }

    //m_queue.push_back(pMsg);
    m_queue.enqueue(pMsg); // 添加到队尾
    return true;
}

base::MessageBase* MessageQueue::getHeadItem(bool isRemove) {
    if (m_queue.isEmpty()) {
        return nullptr;
    }

    base::MessageBase* pHead = nullptr;
    if (isRemove) {
        pHead = m_queue.dequeue();
    }
    else {
        pHead = m_queue.head();
    }
    return pHead;
}

int MessageQueue::getCount() {
    return m_queue.size();
}

bool MessageQueue::isEmpty() {
    return m_queue.isEmpty();
}

bool MessageQueue::isFull() {
    return (m_queue.size() == m_max_count) ? true : false;
}

void MessageQueue::clear() {
    base::MessageBase* pHead = nullptr;
    while(!m_queue.isEmpty()) {
        pHead = m_queue.dequeue();
        if (pHead) {
            delete pHead;
            pHead = nullptr;
        }
    }
}

int MessageQueue::moveTo(MessageQueue& toQue) {
    int count = 0;

    base::MessageBase* pHead = nullptr;
    while(!m_queue.isEmpty()) {
        pHead = m_queue.dequeue();
        if (pHead) {
            toQue.addItem(pHead);
        }
    }
    return count;
}


} // end namespace base
