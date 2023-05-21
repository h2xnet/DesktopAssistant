#include "tool_util.h"

#include <QUuid>

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


} // end namespace base
