#ifndef YY_F_TIMER_QUEUE_H
#define YY_F_TIMER_QUEUE_H
#include "yy_p_type.h"
#include "yy_p_time.h"
#include "yy_e_memcheck.h"
#include "yy_e_time.h"
#include "yy_f_alloc.h"

/*
*定时器队列（由堆实现），由此实现反应器中的定时器
*added by gaoqiang, 2015-08-03
*/

/* 从ACE参考,简化 */

typedef size_t yy_f_timer_id_t;				/* 定时器id  */
#define YY_F_INVALID_TIMERID ((size_t)-1)	/* 无效定时器ID */
#define YY_F_PRI_TIMERID YY_P_PRI_SIZE_T		/* 打印输出定时器ID时使用的格式串 */

typedef struct yy_f_timer_queue_stat_s{
    size_t add_timer_count;				
    size_t cancel_timer_count;				
    size_t slow_timer_count;
    size_t expire_timer_count;
}yy_f_timer_queue_stat_t;

/* 定时器结构体 */
typedef struct yy_f_timer_queue_timer_s{
	YY_E_MEM_MAGIC_PREFIX_DEFINE;
	yy_p_timeval_t interval_tv;			/* 定时间隔时间 */ 
	yy_p_timeval_t expire_tv;			/* 到期时间 */
	void * data;						/* 自定义数据 */
	size_t heap_index;					/* 定时器在堆中的索引 */
	YY_E_MEM_MAGIC_SUFFIX_DEFINE;
}yy_f_timer_queue_timer_t;

/* 定时器队列结构体 */
typedef struct yy_f_timer_queue_s{
    yy_f_alloc_t *alloc_thiz;			/* 内存分配器 */
	size_t * heap_array;				/* 构建的堆结构 */
	yy_f_timer_queue_timer_t *timer_array;	/* 定时器数组 */

	size_t malloced_node_num;			/* 已分配定时器数目 */
	size_t used_node_num;				/* 已使用定时器数目 */
	size_t init_node_num;				/* 初始化定时器数目 */
	size_t max_node_num;				/* 最大定时器数目 */

	size_t free_timer_id;				/* 空闲定时器id */

	yy_p_timeval_t last_tv;			/* 定时器创建时间或上一次定时器修正时间（由于系统时间更改） */

    yy_f_timer_queue_stat_t stat;		/* 队列状态统计 */

}yy_f_timer_queue_t;

/* 创建定时器队列 */
extern yy_f_timer_queue_t * yy_f_timer_queue_create( yy_f_alloc_t *alloc_thiz, size_t init_node_num, size_t max_node_num, const yy_p_timeval_t * now_tv ); 

/* 销毁定时器队列 */
extern void yy_f_timer_queue_destroy( yy_f_timer_queue_t * q );

/* 将定时器插入队列中 */
extern yy_f_timer_id_t yy_f_timer_queue_schedule_timer( yy_f_timer_queue_t * q, void * data, const yy_p_timeval_t * now_tv, const yy_p_timeval_t * interval_tv );

/* 扩充定时器队列 */
extern int yy_f_timer_queue_reserve( yy_f_timer_queue_t * q, size_t more_size );

/* 取消定时器 */
extern void yy_f_timer_queue_cancel_timer( yy_f_timer_queue_t * q, yy_f_timer_id_t timer_id, const void * data );

/* 获取定时器队列数目 */
extern size_t yy_f_timer_queue_size( const yy_f_timer_queue_t * q );

/* 获取一个超时定时器 */
extern int yy_f_timer_queue_get_expire_timer( yy_f_timer_queue_t * q, void ** pdata, const yy_p_timeval_t * now_tv,  yy_p_timeval_t * near_tv );

/* 若系统修改了当前时间，则尝试对所有定时器做修正 */
extern void yy_f_timer_queue_correct_time( yy_f_timer_queue_t * q, const yy_p_timeval_t * now_tv );

//读取定时器的统计信息
extern void yy_f_timer_queue_stat( yy_f_timer_queue_t * q, yy_f_timer_queue_stat_t * stat );

/* 测试用例 */
extern int yy_f_timer_queue_validation_test_test(void);
#endif
