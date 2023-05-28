#include "message_package.h"

#include "base/message/message_base.h"
#include "base/define.h"
#include "base/exception/error.h"

#include <QApplication>

namespace hxxda {

//
// getIPCWelcomeMessage : 获取IPC欢迎消息
//
QString getIPCWelcomeMessage(QString welcome, QString reciver, QString owner) {
    base::MessageBase msg;
    msg.sequeNo = base::MessageBase::getSequeCount();
    msg.type = PUBLIC_MESSAGE_WELCOME_REQUEST;
    msg.sender = QString::number(QApplication::applicationPid());
    if (!owner.isEmpty()) {
        msg.owner = QString("%1").arg(owner);
    }
    if (!reciver.isEmpty()) {
        msg.reciver = QString("%1").arg(reciver);
    }

    QJsonObject dataObj;
    dataObj.insert("welcome", welcome);

    msg.data = QString("%1").arg(
                base::MessageBase::buildMessage(ERROR_CODE_DATA_OK, "ok", dataObj));

    return msg.serialize();
}


} // end namespace hxxda
