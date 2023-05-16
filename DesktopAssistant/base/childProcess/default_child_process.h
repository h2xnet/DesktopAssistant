#ifndef DEFAULT_CHILD_PROCESS_H
#define DEFAULT_CHILD_PROCESS_H

#include "base/childProcess/child_process_base.h"

namespace base {

/*
 * ClassName: DefaultChildProcess
 * Desc: 默认子进程
 * Author: zfs
 * Date: 2023-05-17 07:43
 */
class DefaultChildProcess : public base::ChildProcessBase
{
public:
    DefaultChildProcess();
    virtual ~DefaultChildProcess();

    //
    // base::ChildProcessBase
    //
    virtual int init(int argc, char* argv[]) override;
    virtual int exec() override;
    virtual int quit(int exitCode = 0) override;
    virtual int write(const base::MessageBase* pMsg) override;
    virtual int read(base::MessageBase* pMsg) override;

    virtual bool getRunning() const override;
    virtual void setRunning(bool state) override;

    virtual int getExitCode() override;


};

} // end namespace base

#endif // DEFAULT_CHILD_PROCESS_H
