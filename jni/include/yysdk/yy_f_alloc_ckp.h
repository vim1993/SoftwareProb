#ifndef YY_F_ALLOC_CKP_H
#define YY_F_ALLOC_CKP_H
#include "yy_f_alloc.h"
/**
*   ������ʺ�С���ڴ����,���ǽ�node_size��С��С��,һ������chunk_size��С������
*   һ��node_size��С��1KB��С��,chunk-size�Ǵ���128KB������
*/

/*
*���ڴ�ص�ʵ��ԭ��Ϊ������һ����飬��黮��ΪN��С�飬��С�������û�
*added by gaoqiang, 2015-06-11
*/

/**
*   flag:֧��,YY_F_ALLOC_FLAG_LOCK(����),YY_F_ALLOC_FLAG_GDATA(��д������)
*   node_size:С��Ƭ�Ĵ�С
*   chunk_size:���С,��Ƭ���Ƿֿ��з���
*   init_chunk_num:��ʼ������
*   max_chunk_num: ��������
*   alloc_chunk: �������
*/
/* ����ckp�ڴ�� */
extern yy_f_alloc_t * yy_f_alloc_ckp_create( yy_p_uint32 flag, size_t node_size, size_t chunk_size, size_t init_chunk_num, size_t max_chunk_num,  yy_f_alloc_t * alloc_chunk );

/* �������� */
extern int yy_f_alloc_ckp_validation_test();
#endif
