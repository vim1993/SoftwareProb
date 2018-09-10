#ifndef YY_E_FLOW_H
#define YY_E_FLOW_H
#include "yy_p_type.h"
#include "yy_p_thread.h"
#include "yy_e_time.h"
#include "yy_e_memcheck.h"

#define YY_E_FLOW_NODE_INDEX_MASK    0x3F		/* 正好对应 0~63的node，对应下面的MAX_NUM */
#define YY_E_FLOW_NODE_MAX_NUM		 64			//是最小的统计周期的倍数即可


#if defined( YY_E_FLOW_USE_64BIT )
	typedef yy_p_uint64 yy_e_flow_size_t;
	#define YY_E_PRI_FLOW_SIZE_T "%llu"
#else
	typedef yy_p_uint32 yy_e_flow_size_t;
	#define YY_E_PRI_FLOW_SIZE_T "%u"
#endif

/* 统计流量子节点结构体 */
typedef struct yy_e_flow_node_s{
	yy_e_flow_size_t bytes;         /* 当前分片的字节数 */
	yy_e_flow_size_t packs;         /* 当前分片的包数 */
	yy_e_flow_size_t max_packet_size;   /* 最大包的字节数 */
	yy_e_flow_size_t min_packet_size;   /* 最小包的字节数 */
	yy_p_uint32 splice_index;       /* 当前分片的索引 */
}yy_e_flow_node_t;

/* 流量统计结构体 */
typedef struct yy_e_flow_s{
    YY_E_OBJ_MAGIC_DEFINE;
    yy_p_thr_mutex_t lock;			/* 互斥锁 */
    time_t start_time;				/* 开始时间 */
    //计时周期
    yy_p_uint32 cycle_ms;			/* 计时周期 */
    yy_p_uint32 cycle_fixed_ms;		/* 通过cycle_ms计算出的splice_count倍数的周期 */
    yy_p_uint32 splice_ms;			/* 每个splice的周期 */
    yy_p_uint32 splice_count;		/* splice的个数 */

	//当前的分片索引值与时间
    yy_p_uint32 current_splice_index;/* 当前分片索引值 */
	yy_p_uint32 current_splice_ms;	/* 当前分片时间 */

    yy_e_flow_node_t nodes[YY_E_FLOW_NODE_MAX_NUM];
    //

    yy_e_flow_size_t total_bytes;	/* 总的流量(单位:字节) */
    yy_e_flow_size_t total_packs;	/* 总的包的个数 */
    
}yy_e_flow_t;

/*
cycle_ms:计时周期,以毫秒为单位
use_lock:是不是使用内置锁
*/
/* 初始化流量统计结构体 */
extern void yy_e_flow_init( yy_e_flow_t * stat, yy_p_uint32 cycle_ms, int use_lock );

/* 反初始化统计流结构体 */
extern void yy_e_flow_uninit( yy_e_flow_t * stat ); 

/*
bytes:数据量
packs:包数
now_ms:当前时间(毫秒),使用0代个由内部生成
*/
/* 统计传入的bytes和packs，将这两个值添加到流量统计结构体中 */
extern void yy_e_flow_log(  yy_e_flow_t * stat, size_t bytes, size_t packs, yy_p_uint32 now_ms );

/* 获取字节码率，按秒为单位 */
extern yy_e_flow_size_t yy_e_flow_bps(const  yy_e_flow_t * stat, yy_p_uint32 now_ms );

/* 获取包率，按秒为单位 */
extern yy_e_flow_size_t yy_e_flow_pps( const yy_e_flow_t * stat, yy_p_uint32 now_ms );

/* 获取字节码率,从开始运行现当前 */
extern yy_e_flow_size_t yy_e_flow_total_bps(const  yy_e_flow_t * stat );

/* 获取字节码率，以计时周期 */
extern yy_e_flow_size_t yy_e_flow_bpc(const  yy_e_flow_t * stat, yy_p_uint32 now_ms );

/* 获取包率,以计时周期 */
extern yy_e_flow_size_t yy_e_flow_ppc( const yy_e_flow_t * stat, yy_p_uint32 now_ms );

/* 计算计时周期内，包的平均大小 */
extern yy_e_flow_size_t yy_e_flow_avg_packet_size_pc( const yy_e_flow_t * stat, yy_p_uint32 now_ms );

/* 计算计时周期内，最大包的大小 */
extern yy_e_flow_size_t yy_e_flow_max_packet_size_pc( const yy_e_flow_t * stat, yy_p_uint32 now_ms );

/* 累计字节数 */
extern yy_e_flow_size_t yy_e_flow_total_bytes( const yy_e_flow_t * stat );

/* 累计包数量 */
extern yy_e_flow_size_t yy_e_flow_total_packs( const yy_e_flow_t * stat );

/* 重新设置数据 */
extern void yy_e_flow_reset( yy_e_flow_t * stat, yy_e_flow_size_t bps, yy_e_flow_size_t pps);

/* 开始时间 */
extern time_t yy_e_flow_start_time( const yy_e_flow_t * stat );

/* 测试用例 */
extern int yy_e_flow_validation_test( );
#endif
