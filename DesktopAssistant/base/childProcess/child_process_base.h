#ifndef CHILD_PROCESS_BASE_H
#define CHILD_PROCESS_BASE_H

#include "base/message/message_base.h"
#include <QString>

namespace base {

/*
 * ClassName: ChildProcessBase
 * Desc: 子进程处理类，只是个接口
 * Author: zfs
 * Date: 2023-05-14 15:22
 */
class ChildProcessBase
{
public:
    ChildProcessBase();
    virtual ~ChildProcessBase();

    virtual int init(int argc, char* argv[]) = 0;

    virtual int exec() = 0;

    virtual int quit(int exitCode = 0) = 0;

    virtual int write(const base::MessageBase* pMsg) = 0;

    virtual int read(base::MessageBase* pMsg) = 0;

    virtual bool getRunning() const = 0;
    virtual void setRunning(bool state) = 0;

    virtual int getExitCode() = 0;

};

} // end namespace base

#endif // CHILD_PROCESS_BASE_H
