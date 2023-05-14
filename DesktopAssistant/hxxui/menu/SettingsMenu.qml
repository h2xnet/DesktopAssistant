import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

Popup {
    id: controlId

    property var backgroudColor: "#FFFFFF"
    property int bordRadius: 10
    property var borderColor: "#CCCCCC"
    property int borderWidth: 1

    closePolicy: Popup.CloseOnPressOutside

    x: parent.right
    y: parent.top
    width: 200
    height: 220

    background: Rectangle {
        color: backgroudColor
        radius: bordRadius
        border.color: borderColor
        border.width: borderWidth
    }

    function beginShow() {
        controlId.open();
    }

    function endShow() {
        if (controlId.opened) {
            controlId.close();
        }
    }

}
