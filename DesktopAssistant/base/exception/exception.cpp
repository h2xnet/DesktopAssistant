#include "exception.h"


namespace base {

Exception::Exception()
{

}

Exception::Exception(int errno, QString errmsg) : m_errno(errno), m_errmsg(errmsg) {

}

Exception::~Exception() {

}

} // end namespace base
