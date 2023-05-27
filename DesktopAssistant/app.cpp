#include "app.h"


#include "core/service/child_view_service.h"

#include <QTextCodec>
#include <QQmlApplicationEngine>

// 服务对象列表
core::ChildViewService* g_child_view_service = nullptr; // 子页面服务对象

extern core::Startup g_startup; // 启动器对象

namespace  {

static QObject* ChildViewServiceSingleProvider(QQmlEngine* engine, QJSEngine* scriptEngine) {
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);

    if (!g_child_view_service) {
        int ret = -1;
        g_child_view_service = new core::ChildViewService(engine);
        if (g_child_view_service) {
            ret = g_child_view_service->beginRun(CHILD_VIEW_SERVICE_SERVER_NAME);
        }
        qInfo() << "ChildViewServiceSingleProvider beginRun ChildViewService status:" << ret;
    }
    return g_child_view_service;
}

} // end namespace

App::App(QObject* parent) : QObject(parent)
{

}

App::~App() {

}

bool App::init() {

    // 设置编码
  #if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
  #if _MSC_VER
      QTextCodec *codec = QTextCodec::codecForName("GBK");
  #else
      QTextCodec *codec = QTextCodec::codecForName("UTF-8");
  #endif
      QTextCodec::setCodecForLocale(codec);
      QTextCodec::setCodecForCStrings(codec);
      QTextCodec::setCodecForTr(codec);
  #else
      QTextCodec *codec = QTextCodec::codecForName("UTF-8");
      QTextCodec::setCodecForLocale(codec);
  #endif

  //
  // 注册类型
  //

  // 服务对象
  qmlRegisterSingletonType<core::ChildViewService>("desktopAssistant.net.pc", 1, 0, "ChildViewServiceId", ChildViewServiceSingleProvider);


    return true;
}

core::Startup* App::getStartup() {
    return &g_startup;
}
