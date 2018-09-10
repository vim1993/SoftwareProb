#include <stdio.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif
#include "minidpi/minidpi.h"
#ifdef __cplusplus
}
#endif

#include "DataSysInfoColloct.h"
#include "UtilsMemoryPool.h"
#include "UtilsCommon.h"

#define CHECK_FILTER_DEF 0XFF
#define STRING_CPU_CMD "CPU"
#define STRING_MEM_CMD "Mem"
#define STRING_DISK_CMD "Disk"
#define STRING_NET_CMD "Net"
#define SYS_INFO_FILENAME "/data/sysinfo.txt"
#define CPU_INFO_CMD "dumpsys cpuinfo >/data/sysinfo.txt"
#define MEM_INFO_CMD "dumpsys meminfo > /data/sysinfo.txt"
#define DISK_INFO_CMD "busybox df > /data/sysinfo.txt"
#define STRING_NET_LEN  256

long last_connect_cnt = 1;
long last_event_cnt = 1;
static unsigned int  unorder_up = 0;
static unsigned int  unorder_down = 0;
static unsigned int  retrans_up = 0;
static unsigned int  retrans_down = 0;
static unsigned int  last_get_stat_time = 0;
static unsigned int  current_get_stat_time = 0;

ISysInfoDataColloct::ISysInfoDataColloct()
{

}

ISysInfoDataColloct ::~ISysInfoDataColloct()
{

}

SysInfoDataColloct::SysInfoDataColloct()
{

}

SysInfoDataColloct::~SysInfoDataColloct()
{

}

char* ISysInfoDataColloct::getSysInfoColloctData(const char * cmd)
{
	if (NULL == cmd)
	{
		return NULL;
	}

	 if (!strncasecmp(cmd, STRING_CPU_CMD, strlen(STRING_CPU_CMD)))
      {
            system(CPU_INFO_CMD);
            return getSysInfo(cmd);
      }
      else if (!strncasecmp(cmd, STRING_MEM_CMD, strlen(STRING_MEM_CMD)))
      {
            system(MEM_INFO_CMD);
            return getSysInfo(cmd);
      }
      else if (!strncasecmp(cmd, STRING_DISK_CMD, strlen(STRING_DISK_CMD)))
      {
            system(DISK_INFO_CMD);
            return getSysInfo(cmd);
      }
      else if (!strncasecmp(cmd, STRING_NET_CMD, strlen(STRING_NET_CMD)))
      {
            return getNetInfo(cmd);
      }

      LOGD("cmd error\n");
      return NULL;

}

char* SysInfoDataColloct:: getSysInfo(const char * cmd)
{
      #if 0
	FILE *fp = NULL;
      int ret = 0;
      int flen = 0;
      static char *buf = NULL;
      char *buf_tmp = NULL;

      if (NULL != buf)
      {
            sdk_mem_free(buf);
            buf = NULL;
      }

      if(NULL == cmd)
      {
            return NULL;
      }

      fp=fopen(SYS_INFO_FILENAME,"r");
      if (fp == NULL)
      {
           LOGD("[%s:%d] fopen fail\n", __FUNCTION__, __LINE__);
           remove(SYS_INFO_FILENAME);
           return NULL;
      }

      fseek(fp,0L,SEEK_END);
      flen=ftell(fp);
      if(flen < 0)
      {
           LOGD("[%s:%d] ftell fail\n", __FUNCTION__, __LINE__);
           fclose(fp);
           remove(SYS_INFO_FILENAME);
           return NULL;
      }

      buf =(char *)sdk_mem_malloc(flen+20);
      if(NULL == buf)
      {
            LOGD("[%s:%d] sdk_mem_malloc fail\n", __FUNCTION__, __LINE__);
            fclose(fp);
            remove(SYS_INFO_FILENAME);
            return NULL;
      }
      memset(buf, 0, flen+20);

      buf_tmp =(char *)sdk_mem_malloc(flen+1);
      if(NULL == buf_tmp)
      {
           LOGD("[%s:%d] sdk_mem_malloc fail\n", __FUNCTION__, __LINE__);
           fclose(fp);
           remove(SYS_INFO_FILENAME);
           return NULL;
      }
      memset(buf_tmp, 0x0, flen+1);

      fseek(fp,0L,SEEK_SET);
      LOGD("[%s:%d] ftell flen=%d\n", __FUNCTION__, __LINE__,flen);
      ret = fread(buf_tmp,1,flen,fp);
      LOGD("[%s:%d] ret=%d\n", __FUNCTION__, __LINE__,ret);
      if(ret < 0)
      {
           LOGD("[%s:%d] fread fail\n", __FUNCTION__, __LINE__);
           sdk_mem_free(buf_tmp);
           fclose(fp);
           remove(SYS_INFO_FILENAME);
           return NULL;
      }

      snprintf(buf, flen+20, "{\"%s\":\"%s\"}", cmd, buf_tmp);

      if(NULL != buf_tmp)
      {
            sdk_mem_free(buf_tmp);
      }

      fclose(fp);
      remove(SYS_INFO_FILENAME);
      LOGD("[%s:%d] %s\n", __FUNCTION__, __LINE__, buf);
      return buf;
      #else
      return "this is test";
      #endif
}

char* SysInfoDataColloct::getNetInfo(const char * cmd)
{
	static bool count = true;
	sys_stat *stat = get_sys_stat();
	static char *buf = NULL;

	if (NULL ==cmd && NULL == stat)
	{
		return NULL;
	}
	if (NULL == buf)
	{
		buf = (char *)sdk_mem_malloc(STRING_NET_LEN);
		if (NULL ==buf)
		{
			return NULL;
		}
	}
	memset(buf,0,STRING_NET_LEN);

	if (count)
	{
		last_get_stat_time =stat->start_time;
		count = false;
	}

	current_get_stat_time = stat ->start_time;
	LOGD("[%s:%d] current_get_stat_time=%d\n", __FUNCTION__, __LINE__, current_get_stat_time);
      LOGD("[%s:%d] last_get_stat_time=%d\n", __FUNCTION__, __LINE__, last_get_stat_time);


	snprintf(buf, STRING_NET_LEN, \
			  "{\"%s\":{\"start_time\":%d,\"stat_time\":%d,\"time_interval\":%d,\"recv_cnt\":%d,\"drop_cnt\":%d,\"ifdrop_cnt\":%d,\"unorder\":[%d,%d], \"retrans\":[%d,%d]}}", \
			  cmd, stat->start_time, stat->stat_time, current_get_stat_time - last_get_stat_time, \
			  stat->recv_cnt, stat->drop_cnt, stat->ifdrop_cnt, \
			  unorder_up, unorder_down, retrans_up, retrans_down);


	last_get_stat_time += current_get_stat_time - last_get_stat_time;

      unorder_up = 0;
      unorder_down = 0;
      retrans_up = 0;
      retrans_down = 0;
      LOGD("[%s:%d] %s\n", __FUNCTION__, __LINE__, buf);
      return buf;


}

char* SysInfoDataColloct::getTSInfo(const char * cmd)
{

}

int main(int argc, char * argv[])
{
	ISysInfoDataColloct * colloct = new SysInfoDataColloct();

	printf("[%s][%d]! value:%s\n", __func__, __LINE__, colloct->getSysInfoColloctData(STRING_CPU_CMD));

	delete colloct;

	return 0;
}













































