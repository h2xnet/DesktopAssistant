#include "ipc_client_service.h"


namespace core {

IPCClientService::IPCClientService() : base::ServiceThread(this, this)
{

}

IPCClientService::~IPCClientService() {

}

} // end namespace core
