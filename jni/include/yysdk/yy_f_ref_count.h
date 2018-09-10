#ifndef YY_F_REF_COUNT_H
#define YY_F_REF_COUNT_H
#include "yy_p_type.h"
#include "yy_p_thread.h"
#include "yy_p_test.h"
#include "yy_e_memcheck.h"

/*
*���ü�������Ҫ���ڶԶ��ģ����̹߳�������ݽ������ü���
*added by gaoqiang, 2015-07-29
*/
typedef struct yy_f_ref_count_s{
    YY_E_MEM_MAGIC_PREFIX_DEFINE;
    YY_E_OBJ_MAGIC_DEFINE;
    yy_p_thr_mutex_t lock;		/* ��д�� */
    int ref_count;			/* ���ü���ֵ */
    
    YY_E_MEM_MAGIC_SUFFIX_DEFINE;
}yy_f_ref_count_t;

/* ��ʼ�����ü��� */
extern int yy_f_ref_count_init( yy_f_ref_count_t * ref, int is_use_lock );

/* uninit���ü��� */
extern int yy_f_ref_count_uninit( yy_f_ref_count_t * ref );

/* �������ü��� */
extern int yy_f_ref_count_add_ref( yy_f_ref_count_t * ref );

/* �������ü��� */
extern int yy_f_ref_count_release_ref( yy_f_ref_count_t * ref );

/* ��ȡ��ǰ���ü��� */
extern int yy_f_ref_count_get_count( yy_f_ref_count_t * ref );

/* �������� */
extern int yy_f_ref_count_validation_test();
#endif
