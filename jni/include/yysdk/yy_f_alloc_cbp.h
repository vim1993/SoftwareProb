#ifndef YY_F_ALLOC_CBP_H
#define YY_F_ALLOC_CBP_H
#include "yy_f_alloc.h"
/**
*   池的适应环境: 适合1KB起,且是固定长度的内存池分配
*   这是一个链表形式的池,适合一些较大的内存块构成一个池,如512KB的一个BLOCK大小
*   打开G_DATA时,实际申请的空间会比block_size大一个ALIGNMENT
*/

/**
*   flag: 支持,YY_F_ALLOC_FLAG_LOCK(带锁),YY_F_ALLOC_FLAG_GDATA(带写溢出检查)
*   block_size:块大小
*   init_block_num:初始块个数(这个应是grow_block_num的倍数,如果小于grow_block_num,会被设置为grow_block_num)
*   grow_block_num:池耗尽时,每次增长块个数
*   max_block_num: 最大块数量限制,0为不限制
*/
/* 创建cbp内存池 */
extern yy_f_alloc_t * yy_f_alloc_cbp_create( yy_p_uint32 flag, size_t block_size, size_t init_block_num, size_t grow_block_num, size_t max_block_num, yy_f_alloc_t * alloc_block );

/* 测试用例 */
extern int yy_f_alloc_cbp_validation_test();
#endif
