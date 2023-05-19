#ifndef STARTUP_H
#define STARTUP_H

#include "base/tool/startup_base.h"

namespace core {

/*
 * ClassName: Startup
 * Desc: 启动器类
 * Author: zfs
 * Date: 2023-05-20 07:35
 */
class Startup : public base::StartupBase
{
public:
    Startup();
    virtual ~Startup();

    /*
     * Func: startViewChildProcess
     * Desc: 启动页面子进程
     * Author: zfs
     * Date: 2023-05-20 07:34
     */
    int startViewChildProcess(int argc, char* argv[]);

};

} // end namespace core

#endif // STARTUP_H
