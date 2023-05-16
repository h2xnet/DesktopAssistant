#ifndef CHILD_PROCESS_SERVICE_H
#define CHILD_PROCESS_SERVICE_H

#include "base/thread/service_thread.h"
#include "core/message/default_message_handler.h"

namespace core {

/*
 * ClassName: ChildProcessService
 * Desc: 子进程管理服务类
 * Author: zfs
 * Date: 2023-05-16 21:04
 */
class ChildProcessService : public base::ServiceThread, public core::DefaultMessageHandler
{
    Q_OBJECT
public:
    ChildProcessService(QObject* parent = nullptr);
    virtual ~ChildProcessService();

    //
    // core::DefaultMessageHandler
    //
    virtual int write(const base::MessageBase* pMsg) override;
    virtual int read(base::MessageBase* pMsg) override;
    virtual int process(base::MessageBase* pMsg) override;

protected:

};

} // end namespace core

#endif // CHILD_PROCESS_SERVICE_H
