#ifndef TOOL_UTIL_H
#define TOOL_UTIL_H

#include <QString>

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


};

} // end namespace base

#endif // TOOL_UTIL_H
