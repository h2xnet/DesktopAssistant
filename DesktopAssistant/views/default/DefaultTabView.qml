import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

import "../../hxxui/tab"

Rectangle {
    id: controlId

    property var parentControl: null

    property int tabBarHeight: 30
    property int tabBarBtnLeftPadding: 15
    property int tabBarBtnRightPadding: 15

    property int borderRadius: 4

    property var backgroudColor: "#CCCCCC"

    anchors.fill: parent

    color: backgroudColor
    radius: borderRadius

    // tab
    TabViewExt {
        id: tabViewId

        anchors.fill: parent

        backgroudColor: controlId.backgroudColor

    } // end tabViewId TabViewExt

    Component.onCompleted: {
        console.info("DefaultTableView.qml Component.onCompleted!");

        // test add tab pages
        let tabPageUrl1 = "qrc:/views/default/tabpages/DefaultTabPage.qml";
        let tabPageTitle1 = "新标签页";
        let ret = tabViewId.addNewTabPage(tabPageTitle1, tabPageUrl1,
                                          { backgroudColor: "#FFFFFF"}
                                          );
        console.log("DefaultTableView.qml Component.onCompleted addNewTabPage status:" + ret);

        let tabPageUrl2 = "qrc:/views/default/tabpages/DefaultTabPage.qml";
        let tabPageTitle2 = "新标签页2";
        ret = tabViewId.addNewTabPage(tabPageTitle2, tabPageUrl2,
                                      { backgroudColor: "#FF22FF"}
                                      );
        console.log("DefaultTableView.qml Component.onCompleted addNewTabPage status:" + ret);


    }

    Component.onDestruction: {
        console.info("DefaultTableView.qml Component.onDestruction!");

    }


}
