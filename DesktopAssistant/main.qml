import QtQuick 2.12
import QtQuick.Window 2.12

import QtQuick.Controls 1.4
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0

import "./hxxui/window/mouse"
import "./hxxui/bar"
import "./hxxui/menu"

import desktopAssistant.net.pc 1.0

Window {
    id: mainWndId

    // 背景窗口属性
    property var backgroudColor: "#000000" // 背景颜色
    property int backgroudRadius: 4 // 背景边框圆角值
    property var backgroudOpacity: 0.6 // 背景透明度
    property int borderRadius: 10

    // 背景窗口大小
    property bool isFullScreen: false // 全屏标志
    property int backgroudWidth: 800 // 背景宽
    property int backgroudHeight: 600 // 背景高
    property int minBackgroudWidth: 800
    property int minBackgroudHeight: 600

    // 标题栏
    property var titleBarText: "桌面助手 V1.0"
    property int titleBarHeight: 40

    //
    // 鼠标拖动改变大小
    //
    MouseDrag {
        id: mourseDragId

        target: mainWndId

    } // end MouseDrag

    //
    // 系统托盘
    //
    //
    // 系统托盘
    //
    SystemTrayIcon {
        id: systemTrayId

        visible: true

        menu: menuId
        icon: "qrc:/image/logo/logo.png"
        toolTip: "桌面助手"
        onTrigger: {
            // 单击系统托盘
            showMainWnd();

            // 托盘单击事件
            onSystemTrayClick();
        }

        MyMenu {
            id: menuId

            MyAction {
                id: exitItem
                text: qsTr("退出")
                onTriggered: {
                    console.info("main.qml systemTrap close event");
                    onCloseAppEvent(0);
                }
            }
        }
    } // end SystemTrayIcon

    //
    // 系统设置
    //
    SettingsMenu {
        id: settingsMenuId

        visible: false;
    }

    //
    // 开始菜单
    //
    StartMenu {
        id: startMenuId
        visible: false
    }

    flags: Qt.Tool | Qt.FramelessWindowHint | Qt.CustomizeWindowHint | Qt.MSWindowsFixedSizeDialogHint

    title: qsTr("DesktopAssistant")

    visible: true
    color: "transparent"

    width: (isFullScreen ? Screen.desktopAvailableWidth : backgroudWidth)
    height: (isFullScreen ? Screen.desktopAvailableHeight : backgroudHeight)
    minimumWidth: minBackgroudWidth
    minimumHeight: minBackgroudHeight

    // backgroup
    Rectangle {
        id: backgroupWinId

        anchors.fill: parent

        color: backgroudColor
        radius: backgroudRadius
        opacity: backgroudOpacity

    } // end backgroupWinId Rectangle

    // main page
    Rectangle {
        id: mainPageWinId

        anchors.fill: parent

        color: "transparent"

        // titleBar
        TitleBar {
            id: titleBarId

            //visible: !isFullScreen

            parentControl: mainWndId
            width: parent.width
            height: mainWndId.titleBarHeight

        } // end titleBarId TitleBar

        // 悬浮栏
        FloatBar {
            id: floatBarId

            visible: false
            anchors {
                top: parent.top
                topMargin: mainWndId.titleBarHeight
                right: parent.right
                rightMargin: 5
            }

            parentControl: mainWndId
        } // end floatBarId

        // TAB视图
        Rectangle {
            id: tablePageWinId

            anchors {
                top: parent.top
                topMargin: mainWndId.titleBarHeight
            }

            width: parent.width
            height: parent.height - mainWndId.titleBarHeight
            color: "transparent"
            radius: borderRadius

            StackView {
                id: tableStackViewId

                anchors {
                    left: parent.left
                    leftMargin: 5
                    top: parent.top
                    topMargin: 0
                }

                width: parent.width - 10
                height: parent.height - 5
            }

        } // end tablePageWinId Rectangle


    } // end mainPageWinId

    Component.onCompleted: {
        console.info("main.qml Component.onCompleted!");

        // 初始化界面
        let pageUrl = "qrc:/views/default/DefaultTabView.qml"
        tableStackViewId.push(pageUrl, {mainWndObject: mainWndId});

        // 初始化应用
        onInitAppEvent();

    }

    Component.onDestruction: {
        console.info("main.qml Component.onDestruction!");


    }

    //
    // onInitAppEvent : 初始化应用事件
    //
    function onInitAppEvent() {
        console.info("main.qml onInitAppEvent");

    }

    //
    // onCloseAppEvent : 关闭应用事件
    //
    function onCloseAppEvent(exitCode = 0) {
        console.info("main.qml onCloseApp, exitCode:" + exitCode);

        systemTrayId.visible = false;

        mainWndId.close();
        Qt.quit();
    }

    //
    // showMainWnd : 显示主窗口
    //
    function showMainWnd() {
        // 显示主界面
        mainWndId.showNormal();
        mainWndId.requestActivate();
        mainWndId.show();
    }

    //
    // hideMainWnd : 隐藏主窗口
    //
    function hideMainWnd() {
        mainWndId.visible = false;
    }

    //
    // commonEvent : 公共事件
    //
    function commonEvent(eventName) {
        console.log("main.qml commonEvent params, eventName:" + eventName);

        if (eventName === "sysCloseBtnId") {
            // 关闭事件
            //onCloseAppEvent(0);
            hideMainWnd();
        }
        else if (eventName === "sysMaxBtnId") {
            // 最大化按钮
            onMaxEvent();
        }
        else if (eventName === "sysRestoreBtnId") {
            // 恢复
            onMaxEvent();
        }
        else if (eventName === "sysSettingsBtnId") {
            // 设置按钮
            onSettingsEvent();
        }
        else if (eventName === "startMenuBtnId") {
            // 开始菜单
            onStartMenuEvent();
        }
    }

    //
    // onMaxEvent : 最大化事件
    //
    function onMaxEvent() {

        if (isFullScreen) {
            isFullScreen = false;
        }
        else {
            isFullScreen = true;
        }
        mainWndId.setX(isFullScreen ? 0 : (Screen.desktopAvailableWidth - backgroudWidth) / 2)
        mainWndId.setY(isFullScreen ? 0 : (Screen.desktopAvailableHeight - backgroudHeight) / 2)
        mainWndId.setWidth(isFullScreen ? Screen.desktopAvailableWidth : backgroudWidth);
        mainWndId.setHeight(isFullScreen ? Screen.desktopAvailableHeight : backgroudHeight);

    }

    //
    // onSettingsEvent : 设置事件
    //
    function onSettingsEvent() {
        settingsMenuId.x = mainWndId.width - settingsMenuId.width - 15;
        settingsMenuId.y = titleBarHeight;
        settingsMenuId.beginShow();
    }

    //
    // onSystemTrayClick : 单击托盘事件
    //
    function onSystemTrayClick() {
        console.log("main.qml onSystemTrayClick");
    }

    //
    // onStartMenuEvent : 开始菜单事件
    //
    function onStartMenuEvent() {
        startMenuId.x = mainWndId.width - startMenuId.width - 15;
        startMenuId.y = titleBarHeight;
        startMenuId.beginShow();
    }

}
