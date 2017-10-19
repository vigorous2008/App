//
// Created by wangzhongqiang on 2017/10/17.
//
#include <jni.h>

#include "cn_iviking_app_jni_JNIUtils.h"


#define SIZE 160 //SIZE x SIZE , default: 160 x 160
#define N 4096

JNIEXPORT jstring JNICALL Java_cn_iviking_app_jni_JNIUtils_getString
        (JNIEnv *env, jobject obj){
    return (*env)->NewStringUTF(env,"iviking jni test--ok");
}

JNIEXPORT jstring JNICALL Java_cn_iviking_app_jni_JNIUtils_getSymbol
        (JNIEnv *env, jobject obj, jbyteArray arr, jstring args1, jstring args2, jstring args3, jstring args4){
   // LOGD("btn_fftw_init()");

    return (*env)->NewStringUTF(env, "btn_fftw_init");
   // return (*env)->NewStringUTF(env,"I'm a String");
}

