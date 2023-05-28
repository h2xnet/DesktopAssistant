#ifndef DEFINE_H
#define DEFINE_H

#include <QString>

namespace base  {

#ifndef DEF_LOCAL_SOCKET_SERVER_NAME
#define DEF_LOCAL_SOCKET_SERVER_NAME "DesktopAssistantDefLocalSocketServerName"
#endif

#ifndef CHILD_VIEW_SERVICE_SERVER_NAME
#define CHILD_VIEW_SERVICE_SERVER_NAME "DesktopAssistantChildViewServiceServerName"
#endif


//
// 消息分段信息
// 系统使用 : 1 ~ 50000
// 用户自定义 : 50000 ~
// 其中 :
// 1 ~ 4999 : 子页面相关事件
// 5000 ~ 9999 :
// 10000 ~ 14999 :
// 15000 ~ 19999 :
// 20000 ~ 24999 :
// 25000 ~ 29999 :
// 30000 ~ 34999 :
// 35000 ~ 39999 :
// 40000 ~ 44999 :
// 45000 ~ 49999 :
//
// 所有消息区间都是包含开始的序号，不包含结束序号
//

//
// 默认消息类型
//
#ifndef DEF_MESSAGE_TYPE
#define DEF_MESSAGE_TYPE 0
#endif

//
// 定义公共消息区间
//
#ifndef PUBLIC_MESSAGE_TART_TYPE
#define PUBLIC_MESSAGE_TART_TYPE 1
#endif

#ifndef PUBLIC_MESSAGE_END_TYPE
#define PUBLIC_MESSAGE_END_TYPE 5000
#endif

//
// 定义子页面消息区间
//
#ifndef CHILD_VIEW_MESSAGE_START_TYPE
#define CHILD_VIEW_MESSAGE_START_TYPE 5000
#endif

#ifndef CHILD_VIEW_MESSAGE_END_TYPE
#define CHILD_VIEW_MESSAGE_END_TYPE 10000
#endif

//
// 用户消息类型值：必须要大于或等于 USER_MESSAGE_TYPE 定义的值，比如
// #define USER_MESSAGE_ADD_VIEW (USER_MESSAGE_TYPE + 100)
//
#ifndef USER_MESSAGE_START_TYPE
#define USER_MESSAGE_START_TYPE   50000
#endif

//
// 公共消息定义
//

// 欢迎消息
#define PUBLIC_MESSAGE_WELCOME_REQUEST  (PUBLIC_MESSAGE_TART_TYPE + 0)
#define PUBLIC_MESSAGE_WELCOME_RESPONSE (PUBLIC_MESSAGE_TART_TYPE + 1)

//
// 子进程页面消息映射列表
//

// 添加子页面消息
#define CHILD_VIEW_MESSAGE_ADD_VIEW_REQUEST     (CHILD_VIEW_MESSAGE_START_TYPE + 0)
#define CHILD_VIEW_MESSAGE_ADD_VIEW_RESPONSE    (CHILD_VIEW_MESSAGE_START_TYPE + 1)

} // end namespace base

#endif // DEFINE_H
