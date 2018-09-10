#ifndef YY_F_MESSAGE_QUEUE_H
#define YY_F_MESSAGE_QUEUE_H
#include "yy_f_message_block.h"
#include "yy_s_lxlist.h"

/*
*实现思想：使用消息块（yy_f_message_block)和链表构造队列（先进先出），分别实现从头和尾入队、从头和尾出队 
*added by gaoqiang, 2015-07-29
*/
typedef struct yy_f_message_queue_s{
    YY_E_MEM_MAGIC_PREFIX_DEFINE;
    yy_f_alloc_t *alloc_thiz;			/* 本结构内存分配器 */
    yy_p_thr_mutex_t lock;				/* 锁 */
    size_t water_mark_message_count;	/* 消息队列中最大消息块个数 */
    size_t water_mark_message_bytes;	/* 消息队列能容纳的最大字节数 */
    yy_s_lxlist_head_t mb_list;			/* 消息块链表（以链表实现队列） */
    size_t cur_message_count;			/* 当前消息块个数 */
    size_t cur_message_bytes;			/* 当前消息队列总字节大小 */
    YY_E_MEM_MAGIC_SUFFIX_DEFINE;
}yy_f_message_queue_t;

/* 创建消息队列 */
extern yy_f_message_queue_t * yy_f_message_queue_create( yy_f_alloc_t *alloc_thiz, int is_use_lock );

/* 销毁消息队列 */
extern void yy_f_message_queue_destroy( yy_f_message_queue_t * mq );

/* 清除消息队列中所有消息块，但是保留消息队列结构本身 */
extern int yy_f_message_queue_flush( yy_f_message_queue_t * mq );

/* 获取消息队列中消息块个数 */
extern size_t yy_f_message_queue_count( yy_f_message_queue_t * mq );

/* 获取消息队列中消息长度 */
extern size_t yy_f_message_queue_length( yy_f_message_queue_t * mq );

/* 设置消息队列的最大消息块数量和最大消息数（字节表示） */
extern void yy_f_message_queue_set_water_mark( yy_f_message_queue_t * mq, size_t bytes, size_t count );

/* 从消息队列头部插入消息队块 */
extern int yy_f_message_queue_enqueue_head( yy_f_message_queue_t * mq, yy_f_message_block_t * mb );

/* 从消息队列尾部插入消息块 */
extern int yy_f_message_queue_enqueue_tail( yy_f_message_queue_t * mq, yy_f_message_block_t * mb );

/* 从消息队列头将第一个消息块出队 */
extern int yy_f_message_queue_dequeue_head( yy_f_message_queue_t * mq, yy_f_message_block_t ** mb );

/* 从消息队列尾将第一个消息块出队 */
extern int yy_f_message_queue_dequeue_tail( yy_f_message_queue_t * mq, yy_f_message_block_t ** mb );

/* 测试用例 */
extern int yy_f_message_queue_validation_test();

#endif
