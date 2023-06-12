/*
 * 定义类型常量
 */
var MESSAGE_TYPE_LIST = {
    PUBLIC_MESSAGE_START_TYPE: 1,
    PUBLIC_MESSAGE_END_TYPE: 5000,
    CHILD_VIEW_MESSAGE_START_TYPE: 5000,
    CHILD_VIEW_MESSAGE_END_TYPE: 10000,
    USER_MESSAGE_START_TYPE: 5000,
    PUBLIC_MESSAGE_WELCOME_REQUEST: 1,
    PUBLIC_MESSAGE_WELCOME_RESPONSE: 2,
    PUBLIC_MESSAGE_NODE_REQUEST: 3,
    PUBLIC_MESSAGE_NODE_RESPONSE: 4,
    CHILD_VIEW_MESSAGE_ADD_VIEW_REQUEST: 5001,
    CHILD_VIEW_MESSAGE_ADD_VIEW_RESPONSE: 5002
};

/*
 * Func: getMessageTypeValue
 * Desc: 根据消息类型名，获取对应的消息类型值
 * Author: zfs
 * Date: 2023-06-03 07:32
 */
function getMessageTypeValue(typeName, defValue = -1) {
    if (typeName !== "" && MESSAGE_TYPE_LIST.hasOwnProperty(typeName)) {
        return MESSAGE_TYPE_LIST[typeName];
    }
    return defValue;
}

/*
 * Func: parseResponseEvent
 * Desc: 解析应答事件
 * Author: zfs
 * Date: 2023-06-03 07:11
 */
function parseResponseEvent(code, resultStr) {
    let obj = {};

    if (code !== 0 || resultStr === "") {
        obj["code"] = -1;
        obj["msg"] = "失败";
    }
    else {
        try {
            let resultObj = JSON.parse(resultStr);
            if (resultObj.hasOwnProperty("code")) {
                obj["code"] = resultObj["code"];
            }
            if (resultObj.hasOwnProperty("type")) {
                obj["type"] = resultObj["type"];
            }
            if (resultObj.hasOwnProperty("data")) {
                obj["data"] = resultObj["data"];
            }
        }
        catch(err) {
            console.info("解析应答数据异常, 错误信息:" + JSON.stringify(err) + ", 异常字符串:" + resultStr);
            obj["code"] = -2;
            obj["msg"] = "异常失败";
        }
    }
    return obj;
}



