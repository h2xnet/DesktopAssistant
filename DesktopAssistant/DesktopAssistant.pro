QT += quick

QT += qml sql
QT += network
QT += core
QT += websockets
QT += xml
QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        app.cpp \
        base/buffer/buffer.cpp \
        base/childProcess/child_process_base.cpp \
        base/childProcess/default_child_process.cpp \
        base/exception/exception.cpp \
        base/file/cfg_ini.cpp \
        base/file/file_util.cpp \
        base/log/log.cpp \
        base/message/ipc/local_socket_client.cpp \
        base/message/ipc/local_socket_server.cpp \
        base/message/message_base.cpp \
        base/message/message_handler_base.cpp \
        base/message/message_queue.cpp \
        base/thread/service_thread.cpp \
        base/thread/thread_base.cpp \
        base/tool/command_line.cpp \
        base/tool/startup_base.cpp \
        core/factory/view_process_factory.cpp \
        core/message/default_message_handler.cpp \
        core/process/view_process.cpp \
        core/service/child_view_service.cpp \
        core/startup/startup.cpp \
        main.cpp \
        manager.cpp \
        third-part/systemTray/systemCursor/system_cursor_deal.cpp \
        third-part/systemTray/systemTray/system_tray_icon.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    app.h \
    base/buffer/buffer.h \
    base/childProcess/child_process_base.h \
    base/childProcess/default_child_process.h \
    base/define.h \
    base/exception/error.h \
    base/exception/exception.h \
    base/file/cfg_ini.h \
    base/file/file_util.h \
    base/log/log.h \
    base/message/ipc/local_socket_client.h \
    base/message/ipc/local_socket_server.h \
    base/message/message_base.h \
    base/message/message_handler_base.h \
    base/message/message_queue.h \
    base/thread/service_thread.h \
    base/thread/thread_base.h \
    base/tool/command_line.h \
    base/tool/startup_base.h \
    core/factory/view_process_factory.h \
    core/message/default_message_handler.h \
    core/process/view_process.h \
    core/service/child_view_service.h \
    core/startup/startup.h \
    manager.h \
    third-part/systemTray/systemCursor/system_cursor_deal.h \
    third-part/systemTray/systemTray/system_tray_icon.h
