/*
 * this file is android/tvos jni interface
 */

#include <jni.h>

#include "UtilsCommon.h"
#include "DataProvider.h"
#include "DataProviderFactory.h"

#define CLASSNAME ""

typedef struct JNI_ENV_s {
      JNIEnv * mEnv;
      JavaVM * mJvm;
      jclass * mObj;
}JNV_ENV_t;

static JNV_ENV_t gJniEnv;

typedef struct {
    const char* name;
    const char* signature;
    void*       fnPtr;
} JNINativeMethod;

static JNINativeMethod gNativeMethod[] = {
      {""},
      {},
};

static jint JNI_RegisterNatives(JNIEnv * jniEnv) {
      jnienv->RegisterNatives()
}

jint JNI_OnLoad(JavaVM* vm, void* reserved) {

      gJniEnv.mJvm = vm;
      if((gJniEnv.mJvm)->GetEnv((void **)&gJniEnv.mEnv, JNI_VERSION_1_6) != JNI_OK) {
            LOGE("get jni env failed\n");
            return JNI_ERR;
      }

      if(JNI_RegisterNatives(gJniEnv.mEnv) != JNI_OK) {
            return JNI_ERR;
      }



      return JNI_OK;
}