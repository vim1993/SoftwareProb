#ifndef YY_F_MESSAGE_BLOCK_H
#define YY_F_MESSAGE_BLOCK_H
#include "yy_f_data_block.h"
#include "yy_s_lxlist.h"

/*
*本模块用于创建缓存块（或称作消息块），主要用于从其它模块接收数据或向其它模块发送数据时，如：套接口读写缓存
*added by gaoqiang, 2015-07-23
*/
typedef struct yy_f_message_block_s{
    YY_E_MEM_MAGIC_PREFIX_DEFINE;
    yy_s_lxlist_head_t list_mq;		/* 消息块链表头 */
    int type;					/* 类型，目前未使用 */
    yy_f_alloc_t * alloc_mb;		/* 消息块的内存分配器 */
    struct yy_f_message_block_s *cont;/* 指向下一个消息块 */
    yy_f_data_block_t * db;		/* 分配消息块内存使用的数据块 */

    size_t rd_pos;				/* 消息块读指针 */
    size_t wr_pos;				/* 消息块写指针 */
    //为了加速
    char * db_base;				/* 消息块起始地址 */
    size_t db_size;				/* 消息块大小 */
    YY_E_MEM_MAGIC_SUFFIX_DEFINE;
}yy_f_message_block_t;

/* 创建消息块（常用于套接口接收、发送缓存） */
extern yy_f_message_block_t * yy_f_message_block_create( size_t size, yy_f_alloc_t * alloc_mb, yy_f_alloc_t * alloc_db, yy_f_alloc_t * alloc_buf, yy_p_thr_mutex_t * locking_strategy );

/* 释放消息块 */
extern void yy_f_message_block_release( yy_f_message_block_t * mb );

/* 克隆消息块 */
extern yy_f_message_block_t * yy_f_message_block_clone( yy_f_message_block_t * mb );

/* 创建新消息块，但共用同一数据区 */
extern yy_f_message_block_t * yy_f_message_block_duplicate( yy_f_message_block_t * mb );

/* 获取下一个消息块 */
extern yy_f_message_block_t * yy_f_message_block_get_cont( yy_f_message_block_t * mb );

/* 设置下一个消息块 */
extern void yy_f_message_block_set_cont( yy_f_message_block_t * mb, yy_f_message_block_t * mb_cont );

/* 获取消息块中数据长度 */
extern size_t yy_f_message_block_length( yy_f_message_block_t * mb );

/* 获取消息块总空间大小 */
extern size_t yy_f_message_block_size( yy_f_message_block_t * mb );

/* 获取消息块剩余空间大小 */
extern size_t yy_f_message_block_space( yy_f_message_block_t * mb );

/* 获取链表中所有消息块的数据长度之和 */
extern size_t yy_f_message_block_total_length( yy_f_message_block_t * mb );

/* 获取链表中所有消息块的总空间大小 */
extern size_t yy_f_message_block_total_size( yy_f_message_block_t * mb );

/* 写数据到消息块 */
extern int yy_f_message_block_write( yy_f_message_block_t * mb, const void * data, size_t len );

/* 从消息块读数据 */
extern int yy_f_message_block_read( yy_f_message_block_t * mb, void * data, size_t len );

/* 从消息块读数据，但不修改读指针位置 */
extern int yy_f_message_block_peek( yy_f_message_block_t * mb, void * data, size_t len );

/* 获取数据缓存区基指针 */
extern char * yy_f_message_block_base_ptr( yy_f_message_block_t * mb );

/* 获取消息块读指针 */
extern char * yy_f_message_block_rd_ptr( yy_f_message_block_t * mb );

/* 获取消息块读位置(相对于起始地址) */
extern size_t yy_f_message_block_rd_pos( yy_f_message_block_t * mb );

/* 增加消息块读位置 */
extern size_t yy_f_message_block_rd_pos_add( yy_f_message_block_t * mb, size_t len );

/* 设置消息块读位置(相对于起始地址) */
extern size_t yy_f_message_block_set_rd_pos( yy_f_message_block_t * mb, size_t pos );

/* 获取消息块读位置(相对于起始地址) */
extern size_t yy_f_message_block_get_rd_pos( yy_f_message_block_t * mb );

/* 获取消息块写指针 */
extern char * yy_f_message_block_wr_ptr( yy_f_message_block_t * mb );

/* 获取消息块写位置（相对于起始地址） */
extern size_t yy_f_message_block_wr_pos( yy_f_message_block_t * mb );

/* 增加消息块写位置 */
extern size_t yy_f_message_block_wr_pos_add( yy_f_message_block_t * mb, size_t len );

/* 设置写位置（相对于起始地址） */
extern size_t yy_f_message_block_set_wr_pos( yy_f_message_block_t * mb, size_t pos );

/* 获取写位置（相对于起始地址） */
extern size_t yy_f_message_block_get_wr_pos( yy_f_message_block_t * mb );

/* 重置读写位置 */
extern void yy_f_message_block_reset_pos( yy_f_message_block_t * mb );

/* 紧缩消息块空间 */
extern int yy_f_message_block_truncate( yy_f_message_block_t * mb );

/* 测试用例 */
extern int yy_f_message_block_validation_test();

#endif
