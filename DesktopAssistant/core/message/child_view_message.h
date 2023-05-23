#ifndef CHILD_VIEW_MESSAGE_H
#define CHILD_VIEW_MESSAGE_H

#include "base/message/message_base.h"

namespace core {


/*
 * ClassName: ChildViewMessage
 * Desc: 子页面消息处理类
 * Author: zfs
 * Date: 2023-05-23 06:25
 */
class ChildViewMessage : public base::MessageBase
{
public:

    ChildViewMessage();

    virtual ~ChildViewMessage();



};

} // end namespace core

#endif // CHILD_VIEW_MESSAGE_H
