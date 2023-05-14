#include "thread_base.h"

namespace base {

ThreadBase::ThreadBase(QObject* parent) : QThread(parent)
{

}

ThreadBase::~ThreadBase() {

}

} // end namespace base
