#include "view_process.h"

namespace core {



ViewProcess::ViewProcess(QObject* parent) : QObject(parent), base::DefaultChildProcess(),
    m_running(true), m_exit_code(0)
{

}

ViewProcess::~ViewProcess() {

}

int ViewProcess::init(int argc, char* argv[]) {
    return 0;
}

int ViewProcess::exec() {
    return 0;
}

int ViewProcess::quit(int exitCode) {
    m_exit_code = exitCode;
    m_running = false;
    return 0;
}

int ViewProcess::write(const base::MessageBase* pMsg) {
    return 0;
}

int ViewProcess::read(base::MessageBase* pMsg) {
    return 0;
}

bool ViewProcess::getRunning() const {
    return m_running;
}

void ViewProcess::setRunning(bool state) {
    m_running = state;
}

int ViewProcess::getExitCode() {
    return m_exit_code;
}

} // end namespace core
