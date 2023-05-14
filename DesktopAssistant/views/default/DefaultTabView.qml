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
    TabPageView {
        id: tabViewId

        anchors.fill: parent

        backgroudColor: controlId.backgroudColor

    } // end tabViewId TabViewExt

    Component.onCompleted: {
        console.info("DefaultTableView.qml Component.onCompleted!");

        // test add tab pages
        let tabPageUrl1 = "qrc:/views/default/tabpages/DefaultTabPage.qml";
        let tabPageTitle1 = "新标签页";
        let tabPageName1 = "tab1";
        let ret = tabViewId.addNewTabPage(tabPageName1, tabPageTitle1, tabPageUrl1,
                                          { backgroudColor: "#22FFFF"}
                                          );
        console.log("DefaultTableView.qml Component.onCompleted addNewTabPage status:" + ret);

        let tabPageUrl2 = "qrc:/views/default/tabpages/DefaultTabPage.qml";
        let tabPageTitle2 = "qt qml Text显示省略号";
        let tabPageName2 = "tab2";
        ret = tabViewId.addNewTabPage(tabPageName2, tabPageTitle2, tabPageUrl2,
                                      { backgroudColor: "#FF22FF"}
                                      );
        console.log("DefaultTableView.qml Component.onCompleted addNewTabPage status:" + ret);

        let tabPageUrl3 = "qrc:/views/default/tabpages/DefaultTabPage.qml";
        let tabPageTitle3 = "新标签页3";
        let tabPageName3 = "tab3";
        ret = tabViewId.addNewTabPage(tabPageName3, tabPageTitle3, tabPageUrl3,
                                      { backgroudColor: "#25229F"}
                                      );
        console.log("DefaultTableView.qml Component.onCompleted addNewTabPage status:" + ret);

        let tabPageUrl4 = "qrc:/views/default/tabpages/DefaultTabPage.qml";
        let tabPageTitle4 = "新标签页4";
        let tabPageName4 = "tab4";
        ret = tabViewId.addNewTabPage(tabPageName4, tabPageTitle4, tabPageUrl4,
                                      { backgroudColor: "#85FF00"}
                                      );
        console.log("DefaultTableView.qml Component.onCompleted addNewTabPage status:" + ret);

        let tabPageUrl5 = "qrc:/views/default/tabpages/DefaultTabPage.qml";
        let tabPageTitle5 = "新标签页5";
        let tabPageName5 = "tab5";
        ret = tabViewId.addNewTabPage(tabPageName5, tabPageTitle5, tabPageUrl5,
                                      { backgroudColor: "#25823F"}
                                      );
        console.log("DefaultTableView.qml Component.onCompleted addNewTabPage status:" + ret);


    }

    Component.onDestruction: {
        console.info("DefaultTableView.qml Component.onDestruction!");

    }


}
