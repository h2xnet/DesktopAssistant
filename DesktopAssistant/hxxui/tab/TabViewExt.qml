import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

TabView {
    id: controlId

    property int tabBarHeight: 30
    property int tabBarBtnLeftPadding: 15
    property int tabBarBtnRightPadding: 15

    property var backgroudColor: "transparent"

    anchors.fill: parent

    // 定制tab按钮
    Component {
        id: tabBarId

        Rectangle {
            height: tabBarHeight
            color: backgroudColor
        }
    } // end tabBarId


    style: TabViewStyle {
        tabsAlignment: Qt.AlignLeft

        leftCorner: Rectangle {
           color: "transparent"
           implicitWidth: tabBarBtnLeftPadding
           implicitHeight: tabBarHeight
        }

        rightCorner: Rectangle {
            color: "transparent"
            implicitWidth: tabBarBtnRightPadding
            implicitHeight: tabBarHeight
        }

        tabBar: tabBarId

    }

    //
    // addNewTabPage : 添加新的tab页面，成功返回序号，失败返回-1
    //
    function addNewTabPage(tabTitle, tabPageUrl, param = {}) {
        var newItem = Qt.createComponent(tabPageUrl);
        if (newItem.status === Component.Ready) {
            console.log("TabViewExt.qml addNewTabPage CreateComponent is ready, pageUrl:" + tabPageUrl);
            var itemTabPage = controlId.addTab(qsTr(tabTitle), newItem);
            if (!itemTabPage) {
                console.info("TabViewExt.qml addNewTabPage addTab fail, pageUrl:" + tabPageUrl);
                return -2;
            }

            itemTabPage.active = true;
            var newTabItem = itemTabPage.item;
            if (!newTabItem) {
                console.info("TabViewExt.qml addNewTabPage addTab fail, new page item is null, pageUrl:" + tabPageUrl);
                return -3;
            }

            console.log("TabViewExt.qml addNewTabPage addTab success, current tab page count:" + controlId.count);

            //newTabItem.strName = tabTitle;
            //newTabItem.title = tabTitle;
            return controlId.currentIndex;
        }
        else {
            console.info("TabViewExt.qml addNewTabPage CreateComponent fail, pageUrl:" + tabPageUrl);
            return -1;
        }
    }


} // end TableView
