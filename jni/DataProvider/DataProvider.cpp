#include <jni.h>
#include <unistd.h>

#include "DataProvider.h"
#include "UtilsCommon.h"

#define DEF_METH "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;[BLjava/lang/String;[BLjava/lang/String;I)V"

using namespace std;

static jbyteArray char2Byte(JNIEnv* env, const char* src, int len=-1) {
    if(!env && !src) {
        return NULL;
    }
	if (len < 0) {
		len = strlen(src);
	}

    if(src[0] == 0 || len == 0) {
        return NULL;
    }

    jbyteArray bytes = env->NewByteArray(len);
    if (bytes != NULL) {
        env->SetByteArrayRegion(bytes, 0, len, (jbyte *)src);
    }
    return bytes;
}

static jstring char2Jsting(JNIEnv* env, const char* src) {
    if(!env && !src) {
        return NULL;
    }
    int len = strlen(src);
    if(src[0] == 0 || len == 0) {
        return NULL;
    }

    return env->NewStringUTF(src);
}

static jstring char2Jsting(JNIEnv* env, const flow_key &flow_key) {
	if (!env) {
		return NULL;
	}
	char temp[48];
	snprintf(temp, sizeof(temp), "%X:%X-%X:%X", flow_key.addr1, flow_key.port1, flow_key.addr2, flow_key.port2);
	return env->NewStringUTF(temp);
}

static jstring char2Jsting(JNIEnv* env, time_t t) {
	if (!env) {
		return NULL;
	}
	char temp[16];
	snprintf(temp, sizeof(temp), "%lu", t);
	return env->NewStringUTF(temp);
}


#define JSON_STAT_BASE_PROP "{\"start_time\": %d,\"pkt_count\": %d,\"last_pkt_time\": %d,\"last_stat_time\": %d,\"byte_count\": %d,\"byte_count5m\": %d,\"unorder\": [%d, %d],\"retrans\": [%d, %d]}"

static jstring char2Jsting(JNIEnv* env, const flow_stat *fs, int num) {
	if (!env) {
		return NULL;
	}
	char temp[32 * 1024];
	int wPos = 0;
	temp[wPos] = '[';
	++wPos;
	for (int i = 0; i < num; i++) {
		auto &s = fs[i];
		int len = snprintf(temp + wPos,
			sizeof(temp) - wPos,
			JSON_STAT_BASE_PROP,
			s.start_time,
			s.pkt_count,
			s.last_pkt_time,
			s.last_stat_time,
			s.byte_count,
			s.byte_count5m,
			s.unorder[0],
			s.unorder[1],
			s.retrans[0],
			s.retrans[1]);
		wPos += len;
		if (i < num - 1) {
			temp[wPos] = ',';
			++wPos;
		}
	}
	temp[wPos] = ']';
	++wPos;
	temp[wPos] = 0;
	return env->NewStringUTF(temp);
}


