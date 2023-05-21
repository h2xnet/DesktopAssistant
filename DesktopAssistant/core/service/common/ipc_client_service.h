#ifndef IPC_CLIENT_SERVICE_H
#define IPC_CLIENT_SERVICE_H

#include "base/thread/service_thread.h"
#include "core/message/default_message_handler.h"

namespace core {



class IPCClientService : public base::ServiceThread, public core::DefaultMessageHandler
{
    Q_OBJECT
public:
    IPCClientService();
    virtual ~IPCClientService();

};

} // end namespace core

#endif // IPC_CLIENT_SERVICE_H
