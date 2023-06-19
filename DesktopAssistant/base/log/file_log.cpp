#include "file_log.h"

#include "base/file/file_util.h"

#include <QApplication>
#include <QDateTime>
#include <QTextStream>

namespace base {

FileLog::FileLog()
{

}

FileLog::~FileLog() {
    this->onCloseFile();
}

void FileLog::setPrefix(QString name) {
    if (!name.isEmpty()) {
        m_prefix = QString("%1").arg(name);
    }
}

bool FileLog::reOpen() {
    this->onCloseFile();
    return this->onOpenFile();
}

bool FileLog::onOpenFile() {
    if (m_file.isOpen()) {
        return true;
    }

    QString path = FileUtil::getLogPath("log");

    QDateTime currentTime = QDateTime::currentDateTime();//yyyy.MM.dd hh:mm:ss.zzz ddd
    QString currentTimeStr = currentTime .toString("yyyy-MM-dd-hh");
    QString pid = QString::number(QApplication::applicationPid());

    QString strLogFileName;
    if (m_prefix.isEmpty()) {
        strLogFileName = QString("%1/%2_%3.log").arg(path).arg(currentTimeStr).arg(QApplication::applicationPid());
    }
    else {
        strLogFileName = QString("%1/%2_%3_%4.log").arg(path).arg(currentTimeStr).arg(m_prefix).arg(QApplication::applicationPid());
    }

    m_file.setFileName(strLogFileName);
    if (!m_file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
        return false;
    }

    return true;
}

void FileLog::onCloseFile() {
    if (m_file.isOpen()) {
        m_file.close();
    }
}

bool FileLog::onWrite(const QString& logMsgType, const QString& str) {
    if (!str.isEmpty()) {
        QTextStream tWrite(&m_file);
        tWrite.setCodec("UTF-8");
        QDateTime currentTime = QDateTime::currentDateTime();//yyyy.MM.dd hh:mm:ss.zzz ddd
        QString currentTimeStr = currentTime .toString("yyyy.MM.dd hh:mm:ss.zzz ddd");

        QString msgText = QString("%1 【%2】 %3").arg(currentTimeStr).arg(logMsgType).arg(str);

        tWrite << msgText;
    }
    return false;
}

bool FileLog::Debug(const QString& str) {
    return this->onWrite(FILE_LOG_TYPE_DEBUG, str);
}

bool FileLog::Info(const QString& str) {
    return this->onWrite(FILE_LOG_TYPE_INFO, str);
}

bool FileLog::Error(const QString& str) {
    return this->onWrite(FILE_LOG_TYPE_ERROR, str);
}


} // end namespace base
