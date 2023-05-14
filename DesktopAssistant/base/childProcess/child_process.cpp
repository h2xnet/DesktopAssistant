#include "child_process.h"

namespace base {

ChildProcess::ChildProcess(QObject* parent) : QProcess(parent)
{

}

ChildProcess::~ChildProcess() {

}

} // end namespace base
