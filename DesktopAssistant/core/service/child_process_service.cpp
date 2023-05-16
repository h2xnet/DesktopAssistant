#include "child_process_service.h"

namespace core {

ChildProcessService::ChildProcessService(QObject* parent) : base::ServiceThread(this, parent)
{

}

ChildProcessService::~ChildProcessService() {

}

int ChildProcessService::write(const base::MessageBase* pMsg) {
    return 0;
}

int ChildProcessService::read(base::MessageBase* pMsg) {
    return 0;
}

int ChildProcessService::process(base::MessageBase* pMsg) {
    return 0;
}

} // end namespace core
