#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "base/exception/error.h"

namespace base {

/*
 * ClassName: Exception
 * Desc: 异常信息类
 * Author: zfs
 * Date: 2023-05-14 15:35
 */
class Exception
{
public:
    Exception();
    Exception(int errno, QString errmsg);
    virtual ~Exception();

    int m_errno;
    QString m_errmsg;

};

} // end namespace base

#endif // EXCEPTION_H
