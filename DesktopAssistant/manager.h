#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>

/*
 * ClassName: Manager
 * Desc: 管理器类
 * Author: zfs
 * Date: 2023-05-16 21:40
 */
class Manager : public QObject
{
    Q_OBJECT
public:
    Manager(QObject* parent = nullptr);
    virtual ~Manager();

    /*
     * Func: init
     * Desc: 初始化管理器
     * Author: zfs
     * Date: 2023-05-16 21:41
     */
    int init(int argc, char* argv[]);

    /*
     * Func: uninit
     * Desc: 释放管理器
     * Author: zfs
     * Date: 2023-05-16 21:42
     */
    int uninit();

};

#endif // MANAGER_H
