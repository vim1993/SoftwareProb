#ifndef YY_P_TIME_H
#define YY_P_TIME_H
#include "yy_p_config.h"
#include "yy_p_type.h"
#include <time.h>

#if YY_P_IS_NIX
    #include <sys/time.h>
#endif

#ifdef  __cplusplus
extern "C" {
#endif

#if YY_P_IS_WINDOWS
	#if defined( _USE_32BIT_TIME_T )
		#define YY_P_PRI_TIME_T "%d"
	#else
		#define YY_P_PRI_TIME_T "%lld"
	#endif
#else
	#if YY_P_IS_BUS_WIDTH_64
		#define YY_P_PRI_TIME_T "%ld"
	#else
		#define YY_P_PRI_TIME_T "%ld"
	#endif
#endif

typedef time_t yy_p_time_t;
#define YY_P_INVALID_TIME_T (yy_p_time_t)(-1)
#define YY_P_TIME_MAX     0x7FFFFFFF

/* C���Բ�ʱ�亯��,�����Ǳ�׼���Ӽ�,�����ǳ��� */
#define yy_p_time      time
#define yy_p_mktime    mktime
#define yy_p_gmtime     gmtime
#define yy_p_localtime localtime


/* OS����ʱ�亯���ṹ�� */
typedef struct yy_p_timeval_s{
    long sec;   // ����
    long usec;  //1sec = 1000000usec
}yy_p_timeval_t;


/* �õ���ȷ��ʱ�䣬����Ϊ΢�룬�˺���Ϊlinux���У�windows����ģ��ʵ�� */
extern int yy_p_gettimeofday( yy_p_timeval_t * t );

/* ʹ��ǰ�߳�sleepָ��ʱ�䣬��λΪ���� */
extern int yy_p_sleep_millisecond( yy_p_uint32 ms );

/* ����ϵͳ��������������������ʱ��(��λ ms) */
extern yy_p_uint32 yy_p_millisecond32();


extern int yy_p_time_validation_test();

#ifdef  __cplusplus
}
#endif

#endif
