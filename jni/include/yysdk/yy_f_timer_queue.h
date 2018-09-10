#ifndef YY_F_TIMER_QUEUE_H
#define YY_F_TIMER_QUEUE_H
#include "yy_p_type.h"
#include "yy_p_time.h"
#include "yy_e_memcheck.h"
#include "yy_e_time.h"
#include "yy_f_alloc.h"

/*
*��ʱ�����У��ɶ�ʵ�֣����ɴ�ʵ�ַ�Ӧ���еĶ�ʱ��
*added by gaoqiang, 2015-08-03
*/

/* ��ACE�ο�,�� */

typedef size_t yy_f_timer_id_t;				/* ��ʱ��id  */
#define YY_F_INVALID_TIMERID ((size_t)-1)	/* ��Ч��ʱ��ID */
#define YY_F_PRI_TIMERID YY_P_PRI_SIZE_T		/* ��ӡ�����ʱ��IDʱʹ�õĸ�ʽ�� */

typedef struct yy_f_timer_queue_stat_s{
    size_t add_timer_count;				
    size_t cancel_timer_count;				
    size_t slow_timer_count;
    size_t expire_timer_count;
}yy_f_timer_queue_stat_t;

/* ��ʱ���ṹ�� */
typedef struct yy_f_timer_queue_timer_s{
	YY_E_MEM_MAGIC_PREFIX_DEFINE;
	yy_p_timeval_t interval_tv;			/* ��ʱ���ʱ�� */ 
	yy_p_timeval_t expire_tv;			/* ����ʱ�� */
	void * data;						/* �Զ������� */
	size_t heap_index;					/* ��ʱ���ڶ��е����� */
	YY_E_MEM_MAGIC_SUFFIX_DEFINE;
}yy_f_timer_queue_timer_t;

/* ��ʱ�����нṹ�� */
typedef struct yy_f_timer_queue_s{
    yy_f_alloc_t *alloc_thiz;			/* �ڴ������ */
	size_t * heap_array;				/* �����Ķѽṹ */
	yy_f_timer_queue_timer_t *timer_array;	/* ��ʱ������ */

	size_t malloced_node_num;			/* �ѷ��䶨ʱ����Ŀ */
	size_t used_node_num;				/* ��ʹ�ö�ʱ����Ŀ */
	size_t init_node_num;				/* ��ʼ����ʱ����Ŀ */
	size_t max_node_num;				/* ���ʱ����Ŀ */

	size_t free_timer_id;				/* ���ж�ʱ��id */

	yy_p_timeval_t last_tv;			/* ��ʱ������ʱ�����һ�ζ�ʱ������ʱ�䣨����ϵͳʱ����ģ� */

    yy_f_timer_queue_stat_t stat;		/* ����״̬ͳ�� */

}yy_f_timer_queue_t;

/* ������ʱ������ */
extern yy_f_timer_queue_t * yy_f_timer_queue_create( yy_f_alloc_t *alloc_thiz, size_t init_node_num, size_t max_node_num, const yy_p_timeval_t * now_tv ); 

/* ���ٶ�ʱ������ */
extern void yy_f_timer_queue_destroy( yy_f_timer_queue_t * q );

/* ����ʱ����������� */
extern yy_f_timer_id_t yy_f_timer_queue_schedule_timer( yy_f_timer_queue_t * q, void * data, const yy_p_timeval_t * now_tv, const yy_p_timeval_t * interval_tv );

/* ���䶨ʱ������ */
extern int yy_f_timer_queue_reserve( yy_f_timer_queue_t * q, size_t more_size );

/* ȡ����ʱ�� */
extern void yy_f_timer_queue_cancel_timer( yy_f_timer_queue_t * q, yy_f_timer_id_t timer_id, const void * data );

/* ��ȡ��ʱ��������Ŀ */
extern size_t yy_f_timer_queue_size( const yy_f_timer_queue_t * q );

/* ��ȡһ����ʱ��ʱ�� */
extern int yy_f_timer_queue_get_expire_timer( yy_f_timer_queue_t * q, void ** pdata, const yy_p_timeval_t * now_tv,  yy_p_timeval_t * near_tv );

/* ��ϵͳ�޸��˵�ǰʱ�䣬���Զ����ж�ʱ�������� */
extern void yy_f_timer_queue_correct_time( yy_f_timer_queue_t * q, const yy_p_timeval_t * now_tv );

//��ȡ��ʱ����ͳ����Ϣ
extern void yy_f_timer_queue_stat( yy_f_timer_queue_t * q, yy_f_timer_queue_stat_t * stat );

/* �������� */
extern int yy_f_timer_queue_validation_test_test(void);
#endif
