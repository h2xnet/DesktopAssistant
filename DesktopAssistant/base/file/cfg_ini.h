#ifndef CFG_INI_H
#define CFG_INI_H

#include <QString>

namespace base {

/*
 * ClassName: CfgIni
 * Desc: INI配置文件操作类
 * Author: zfs
 * Date: 2022-04-09 10:12
 */
class CfgIni
{
public:
    CfgIni();
    CfgIni(QString fileName);
    ~CfgIni();

    //
    // init : 初始化ini文件名
    //
    bool init(QString iniFileName);

    //
    // 读写ini文件布尔值
    //
    bool readBoolValue(QString key, bool defValue = false);
    bool writeBoolValue(QString key, bool value);

    //
    // 读写ini文件整数值
    //
    int readIntValue(QString key, int defValue = -1);
    bool writeIntValue(QString key, int value);

    //
    // 读写ini文件字符串值
    //
    QString readStringValue(QString key, QString defValue = (""));
    bool writeStringValue(QString key, QString value);

private:
    bool OnFileIsExist();

    QString file_name_;
};

} // end namespace base

#endif // CFGINI_H
