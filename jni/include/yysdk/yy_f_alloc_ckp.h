#ifndef YY_F_ALLOC_CKP_H
#define YY_F_ALLOC_CKP_H
#include "yy_f_alloc.h"
/**
*   这个池适合小块内存分配,总是将node_size大小的小块,一次性用chunk_size大小的申请
*   一般node_size是小于1KB的小块,chunk-size是大于128KB的整块
*/

/*
*本内存池的实现原理为：申请一个大块，大块划分为N个小块，将小块分配给用户
*added by gaoqiang, 2015-06-11
*/

/**
*   flag:支持,YY_F_ALLOC_FLAG_LOCK(带锁),YY_F_ALLOC_FLAG_GDATA(带写溢出检查)
*   node_size:小分片的大小
*   chunk_size:块大小,分片总是分块中分配
*   init_chunk_num:初始块数量
*   max_chunk_num: 最大块数量
*   alloc_chunk: 块分配器
*/
/* 创建ckp内存池 */
extern yy_f_alloc_t * yy_f_alloc_ckp_create( yy_p_uint32 flag, size_t node_size, size_t chunk_size, size_t init_chunk_num, size_t max_chunk_num,  yy_f_alloc_t * alloc_chunk );

/* 测试用例 */
extern int yy_f_alloc_ckp_validation_test();
#endif
