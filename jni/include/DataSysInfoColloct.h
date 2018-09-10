#ifndef __DATA_SYSINFO_COLLOCT_H__
#define __DATA_SYSINFO_COLLOCT_H__

#include <pthread.h>

using namespace std;

class ISysInfoDataColloct {

      protected:
            virtual char * getNetInfo(const char * cmd) = 0;
            virtual char * getSysInfo(const char * cmd) = 0;
            virtual char * getTSInfo(const char * cmd) = 0;

      public:
            ISysInfoDataColloct();
            ~ISysInfoDataColloct();

            char * getSysInfoColloctData(const char * cmd);
};

class SysInfoDataColloct: public ISysInfoDataColloct {
      private:
            pthread_t mtid;

      protected:
            char * getNetInfo(const char * cmd);
            char * getSysInfo(const char * cmd);
            char * getTSInfo(const char * cmd);

      public:
            SysInfoDataColloct();
            ~SysInfoDataColloct();
};

#endif