#ifndef FILEUTIL_H
#define FILEUTIL_H

#include <QString>

namespace base {

class FileUtil
{
public:
    FileUtil();
    ~FileUtil();

    /*
     * Function: getAppPath
     * Desc: 获取应用路径
     * Author: zfs
     * Date: 2022-04-07 14:12
     */
    static QString getAppPath();

    /*
     * Function: getAppSubFileName
     * Desc: 获取应用目录下字文件名
     * Author: zfs
     * Date: 2022-04-07 14:17
     */
    static QString getAppSubFileName(QString subFileName);

    /*
     * Function: getLogPath
     * Desc: 获取日志文件路径
     * Author: zfs
     * Date: 2022-06-20 07:12
     */
    static QString getLogPath(QString logFolderName = "log");

    /*
     * Function: fileIsExist
     * Desc: 判断文件是否存在
     * Author: zfs
     * Date: 2022-04-07 14:24
     */
    static bool fileIsExist(const QString& fileName);

    /*
     * Function: pathIsExist
     * Desc: 判断路径是否存在
     * Author: zfs
     * Date: 2022-04-08 11:29
     */
    static bool pathIsExist(const QString& path, bool isCreated);

};

} // end namespace base

#endif // FILEUTIL_H
