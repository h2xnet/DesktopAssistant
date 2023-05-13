import QtQuick 2.0
import QtQuick.Controls 2.12

Rectangle {
    id: controlId

    property var parentControl: null

    property var backgroudColor: "#000000"
    property var backgroudOpacity: 0.4

    width: 200
    height: 380
    radius: 10

    opacity: backgroudOpacity
    color: backgroudColor
    z: 9999

    MouseArea {
        anchors.fill: parent

        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor

        onClicked: {
            onEvent("sysRestoreBtnId")
        }
    }

    function onEvent(sourceId) {
        if (parentControl) {
            parentControl.commonEvent(sourceId);
        }
    }

}
