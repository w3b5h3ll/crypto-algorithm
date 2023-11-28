function arr2string(arr) {
    var str = "";
    for (let index = 0; index < arr.length; index++) {
        var c = String.fromCharCode(arr[index]);
        str += c;
    }
    return str;
}

function main() {
    Java.perform(function () {
        var base64Class = Java.use("android.util.Base64");

        // encode
        // String encodeString = Base64.encodeToString(data.getBytes(), Base64.DEFAULT);
        // Error: encodeToString(): has more than one overload, use .overload(<signature>) to choose from:
        // .overload('[B', 'int')
        // .overload('[B', 'int', 'int', 'int')

        base64Class.encodeToString.overload("[B", "int").implementation =
            function (arg0, arg1) {
                // console.log("data >> " + arg0);
                // 字符串化
                // console.log("data >> ", JSON.stringify(arg0));
                console.log("data >> ", arr2string(arg0));
                // 调用堆栈打印
                console.log(
                    Java.use("android.util.Log").getStackTraceString(
                        Java.use("java.lang.Throwable").$new()
                    )
                );
                return this.encodeToString(arg0, arg1);
            };

        // byte[] decodeByte = Base64.decode(encodeString, Base64.DEFAULT);
        base64Class.decode.overload("java.lang.String", "int").implementation =
            function (arg0, arg1) {
                console.log("encodeString >> " + arg0);
                console.log(
                    Java.use("android.util.Log").getStackTraceString(
                        Java.use("java.lang.Throwable").$new()
                    )
                );
                return this.decode(arg0, arg1);
            };
    });
}

setImmediate(main);
// spawn模式启动
// frida -U -f com.example.base64democpp -l ./hook_java.js
