#ifndef VIEW_PROCESS_APP_H
#define VIEW_PROCESS_APP_H

#include "base/childProcess/child_process_app.h"

#include <QObject>
#include <QProcess>
#include <QSocketNotifier>
#include <QFile>

namespace core {

/*
 * ClassName: ViewProcessApp
 * Desc: 页面进程应用类
 * Author: zfs
 * Date: 2023-05-20 20:32
 */
class ViewProcessApp : public QObject, public base::ChildProcessApp
{
    Q_OBJECT
public:
    ViewProcessApp();
    virtual ~ViewProcessApp();

    //
    // base::ChildProcessApp
    //
    virtual int init(int argc, char* argv[]) override;
    virtual int exec() override;
    virtual int quit(int exitCode) override;

public slots:



private:
    bool m_running;
    int m_exit_code;


};

} // end namespace core

#endif // VIEW_PROCESS_APP_H
