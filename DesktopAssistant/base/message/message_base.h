#ifndef MESSAGE_BASE_H
#define MESSAGE_BASE_H

#include "base/define.h"

#include <QString>
#include <QJsonObject>

namespace base {

/*
 * ClassName: MessageBase
 * Desc: 消息基类
 * Author: zfs
 * Date: 2023-05-23 06:40
 */
class MessageBase
{
public:
    //
    // getSequeCount : 获取统计个数
    //
    static qint32 getSequeCount();

    //
    // isChildViewType : 判断是否为子页面消息
    //
    static bool isChildViewType(int type);

    //
    // getMessageData : 获取消息data对象
    //
    static QJsonObject buildMessageObj(int code, QString msg, QJsonObject dataObj);
    static QString buildMessage(int code, QString msg, QJsonObject dataObj);


    MessageBase();
    ~MessageBase();

    qint32 sequeNo; // 消息编号
    int type; // 消息类型
    QString data; // 消息数据
    QString owner; // 自定义数据

    QString sender; // 发送者
    QString recver; // 接收者

    int code; // 最后执行结果
};

} // end namespace base

#endif // MESSAGEBASE_H
