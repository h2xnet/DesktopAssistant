import QtQuick 2.0
import QtQuick.Controls 2.12

Rectangle {
    id: controlId

    property var mainWndObject: null
    property var parentControlObject: null

    // 页面自定义参数
    property var pageOwnerStr: ""
    property var pageOwnerObj: null

    property var backgroudColor: "#F23FFF"

    anchors.fill: parent

    color: backgroudColor

}
