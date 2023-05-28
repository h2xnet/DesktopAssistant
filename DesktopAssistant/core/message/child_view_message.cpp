#include "child_view_message.h"

#include "base/util/tool_util.h"



namespace core {


ChildViewMessage::ChildViewMessage() : base::MessageBase()
{
    sender = base::ToolUtil::getCurrentPID();
    reciver = sender;
}

ChildViewMessage::~ChildViewMessage() {

}


} // end namespace core
