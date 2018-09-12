#ifndef __DATA_PROVIDER_H__
#define __DATA_PROVIDER_H__

/*
 *by zheng.yi
 */

#include <pthread.h>

#include "UtilsDataMsgQue.h"
#include "DataSysInfoColloct.h"

using namespace std;

class IDataProvider {
      protected:
            pthread_t mtid;

            bool isInit;
            bool stopTask;

            void * mReportMsgQue;

            ISysInfoDataColloct * mSYSINFO;

      public:
            virtual bool init(void) = 0;
            virtual void deinit(void) = 0;

            virtual bool RegisterContentCallBack(void *param, void * registerCb) = 0; //注册回调函数相关参数
            virtual char * getSysInfo(const char * cmd) = 0;
};

typedef struct JNI_ENV_s {
      JNIEnv * mEnv;
      JavaVM * mJvm;
      jobject mObj;
}JNV_ENV_t;

class DataProviderAndroid : public IDataProvider {

      private:
            DataProviderAndroid();
            ~DataProviderAndroid();

            static DataProviderAndroid instance;

            JNV_ENV_t mJNIEnv;

            static void * dataReport2APP_TaskProc(void * param);

      public:
            DataProviderAndroid * getInstance(void) {
                  return &instance;
            };//采用饿汉模式,避免多线程不安全

            bool init(void);
            void deinit(void);

            bool RegisterContentCallBack(void *param, void * registerCb);
            char * getSysInfo(const char * cmd);
};

class DataProviderNative : public IDataProvider {

      private:
            DataProviderNative();
            ~DataProviderNative();

            static DataProviderNative instance;

            static void dataReport2APP_TaskProc(void * param);

      public:
            static DataProviderNative * getInstance(void) {
                  return &instance;
            };//采用饿汉模式,避免多线程不安全

            bool init(void);
            void deinit(void);
            bool RegisterContentCallBack(void *param, void * registerCb);
            char * getSysInfo(const char * cmd);
};

#endif