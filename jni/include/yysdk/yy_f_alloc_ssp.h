#ifndef YY_F_ALLOC_SSP_H
#define YY_F_ALLOC_SSP_H
#include "yy_f_alloc.h"

/*
*本内存池实现原理：该池实际上是内存池组，包含多个子池，每个子池用ckp池实现
*ckp池的原理：申请一个大块，大块划分为N个小块，将小块分配给用户
*added by gaoqiang, 2015-06-19
*/

/* 池创建参数 */
typedef struct yy_f_alloc_ssp_init_s{    
    size_t node_size;		/* 结点（或理解为对外分配的内存分片）大小 */
    size_t chunk_size;		/* 块大小，包含多个结点 */
    size_t init_chunk_num;	/* 初始块数 */
    size_t grow_chunk_num;	/* 增长内存池时，每次增长的块数 */
    size_t max_chunk_num;	/* 池中最大块数 */
    yy_f_alloc_t * alloc_chunk;	/* 块分配器 */
}yy_f_alloc_ssp_init_t;

/* 创建ssp内存池 */
extern yy_f_alloc_t * yy_f_alloc_ssp_create( yy_p_uint32 flag, const yy_f_alloc_ssp_init_t * ssp_init, size_t ssp_init_num, yy_f_alloc_t * alloc_large, size_t large_alignment );

/* 测试用例 */
extern int yy_f_alloc_ssp_validation_test();
#endif
