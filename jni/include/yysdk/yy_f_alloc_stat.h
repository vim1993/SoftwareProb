#ifndef YY_F_ALLOC_STAT_H
#define YY_F_ALLOC_STAT_H
#include "yy_f_alloc.h"

/**
*   封装某种类型的内存分配器，添加分配释放统计和回调处理
*	added by gaoqiang, 2015-06-16
*/


/* 回调函数， 用于分配成功或失败时信息回调 */
typedef void (*yy_f_alloc_stat_malloc_cb_t)(yy_f_alloc_t *alloc, void * p, size_t size);

/* 回调函数，用于外部处理打印等信息 */
typedef void (*yy_f_alloc_stat_free_cb_t)(yy_f_alloc_t *alloc, void * p);

/* 初始化统计结构体 */
extern yy_f_alloc_t * yy_f_alloc_stat_create( yy_p_uint32 flag,  yy_f_alloc_t * alloc_ori );

/* 用于统计的回调 (非线程安全，建议在创建后，马上设置，后续将不再更改 )*/
extern void yy_f_alloc_stat_set_malloc_free_cb( yy_f_alloc_t *alloc, yy_f_alloc_stat_malloc_cb_t f_malloc, yy_f_alloc_stat_free_cb_t f_free );

#endif
