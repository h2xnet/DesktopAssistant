#include "startup.h"

#include "sdk/dasdk.h"

namespace core {

Startup::Startup()
{

}

Startup::~Startup() {

}

QProcess* Startup::startViewChildProcess(int timeout, QObject* parent) {
    QString strCmd = hxxda::getStartViewChildProcessCmd();
    QStringList arguments = hxxda::getStartViewChildProcessArguments();

    QProcess* process = new QProcess(parent);
    if (process) {
        process->start(strCmd, arguments);
        if (timeout > 0) {
            bool bret = process->waitForStarted(timeout);
            if (!bret) {
                process->deleteLater();
                process = nullptr;
            }
        }
    }
    return process;
}


} // end namespace core
