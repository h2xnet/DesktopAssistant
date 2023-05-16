#include "default_child_process.h"

namespace base {


DefaultChildProcess::DefaultChildProcess() : base::ChildProcessBase()
{

}

DefaultChildProcess::~DefaultChildProcess() {

}

int DefaultChildProcess::init(int argc, char* argv[]) {
    return 0;
}

int DefaultChildProcess::exec() {
    return 0;
}

int DefaultChildProcess::quit(int exitCode) {
    return 0;
}

int DefaultChildProcess::write(const base::MessageBase* pMsg) {
    return 0;
}

int DefaultChildProcess::read(base::MessageBase* pMsg) {
    return 0;
}

bool DefaultChildProcess::getRunning() const {
    return false;
}

void DefaultChildProcess::setRunning(bool state) {

}

int DefaultChildProcess::getExitCode() {
    return 0;
}

} // end namespace base
