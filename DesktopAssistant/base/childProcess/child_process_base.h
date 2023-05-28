#ifndef CHILD_PROCESS_BASE_H
#define CHILD_PROCESS_BASE_H

#include "base/message/message_base.h"
#include <QString>

namespace base {

/*
 * ClassName: ChildProcessBase
 * Desc: 子进程包装类，只是个接口
 * Author: zfs
 * Date: 2023-05-14 15:22
 */
class ChildProcessBase
{
public:
    ChildProcessBase();
    virtual ~ChildProcessBase();

    /*
     * Func: main
     * Desc: 子进程主函数接口，比普通的主函数接口多一个参数，此参数用户可以根据需要传递任何值，非必须
     * Author: zfs
     * Date: 2023-05-28 04:48
     * @argc: 参数个数
     * @argv: 参数列表
     * @owner: 自定义参数，默认情况下会传递命令行列表指针，如果没有传递，则命令行指针可以通过SDK函数获取
     */
    virtual int main(int argc, char* argv[], void* owner = nullptr) = 0;

};

} // end namespace base

#endif // CHILD_PROCESS_BASE_H
