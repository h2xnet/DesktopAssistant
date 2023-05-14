#ifndef MESSAGE_HANDLER_BASE_H
#define MESSAGE_HANDLER_BASE_H

#include "base/message/message_base.h"
#include "base/buffer/buffer.h"

namespace base {

/*
 * ClassName: MessageHandlerBase
 * Desc: 消息处理器基类
 * Author: zfs
 * Date: 203-05-15 07:19
 */
class MessageHandlerBase
{
public:
    MessageHandlerBase();
    virtual ~MessageHandlerBase();

    virtual int write(const base::MessageBase* pMsg) = 0;

    virtual int read(base::MessageBase* pMsg) = 0;

    virtual bool serialize(const base::MessageBase* pMsg, base::Buffer* pBuffer) = 0;

    virtual bool deserialize(const base::Buffer* pBuffer, base::MessageBase* pMsg) = 0;

    virtual int process(base::MessageBase* pMsg) = 0;

};


} // end namespace base

#endif // MESSAGE_HANDLER_BASE_H
