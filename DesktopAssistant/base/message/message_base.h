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

    /*
     * Func: getRequestTypeValue
     * Desc: 获取请求消息类型值
     * Author: zfs
     * Date: 2023-05-23 06:46
     * 返回值：查询成功返回对应的值，失败返回0
     */
    virtual int getRequestTypeValue(int type) { return DEF_MESSAGE_TYPE; }

    /*
     * Func: getResponseTypeValue
     * Desc: 获取应答消息类型值
     * Author: zfs
     * Date: 2023-05-23 06:46
     * 返回值：查询成功返回对应的值，失败返回0
     */
    virtual int getResponseTypeValue(int type) {    return DEF_MESSAGE_TYPE;    }

    /*
     * Func: getValidTypeCount
     * Desc: 获取当前有效的类型个数
     * Author: zfs
     * Date: 2023-05-23 06:58
     */
    virtual int getValidTypeCount() {return 0;}

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
