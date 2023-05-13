#include "cfg_ini.h"

#include "base/file/file_util.h"

#include <QSettings>

CfgIni::CfgIni() {

}

CfgIni::CfgIni(QString fileName) : file_name_(fileName) {

}

CfgIni::~CfgIni() {

}

bool CfgIni::init(QString iniFileName) {
    file_name_ = iniFileName;
    return file_name_.isEmpty() ? false : true;
}

bool CfgIni::OnFileIsExist() {
    return FileUtil::fileIsExist(file_name_);
}

//
// 读写ini文件布尔值
//
bool CfgIni::readBoolValue(QString key, bool defValue) {
    if (!OnFileIsExist()) {
        return false;
    }

    QSettings ini(file_name_, QSettings::IniFormat);
    int ret = ini.value(key, defValue ? 1 : 0).toInt();

    return ret > 0 ? true : false;
}

bool CfgIni::writeBoolValue(QString key, bool value) {
    if (file_name_.isEmpty()) {
        return false;
    }

    QSettings ini(file_name_, QSettings::IniFormat);
    ini.setValue(key, value ? "1" : "0");
    return true;
}

//
// 读写ini文件整数值
//
int CfgIni::readIntValue(QString key, int defValue) {
    if (!OnFileIsExist()) {
        return defValue;
    }

    QSettings ini(file_name_, QSettings::IniFormat);
    return ini.value(key, defValue).toInt();
}

bool CfgIni::writeIntValue(QString key, int value) {
    if (file_name_.isEmpty()) {
        return false;
    }

    QSettings ini(file_name_, QSettings::IniFormat);
    ini.setValue(key, value);
    return true;
}

//
// 读写ini文件字符串值
//
QString CfgIni::readStringValue(QString key, QString defValue) {
    if (!OnFileIsExist()) {
        return defValue;
    }

    QSettings ini(file_name_, QSettings::IniFormat);
    return ini.value(key, defValue).toString();
}

bool CfgIni::writeStringValue(QString key, QString value) {
    if (file_name_.isEmpty()) {
        return false;
    }

    QSettings ini(file_name_, QSettings::IniFormat);
    ini.setValue(key, value);
    return true;
}
