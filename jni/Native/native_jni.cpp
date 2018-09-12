//
// Created by shmdu on 2018/1/29.
//
#include <jni.h>
#include <string>
#include "SoftwareProbeFilter.h"
#include "needleimpl.h"
#include "reportcenter.h"
#include "needlecommon.h"
#include "common.h"

#include "pcre.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

NetPackage *np = NULL;
IDataProvider *dp = NULL;
bool gInit = false;

extern "C"
JNIEXPORT jstring JNICALL
Java_com_starcor_data_needle_crawler_crawl_NeedleJNI_getSysInfo(JNIEnv *env,  jobject instance,  jstring cmd)
{
      LOGD("[%s][%d]! getSysInfo start\n", __func__, __LINE__);
      const char *cmd_tmp = env->GetStringUTFChars(cmd, 0);
      char* buff = dp->getSysInfo(cmd_tmp);
      jstring result = env->NewStringUTF(buff);
      env->ReleaseStringUTFChars(cmd, cmd_tmp);
      return result;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_starcor_data_needle_crawler_crawl_NeedleJNI_start(JNIEnv *env, jobject instance) {
    LOGD("[%s][%d]! jni start\n", __func__, __LINE__);
    np->start();
    int result = np->startCaptrue();
    return result;
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_starcor_data_needle_crawler_crawl_NeedleJNI_stop(JNIEnv *env, jobject instance) {
    int result = np->stopCaptrue();
    np->reset();
    rp->stop();
    return result;
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_starcor_data_needle_crawler_crawl_NeedleJNI_setFlowCache(JNIEnv *env, jobject instance, jint pkt) {
    int result = np->setFlowCache(pkt);
    return result;
}
extern "C"
JNIEXPORT jlong JNICALL
Java_com_starcor_data_needle_crawler_crawl_NeedleJNI_createFilter(JNIEnv *env, jobject instance, jstring id_) {
    LOGD("[%s][%d]! jni createFilter\n", __func__, __LINE__);
    const char *id = env->GetStringUTFChars(id_, 0);
    SoftwareProbeFilter *filter = np->createFilter(id);
    env->ReleaseStringUTFChars(id_, id);
    return reinterpret_cast<jlong> (filter);
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_starcor_data_needle_crawler_crawl_NeedleJNI_setBPFFilter(JNIEnv *env, jobject instance, jstring filter_) {
    LOGD("[%s][%d]! jni setBPFFilter\n", __func__, __LINE__);
    const char *filter = env->GetStringUTFChars(filter_, 0);
    np->setBPFFilter((char *) filter);
    env->ReleaseStringUTFChars(filter_, filter);
    return 0;
}
extern "C"
JNIEXPORT void JNICALL
Java_com_starcor_data_needle_crawler_crawl_NeedleJNI_setIp(JNIEnv *env, jobject instance
    , jlong obj , jobjectArray ips, jboolean exclude) {
    SoftwareProbeFilter *filter = reinterpret_cast<SoftwareProbeFilter *> (obj);
    jsize size = env->GetArrayLength(ips);
    for (int i = 0; i < size; ++i) {
        jstring str = (jstring) env->GetObjectArrayElement(ips, i);
        const char *ip = env->GetStringUTFChars(str, 0);
        filter->addIp(inet_addr(ip), exclude);
        DEBUG_TRACK;
        env->ReleaseStringUTFChars(str, ip);
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_com_starcor_data_needle_crawler_crawl_NeedleJNI_setIpMask(JNIEnv *env, jobject instance
    , jlong obj , jstring ipBegin_, jstring ipEnd_, jboolean exclude) {

    const char *ipBegin = env->GetStringUTFChars(ipBegin_, 0);
    const char *ipEnd = env->GetStringUTFChars(ipEnd_, 0);

    SoftwareProbeFilter *filter = reinterpret_cast<SoftwareProbeFilter *> (obj);

    filter->addIpMask(inet_addr(ipBegin), inet_addr(ipEnd), exclude);

    env->ReleaseStringUTFChars(ipBegin_, ipBegin);
    env->ReleaseStringUTFChars(ipEnd_, ipEnd);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_starcor_data_needle_crawler_crawl_NeedleJNI_setPort(JNIEnv *env, jobject instance
    , jlong obj, jintArray ports_, jboolean exclude) {
    SoftwareProbeFilter *filter = reinterpret_cast<SoftwareProbeFilter *> (obj);
    jint *ports = env->GetIntArrayElements(ports_, NULL);
    jint size = env->GetArrayLength(ports_);
    for (int i = 0; i < size; ++i) {
        filter->addPort(ports[i], exclude);
    }
    env->ReleaseIntArrayElements(ports_, ports, 0);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_starcor_data_needle_crawler_crawl_NeedleJNI_addRule(JNIEnv *env, jobject instance
    , jlong obj , jstring ruleName_, jstring compare_, jstring value_, jboolean exclude) {

    const char *ruleName = env->GetStringUTFChars(ruleName_, 0);
    const char *compare = env->GetStringUTFChars(compare_, 0);
    const char *value = env->GetStringUTFChars(value_, 0);

    SoftwareProbeFilter *filter = reinterpret_cast<SoftwareProbeFilter *> (obj);
    filter->setRule(ruleName, compare, value, exclude);
    env->ReleaseStringUTFChars(ruleName_, ruleName);
    env->ReleaseStringUTFChars(compare_, compare);
    env->ReleaseStringUTFChars(value_, value);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_starcor_data_needle_crawler_crawl_NeedleJNI_setStatistics(JNIEnv *env, jobject instance, jlong obj, jboolean statistics) {
    SoftwareProbeFilter *filter = reinterpret_cast<SoftwareProbeFilter *> (obj);
    filter->setStatistics(statistics);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_starcor_data_needle_crawler_crawl_NeedleJNI_init(JNIEnv *env, jobject instance) {
    if(gInit) {
        LOGD("[%s][%d]! have been init\n", __func__, __LINE__);
        return;
    }
    int ret = 0;
    ret = sdk_mem_init();
    if(ret == 0)
    {
        LOGD("\n\n\n[%s][%d]! sdk_mem_init error\n\n\n\n", __func__, __LINE__);
    }

    IDataProviderCreateFactory factory;
    np = NetPackage::getInstance();
    dp = factory.createDataProvider(CREATE_JNI_PRODUCT);
    if(dp->RegisterContentCallBack((void *)env, (void *)&instance) != true) {
          return false;
    }
    dp->init();

    gInit = true;
    DEBUG_CHECK_FUNC();
}