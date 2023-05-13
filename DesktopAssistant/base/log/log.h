#ifndef LOG_H
#define LOG_H

#include <qlogging.h>
#include <QString>

class Log {
public:
    Log();
    ~Log();

    /*
     * Func: clearLogFiles
     * Desc: 清理过期日志文件
     * Author: zfs
     * Date: 2022-08-25 06:47
     */
    static void clearLogFiles(QString logFileName, int preDays = 7);

    static bool init(QString fileName = QString("printclient.log"));
    static void uninit();

    static void messageOutput(QtMsgType type, const QMessageLogContext& context, const QString& msg);

    static void setLogRange(int logRange);
    static int getLogRange();
private:

    static bool OnLogCanOutput(QtMsgType logMsgType);

};

#endif // LOG_H
