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

            NeedleCommonMsg * mTSDataMsgQue;
            NeedleCommonMsg * mReportMsgQue;

            ISysInfoDataColloct * mSYSINFO;

      public:
            virtual void init(void) = 0;
            virtual void RegisterContentCallBack(void *param, void * registerCb) = 0; //注册回调函数相关参数
            virtual char * getSysInfo(const char * cmd) = 0;
};

class DataProviderAndroid : public IDataProvider {

      private:
            DataProviderAndroid();
            ~DataProviderAndroid();

            static DataProviderAndroid instance;

      public:
            DataProviderAndroid * getInstance(void) {
                  return &instance;
            };//采用饿汉模式,避免多线程不安全

            void init(void);
            void RegisterContentCallBack(void *param, void * registerCb);
            char * getSysInfo(const char * cmd);
};

class DataProviderNative : public IDataProvider {

      private:
            DataProviderNative();
            ~DataProviderNative();

            static DataProviderNative instance;

      public:
            static DataProviderNative * getInstance(void) {
                  return &instance;
            };//采用饿汉模式,避免多线程不安全

            void init(void);
            void RegisterContentCallBack(void *param, void * registerCb);
            char * getSysInfo(const char * cmd);
};

#endif