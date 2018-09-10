#ifndef YY_S_LIST_H
#define YY_S_LIST_H
#include "yy_f_alloc.h"
/**
*   ���˼��ο���LINUX LIST,�ӿڲο�STL
*   ÿһ�������Ҫ����ָ���С�Ŀռ�,���ڴ洢�������
*/


/* �������ݽ���ַ��nΪ�����㣨��������������ڵ��ڴ�飩 */
#define YY_S_LIST_DATA_PTR( n ) (void *)((char *)(n)+sizeof(yy_s_list_node_t) )

typedef struct yy_s_list_node_s{
    struct yy_s_list_node_s * prev;
    struct yy_s_list_node_s * next;
}yy_s_list_node_t;

typedef struct yy_s_list_s{
    YY_E_MEM_MAGIC_PREFIX_DEFINE;
    yy_f_alloc_t * alloc_thiz;			/* ���ṹ���ڴ������ */
    yy_f_alloc_t * alloc_list_node;		/* �������ڴ������ */
    yy_s_list_node_t head;				/* ����ͷ */
    size_t node_data_len;               /* ÿ�������������ݳ��� */
    size_t node_size_aligned;           /* �ڴ�������������С */
    size_t max_node_num;				/* ������������� */
    size_t used_node_num;				/* ��ǰ���������� */
    YY_E_MEM_MAGIC_SUFFIX_DEFINE;
}yy_s_list_t;

/* �ص�������������ȽϺ��� */
typedef int (*yy_s_list_node_sort_cmp_t)( yy_s_list_t * l, yy_s_list_node_t * left, yy_s_list_node_t * right );

/* �������� */
extern yy_s_list_t * yy_s_list_create( size_t max_node_num, size_t data_len, yy_f_alloc_t * alloc_list_node, yy_f_alloc_t * alloc_thiz );

/* �������� */
extern void yy_s_list_destroy( yy_s_list_t * l );

/* �����¡ */
extern yy_s_list_t * yy_s_list_clone( yy_s_list_t * l );

/* ������������ */
extern size_t yy_s_list_size( yy_s_list_t * l );

/* ɾ����� */
extern yy_s_list_node_t * yy_s_list_erase( yy_s_list_t * l, yy_s_list_node_t * n );

/* ʹ��ָ���ȽϺ����������������� */
extern void yy_s_list_sort( yy_s_list_t * l, yy_s_list_node_sort_cmp_t func_cmp );

/* �����루�����ڻ�Ϊdata_in�����ڴ棩 */
extern yy_s_list_node_t * yy_s_list_push_back(  yy_s_list_t * l, const void * data_in );

/* �����룬ָ�����ݳ��ȣ������ڻ�Ϊdata_in�����ڴ棩 */
extern yy_s_list_node_t * yy_s_list_push_back2(  yy_s_list_t * l, const void * data_in, size_t in_len );

/* �����룬ָ�����ݳ��ȣ��������Ϊ�ַ����������ڻ�Ϊdata_in�����ڴ棩 */
extern yy_s_list_node_t * yy_s_list_push_back3(  yy_s_list_t * l, const void * data_in, size_t in_len );

/* ������ݳ��� */
extern size_t yy_s_list_data_len( yy_s_list_t * l );

/* ɾ������ͷ��㣨�Ƚ��ȳ��� */
extern void yy_s_list_pop_front( yy_s_list_t * l );

/* ����n����ǰһ����� */
extern yy_s_list_node_t * yy_s_list_prev( yy_s_list_t * l, yy_s_list_node_t * n );

/* ����n������һ����� */
extern yy_s_list_node_t * yy_s_list_next( yy_s_list_t * l, yy_s_list_node_t * n );

/* ���ص�һ����� */
extern yy_s_list_node_t * yy_s_list_first( yy_s_list_t * l );

/* �������һ����� */
extern yy_s_list_node_t * yy_s_list_last( yy_s_list_t * l );

/* �������һ����� */
extern yy_s_list_node_t * yy_s_list_rand( yy_s_list_t * l );

/* ɾ�����н�� */
extern void yy_s_list_clear( yy_s_list_t * l );

/* ���ؽ�����ݵ�ַ */
extern void * yy_s_list_data_ptr( yy_s_list_t *l, yy_s_list_node_t * n );

/* �ӽ���ȡ���ݣ�д��data_out */
extern int yy_s_list_read_data( yy_s_list_t *l, yy_s_list_node_t * n, void * data_out );

/* ����д���� */
extern int yy_s_list_write_data( yy_s_list_t *l, yy_s_list_node_t * n, const void * data_in );

extern int yy_s_list_validation_test();
#endif
