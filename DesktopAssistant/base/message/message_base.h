#ifndef MESSAGE_BASE_H
#define MESSAGE_BASE_H

#include <QString>

namespace base {


class MessageBase
{
public:
    //
    // getSequeCount : 获取统计个数
    //
    static qint32 getSequeCount();

    //
    // eMessageType : 消息类型
    //
    enum eMessageType {
        eEventType = 0, // 事件类型
        eActionType = 1, // 动作类型
        eDataType // 数据类型
    };

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
