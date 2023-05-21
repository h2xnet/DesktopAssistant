#ifndef STARTUP_H
#define STARTUP_H

#include "base/util/startup_base.h"

#include <QObject>
#include <QProcess>

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
    QProcess* startViewChildProcess(int timeout = 5000, QObject* parent = nullptr);

};

} // end namespace core

#endif // STARTUP_H
