#ifndef YY_E_STDLIB_H
#define YY_E_STDLIB_H
#include "yy_p_stdlib.h"
#include "yy_p_time.h"

/* added qwh 2016-1-18 cpu、内存、网络、句柄、在线人数、磁盘负载  */
/*******************************下面为需要移植到yy库中的东西*********************************************/
#if YY_P_IS_NIX
    #include <sys/param.h>
#endif

#define  MAX_CPU_COUNT    (128)              /* 最大cpu个数 */
#define  MAX_NET_CARD_COUNT   (64)           /* 最大网卡个数 */
#define  MAX_DISK_PARTITION_COUNT (256)      /* 磁盘分区个数 */

/* cpu的结构体 */
typedef struct yy_e_cpu_occupy_s
{
    char name[64];      /* cpu的名字 */
    yy_p_uint64 idle;   /* 除硬盘IO等待时间以外其它等待时间 */
    yy_p_uint64 total;  /* 所有cpu时间 */
}yy_e_cpu_occupy_t;

/* 所有cpu(多核)的负载结构体 */
typedef struct yy_e_cpu_load_s
{
    yy_e_cpu_occupy_t cpu_occ[MAX_CPU_COUNT];/* 最多MAX_CPU_COUNT个cpu */
    int cpu_count;                         /* cpu的个数 */
}yy_e_cpu_load_t;

/* 内存负载结构体 */
typedef struct yy_e_mem_load_s
{
    yy_p_uint64 memtotal;                   /* 总的系统内存 */
    yy_p_uint64 memfree;                    /* 空闲的系统内存 */
    yy_p_uint64 buffers;                    /* 总的buffers内存 */
    yy_p_uint64 cached;                     /* 总的cached内存 */
}yy_e_mem_load_t;

/* net结构体 */
typedef struct yy_e_net_occupy_s
{
    char name[64];
    yy_p_uint64 recv_bytes;                 /* 接受的字节数 */
    yy_p_uint64 send_bytes;                 /* 发出的字节数 */
    yy_p_uint64 total_bytes;                /* 总的字节数 */
    time_t _time;                           /* 当前的时间 */
}yy_e_net_occupy_t;

/* 所有网卡net的负载结构体 */
typedef struct yy_e_net_load_s
{
    yy_e_net_occupy_t net_occ[MAX_NET_CARD_COUNT];/* 最多MAX_NET_CARD_COUNT个网卡 */
    int net_count;                          /* 网卡的个数 */
}yy_e_net_load_t;

/* disk_io结构体 */
typedef struct yy_e_disk_io_occupy_s
{
    char            name[64];               /* 设备名 */
    yy_p_uint32     major;                  /* Device major number */
    yy_p_uint32     minor;                  /* Device minor number */
	yy_p_uint64     ticks;	                /* Time of requests in queue */
}yy_e_disk_io_occupy_t;

/* disk_io负载结构体 */
typedef struct yy_e_disk_io_load_s
{
    yy_e_disk_io_occupy_t disk_io_occ[MAX_DISK_PARTITION_COUNT];    /* 最多MAX_DISK_PARTITION_COUNT个磁盘分区 */
    int disk_io_count;                      /* 磁盘分区个数 */
}yy_e_disk_io_load_t;

/* 读取/proc/stat内存文件，获取所有cpu被关注的数据到cpu_load结构体中 */
extern int yy_e_get_cpu_info(yy_e_cpu_load_t *cpu_load);

/* 读取/proc/meminfo内存文件，获取me被关注的数据到mem_load结构体中 */
extern int yy_e_get_mem_info(yy_e_mem_load_t *mem_load);

/* 读取/proc/diskstats内存文件，获取所有disk_io被关注的数据到disk_io_load结构体中 */
extern int yy_e_get_disk_io_info(yy_e_disk_io_load_t *disk_io_load);
/********************************************************************************************************/
/* crc32 循环冗余效验 */
extern int yy_e_crc32(const char * buf, size_t len, yy_p_uint32 * crc32);

/********************************************************************************************************/
/* 将字符串转换成int ，但要对字符串检测 */
extern int yy_e_atoi( const char * str );

#endif
