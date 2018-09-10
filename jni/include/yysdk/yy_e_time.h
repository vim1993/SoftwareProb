#ifndef YY_E_TIME_H
#define YY_E_TIME_H
#include "yy_p_time.h"
#include "yy_p_type.h"

#ifdef  __cplusplus
extern "C" {
#endif

/* 返回32无符号整数表示的自1970年1月1日00:00:00开始到现在的UTC时间秒数 */
extern yy_p_uint32 yy_e_time32();

/* 返回64无符号整数表示的自1970年1月1日00:00:00开始到现在的UTC时间秒数 */
extern yy_p_uint64 yy_e_time64();

/* 将时间t（通常由time()获取）转换为UTC时间 */
extern int yy_e_gmtime(time_t *t, struct tm *result);

/* 把时间t（通常由time()获取）转换为本地时间(local time)，并存于result结构中 */
extern int yy_e_localtime(time_t *t, struct tm *result);

/* 返回UTC epoch（1970年1月1日00:00:00）以来经历的毫秒数 */
extern yy_p_uint64 yy_e_millisecond64();

/* 检测时间now是否在begin和begin+range范围内 */
extern int yy_e_millitime_is_in_range( yy_p_uint32 begin, yy_p_uint32 range, yy_p_uint32 now );

/* 检测时间now是否在begin和begin+range范围内，与上面的区别是单位不一样 */
extern int yy_e_time_is_in_range( time_t begin, time_t range, time_t now );

/* 如果当前时间不在这个指定的范围内,则认为授权时间检查失败 */
extern int yy_e_time_check_lencese_valid( int yb, int mb , int db, int ye, int me, int de );

/* 用sec和usec初始化tv.sec和tv.usec，并校正 */
extern void yy_e_timeval_init( yy_p_timeval_t * tv, long sec, long usec );

/* 比较left和right时间大小 */
extern int yy_e_timeval_cmp( const yy_p_timeval_t * left, const yy_p_timeval_t * right );

/* 校正时间 */
extern void yy_e_timeval_normalize( yy_p_timeval_t * tv );

/* 将时间left与right相加，校正后保存到result中 */
extern void yy_e_timeval_add( const yy_p_timeval_t * left, const yy_p_timeval_t * right, yy_p_timeval_t * result );

/* 将时间left减去right，校正后保存到result中 */
extern void yy_e_timeval_sub( const yy_p_timeval_t * left, const yy_p_timeval_t * right, yy_p_timeval_t * result );

/*将时间left减去right,并将结果转换到long输出，单位是1秒=1000000 ，即百万分之一秒
有溢出的可能
*/
extern long yy_e_timeval_sub_2_long( const yy_p_timeval_t * left, const yy_p_timeval_t * right );

/**
*   timex,实现ISO8601的一个子集
*   YYYYMMDDTHHMMSS->time_t
*/
#define YY_E_TIMEX_MAX_LEN				32
#define YY_E_TIMEX_YYYYMMDDTHHMMSSZ     1
#define YY_E_TIMEX_YYYYMMDD             2
#define YY_E_TIMEX_HHMMSS               3
#define YY_E_TIMEX_YYYYMMDDTHHMMSS_mmmZ	4


/* 将timex字符串时间转换为指定时区时间，时区在timex串中指定 */
extern time_t yy_e_timex_2_time( const char * timex );

/* 将timex字符串时间转换为指定时区时间，时区由timezone参数指定 */
extern time_t yy_e_timex_part_2_time( const char * timex_day, const char * timex_time, int timezone );

/* 将时间t转换为指定时区timezone的时间，并按格式存储到timex中 */
extern int yy_e_time_2_timex( char * timex, size_t x_len, int type, time_t t, int timezone );
extern int yy_e_time_2_timex2( char * timex, size_t x_len, int type, time_t t, yy_p_uint32 t_ms, int timezone );

/* 获取本地时区 */
extern int yy_e_timezone();

/*  获取当前时间在一年中所处的天数   */
extern int yy_e_localtime_yday();


#ifdef  __cplusplus
}
#endif

#endif
