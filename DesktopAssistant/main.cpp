//#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>

#include "app.h"

#include "base/log/log.h"
#include "base/util/command_line.h"

#include "core/startup/startup.h"
#include "core/process/viewProcessApp/view_process_app.h"

#include "core/service/child_view_service.h"


// 系统托盘
#include "third-part/systemTray/systemCursor/system_cursor_deal.h"
#include "third-part/systemTray/systemTray/system_tray_icon.h"

#include "manager.h"

using namespace SystemCursorDealSpace;

App g_app; // 应用对象
base::CommandLine g_command_line; // 命令行参数
core::Startup g_startup; // 启动器对象

Manager g_manager; // 管理器对象

// 服务对象列表
core::ChildViewService g_child_view_service; // 子页面服务对象

App& getApp() {
    return g_app;
}

static QObject* AppSingleProvider(QQmlEngine* engine, QJSEngine* scriptEngine) {
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return &g_app;
}

static QObject* ManagerSingleProvider(QQmlEngine* engine, QJSEngine* scriptEngine) {
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return &g_manager;
}

static QObject* ChildViewServiceSingleProvider(QQmlEngine* engine, QJSEngine* scriptEngine) {
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);

    return &g_child_view_service;
}


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseOpenGLES, false);
    QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL, true);

    int ret = -1;
    QString strValue;
    // 根据输入的参数，启动不同的进程
    g_command_line.parse(argc, argv);
    if (g_command_line.contain(base::CommandLine::getStartViewKey())) {
        // 子页面进程
        strValue = g_command_line.getItemValue(base::CommandLine::getStartViewKey());
        if (strValue.compare("on", Qt::CaseInsensitive) == 0) {
            // 子页面进程
            core::ViewProcessApp app;
            ret = app.init(argc, argv);
            if (ret != 0) {
                return ret;
            }
            ret = app.exec();
            return ret;
        }
    }

    // 主窗口进程
    //QGuiApplication app(argc, argv);
    QApplication app(argc, argv);

    // 清理日志文件
    QString logFileName("DesktopAssistant.log");
    base::Log::clearLogFiles(logFileName, 7);

    // 初始化日志
    base::Log::setLogRange(0);
    base::Log::init(logFileName);

    ret = g_app.init();
    qInfo() << "主程序应用初始化结果:" << ret;

    ret = g_manager.init(argc, argv);
    qInfo() << "程序管理器初始化结果:" << ret;

    // 单列全局对象
    qmlRegisterSingletonType<App>("desktopAssistant.net.pc", 1, 0, "appId", AppSingleProvider);  // 注册应用类型
    qmlRegisterSingletonType<Manager>("desktopAssistant.net.pc", 1, 0, "managerId", ManagerSingleProvider);  // 注册管理类型

    // 服务对象
    qmlRegisterSingletonType<core::ChildViewService>("desktopAssistant.net.pc", 1, 0, "childViewServiceId", ChildViewServiceSingleProvider);

    // 系统托盘
    qmlRegisterType<MyMenu>("desktopAssistant.net.pc", 1, 0, "MyMenu");
    qmlRegisterType<MyAction>("desktopAssistant.net.pc", 1, 0, "MyAction");
    qmlRegisterType<MySeparator>("desktopAssistant.net.pc", 1, 0, "MySeparator");
    qmlRegisterType<SystemTrayIcon>("desktopAssistant.net.pc", 1, 0, "SystemTrayIcon");
    qmlRegisterType<SystemCursorDeal>("desktopAssistant.net.pc", 1, 0, "SystemCursorDeal");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
