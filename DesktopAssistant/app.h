#ifndef APP_H
#define APP_H

#include "core/startup/startup.h"

#include <QDebug>
#include <QString>

class App : public QObject
{
    Q_OBJECT
public:
    App(QObject* parent = nullptr);
    ~App();

    Q_INVOKABLE bool init();

    Q_INVOKABLE void uninit();

    /*
     * Func: getStartup
     * Desc: 获取启动器
     * Author: zfs
     * Date: 2023-05-21 17:04
     */
    core::Startup* getStartup();


};

extern App& getApp();

#endif // APP_H
