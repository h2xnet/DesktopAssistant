#include "message_base.h"

#include "base/util/tool_util.h"

namespace base {

qint32 MessageBase::getSequeCount() {
    static qint32 sequeCount = 0;
    return (sequeCount++);
}

MessageBase::MessageBase() : sequeNo(0), type(DEF_MESSAGE_TYPE), code(0)
{
    sequeNo = getSequeCount();
}

MessageBase::~MessageBase() {

}

bool MessageBase::isChildViewType(int type) {
    if (type >= CHILD_VIEW_MESSAGE_START_TYPE && type < CHILD_VIEW_MESSAGE_END_TYPE) {
        return true;
    }
    return false;
}

QJsonObject MessageBase::buildMessageObj(int code, QString msg, QJsonObject dataObj) {
    QJsonObject obj;
    obj.insert("code", code);
    obj.insert("msg", msg);
    obj.insert("data", dataObj);
    return obj;
}

QString MessageBase::buildMessage(int code, QString msg, QJsonObject dataObj) {
    QJsonObject obj;
    obj.insert("code", code);
    obj.insert("msg", msg);
    obj.insert("data", dataObj);
    return base::ToolUtil::qjsonobjectToQstring(obj);
}

} // end namespace base
