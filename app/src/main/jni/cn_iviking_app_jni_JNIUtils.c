//
// Created by wangzhongqiang on 2017/10/17.
//
#include <jni.h>
#include<android/log.h>
#include "cn_iviking_app_jni_JNIUtils.h"
#include "extmessage.h"
#include "extmessage_emxAPI.h"
#include "extmessage_initialize.h"

#define LOG "liubox-jni"// 这个是自定义的LOG的标识  
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG,__VA_ARGS__) // 定义LOGD类型  
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG,__VA_ARGS__) // 定义LOGI类型  
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,LOG,__VA_ARGS__) // 定义LOGW类型  
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG,__VA_ARGS__) // 定义LOGE类型  
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,LOG,__VA_ARGS__) // 定义LOGF类型  

#define SIZE 160 //SIZE x SIZE , default: 160 x 160
#define N 4096

JNIEXPORT jstring JNICALL Java_cn_iviking_app_jni_JNIUtils_getString
        (JNIEnv *env, jobject obj){
    return (*env)->NewStringUTF(env,"iviking jni test--ok");
}

JNIEXPORT jstring JNICALL Java_cn_iviking_app_jni_JNIUtils_getSymbol
        (JNIEnv *env, jobject obj, jbyteArray arr, jstring args1, jlong args2, jstring args3, jstring args4){
   // LOGD("btn_fftw_init()");

    extmessage_initialize();
    emxArray_real_T* msg = emxCreate_real_T(600,1);
    jbyte *bytes = (*env)->GetByteArrayElements(env,arr,0);
    emxArray_real_T *data = emxCreateWrapper_real_T((double*)bytes, args2/8/ (sizeof(double) / sizeof(char)), 1);
    LOGI( "liuboxtest %d ",args2);
    extmessage(data, 44100, 1, msg);
    LOGI( "liuboxtest[ %s] returned ",msg);
  //  return (*env)->NewStringUTF(env, msg);
   return (*env)->NewStringUTF(env,"I'm a String");
}

