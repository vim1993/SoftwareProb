#ifndef YY_F_MESSAGE_BLOCK_H
#define YY_F_MESSAGE_BLOCK_H
#include "yy_f_data_block.h"
#include "yy_s_lxlist.h"

/*
*��ģ�����ڴ�������飨�������Ϣ�飩����Ҫ���ڴ�����ģ��������ݻ�������ģ�鷢������ʱ���磺�׽ӿڶ�д����
*added by gaoqiang, 2015-07-23
*/
typedef struct yy_f_message_block_s{
    YY_E_MEM_MAGIC_PREFIX_DEFINE;
    yy_s_lxlist_head_t list_mq;		/* ��Ϣ������ͷ */
    int type;					/* ���ͣ�Ŀǰδʹ�� */
    yy_f_alloc_t * alloc_mb;		/* ��Ϣ����ڴ������ */
    struct yy_f_message_block_s *cont;/* ָ����һ����Ϣ�� */
    yy_f_data_block_t * db;		/* ������Ϣ���ڴ�ʹ�õ����ݿ� */

    size_t rd_pos;				/* ��Ϣ���ָ�� */
    size_t wr_pos;				/* ��Ϣ��дָ�� */
    //Ϊ�˼���
    char * db_base;				/* ��Ϣ����ʼ��ַ */
    size_t db_size;				/* ��Ϣ���С */
    YY_E_MEM_MAGIC_SUFFIX_DEFINE;
}yy_f_message_block_t;

/* ������Ϣ�飨�������׽ӿڽ��ա����ͻ��棩 */
extern yy_f_message_block_t * yy_f_message_block_create( size_t size, yy_f_alloc_t * alloc_mb, yy_f_alloc_t * alloc_db, yy_f_alloc_t * alloc_buf, yy_p_thr_mutex_t * locking_strategy );

/* �ͷ���Ϣ�� */
extern void yy_f_message_block_release( yy_f_message_block_t * mb );

/* ��¡��Ϣ�� */
extern yy_f_message_block_t * yy_f_message_block_clone( yy_f_message_block_t * mb );

/* ��������Ϣ�飬������ͬһ������ */
extern yy_f_message_block_t * yy_f_message_block_duplicate( yy_f_message_block_t * mb );

/* ��ȡ��һ����Ϣ�� */
extern yy_f_message_block_t * yy_f_message_block_get_cont( yy_f_message_block_t * mb );

/* ������һ����Ϣ�� */
extern void yy_f_message_block_set_cont( yy_f_message_block_t * mb, yy_f_message_block_t * mb_cont );

/* ��ȡ��Ϣ�������ݳ��� */
extern size_t yy_f_message_block_length( yy_f_message_block_t * mb );

/* ��ȡ��Ϣ���ܿռ��С */
extern size_t yy_f_message_block_size( yy_f_message_block_t * mb );

/* ��ȡ��Ϣ��ʣ��ռ��С */
extern size_t yy_f_message_block_space( yy_f_message_block_t * mb );

/* ��ȡ������������Ϣ������ݳ���֮�� */
extern size_t yy_f_message_block_total_length( yy_f_message_block_t * mb );

/* ��ȡ������������Ϣ����ܿռ��С */
extern size_t yy_f_message_block_total_size( yy_f_message_block_t * mb );

/* д���ݵ���Ϣ�� */
extern int yy_f_message_block_write( yy_f_message_block_t * mb, const void * data, size_t len );

/* ����Ϣ������� */
extern int yy_f_message_block_read( yy_f_message_block_t * mb, void * data, size_t len );

/* ����Ϣ������ݣ������޸Ķ�ָ��λ�� */
extern int yy_f_message_block_peek( yy_f_message_block_t * mb, void * data, size_t len );

/* ��ȡ���ݻ�������ָ�� */
extern char * yy_f_message_block_base_ptr( yy_f_message_block_t * mb );

/* ��ȡ��Ϣ���ָ�� */
extern char * yy_f_message_block_rd_ptr( yy_f_message_block_t * mb );

/* ��ȡ��Ϣ���λ��(�������ʼ��ַ) */
extern size_t yy_f_message_block_rd_pos( yy_f_message_block_t * mb );

/* ������Ϣ���λ�� */
extern size_t yy_f_message_block_rd_pos_add( yy_f_message_block_t * mb, size_t len );

/* ������Ϣ���λ��(�������ʼ��ַ) */
extern size_t yy_f_message_block_set_rd_pos( yy_f_message_block_t * mb, size_t pos );

/* ��ȡ��Ϣ���λ��(�������ʼ��ַ) */
extern size_t yy_f_message_block_get_rd_pos( yy_f_message_block_t * mb );

/* ��ȡ��Ϣ��дָ�� */
extern char * yy_f_message_block_wr_ptr( yy_f_message_block_t * mb );

/* ��ȡ��Ϣ��дλ�ã��������ʼ��ַ�� */
extern size_t yy_f_message_block_wr_pos( yy_f_message_block_t * mb );

/* ������Ϣ��дλ�� */
extern size_t yy_f_message_block_wr_pos_add( yy_f_message_block_t * mb, size_t len );

/* ����дλ�ã��������ʼ��ַ�� */
extern size_t yy_f_message_block_set_wr_pos( yy_f_message_block_t * mb, size_t pos );

/* ��ȡдλ�ã��������ʼ��ַ�� */
extern size_t yy_f_message_block_get_wr_pos( yy_f_message_block_t * mb );

/* ���ö�дλ�� */
extern void yy_f_message_block_reset_pos( yy_f_message_block_t * mb );

/* ������Ϣ��ռ� */
extern int yy_f_message_block_truncate( yy_f_message_block_t * mb );

/* �������� */
extern int yy_f_message_block_validation_test();

#endif
