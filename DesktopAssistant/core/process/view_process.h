#ifndef VIEW_PROCESS_H
#define VIEW_PROCESS_H

#include "base/childProcess/default_child_process.h"

#include <QObject>

namespace core {

/*
 * ClassName: ViewProcess
 * Desc: 页面进程
 * Author: zfs
 * Date: 2023-05-17 07:17
 */
class ViewProcess : public QObject, public base::DefaultChildProcess
{
    Q_OBJECT
public:
    ViewProcess(QObject* parent = nullptr);
    virtual ~ViewProcess();

    //
    // base::DefaultChildProcess
    //
    virtual int init(int argc, char* argv[]) override;
    virtual int exec() override;
    virtual int quit(int exitCode = 0) override;
    virtual int write(const base::MessageBase* pMsg) override;
    virtual int read(base::MessageBase* pMsg) override;
    virtual bool getRunning() const override;
    virtual void setRunning(bool state) override;
    virtual int getExitCode() override;

private:
    bool m_running; // 支行状态
    int m_exit_code; // 关闭代码

};


} // end namespace core

#endif // VIEW_PROCESS_H
