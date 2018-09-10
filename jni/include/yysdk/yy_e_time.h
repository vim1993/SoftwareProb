#ifndef YY_E_TIME_H
#define YY_E_TIME_H
#include "yy_p_time.h"
#include "yy_p_type.h"

#ifdef  __cplusplus
extern "C" {
#endif

/* ����32�޷���������ʾ����1970��1��1��00:00:00��ʼ�����ڵ�UTCʱ������ */
extern yy_p_uint32 yy_e_time32();

/* ����64�޷���������ʾ����1970��1��1��00:00:00��ʼ�����ڵ�UTCʱ������ */
extern yy_p_uint64 yy_e_time64();

/* ��ʱ��t��ͨ����time()��ȡ��ת��ΪUTCʱ�� */
extern int yy_e_gmtime(time_t *t, struct tm *result);

/* ��ʱ��t��ͨ����time()��ȡ��ת��Ϊ����ʱ��(local time)��������result�ṹ�� */
extern int yy_e_localtime(time_t *t, struct tm *result);

/* ����UTC epoch��1970��1��1��00:00:00�����������ĺ����� */
extern yy_p_uint64 yy_e_millisecond64();

/* ���ʱ��now�Ƿ���begin��begin+range��Χ�� */
extern int yy_e_millitime_is_in_range( yy_p_uint32 begin, yy_p_uint32 range, yy_p_uint32 now );

/* ���ʱ��now�Ƿ���begin��begin+range��Χ�ڣ�������������ǵ�λ��һ�� */
extern int yy_e_time_is_in_range( time_t begin, time_t range, time_t now );

/* �����ǰʱ�䲻�����ָ���ķ�Χ��,����Ϊ��Ȩʱ����ʧ�� */
extern int yy_e_time_check_lencese_valid( int yb, int mb , int db, int ye, int me, int de );

/* ��sec��usec��ʼ��tv.sec��tv.usec����У�� */
extern void yy_e_timeval_init( yy_p_timeval_t * tv, long sec, long usec );

/* �Ƚ�left��rightʱ���С */
extern int yy_e_timeval_cmp( const yy_p_timeval_t * left, const yy_p_timeval_t * right );

/* У��ʱ�� */
extern void yy_e_timeval_normalize( yy_p_timeval_t * tv );

/* ��ʱ��left��right��ӣ�У���󱣴浽result�� */
extern void yy_e_timeval_add( const yy_p_timeval_t * left, const yy_p_timeval_t * right, yy_p_timeval_t * result );

/* ��ʱ��left��ȥright��У���󱣴浽result�� */
extern void yy_e_timeval_sub( const yy_p_timeval_t * left, const yy_p_timeval_t * right, yy_p_timeval_t * result );

/*��ʱ��left��ȥright,�������ת����long�������λ��1��=1000000 ���������֮һ��
������Ŀ���
*/
extern long yy_e_timeval_sub_2_long( const yy_p_timeval_t * left, const yy_p_timeval_t * right );

/**
*   timex,ʵ��ISO8601��һ���Ӽ�
*   YYYYMMDDTHHMMSS->time_t
*/
#define YY_E_TIMEX_MAX_LEN				32
#define YY_E_TIMEX_YYYYMMDDTHHMMSSZ     1
#define YY_E_TIMEX_YYYYMMDD             2
#define YY_E_TIMEX_HHMMSS               3
#define YY_E_TIMEX_YYYYMMDDTHHMMSS_mmmZ	4


/* ��timex�ַ���ʱ��ת��Ϊָ��ʱ��ʱ�䣬ʱ����timex����ָ�� */
extern time_t yy_e_timex_2_time( const char * timex );

/* ��timex�ַ���ʱ��ת��Ϊָ��ʱ��ʱ�䣬ʱ����timezone����ָ�� */
extern time_t yy_e_timex_part_2_time( const char * timex_day, const char * timex_time, int timezone );

/* ��ʱ��tת��Ϊָ��ʱ��timezone��ʱ�䣬������ʽ�洢��timex�� */
extern int yy_e_time_2_timex( char * timex, size_t x_len, int type, time_t t, int timezone );
extern int yy_e_time_2_timex2( char * timex, size_t x_len, int type, time_t t, yy_p_uint32 t_ms, int timezone );

/* ��ȡ����ʱ�� */
extern int yy_e_timezone();

/*  ��ȡ��ǰʱ����һ��������������   */
extern int yy_e_localtime_yday();


#ifdef  __cplusplus
}
#endif

#endif
