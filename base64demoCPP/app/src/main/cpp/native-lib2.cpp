//
// Created by 尘埃落定 on 2023/11/22.
// 参考：https://opensource.apple.com/source/QuickTimeStreamingServer/QuickTimeStreamingServer-452/CommonUtilitiesLib/base64.c
//
#include <jni.h>
#include <string>
#include <android/log.h>

#define TAG "w3b5h3ll"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)

static const char basis_64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static const char basis_pad = '=';
// 解码表
// 65 >> 0 66 >> 1 ... 48 >> 52
static char *decoding_table = NULL;

void base64Encode(char *data, char *out);

void base64Decode(char *data, char *out);


void build_decoding_table() {
    decoding_table = static_cast<char *>(malloc(256));
    for (int i = 0; i < 64; i++)
        decoding_table[(unsigned char) basis_64[i]] = i;


}


void base64Encode(char *data, char *out) {
    int len = strlen(data);
    char *p;
    p = out;
    int i = 0;
    char c;
    char last_c;
    for (i = 0; i < len; i++) {
        c = data[i];
        switch (i % 3) {
            case 0:
                *p++ = basis_64[(c >> 2) & 0x3f];
                break;
            case 1:
                *p++ = basis_64[((last_c & 0x3) << 4) | ((c >> 4) & 0xf)];
                break;
            case 2:
                *p++ = basis_64[((last_c & 0xf) << 2) | ((c >> 6) & 0x3)];
                *p++ = basis_64[c & 0x3f];
                break;


        }
        last_c = c;


    }
    if (len % 3 == 1) {
//        剩余2字符填充
        *p++ = basis_64[(c & 0x3) << 4];
        *p++ = basis_pad;
        *p++ = basis_pad;

    }
    if (len % 3 == 2) {
//        剩余1字符填充
        *p++ = basis_64[(c & 0xf) << 2];
        *p++ = basis_pad;

    }


}

void base64Decode(char *data, char *out) {
    build_decoding_table();
    int len = strlen(data);
    LOGI("input length: %d", len);
//    输入长度应为4的倍数
    if (len % 4 != 0) {
        LOGI("input error!");
        return;
    }
    int output_len = (len / 4) * 3;
    LOGI("output length: %d", output_len);
    if (data[len - 1] == '=') output_len--;
    if (data[len - 2] == '=') output_len--;

//    4个一组进行处理
    for (int i = 0, j = 0; i < len;) {
//        32位无符号整数
        uint32_t a = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        uint32_t b = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        uint32_t c = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        uint32_t d = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];

//        4 >> 3
        uint32_t triple = (a << 18) + (b << 12) + (c << 6) + d;
        if (j < output_len) {
            out[j++] = (triple >> 16) & 0xFF;
        }
        if (j < output_len) {
            out[j++] = (triple >> 8) & 0xFF;
        }
        if (j < output_len) {
            out[j++] = triple & 0xFF;
        }


    }


}


extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_base64democpp_MainActivity_stringFromBase64(JNIEnv *env, jobject thiz) {
    // TODO: implement stringFromBase64()
    char *data = "w3b5h3ll";
    char out[0x100] = {0};
    char decode_out[0x100] = {0};

    base64Encode(data, out);
    LOGI("base64Encode: w3b5h3ll >> %s", out);
    base64Decode(out, decode_out);
    LOGI("base64Decode: %s >> %s", out, decode_out);
    return env->NewStringUTF(out);

}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_base64democpp_MainActivity_stringFromJNIAdd(JNIEnv *env, jobject thiz,
                                                             jstring str1, jstring str2) {
    // TODO: implement stringFromJNIAdd()
}