import QtQuick 2.12
import QtQuick.Window 2.12

import QtQuick.Controls 1.4
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0

import "./hxxui/window/mouse"
import "./hxxui/bar"

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

    flags: Qt.Tool | Qt.FramelessWindowHint | Qt.CustomizeWindowHint | Qt.MSWindowsFixedSizeDialogHint

    title: qsTr("DesktopAssistant")

    visible: true
    color: "transparent"

    width: (isFullScreen ? Screen.desktopAvailableWidth : backgroudWidth)
    height: (isFullScreen ? Screen.desktopAvailableHeight : backgroudHeight)


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

            visible: !isFullScreen

            parentControl: mainWndId
            width: parent.width
            height: mainWndId.titleBarHeight

        } // end titleBarId TitleBar

        // 悬浮栏
        FloatBar {
            id: floatBarId

            visible: isFullScreen
            anchors {
                top: parent.top
                topMargin: 30
                right: parent.right
                rightMargin: 30
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
        tableStackViewId.push(pageUrl, {parentControl: mainWndId});

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

        mainWndId.close();
        Qt.quit();
    }

    //
    // commonEvent : 公共事件
    //
    function commonEvent(eventName) {
        console.log("main.qml commonEvent params, eventName:" + eventName);

        if (eventName === "sysCloseBtnId") {
            // 关闭事件
            onCloseAppEvent(0);
        }
        else if (eventName === "sysMaxBtnId") {
            // 最大化按钮
            onMaxEvent();
        }
        else if (eventName === "sysRestoreBtnId") {
            // 恢复
            onMaxEvent();
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

}
