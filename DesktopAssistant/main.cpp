//#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>

#include "app.h"

#include "base/log/log.h"


// 系统托盘
#include "third-part/systemTray/systemCursor/system_cursor_deal.h"
#include "third-part/systemTray/systemTray/system_tray_icon.h"

using namespace SystemCursorDealSpace;

App g_app;

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    //QGuiApplication app(argc, argv);
    QApplication app(argc, argv);

    int ret = -1;
    // 清理日志文件
    QString logFileName("DesktopAssistant.log");
    base::Log::clearLogFiles(logFileName, 7);

    // 初始化日志
    base::Log::setLogRange(0);
    base::Log::init(logFileName);

    ret = g_app.init();
    qInfo() << "主程序应用初始化结果:" << ret;

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
