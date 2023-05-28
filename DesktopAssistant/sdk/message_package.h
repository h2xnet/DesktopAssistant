#ifndef MESSAGE_PACKAGE_H
#define MESSAGE_PACKAGE_H

#include <QString>

namespace hxxda {

/*
 * Func: getIPCWelcomeMessage
 * Desc: 获取IPC欢迎消息
 * Author: zfs
 * Date: 2023-05-28 10:26
 * @welcome: 欢迎文本
 * @reciver: 接收者
 * @owner: 自定义内容，可以为空
 * 返回值：返回序列化后的消息字符串
 */
QString getIPCWelcomeMessage(QString welcome, QString reciver = "", QString owner = "");

} // end namespace hxxda

#endif // MESSAGE_PACKAGE_H
