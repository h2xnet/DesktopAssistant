#ifndef ERROR_H
#define ERROR_H

#include <QString>

namespace base {

#define ERROR_CODE_OK   0   // 顺利完成
#define ERROR_CODE_NEXT 5   // 进入下一轮
#define ERROR_CODE_FAIL 100   // 失败

#define ERROR_CODE_PARAM_ERROR  -1  // 参数错误


#define ERROR_CODE_NO_RESOURCE  -1000 // 资源耗尽
#define ERROR_CODE_TIMEOUT  -1001   // 超时


} // end namespace base

#endif // ERROR_H
