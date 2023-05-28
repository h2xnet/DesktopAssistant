#include "view_process_main.h"

#include "core/process/viewProcessApp/view_process_app.h"


namespace core {



ViewProcessMain::ViewProcessMain(QObject* parent) : QObject(parent), base::ChildProcessBase(),
    m_running(true), m_exit_code(0)
{

}

ViewProcessMain::~ViewProcessMain() {

}

int ViewProcessMain::main(int argc, char* argv[], void* owner) {

    // 创建应用对象，并且运行
    ViewProcessApp app;
    int ret = app.init(argc, argv, owner);
    if (ret != 0) {
        return ret;
    }

    ret = app.exec();

    return ret;
}



} // end namespace core
