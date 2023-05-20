#ifndef CHILD_PROCESS_APP_H
#define CHILD_PROCESS_APP_H

namespace base {

/*
 * ClassName: ChildProcessApp
 * Desc: 子进程应用基类
 * Author: zfs
 * Date: 2023-05-20 20:24
 */
class ChildProcessApp
{
public:
    ChildProcessApp();
    virtual ~ChildProcessApp();

    virtual int init(int argc, char* argv[]) = 0;

    virtual int exec() = 0;

    virtual int quit(int exitCode) = 0;

};

} // end namespace base

#endif // CHILD_PROCESS_APP_H
