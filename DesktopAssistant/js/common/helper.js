
/*
 * Func: parseJsonStr
 * Desc: 解析JSON字符串
 * Author: zfs
 * Date: 2023-05-29 06:53
 */
function parseJsonStr(str) {
    if (str === "") {
        return null;
    }
    var obj = null;
    try {
        obj = JSON.parse(str);
    }
    catch(e) {
        console.info("parseJsonStr exception, error:" + JSON.stringify(e) + ", str:" + str);
        obj = null;
    }
    return obj;
}

