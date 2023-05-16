#ifndef DEFAULT_MESSAGE_HANDLER_H
#define DEFAULT_MESSAGE_HANDLER_H

#include "base/message/message_handler_base.h"

namespace core {

/*
 * ClassName: DefaultMessageHandler
 * Desc: 通用消息处理器
 * Author: zfs
 * Date: 2023-05-16 21:16
 */
class DefaultMessageHandler : public base::MessageHandlerBase
{
public:
    DefaultMessageHandler();
    virtual ~DefaultMessageHandler();

    //
    // base::MessageHandlerBase
    //
    virtual int write(const base::MessageBase* pMsg) override;
    virtual int read(base::MessageBase* pMsg) override;
    virtual bool serialize(const base::MessageBase* pMsg, base::Buffer* pBuffer) override;
    virtual bool deserialize(const base::Buffer* pBuffer, base::MessageBase* pMsg) override;
    virtual int process(base::MessageBase* pMsg) override;

};


} // end namespace core

#endif // DEFAULT_MESSAGE_HANDLER_H
