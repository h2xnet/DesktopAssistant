#include "dasdk.h"

#include "base/file/file_util.h"

namespace hxxda {

QString getStartViewChildProcessCmd() {
#ifdef Q_OS_WIN
    QString name = "DesktopAssistant.exe";
#else
    QString name = "DesktopAssistant";
#endif
    QString strCmd = base::FileUtil::getAppSubFileName(name);
    return strCmd;
}

QStringList getStartViewChildProcessArguments() {
    QStringList args;
    args << "-startView=on";
    args << "-mainPid=" << QString::number(QApplication::applicationPid());

    return args;
}

} // end namespace hxxda