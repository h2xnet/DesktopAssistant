#include "child_view_message.h"

#include "base/util/tool_util.h"

namespace  {

//
// 子页面消息列表
//
static const base::MESSAGE_PAIR message_list [] = {
    {(CHILD_VIEW_MESSAGE_START_TYPE + 0), (CHILD_VIEW_MESSAGE_START_TYPE + 1)},
    {0, 0}
};

} // end namespace


namespace core {


ChildViewMessage::ChildViewMessage() : base::MessageBase()
{
    sender = base::ToolUtil::getCurrentPID();
    recver = sender;
}

ChildViewMessage::~ChildViewMessage() {

}

int ChildViewMessage::getRequestTypeValue(int type) {
    if (isChildViewType(type) && (type < getValidTypeCount())) {
        return message_list[type].requestType;
    }
    return DEF_MESSAGE_TYPE;
}

int ChildViewMessage::getResponseTypeValue(int type) {
    if (isChildViewType(type) && (type < getValidTypeCount())) {
        return message_list[type].responseType;
    }
    return DEF_MESSAGE_TYPE;
}

int ChildViewMessage::getValidTypeCount() {
    return (sizeof(message_list) / sizeof(message_list[0]));
}

} // end namespace core
