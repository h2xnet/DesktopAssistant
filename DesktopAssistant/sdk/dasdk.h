#ifndef DASDK_H
#define DASDK_H

#include "base/util/command_line.h"

#include <QString>
#include <QStringList>
#include <QApplication>

namespace hxxda {

/*
 * Func: getStartViewChildProcessCmd
 * Desc: 获取启动页面子进程命令行
 * Author: zfs
 * Date: 2023-05-21 16:36
 */
QString getStartViewChildProcessCmd();

/*
 * Func: getStartViewChildProcessArguments
 * Desc: 获取启动页面子进程命令行参数
 * Author: zfs
 * Date: 2023-05-21 16:36
 */
QStringList getStartViewChildProcessArguments();

/*
 * Func: getCommandLine
 * Desc: 获取用户输入的命令参数列表
 * Author: zfs
 * Date: 2023-05-28 08:51
 */
base::CommandLine* getCommandLine();


} // end namespace hxxda

#endif // DASDK_H
