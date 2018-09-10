#ifndef YY_E_STDLIB_H
#define YY_E_STDLIB_H
#include "yy_p_stdlib.h"
#include "yy_p_time.h"

/* added qwh 2016-1-18 cpu���ڴ桢���硢������������������̸���  */
/*******************************����Ϊ��Ҫ��ֲ��yy���еĶ���*********************************************/
#if YY_P_IS_NIX
    #include <sys/param.h>
#endif

#define  MAX_CPU_COUNT    (128)              /* ���cpu���� */
#define  MAX_NET_CARD_COUNT   (64)           /* ����������� */
#define  MAX_DISK_PARTITION_COUNT (256)      /* ���̷������� */

/* cpu�Ľṹ�� */
typedef struct yy_e_cpu_occupy_s
{
    char name[64];      /* cpu������ */
    yy_p_uint64 idle;   /* ��Ӳ��IO�ȴ�ʱ�����������ȴ�ʱ�� */
    yy_p_uint64 total;  /* ����cpuʱ�� */
}yy_e_cpu_occupy_t;

/* ����cpu(���)�ĸ��ؽṹ�� */
typedef struct yy_e_cpu_load_s
{
    yy_e_cpu_occupy_t cpu_occ[MAX_CPU_COUNT];/* ���MAX_CPU_COUNT��cpu */
    int cpu_count;                         /* cpu�ĸ��� */
}yy_e_cpu_load_t;

/* �ڴ渺�ؽṹ�� */
typedef struct yy_e_mem_load_s
{
    yy_p_uint64 memtotal;                   /* �ܵ�ϵͳ�ڴ� */
    yy_p_uint64 memfree;                    /* ���е�ϵͳ�ڴ� */
    yy_p_uint64 buffers;                    /* �ܵ�buffers�ڴ� */
    yy_p_uint64 cached;                     /* �ܵ�cached�ڴ� */
}yy_e_mem_load_t;

/* net�ṹ�� */
typedef struct yy_e_net_occupy_s
{
    char name[64];
    yy_p_uint64 recv_bytes;                 /* ���ܵ��ֽ��� */
    yy_p_uint64 send_bytes;                 /* �������ֽ��� */
    yy_p_uint64 total_bytes;                /* �ܵ��ֽ��� */
    time_t _time;                           /* ��ǰ��ʱ�� */
}yy_e_net_occupy_t;

/* ��������net�ĸ��ؽṹ�� */
typedef struct yy_e_net_load_s
{
    yy_e_net_occupy_t net_occ[MAX_NET_CARD_COUNT];/* ���MAX_NET_CARD_COUNT������ */
    int net_count;                          /* �����ĸ��� */
}yy_e_net_load_t;

/* disk_io�ṹ�� */
typedef struct yy_e_disk_io_occupy_s
{
    char            name[64];               /* �豸�� */
    yy_p_uint32     major;                  /* Device major number */
    yy_p_uint32     minor;                  /* Device minor number */
	yy_p_uint64     ticks;	                /* Time of requests in queue */
}yy_e_disk_io_occupy_t;

/* disk_io���ؽṹ�� */
typedef struct yy_e_disk_io_load_s
{
    yy_e_disk_io_occupy_t disk_io_occ[MAX_DISK_PARTITION_COUNT];    /* ���MAX_DISK_PARTITION_COUNT�����̷��� */
    int disk_io_count;                      /* ���̷������� */
}yy_e_disk_io_load_t;

/* ��ȡ/proc/stat�ڴ��ļ�����ȡ����cpu����ע�����ݵ�cpu_load�ṹ���� */
extern int yy_e_get_cpu_info(yy_e_cpu_load_t *cpu_load);

/* ��ȡ/proc/meminfo�ڴ��ļ�����ȡme����ע�����ݵ�mem_load�ṹ���� */
extern int yy_e_get_mem_info(yy_e_mem_load_t *mem_load);

/* ��ȡ/proc/diskstats�ڴ��ļ�����ȡ����disk_io����ע�����ݵ�disk_io_load�ṹ���� */
extern int yy_e_get_disk_io_info(yy_e_disk_io_load_t *disk_io_load);
/********************************************************************************************************/
/* crc32 ѭ������Ч�� */
extern int yy_e_crc32(const char * buf, size_t len, yy_p_uint32 * crc32);

/********************************************************************************************************/
/* ���ַ���ת����int ����Ҫ���ַ������ */
extern int yy_e_atoi( const char * str );

#endif
