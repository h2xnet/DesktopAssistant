#include "message_base.h"

namespace base {

qint32 MessageBase::getSequeCount() {
    static qint32 sequeCount = 0;
    return (sequeCount++);
}

MessageBase::MessageBase() : sequeNo(0), type(eMessageType::eEventType), code(0)
{
    sequeNo = getSequeCount();
}

MessageBase::~MessageBase() {

}

} // end namespace base
