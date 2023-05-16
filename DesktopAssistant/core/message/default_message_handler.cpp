#include "default_message_handler.h"


namespace core {

DefaultMessageHandler::DefaultMessageHandler()
{

}

DefaultMessageHandler::~DefaultMessageHandler() {

}

int DefaultMessageHandler::write(const base::MessageBase* pMsg) {
    return 0;
}

int DefaultMessageHandler::read(base::MessageBase* pMsg) {
    return 0;
}

bool DefaultMessageHandler::serialize(const base::MessageBase* pMsg, base::Buffer* pBuffer) {
    return true;
}

bool DefaultMessageHandler::deserialize(const base::Buffer* pBuffer, base::MessageBase* pMsg) {
    return true;
}

int DefaultMessageHandler::process(base::MessageBase* pMsg) {
    return 0;
}

} // end namespace core
