#ifndef CHILD_PROCESS_SERVICE_H
#define CHILD_PROCESS_SERVICE_H

#include "base/thread/service_thread.h"
#include "core/message/default_message_handler.h"
#include "core/process/view_process.h"

#include <QMap>

namespace core {

/*
 * ClassName: ChildViewService
 * Desc: 子页面管理服务类
 * Author: zfs
 * Date: 2023-05-16 21:04
 */
class ChildViewService : public base::ServiceThread, public core::DefaultMessageHandler
{
    Q_OBJECT
public:
    // 页面进程列表
    typedef QMap<QString, ViewProcess*> ViewProcessMap;

    ChildViewService(QObject* parent = nullptr);
    virtual ~ChildViewService();

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
