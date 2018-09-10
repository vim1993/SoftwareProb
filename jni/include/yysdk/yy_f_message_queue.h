#ifndef YY_F_MESSAGE_QUEUE_H
#define YY_F_MESSAGE_QUEUE_H
#include "yy_f_message_block.h"
#include "yy_s_lxlist.h"

/*
*ʵ��˼�룺ʹ����Ϣ�飨yy_f_message_block)����������У��Ƚ��ȳ������ֱ�ʵ�ִ�ͷ��β��ӡ���ͷ��β���� 
*added by gaoqiang, 2015-07-29
*/
typedef struct yy_f_message_queue_s{
    YY_E_MEM_MAGIC_PREFIX_DEFINE;
    yy_f_alloc_t *alloc_thiz;			/* ���ṹ�ڴ������ */
    yy_p_thr_mutex_t lock;				/* �� */
    size_t water_mark_message_count;	/* ��Ϣ�����������Ϣ����� */
    size_t water_mark_message_bytes;	/* ��Ϣ���������ɵ�����ֽ��� */
    yy_s_lxlist_head_t mb_list;			/* ��Ϣ������������ʵ�ֶ��У� */
    size_t cur_message_count;			/* ��ǰ��Ϣ����� */
    size_t cur_message_bytes;			/* ��ǰ��Ϣ�������ֽڴ�С */
    YY_E_MEM_MAGIC_SUFFIX_DEFINE;
}yy_f_message_queue_t;

/* ������Ϣ���� */
extern yy_f_message_queue_t * yy_f_message_queue_create( yy_f_alloc_t *alloc_thiz, int is_use_lock );

/* ������Ϣ���� */
extern void yy_f_message_queue_destroy( yy_f_message_queue_t * mq );

/* �����Ϣ������������Ϣ�飬���Ǳ�����Ϣ���нṹ���� */
extern int yy_f_message_queue_flush( yy_f_message_queue_t * mq );

/* ��ȡ��Ϣ��������Ϣ����� */
extern size_t yy_f_message_queue_count( yy_f_message_queue_t * mq );

/* ��ȡ��Ϣ��������Ϣ���� */
extern size_t yy_f_message_queue_length( yy_f_message_queue_t * mq );

/* ������Ϣ���е������Ϣ�������������Ϣ�����ֽڱ�ʾ�� */
extern void yy_f_message_queue_set_water_mark( yy_f_message_queue_t * mq, size_t bytes, size_t count );

/* ����Ϣ����ͷ��������Ϣ�ӿ� */
extern int yy_f_message_queue_enqueue_head( yy_f_message_queue_t * mq, yy_f_message_block_t * mb );

/* ����Ϣ����β��������Ϣ�� */
extern int yy_f_message_queue_enqueue_tail( yy_f_message_queue_t * mq, yy_f_message_block_t * mb );

/* ����Ϣ����ͷ����һ����Ϣ����� */
extern int yy_f_message_queue_dequeue_head( yy_f_message_queue_t * mq, yy_f_message_block_t ** mb );

/* ����Ϣ����β����һ����Ϣ����� */
extern int yy_f_message_queue_dequeue_tail( yy_f_message_queue_t * mq, yy_f_message_block_t ** mb );

/* �������� */
extern int yy_f_message_queue_validation_test();

#endif
