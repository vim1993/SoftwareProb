#ifndef YY_F_ALLOC_STAT_H
#define YY_F_ALLOC_STAT_H
#include "yy_f_alloc.h"

/**
*   ��װĳ�����͵��ڴ����������ӷ����ͷ�ͳ�ƺͻص�����
*	added by gaoqiang, 2015-06-16
*/


/* �ص������� ���ڷ���ɹ���ʧ��ʱ��Ϣ�ص� */
typedef void (*yy_f_alloc_stat_malloc_cb_t)(yy_f_alloc_t *alloc, void * p, size_t size);

/* �ص������������ⲿ�����ӡ����Ϣ */
typedef void (*yy_f_alloc_stat_free_cb_t)(yy_f_alloc_t *alloc, void * p);

/* ��ʼ��ͳ�ƽṹ�� */
extern yy_f_alloc_t * yy_f_alloc_stat_create( yy_p_uint32 flag,  yy_f_alloc_t * alloc_ori );

/* ����ͳ�ƵĻص� (���̰߳�ȫ�������ڴ������������ã����������ٸ��� )*/
extern void yy_f_alloc_stat_set_malloc_free_cb( yy_f_alloc_t *alloc, yy_f_alloc_stat_malloc_cb_t f_malloc, yy_f_alloc_stat_free_cb_t f_free );

#endif
