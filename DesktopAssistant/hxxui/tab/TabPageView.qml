import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

import "./"

Rectangle {
    id: controlId

    property int tabBarHeight: 50
    property int tabBarBtnLeftPadding: 15
    property int tabBarBtnRightPadding: 15

    property var tabBarBackgroudColor: "#FCFCFC"
    property var backgroudColor: "#FFFFFF"

    property int tabButtonWidth: 220
    property int tabButtonHeight: 48
    property int tabButtonSpaceWidth: 5
    property var tabButtonBackgroudColor: "#F9F9F9"
    property var tabButtonTextNormalColor: "#000000"
    property var tabButtonTextHoverColor: "#FF0022"
    property var tabButtonBorderLineWidth: 2
    property var tabButtonBorderLineColor: "#F5F5F5"
    property int tabButtonTextPixelSize: 14

    property bool tabButtonExitEnable: true

    property int currentIndex: -1
    property ListModel modelDatas: ListModel {}

    anchors.fill: parent

    color: backgroudColor

    // TabView
    Column {
        id: tabViewColumnId

        spacing: 0
        width: controlId.width
        height: controlId.height

        // TabBar
        Rectangle {
            id: tabBarWinId

            width: controlId.width
            height: tabBarHeight
            color: tabBarBackgroudColor
            clip: true

            // TabBar容器
            Flickable {
                id: tabBarFlickableId

                width: tabBarWinId.width - 100
                height: tabBarWinId.height
                contentWidth: tabBarButtonRowId.implicitWidth + 120
                contentHeight: tabBarButtonRowId.implicitHeight
                clip: true


                // TabButton
                Row {
                    id: tabBarButtonRowId

                    spacing: tabButtonSpaceWidth
                    width: tabBarFlickableId.width
                    height: tabBarFlickableId.height

                    Rectangle {
                        width: tabBarBtnLeftPadding
                        height: parent.height
                        color: "transparent"
                    }

                    Repeater {
                        model: modelDatas

                        delegate: Rectangle {
                            width: tabButtonWidth
                            height: tabButtonHeight
                            color: tabButtonBackgroudColor
                            border.width: tabButtonBorderLineWidth
                            border.color: tabButtonBorderLineColor


                            // TAB按钮文本
                            Rectangle {
                                anchors {
                                    left: parent.left
                                    leftMargin: 0
                                }

                                width: parent.width - 15
                                height: parent.height
                                color: "transparent"

                                Text {
                                    id: tabBtnTextId

                                    anchors.centerIn: parent
                                    text: title
                                    color: index == controlId.currentIndex ? tabButtonTextHoverColor : tabButtonTextNormalColor
                                    font.pixelSize: tabButtonTextPixelSize
                                    wrapMode: Text.NoWrap
                                    elide: Text.ElideRight
                                    width: tabBtnTextId.implicitWidth > parent.width ? parent.width : tabBtnTextId.implicitWidth
                                }

                                ToolTip {
                                    id: tabBtnTextToolTipId

                                    delay: Qt.styleHints.mousePressAndHoldInterval
                                    text: title
                                    onOpened:{
                                       if (!mouseAreaId.containsMouse) {
                                           close()
                                       }
                                    }
                                }

                                MouseArea {
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    onClicked: {
                                        onTabButtonClick(index);
                                    }

                                    onEntered: {
                                        tabBtnTextToolTipId.visible = true;
                                    }

                                    onExited: {
                                        tabBtnTextToolTipId.visible = false;
                                    }

                                }

                            }

                            // 关闭按钮
                            Image {
                                anchors {
                                    verticalCenter: parent.verticalCenter
                                    right: parent.right
                                    rightMargin: 5
                                }
                                visible: tabButtonExitEnable
                                source: "qrc:/image/default/close_normal.png"
                                width: 10
                                height: 10

                                MouseArea {
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    cursorShape: Qt.PointingHandCursor
                                    onClicked: {
                                        onRemoveTabPage(index);
                                    }
                                }
                            }


                        } // end Rectangle

                    } // end Repeater

                } // end Row


            } // tabBarFlickableId Flickable

            // 右侧箭头
            Rectangle {
                anchors {
                    left: tabBarFlickableId.right
                    leftMargin: 10
                }
                visible: (tabBarButtonRowId.implicitWidth > tabBarFlickableId.width ? true : false)
                width: 20
                height: tabBarHeight
                color: "transparent"
                border.color: "#CCCCCC"
                border.width: 1
                radius: 4

                Image {
                    anchors.centerIn: parent
                    source: "qrc:/image/default/rightPageArrow.png"
                    width: 12
                    height: 12
                }

            }


        } // end tabBarWinId Rectangle

        // tab页面
        Rectangle {
            id: tabPageWinId

            width: controlId.width
            height: controlId.height - tabBarHeight
            color: "transparent"

            // tab页面加载器
            Loader {
                id: tabPageLoaderId

                anchors.fill: parent

            } // end tabPageLoaderId Loader

        } // end tabPageWinId Rectangle

    } // end tabViewColumnId Column


    //
    // addNewTabPage : 添加新的tab页面，成功返回序号，失败返回-1
    // @tabId: TAB页ID，最好唯一
    // @tabTitle: TAB页标题
    // @tabPageUrl: TAB页地址
    // @param: TAB页初始属性参数，可以为空
    //
    function addNewTabPage(tabName, tabTitle, tabPageUrl, param = {}) {
        if (tabPageUrl !== "") {
            console.log("TabPageView.qml addNewTabPage pageUrl:" + tabPageUrl);

            var itemTabPage = {};
            itemTabPage["title"] = tabTitle;
            itemTabPage["path"] = tabPageUrl;
            itemTabPage["active"] = true;
            itemTabPage["vid"] = tabName;
            itemTabPage["param"] = param;

            modelDatas.append(itemTabPage);

            // 激活
            onTabButtonClick(modelDatas.count - 1);

            return controlId.currentIndex;
        }
        else {
            console.info("TabPageView.qml addNewTabPage fail, pageUrl:" + tabPageUrl);
            return -1;
        }
    }

    //
    // onRemoveTabPage : 移除TAB页
    //
    function onRemoveTabPage(index) {
        if (index < 0 || index >= modelDatas.count) {
            return false;
        }

        let oldSelectIndex = controlId.currentIndex;
        // 删除列表
        modelDatas.remove(index);
        controlId.currentIndex = controlId.currentIndex - 1;

        // 修正当前选中项
        let isPageChanged = false;
        if (modelDatas.count > 0) {
            if (controlId.currentIndex >= modelDatas.count) {
                controlId.currentIndex = 0;
                isPageChanged = true;
            }
        }
        else {
            controlId.currentIndex = -1;
            isPageChanged = true;
        }

        // 重新加载页面
        if (oldSelectIndex === index || isPageChanged) {
            // 重置页面
            tabPageLoaderId.source = "";
            tabPageLoaderId.sourceComponent = undefined;

            // 重新加载页面
            onLoadTabPage(controlId.currentIndex);
        }

    }

    //
    // onTabButtonClick : TabView按钮事件
    //
    function onTabButtonClick(index) {
        // 修改当前选中序号
        controlId.currentIndex = index;

        // 加载新页面
        onLoadTabPage(index);
    }

    //
    // onLoadTabPage : 加载Tab页面
    //
    function onLoadTabPage(index) {
        if (index < 0 || index >= modelDatas.count) {
            return false;
        }

        let itemObj = modelDatas.get(index);
        if (!itemObj["path"]) {
            return false;
        }

        //tabPageLoaderId.source = itemObj["path"];
        tabPageLoaderId.setSource(Qt.resolvedUrl(itemObj["path"]), itemObj["param"]);
        return true;
    }

} // end TabPageView

