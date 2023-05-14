import QtQuick 2.0
import QtQuick.Controls 2.12

import "../button"

Rectangle {
    id: controlId

    property var parentControl: null

    property var titleBarText: "桌面助手"

    property var backgroudColor: "#FFFFFF"
    property int backgroudRadius: 4

    property int sysBtnWidth: 40
    property int sysBtnHeight: 40

    color: backgroudColor
    radius: backgroudRadius

    MouseArea {
        anchors.fill: parent
        onDoubleClicked: {
            onClickEvent("sysMaxBtnId");
        }
    }

    // 标题文本
    Text {
        id: titleBarTextId

        anchors.centerIn: parent

        text: titleBarText
    }

    // 开始菜单按钮
    ImageColorButton {
        id: startMenuBtnId

        anchors {
            verticalCenter: parent.verticalCenter
            right: parent.right
            rightMargin: 130
        }

        tipText: "开始"
        imageWidth: 24
        imageHeight: 24
        normalColor: "#FFFFFF"
        hoverColor: "#F5F5F5"
        normalImageUrl: "qrc:/image/default/start_menu2.png"
        hoverImageUrl: "qrc:/image/default/start_menu2.png"

        width: 30
        height: 30
        color: "transparent"

        onClicked: {
            onClickEvent("startMenuBtnId");
        }

    } // end startMenuBtnId

    // 设置按钮
    ImageColorButton {
        id: sysSettingsBtnId

        anchors {
            verticalCenter: parent.verticalCenter
            right: parent.right
            rightMargin: 85
        }

        tipText: "系统设置"
        imageWidth: 14
        imageHeight: 14
        normalColor: "#FFFFFF"
        hoverColor: "#F5F5F5"
        normalImageUrl: "qrc:/image/default/settings_normal.png"
        hoverImageUrl: "qrc:/image/default/settings_normal.png"

        width: 30
        height: 30
        color: "transparent"

        onClicked: {
            onClickEvent("sysSettingsBtnId");
        }


    } // end sysSettingsBtnId ImageColorButton

    // 最大化按钮
    ImageColorButton {
        id: sysMaxBtnId

        anchors {
            verticalCenter: parent.verticalCenter
            right: parent.right
            rightMargin: 50
        }

        tipText: "最大化"
        imageWidth: 14
        imageHeight: 14
        normalColor: "#FFFFFF"
        hoverColor: "#F5F5F5"
        normalImageUrl: "qrc:/image/default/max_normal.png"
        hoverImageUrl: "qrc:/image/default/max_normal.png"

        width: 30
        height: 30
        color: "transparent"

        onClicked: {
            onClickEvent("sysMaxBtnId");
        }

    } // end sysMaxBtnId ImageColorButton

    // 关闭按钮
    ImageColorButton {
        id: sysCloseBtnId

        anchors {
            verticalCenter: parent.verticalCenter
            right: parent.right
            rightMargin: 15
        }

        tipText: "关闭"
        imageWidth: 14
        imageHeight: 14
        normalColor: "#FFFFFF"
        hoverColor: "#F5F5F5"
        normalImageUrl: "qrc:/image/default/close_normal.png"
        hoverImageUrl: "qrc:/image/default/close_normal.png"

        width: 30
        height: 30
        color: "transparent"

        onClicked: {
            onClickEvent("sysCloseBtnId");
        }

    } // end sysCloseBtnId ImageColorButton


    function onClickEvent(sourceId) {
        if (parentControl) {
            parentControl.commonEvent(sourceId);
        }
    }

}
