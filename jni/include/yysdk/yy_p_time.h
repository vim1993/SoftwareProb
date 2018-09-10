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

/* C语言层时间函数,可以是标准的子集,不能是超集 */
#define yy_p_time      time
#define yy_p_mktime    mktime
#define yy_p_gmtime     gmtime
#define yy_p_localtime localtime


/* OS层面时间函数结构体 */
typedef struct yy_p_timeval_s{
    long sec;   // 秒数
    long usec;  //1sec = 1000000usec
}yy_p_timeval_t;


/* 得到精确的时间，精度为微秒，此函数为linux所有，windows下是模拟实现 */
extern int yy_p_gettimeofday( yy_p_timeval_t * t );

/* 使当前线程sleep指定时间，单位为毫秒 */
extern int yy_p_sleep_millisecond( yy_p_uint32 ms );

/* 返回系统从启动到现在所经历的时间(单位 ms) */
extern yy_p_uint32 yy_p_millisecond32();


extern int yy_p_time_validation_test();

#ifdef  __cplusplus
}
#endif

#endif
