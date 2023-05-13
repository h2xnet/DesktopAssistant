//#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>

#include "app.h"

#include "base/log/log.h"

App g_app;

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    //QGuiApplication app(argc, argv);
    QApplication app(argc, argv);

    int ret = -1;
    // 清理日志文件
    QString logFileName("DesktopAssistant.log");
    Log::clearLogFiles(logFileName, 7);

    // 初始化日志
    Log::setLogRange(0);
    Log::init(logFileName);

    ret = g_app.init();
    qInfo() << "主程序应用初始化结果:" << ret;

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
