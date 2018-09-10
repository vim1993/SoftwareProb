#ifndef YY_F_ALLOC_SSP_H
#define YY_F_ALLOC_SSP_H
#include "yy_f_alloc.h"

/*
*���ڴ��ʵ��ԭ���ó�ʵ�������ڴ���飬��������ӳأ�ÿ���ӳ���ckp��ʵ��
*ckp�ص�ԭ������һ����飬��黮��ΪN��С�飬��С�������û�
*added by gaoqiang, 2015-06-19
*/

/* �ش������� */
typedef struct yy_f_alloc_ssp_init_s{    
    size_t node_size;		/* ��㣨�����Ϊ���������ڴ��Ƭ����С */
    size_t chunk_size;		/* ���С������������ */
    size_t init_chunk_num;	/* ��ʼ���� */
    size_t grow_chunk_num;	/* �����ڴ��ʱ��ÿ�������Ŀ��� */
    size_t max_chunk_num;	/* ���������� */
    yy_f_alloc_t * alloc_chunk;	/* ������� */
}yy_f_alloc_ssp_init_t;

/* ����ssp�ڴ�� */
extern yy_f_alloc_t * yy_f_alloc_ssp_create( yy_p_uint32 flag, const yy_f_alloc_ssp_init_t * ssp_init, size_t ssp_init_num, yy_f_alloc_t * alloc_large, size_t large_alignment );

/* �������� */
extern int yy_f_alloc_ssp_validation_test();
#endif
