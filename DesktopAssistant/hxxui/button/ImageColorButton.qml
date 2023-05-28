import QtQuick 2.0
import QtQuick.Controls 2.12

Rectangle {
    id: controlId

    signal clicked();

    property alias backgroudId: backgroudImageId

    property var tipText: ""

    property var normalImageUrl: ""
    property var hoverImageUrl: ""

    property var normalColor: "#FFFFFF"
    property var hoverColor: "#F5F5F5"

    property int imageWidth: 14
    property int imageHeight: 14
    property int borderRadius: 4

    radius: borderRadius
    color: normalColor

    Image {
        id: backgroudImageId

        anchors.centerIn: parent

        z: 1
        width: imageWidth
        height: imageHeight
        source: normalImageUrl
    }

    ToolTip {
        id: toolTipId

        delay: Qt.styleHints.mousePressAndHoldInterval
        text: tipText
        onOpened:{
           if (!mouseAreaId.containsMouse) {
               close()
           }
        }
    }

    MouseArea {
        id: mouseAreaId

        anchors.fill: parent

        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor

        onClicked: {
            controlId.clicked();
        }

        onEntered: {
            color: hoverColor
            backgroudId.source = hoverImageUrl;

            if (tipText !== "") {
                toolTipId.visible = true;
            }
        }

        onPressed: {
            color: hoverColor
            backgroudId.source = hoverImageUrl;
        }

        onExited: {
            color: normalColor
            backgroudId.source = normalImageUrl;

            if (tipText !== "") {
                toolTipId.visible = false;
            }
        }

        onReleased: {
            color: normalColor
            backgroudId.source = normalImageUrl;
        }

    }

}
