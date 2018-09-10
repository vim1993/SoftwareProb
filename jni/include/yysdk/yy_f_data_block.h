#ifndef YY_F_DATA_BLOCK_H
#define YY_F_DATA_BLOCK_H
#include "yy_p_thread.h"
#include "yy_f_alloc.h"
/*
*���ݿ�ʵ��
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

/* �������ݿ� */
extern yy_f_data_block_t * yy_f_data_block_create( size_t size, yy_f_alloc_t * alloc_db, yy_f_alloc_t * alloc_buf, yy_p_thr_mutex_t * locking_strategy );
/* �ͷ����ݿ飬���ݿ����ü�������Ϊ0ʱ���� */
extern void yy_f_data_block_release( yy_f_data_block_t *db );
/* ��¡���ݿ� */
extern yy_f_data_block_t * yy_f_data_block_clone( yy_f_data_block_t *db );
/* �������ݿ� */
extern yy_f_data_block_t * yy_f_data_block_duplicate( yy_f_data_block_t *db );
/* ��ȡ���ݿ���������ʼ��ַ */
extern char * yy_f_data_block_base( yy_f_data_block_t *db );
/* ��ȡ���ݿ��С */
extern size_t yy_f_data_block_size( yy_f_data_block_t *db );

#endif
