import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

import "../../hxxui/tab"

import desktopAssistant.net.pc 1.0

import "../../js/common/CommonEvent.js" as CommonEvent;
import "../../js/view/ViewEvent.js" as ViewEvent;

Rectangle {
    id: controlId

    property var mainWndObject: null

    property int tabBarHeight: 30
    property int tabBarBtnLeftPadding: 15
    property int tabBarBtnRightPadding: 15

    property int borderRadius: 4

    property var backgroudColor: "#CCCCCC"

    anchors.fill: parent

    color: backgroudColor
    radius: borderRadius

    //
    // 启动定时器，延迟启动
    //
    Timer {
        id: startupTimerId

        repeat: false
        interval: 3000
        onTriggered: {
            onStartupEvent();
            if (startupTimerId.running) {
                startupTimerId.stop();
            }
        }
    }

    // tab
    TabPageView {
        id: tabViewId

        anchors.fill: parent

        backgroudColor: controlId.backgroudColor

    } // end tabViewId TabViewExt

    Component.onCompleted: {
        console.info("DefaultTableView.qml Component.onCompleted!");

        // 子页面服务事件绑定
        ChildViewServiceId.childViewSimpleResponseEvent.connect(onChildViewSimpleResponseEvent);
        ChildViewServiceId.childViewResponseEvent.connect(onChildViewResponseEvent);

        // 初始化页面
        onViewInit();


        /*// test add tab pages
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
        console.log("DefaultTableView.qml Component.onCompleted addNewTabPage status:" + ret);*/


    }

    Component.onDestruction: {
        console.info("DefaultTableView.qml Component.onDestruction!");

        // 取消子页面服务事件绑定
        ChildViewServiceId.childViewSimpleResponseEvent.disconnect(onChildViewSimpleResponseEvent);
        ChildViewServiceId.childViewResponseEvent.disconnect(onChildViewResponseEvent);



    }

    //
    // onViewInit : 页面初始化
    //
    function onViewInit() {
        console.log("DefaultTableView.qml onViewInit");

        startupTimerId.start();

    }

    //
    // onStartupEvent : 启动事件
    //
    function onStartupEvent() {
        console.log("DefaultTabView.qml onStartupEvent");

        // 初始化导航页面
        let navigateOwnerObj = {};
        navigateOwnerObj["name"] = "navigatePage";
        navigateOwnerObj["title"] = "导航主页";
        let navigateOwenrStr = ViewEvent.getViewOwnerStr(navigateOwnerObj);
        let ret = ChildViewServiceId.addView(navigateOwnerObj["title"], navigateOwenrStr);

        console.info("DefaultTabView.qml onStartupEvent addView status:" + ret + ", ownerStr:" + navigateOwenrStr);
    }

    //
    // onChildViewSimpleResponseEvent : 子页面简单事件
    // @type: 事件类型
    // @status: 处理结果状态值，0代表成功，其它代表失败
    // @msg: 事件处理结果对应消息
    // @owner: 用户请求自定义参数
    //
    function onChildViewSimpleResponseEvent(type, status, msg, owner) {
        let paramsObj = {};
        paramsObj["type"] = type;
        paramsObj["status"] = status;
        paramsObj["msg"] = msg;
        paramsObj["owner"] = owner;
        console.log("DefaultTabView.qml onChildViewSimpleResponseEvent params: " + JSON.stringify(paramsObj));

    }

    //
    // onChildViewResponseEvent : 子页面事件
    //
    function onChildViewResponseEvent(type, status, obj, owner) {
        // {"type":5001,"status":0,"obj":{"code":200,"data":{"viewId":"12756","viewTitle":"导航主页"},"msg":"成功"}}
        let paramsObj = {};
        paramsObj["type"] = type;
        paramsObj["status"] = status;
        paramsObj["obj"] = obj;
        paramsObj["owner"] = owner;
        console.log("DefaultTabView.qml onChildViewResponseEvent params: " + JSON.stringify(paramsObj));

        //CommonEvent.childViewResponseEventHandler(type, status, obj, owner, tabViewId);
        if (type === CommonEvent.getMessageTypeValue("CHILD_VIEW_MESSAGE_ADD_VIEW_REQUEST", -1)) {
            // 添加子页面
            onAddViewHandler(status, obj, owner);
        }

    }

    //
    // onAddViewHandler : 添加页面处理器
    //
    function onAddViewHandler(status, obj, owner) {
        let paramsObj = {};
        paramsObj["status"] = status;
        paramsObj["obj"] = obj;
        paramsObj["owner"] = owner;
        console.log("DefaultTabView.qml onAddViewHandler params: " + JSON.stringify(paramsObj));

        if (status !== 0) {
            // 失败
        }
        else {
            let code = obj["code"];
            if (code === 200) {
                let dataObj = obj["data"];
                let viewId = dataObj["viewId"];
                let viewTitle = dataObj["viewTitle"];
                onAddNewViewUI(viewId, viewTitle, owner);
            }
        }

    }

    //
    // onAddNewViewUI : 增加新的视图界面
    //
    function onAddNewViewUI(viewId, viewTitle, owner, viewBackgroudColor = null) {
        let tabPageUrl = "qrc:/views/default/tabpages/DefaultTabPage.qml";

        var params = {};
        if (viewBackgroudColor !== null) {
            params["backgroudColor"] = viewBackgroudColor;
        }
        else {
             params["backgroudColor"] = "#BDBDBD";
        }
        let ret = tabViewId.addNewTabPage(viewId, viewTitle, tabPageUrl, params);
        console.log("DefaultTableView.qml onAddNewViewUI status:" + ret);

    }


}
