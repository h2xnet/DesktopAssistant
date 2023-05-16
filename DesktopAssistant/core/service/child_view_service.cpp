#include "child_view_service.h"

namespace core {

ChildViewService::ChildViewService(QObject* parent) : base::ServiceThread(this, parent)
{

}

ChildViewService::~ChildViewService() {

}

int ChildViewService::write(const base::MessageBase* pMsg) {
    return 0;
}

int ChildViewService::read(base::MessageBase* pMsg) {
    return 0;
}

int ChildViewService::process(base::MessageBase* pMsg) {
    return 0;
}

} // end namespace core
