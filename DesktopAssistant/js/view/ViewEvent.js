

/*
 * Func: getViewOwnerStr
 * Desc: 获取页面自定义参数字符串
 * Author: zfs
 * Date: 2023-05-29 06:57
 */
function getViewOwnerStr(obj = null) {
    if (obj === null) {
        return "";
    }
    return JSON.stringify(obj);
}
