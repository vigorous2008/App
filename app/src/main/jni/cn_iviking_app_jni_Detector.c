//
// Created by wangzhongqiang on 2017/10/17.
//
#include <jni.h>
#include<android/log.h>
#include "cn_iviking_app_jni_Detector.h"
#include "extmessage.h"
#include "extmessage_emxAPI.h"
#include "extmessage_initialize.h"
#include "math.h"
#include <string.h>
#define LOG " WaterMark Detector"// 这个是自定义的LOG的标识  
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG,__VA_ARGS__) // 定义LOGD类型  
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG,__VA_ARGS__) // 定义LOGI类型  
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,LOG,__VA_ARGS__) // 定义LOGW类型  
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG,__VA_ARGS__) // 定义LOGE类型  
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,LOG,__VA_ARGS__) // 定义LOGF类型  

#define SIZE 160 //SIZE x SIZE , default: 160 x 160
#define N 4096

static emxArray_real_T *argInit_Unboundedx1_real_T(unsigned char * buf,int size)
{
    emxArray_real_T *result;
    //static int iv0[1] = { size };

    int idx0;

    /* Set the size of the array.
    Change this size to the value that the application requires. */
    result = emxCreateND_real_T(1, &size);

    /* Loop over the array to initialize each element. */
    for (idx0 = 0; idx0 < result->size[0U]; idx0++) {
        /* Set the value of the array element.
        Change this value to the value that the application requires. */
        result->data[idx0] = 0.0;
    }
    for (int i = 0; i < size/2; i++)
    {
        unsigned char bl = buf[2 * i];
        unsigned char bh = buf[2 * i + 1];
        short s= (short)((bh&0x00FF)<<8|bl&0x00FF);
        result->data[i] = round((double)s*10000/32768)/10000;
    }

    return result;
}
JNIEXPORT jstring JNICALL Java_cn_iviking_app_jni_Detector_getString
        (JNIEnv *env, jobject obj){
    return (*env)->NewStringUTF(env,"IVIKING 水印测试");
}

JNIEXPORT jbyteArray JNICALL Java_cn_iviking_app_jni_Detector_getSymbol
        (JNIEnv *env, jobject obj, jbyteArray arr, jlong args1, jlong args2, jstring args3, jstring args4){
   // LOGD("btn_fftw_init()");
    LOGI( "revcieve: %d ",args2);

    extmessage_initialize();
    emxArray_char_T* msg;
    emxInitArray_char_T(&msg, 2);
    jbyte *bytes = (*env)->GetByteArrayElements(env,arr,0);

    //     emxArray_real_T *data =  argInit_Unboundedx1_real_T((unsigned char*)bytes,args2-44);//音频文件数据，需要减去wav头
    emxArray_real_T *data =  argInit_Unboundedx1_real_T((unsigned char*)bytes,args2);//音频流数据

    //emxCreateWrapper_real_T((double*)buf, a / (sizeof(double) / sizeof(char)), 1);
    extmessage(data, 44100, 1, msg);


    jbyteArray array = (*env)->NewByteArray(env,msg->size[1]);

    for (int i =0;i<msg->size[1];i++){
        LOGI( "liuboxtest  returned: %c ",msg->data[i]);
        //  return (*env)->NewStringUTF(env, msg);
        //LOGI( "String returned: %s ",ret[i]);
       // strcat(mark,(char)ret[i]);

    }
    //jstring deviceNum = env->NewStringUTF((const char*)devicenumber);

    (*env)->SetByteArrayRegion(env,array,0,msg->size[1],msg->data);

    return array;
}




