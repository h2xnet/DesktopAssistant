#ifndef CHILD_PROCESS_H
#define CHILD_PROCESS_H

#include <QProcess>

namespace base {

/*
 * ClassName: ChildProcess
 * Desc: 子进程处理类
 * Author: zfs
 * Date: 2023-05-14 15:22
 */
class ChildProcess : QProcess
{
    Q_OBJECT
public:
    ChildProcess(QObject* parent = nullptr);
    virtual ~ChildProcess();

};

} // end namespace base

#endif // CHILD_PROCESS_H
