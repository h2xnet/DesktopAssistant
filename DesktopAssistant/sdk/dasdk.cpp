#include "dasdk.h"

#include "base/file/file_util.h"


extern base::CommandLine g_command_line;

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
    QString strArg1 = QString("-mainPid=%1").arg(QString::number(QApplication::applicationPid()));

    QStringList args;
    args << "-startView=on";
    args << strArg1;

    return args;
}

base::CommandLine* getCommandLine() {
    return &g_command_line;
}

} // end namespace hxxda
