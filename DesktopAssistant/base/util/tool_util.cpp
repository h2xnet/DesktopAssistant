#include "tool_util.h"

#include <QUuid>
#include <QApplication>
#include <QJsonDocument>

namespace base {

ToolUtil::ToolUtil()
{

}

QString ToolUtil::getUuid() {
    QUuid uuid = QUuid::createUuid();
    QString strUuid = uuid.toString();
    int pos1 = strUuid.indexOf('{', 0);
    int pos2 = strUuid.lastIndexOf('}');
    if (pos1 >= 0) {
        strUuid = strUuid.mid(pos1 + 1);
    }
    if (pos2 > 0) {
        strUuid = strUuid.left(pos2);
    }
    return strUuid;
}

//
// getCurrentPID : 获取当前进程ID
//
QString ToolUtil::getCurrentPID() {
    QString strPID = QString::number(QApplication::applicationPid());
    return strPID;
}

QString ToolUtil::qjsonobjectToQstring(const QJsonObject& obj) {
    return QString(QJsonDocument(obj).toJson(QJsonDocument::Compact));
}

QString ToolUtil::qjsonarrayToQstring(const QJsonArray& arr) {
    return QString(QJsonDocument(arr).toJson(QJsonDocument::Compact));
}

QJsonObject ToolUtil::qstringToQjsonobject(const QString& str) {
    QJsonObject obj;
    QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());

    // check validity of the document
    if (!doc.isNull())
    {
        if(doc.isObject())
        {
            obj = doc.object();
        }
    }

    return obj;
}

QJsonArray ToolUtil::qstringToQjsonarray(const QString& str) {
    QJsonArray obj;
    QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());

    // check validity of the document
    if(!doc.isNull())
    {
        if(doc.isArray())
        {
            obj = doc.array();
        }
    }

    return obj;
}

} // end namespace base
