#ifndef YY_F_BUFFER_H
#define YY_F_BUFFER_H
#include "yy_f_alloc.h"

/*
*������ʵ��
*added by gaoqiang, 2015-06-25
*/

/* �������ṹ���� */
typedef struct yy_f_buffer_s{
    yy_f_alloc_t * alloc_data;	/* ���仺�������ڴ������ */
    char * data_ptr;			/* ��������ʼ��ַ */


    size_t pos;				/* дָ��λ�ã�0~N */
    size_t size;				/* ��������С */

    YY_E_OBJ_MAGIC_DEFINE;
}yy_f_buffer_t;

/* ��������ʼ�� */
extern int yy_f_buffer_init( yy_f_buffer_t * buf, yy_f_alloc_t * alloc_data, size_t size );

/* ��������Դ�ͷ� */
extern int yy_f_buffer_uninit( yy_f_buffer_t * buf );

/* ��ȡ���������ݳ��� */
extern size_t yy_f_buffer_data_len( yy_f_buffer_t * buf );

/* ��ȡ������ʣ��ռ��С */
extern size_t yy_f_buffer_space_len( yy_f_buffer_t * buf );

/* ��ȡ�������ܿռ��С */
extern size_t yy_f_buffer_buf_size( yy_f_buffer_t * buf );

/* ������������С���µĻ�������С����С�ڵ�ǰ�����������ݴ�С */
extern int yy_f_buffer_resize( yy_f_buffer_t * buf, size_t new_size );

/* ������������ǰ��һ������ */
extern int yy_f_buffer_drop( yy_f_buffer_t * buf, size_t drop_size );

/* δʵ�� */
extern void yy_f_buffer_truncate( yy_f_buffer_t * buf );

/* ��ȡ������дָ��λ�� */
extern char * yy_f_buffer_data_ptr( yy_f_buffer_t * buf );

/* ��ȡ��������ָ��λ�� */
extern char * yy_f_buffer_buf_ptr( yy_f_buffer_t * buf );
extern void yy_f_buffer_set_data_len( yy_f_buffer_t * buf, size_t data_len );

/* ����дָ��λ�� */
extern void yy_f_buffer_data_pos_add( yy_f_buffer_t * buf, size_t pos );


#endif
