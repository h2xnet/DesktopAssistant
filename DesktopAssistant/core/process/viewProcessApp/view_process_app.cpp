#include "view_process_app.h"

namespace core {

ViewProcessApp::ViewProcessApp() : QObject(nullptr), m_running(true), m_exit_code(0)
{

}

ViewProcessApp::~ViewProcessApp() {

}

int ViewProcessApp::init(int argc, char* argv[]) {
    // 根据参数，解析IPC管道名称，连接父进程管道服务
    return 0;
}

int ViewProcessApp::quit(int exitCode) {
    m_exit_code = exitCode;
    if (m_running) {
        m_running = false;
    }
    return 0;
}

int ViewProcessApp::exec() {
    int ret = -1;
    while(m_running) {

    }
    return ret;
}


} // end namespace core
