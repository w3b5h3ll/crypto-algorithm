#include <jni.h>
#include <string>
#include <android/log.h>

#define TAG "nativeBase64"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)

// 编码表
const char base64en[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
                         'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',
                         'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
                         't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7',
                         '8', '9', '+', '/'};

void base64_encode(const char *data, char out[256]);

const char base64pad = '=';

extern "C" JNIEXPORT jstring

JNICALL
Java_com_example_base64democpp_MainActivity_stringFromJNI(JNIEnv *env, jobject /* this */) {

//    初始化
    const char *data = "w3b5h3ll";
    char out[0x100] = {0};

    base64_encode(data, out);
    LOGI("output >> %s", out);

    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}


void base64_encode(const char *data, char out[256]) {
    int len_data = strlen(data);
    LOGI("len_data >> %d", len_data);
    if (len_data == 0) {
        out[0] = '\0';
        return;
    }
    char c;
    char last_c;
    int index = 0;
    int temp_index;
    for (int i = 0; i < len_data; i++) {
        c = data[i];
        switch (i % 3) {
            case 0:
//                右移动2位 01010101 & 111111
                temp_index = (c >> 2) & 0x3f;
                out[index++] = base64en[temp_index];
                break;
            case 1:
//                右移动4位
                temp_index = ((last_c & 0x3) << 4) | ((c >> 4) & 0xf);
                out[index++] = base64en[temp_index];
                break;
            case 2:
                temp_index = ((last_c & 0xf) << 2) | ((c >> 6) & 0x3);
                out[index++] = base64en[temp_index];
                out[index++] = base64en[c & 0x3f];
                break;
        }
        last_c = c;


    }
    int str_left = len_data % 3;
    if (str_left == 1) {
//            剩余2位填充
        out[index++] = base64en[(c & 0x3) << 4];
        out[index++] = base64pad;
        out[index++] = base64pad;
    }

    if (str_left == 2) {
//            剩余1位填充
        out[index++] = base64en[(c & 0xf) << 2];
        out[index++] = base64pad;
    }


}