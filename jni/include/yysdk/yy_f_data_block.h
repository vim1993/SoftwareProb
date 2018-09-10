#ifndef YY_F_DATA_BLOCK_H
#define YY_F_DATA_BLOCK_H
#include "yy_p_thread.h"
#include "yy_f_alloc.h"
/*
*数据块实现
*added by gaoqiang, 2015-06-26
*/
//ace_data_block
typedef struct yy_f_data_block_s{
    YY_E_MEM_MAGIC_PREFIX_DEFINE;
    yy_p_thr_mutex_t * locking_strategy;
    int ref_count;
    yy_f_alloc_t * alloc_db;
    yy_f_alloc_t * alloc_buf;
    char * base;
    size_t size;
    size_t size_aligned;
    YY_E_MEM_MAGIC_SUFFIX_DEFINE;
}yy_f_data_block_t;

/* 创建数据块 */
extern yy_f_data_block_t * yy_f_data_block_create( size_t size, yy_f_alloc_t * alloc_db, yy_f_alloc_t * alloc_buf, yy_p_thr_mutex_t * locking_strategy );
/* 释放数据块，数据块引用计数减少为0时销毁 */
extern void yy_f_data_block_release( yy_f_data_block_t *db );
/* 克隆数据块 */
extern yy_f_data_block_t * yy_f_data_block_clone( yy_f_data_block_t *db );
/* 引用数据块 */
extern yy_f_data_block_t * yy_f_data_block_duplicate( yy_f_data_block_t *db );
/* 获取数据块数据区起始地址 */
extern char * yy_f_data_block_base( yy_f_data_block_t *db );
/* 获取数据块大小 */
extern size_t yy_f_data_block_size( yy_f_data_block_t *db );

#endif
