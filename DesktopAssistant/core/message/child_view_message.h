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

    //
    // ChildViewMessageType : 子页面消息类型
    //
    enum ChildViewMessageType {
        eAddViewTypeIndex = 0, // 添加页面消息
        MAX_COUNT // 最大个数
    };

    ChildViewMessage();

    virtual ~ChildViewMessage();

    //
    // base::MessageBase
    //
    virtual int getRequestTypeValue(int type) override;
    virtual int getResponseTypeValue(int type) override;
    virtual int getValidTypeCount() override;


};

} // end namespace core

#endif // CHILD_VIEW_MESSAGE_H
