#include "base/file/file_util.h"

#include <QCoreApplication>
#include <QFileInfo>
#include <QDir>

//#if defined (WIN32) || defined(WIN64)
//#include <Windows.h>
//#endif

FileUtil::FileUtil() {

}

FileUtil::~FileUtil() {

}

QString FileUtil::getAppPath() {
    return QDir::toNativeSeparators(QCoreApplication::applicationDirPath());
}

QString FileUtil::getAppSubFileName(QString subFileName) {
    return getAppPath() + QDir::separator() + subFileName;
}

//
// fileIsExist : 判断文件是否存在
//
bool FileUtil::fileIsExist(const QString& fileName) {
    QFileInfo finfo(fileName);
    return finfo.exists();
}

//
// pathIsExist : 判断路径是否存在
//
bool FileUtil::pathIsExist(const QString& path, bool isCreated) {
    QDir dir(path);
    if (!dir.exists()) {
        if (isCreated) {
            dir.mkpath(path);
        }
    }
    return dir.exists();
}
