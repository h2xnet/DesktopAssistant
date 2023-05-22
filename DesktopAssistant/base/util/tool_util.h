#ifndef TOOL_UTIL_H
#define TOOL_UTIL_H

#include <QString>
#include <QJsonObject>
#include <QJsonArray>

namespace base {

/*
 * ClassName: ToolUtil
 * Desc: 工具集合类
 * Author: zfs
 * Date: 2023-05-21 09:32
 */
class ToolUtil
{
public:
    ToolUtil();

    /*
     * Func: getUuid
     * Desc: 生成UUID
     * Author: zfs
     * Date: 2023-05-21 09:37
     */
    static QString getUuid();

    /*
     * Func: getCurrentPID
     * Desc: 获取当前进程ID
     * Author: zfs
     * Date: 2023-05-23 07:18
     */
    static QString getCurrentPID();

    static QString qjsonobjectToQstring(const QJsonObject& obj);
    static QString qjsonarrayToQstring(const QJsonArray& arr);
    static QJsonObject qstringToQjsonobject(const QString& str);
    static QJsonArray qstringToQjsonarray(const QString& str);


};

} // end namespace base

#endif // TOOL_UTIL_H
