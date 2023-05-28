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
        base/childProcess/child_process_app.cpp \
        base/childProcess/child_process_base.cpp \
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
        base/util/command_line.cpp \
        base/util/startup_base.cpp \
        base/util/tool_util.cpp \
        core/factory/view_process_factory.cpp \
        core/message/child_view_message.cpp \
        core/message/default_message_handler.cpp \
        core/process/viewProcessApp/view_process_app.cpp \
        core/process/view_process_main.cpp \
        core/service/child_view_service.cpp \
        core/service/common/ipc_client_service.cpp \
        core/service/common/ipc_server_service.cpp \
        core/startup/startup.cpp \
        main.cpp \
        manager.cpp \
        sdk/dasdk.cpp \
        sdk/message_package.cpp \
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
    base/childProcess/child_process_app.h \
    base/childProcess/child_process_base.h \
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
    base/util/command_line.h \
    base/util/startup_base.h \
    base/util/tool_util.h \
    core/factory/view_process_factory.h \
    core/message/child_view_message.h \
    core/message/default_message_handler.h \
    core/process/viewProcessApp/view_process_app.h \
    core/process/view_process_main.h \
    core/service/child_view_service.h \
    core/service/common/ipc_client_service.h \
    core/service/common/ipc_server_service.h \
    core/startup/startup.h \
    manager.h \
    sdk/dasdk.h \
    sdk/message_package.h \
    third-part/systemTray/systemCursor/system_cursor_deal.h \
    third-part/systemTray/systemTray/system_tray_icon.h
