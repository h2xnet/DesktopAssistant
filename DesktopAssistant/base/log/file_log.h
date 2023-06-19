#ifndef FILE_LOG_H
#define FILE_LOG_H

#include <QDebug>
#include <QFile>

namespace base {

#define FILE_LOG_TYPE_DEBUG "Debug"
#define FILE_LOG_TYPE_INFO  "Info"
#define FILE_LOG_TYPE_ERROR "Error"

/*
 * ClassName: FileLog
 * Desc: 文件日志类
 * Author: zfs
 * Date: 2023-06-20 07:10
 */
class FileLog
{
public:
    FileLog();
    virtual ~FileLog();

    void setPrefix(QString name);

    bool reOpen();

    bool Debug(const QString& str);
    bool Info(const QString& str);
    bool Error(const QString& str);

private:
    bool onOpenFile();
    void onCloseFile();
    bool onWrite(const QString& logMsgType, const QString& str);

    QString m_prefix;
    QFile m_file;
};

} // end namespace base

#endif // FILE_LOG_H
