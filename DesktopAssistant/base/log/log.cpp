#include "log.h"

#include "base/file/file_util.h"

#include <QCoreApplication>
#include <QDateTime>
#include <QFile>
#include <QDir>
#include <QMutex>
#include <QTextStream>
#include <QDebug>

namespace base {

static QMutex mutex_;
static QFile* file_ = nullptr;
static QString log_file_name_ = QString("log.log");
static int log_range_ = 0;
static double log_file_max_size = 500;  //per M
static double default_log_max_size = 10 ;//per M

static QString msgHead[]={
    QString("Debug   "),
    QString("Warning "),
    QString("Critical"),
    QString("Fatal   "),
    QString("Info    ")
};

void Log::clearLogFiles(QString logFileName, int preDays/* = 7*/) {
    if (preDays < 0) {
        preDays = 3;
    }

    //QString logPath = QCoreApplication::applicationDirPath();
    //QString path = logPath + "/log";
    QString path = FileUtil::getLogPath("log");
    QString strSearchText = logFileName;

    if (strSearchText.isEmpty()) {
        strSearchText = QString("printClient.log");
    }

    QDateTime currentTime = QDateTime::currentDateTime();
    QDir dir(path);
    QFileInfoList fileInfoList = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);

    // 秒数
    qint64 dayOfSecs = 3600 * 24 * preDays;

    int count = 0;
    foreach (auto fileInfo, fileInfoList) {
        if (fileInfo.isFile()) {
            QString strFilePath = fileInfo.absoluteFilePath();
            QString strFileName = fileInfo.fileName();
            qDebug("logofile.cpp ClearLogFiles filePath:%s fileName:%s\r\n", strFilePath.toUtf8().data(), strFileName.toUtf8().data());

            QString strFileDate = strFileName.replace(QRegExp(strSearchText), "");
            qDebug("logfile.cpp ClearLogFiles fileData:%s\r\n", strFileDate.toUtf8().data());

            // 2022-05-31-20-32-51
            QDateTime fileTime = QDateTime::fromString(strFileDate, "yyyy-MM-dd-hh-mm-ss");

            // 计算时间差，秒数
            qint64 intervalTimes = fileTime.secsTo(currentTime);

            qDebug("logfile.cpp ClearLogFiles intervalTimes : %s\r\n", QString::number(intervalTimes).toUtf8().data());

           if (intervalTimes >= dayOfSecs) {
                QFile::remove(strFilePath);
                count++;
           }
        }
    }

    qDebug("logfile.cpp ClearLogFiles count: %d\r\n", count);
}

void Log::messageOutput(QtMsgType type, const QMessageLogContext& context, const QString& msg) {
    if (!OnLogCanOutput(type)) {
        return;
    }

    QByteArray localMsg = msg.toUtf8();
    QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");

    if (file_) {
        QMutexLocker lock(&mutex_);
        double fileSize = file_->size();

        if (fileSize >= log_file_max_size){
            if (file_){
                file_->close();
                delete file_;
                file_ =  nullptr;
            }

            // log path
            QString strLogPath = FileUtil::getLogPath("log");

            QDateTime currentTime = QDateTime::currentDateTime();//yyyy.MM.dd hh:mm:ss.zzz ddd
            QString currentTimeStr =currentTime .toString("yyyy-MM-dd-hh");

            QString logFileName = strLogPath + QDir::separator() + currentTimeStr + "-" + log_file_name_;

            // 打开文件
            file_ = new QFile(logFileName);
            if (!file_) {
                return;
            }

            if (!file_->open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
                delete file_;
                file_ = nullptr;
                return;
            }

            qInstallMessageHandler(messageOutput);

        }

        QTextStream tWrite(file_);
        tWrite.setCodec("UTF-8");
        QString msgText="%1 | %5 | %2:%3 | %4\n";
        msgText = msgText.arg(msgHead[type].toStdString().data()).arg(context.file).arg(context.line).arg(localMsg.constData()).arg(current_date_time);
        tWrite << msgText;
    }
    else {
    }
}

Log::Log() {

}

Log::~Log() {

}

void Log::setLogRange(int logRange) {
    log_range_ = logRange;
}

int Log::getLogRange() {
    return log_range_;
}

bool Log::init(QString fileName) {
    //QMutexLocker lock(&mutex_);

    QString strLogPath = FileUtil::getLogPath("log");
    qInfo() << "Log::init log path:" << strLogPath;

    QDateTime currentTime = QDateTime::currentDateTime();//yyyy.MM.dd hh:mm:ss.zzz ddd
    QString currentTimeStr = currentTime .toString("yyyy-MM-dd-hh");

    if (fileName.isEmpty()) {
        fileName = QString("DriverServer.log");
    }
    log_file_name_ = fileName;

    QString logFileName = strLogPath + QDir::separator() + currentTimeStr + "-" + fileName;

    qInfo("Log::init log fileName: %s\n", logFileName.toUtf8().data());

    // 打开文件
    file_ = new QFile(logFileName);
    if (!file_) {
        qDebug("Log::init open log file fail.\n");
        return false;
    }

    if (!file_->open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {

        QString err = file_->errorString();
        qDebug("Log::init open log file fail2, errmsg:%s\n", err.toUtf8().data());

        delete file_;
        file_ = nullptr;

        return false;
    }

    qInstallMessageHandler(Log::messageOutput);

    qDebug("Log::init open log file success.\n");

    return true;
}

void Log::uninit() {
    //QMutexLocker lock(&mutex_);
    if (file_){
        if (file_->isOpen()) {
            file_->close();
        }
        delete file_;
        file_ =  nullptr;
    }
}

bool Log::OnLogCanOutput(QtMsgType logMsgType) {
    return (log_range_ <= (int)logMsgType ? true : false);
}

} // end namespace base
