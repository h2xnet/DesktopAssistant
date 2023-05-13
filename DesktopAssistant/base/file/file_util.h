#ifndef FILEUTIL_H
#define FILEUTIL_H

#include <QString>

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

#endif // FILEUTIL_H
