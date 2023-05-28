#include "message_base.h"

#include "base/util/tool_util.h"

#include <QDateTime>

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

void MessageBase::reset() {
    type = 0;
    sequeNo = 0;
    code = 0;
    serializeTimes = 0;

    sender = "";
    reciver = "";
    owner = "";
    data = "";
    sessionId = "";
}

QString MessageBase::serialize() {
    QJsonObject obj;
    obj.insert("sequeNo", sequeNo);
    obj.insert("type", type);
    obj.insert("data", data);
    obj.insert("owner", owner);
    obj.insert("sender", sender);
    obj.insert("reciver", reciver);
    obj.insert("code", code);
    obj.insert("serializeTimes", QDateTime::currentMSecsSinceEpoch());
    obj.insert("sessionId", sessionId);

    return base::ToolUtil::qjsonobjectToQstring(obj);
}

bool MessageBase::deserialize(const QString& str) {
    if (str.isEmpty()) {
        return false;
    }

    QJsonObject obj = base::ToolUtil::qstringToQjsonobject(str);
    if (obj.isEmpty()) {
        return false;
    }

    this->reset();
    if (obj.contains("sequeNo")) {
        sequeNo = obj.value("sequeNo").toInt();
    }
    if (obj.contains("type")) {
        type = obj.value("type").toInt();
    }
    if (obj.contains("data")) {
        data = obj.value("data").toString();
    }
    if (obj.contains("owner")) {
        owner = obj.value("owner").toString();
    }
    if (obj.contains("sender")){
        sender = obj.value("sender").toString();
    }
    if (obj.contains("reciver")) {
        reciver = obj.value("reciver").toString();
    }
    if (obj.contains("code")) {
        code = obj.value("code").toInt();
    }
    if (obj.contains("serializeTimes")) {
        serializeTimes = (qint64)obj.value("serializeTimes").toDouble();
    }
    if (obj.contains("sessionId")) {
        sessionId = obj.value("sessionId").toString();
    }
    return true;
}

} // end namespace base
