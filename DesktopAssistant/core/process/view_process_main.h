#ifndef VIEW_PROCESS_MAIN_H
#define VIEW_PROCESS_MAIN_H

#include "base/childProcess/child_process_base.h"

#include <QObject>

namespace core {

/*
 * ClassName: ViewProcessMain
 * Desc: 页面子进程主类
 * Author: zfs
 * Date: 2023-05-17 07:17
 */
class ViewProcessMain : public QObject, public base::ChildProcessBase
{
    Q_OBJECT
public:
    ViewProcessMain(QObject* parent = nullptr);
    virtual ~ViewProcessMain();

    //
    // base::ChildProcessBase
    //
    virtual int main(int argc, char* argv[], void* owner = nullptr) override;


private:
    bool m_running; // 支行状态
    int m_exit_code; // 关闭代码

};


} // end namespace core

#endif // VIEW_PROCESS_MAIN_H
