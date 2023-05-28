#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H

#include "base/message/message_base.h"

#include <QQueue>

namespace base {


/*
 * ClassName: MessageQueue
 * Desc: 消息队列
 * Author: zfs
 * Date: 2023-05-14
 */
class MessageQueue
{
public:
    typedef QQueue<MessageBase*> MessageQueueType;

    MessageQueue();
    virtual ~MessageQueue();

    void setRunning(bool val) { m_running = val;    }
    bool getRunning() const {   return m_running;   }

    void setMaxCount(int val)   {   m_max_count = val;  }
    int getMaxCount() const {   return m_max_count; }

    bool addItem(int type, QString data, QString owner, QString sender, QString reciver,
                 QString sessionId = "", int sequeNo = 0);

    bool addItem(base::MessageBase* pMsg);

    base::MessageBase* getHeadItem(bool isRemove = true);

    int getCount();

    bool isEmpty();

    bool isFull();

    void clear();

    /*
     * Func: moveTo
     * Desc: 将队列元素全部转换到目标队列
     * Author: zfs
     * Date: 2023-05-15 07:08
     */
    int moveTo(MessageQueue& toQue);

private:

    bool m_running;
    int m_max_count;
    MessageQueueType m_queue;

};


} // end namespace base

#endif // MESSAGE_QUEUE_H