void * DataProviderAndroid::dataReport2APP_TaskProc(void * param) {
      jclass eventClass;
      jmethodID event_cb;
      needle_package_data_s * MsgData = NULL;
      DataProviderAndroid * pThis = (DataProviderAndroid *) param;
      jbyteArray requst = NULL, response = NULL;
      jstring filterid = NULL, requsthead = NULL, responsehead = NULL, statistics = NULL, flowkey = NULL, flowtime = NULL;

      if(pThis->mReportMsgQue == NULL || pThis->mJNIEnv.mJvm == NULL) {
            return NULL;
      }

      if(pThis->mJNIEnv.mJvm->GetEnv((void **)&(pThis->mJNIEnv.mEnv), JNI_VERSION_1_6) != JNI_OK) {

            LOGD("[%s][%d]! get JNIENV failed\n", __func__, __LINE__);
            return NULL;
      }

      if(pThis->mJNIEnv.mJvm->AttachCurrentThread(&(pThis->mJNIEnv.mEnv), NULL) != JNI_OK) {
            LOGD("[%s][%d]! AttachCurrentThread failed\n", __func__, __LINE__);
            return NULL;
      }

      eventClass = pThis->mJNIEnv.mEnv->GetObjectClass(pThis->mJNIEnv.mObj);
      if(eventClass == NULL) {
            LOGD("[%s][%d]! GetObjectClass failed\n", __func__, __LINE__);
            return NULL;
      }

      event_cb = pThis->mJNIEnv.mEnv->GetMethodID(eventClass, "reportHttpPackageData", DEF_METH);
      if(!event_cb) {
        LOGD("event_cb is null, continue\n");
        return NULL;
      }

      while(pThis->stopTask == false)
      {
            MsgData = ((CommonMsg<needle_package_data_t> *)pThis->mReportMsgQue)->receiveCommonMessageMsg();
            if(!MsgData)
            {
                  usleep(100000);
                  LOGE("MSG is NULL, continue\n");
                  continue;
            }

            clock_t  start_time = clock();
            requst = char2Byte(pThis->mJNIEnv.mEnv, (const char*)MsgData->requestPkg.data(), MsgData->requestPkg.dataSize());
            response = char2Byte(pThis->mJNIEnv.mEnv, (const char*)MsgData->responsePkg.data(), MsgData->responsePkg.dataSize());
            flowkey = char2Jsting(pThis->mJNIEnv.mEnv, MsgData->flowKey);
            filterid = char2Jsting(pThis->mJNIEnv.mEnv, MsgData->filterid);
            requsthead = char2Jsting(pThis->mJNIEnv.mEnv, MsgData->requestHead);
            responsehead = char2Jsting(pThis->mJNIEnv.mEnv, MsgData->responseHead);
            flowtime = char2Jsting(pThis->mJNIEnv.mEnv, MsgData->flowtime);
            if (MsgData->flowStatWPos > 0)
            {
            	statistics = char2Jsting(pThis->mJNIEnv.mEnv, MsgData->flowStat, MsgData->flowStatWPos);
            }
            else
            {
            	statistics = NULL;
            }

            pThis->mJNIEnv.mEnv->CallVoidMethod(pThis->mJNIEnv.mObj, \
            event_cb, \
            flowkey, \
            flowtime, \
            filterid, \
            requsthead, \
            requst, \
            responsehead, \
            response, \
            statistics, \
            MsgData->State);

            pThis->mJNIEnv.mEnv->DeleteLocalRef(requst);
            pThis->mJNIEnv.mEnv->DeleteLocalRef(response);
            pThis->mJNIEnv.mEnv->DeleteLocalRef(filterid);
            pThis->mJNIEnv.mEnv->DeleteLocalRef(requsthead);
            pThis->mJNIEnv.mEnv->DeleteLocalRef(responsehead);
            pThis->mJNIEnv.mEnv->DeleteLocalRef(flowkey);
            pThis->mJNIEnv.mEnv->DeleteLocalRef(statistics);
            pThis->mJNIEnv.mEnv->DeleteLocalRef(flowtime);
            filterid = NULL;
            requsthead = NULL;
            responsehead = NULL;
            statistics = NULL;
            flowkey = NULL;
            flowtime = NULL;
            requst = NULL;
            response = NULL;
      }

      return NULL;
}

DataProviderAndroid::DataProviderAndroid() {

}

DataProviderAndroid::~DataProviderAndroid() {

}

void DataProviderAndroid::deinit(void) {
      this->stopTask = true;

      pthread_join(this->mtid, NULL);
}

bool DataProviderAndroid::init(void) {
      if(isInit) {
            return false;
      }

      this->stopTask = false;
      mSYSINFO = new SysInfoDataColloct();
      mReportMsgQue = (void *)(new CommonMsg<needle_package_data_t>(MSGQUE_DATA_MAX));

      CommonMsgManager::getInstance()->addCommonMsgHandle(MSG_QUE_REPORT, mReportMsgQue);

      if(pthread_create(&mtid, NULL, &dataReport2APP_TaskProc, (void *)this) != 0) {
            CommonMsgManager::getInstance()->delCommonMsgHandle(MSG_QUE_REPORT);
            return false;
      }

      isInit = true;

      return true;
}

bool DataProviderAndroid::RegisterContentCallBack(void *param, void * registerCb) {
      if(((JNIEnv *)param)->GetJavaVM(&(mJNIEnv.mJvm)) != JNI_OK) {
            return false;
      }
      mJNIEnv.mObj = *((jobject *)registerCb);

      return true;
}

char * DataProviderAndroid::getSysInfo(const char * cmd) {

      return mSYSINFO->getSysInfoColloctData(cmd);
}

int main(int argc, char const *argv[])
{
      /* code */
      return 0;
}

