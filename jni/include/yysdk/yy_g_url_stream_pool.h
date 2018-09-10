/* ���ļ�����ʵ�ּ򵥵�http������أ������пɱ��ֶ��http���� */
#ifndef YY_G_URL_STREAM_POOL_H
#define YY_G_URL_STREAM_POOL_H
#include "yy_g_url_stream.h"
#include "yy_s_list.h"
#include "yy_p_thread.h"

/* http������ؽṹ�� */
typedef struct yy_g_url_stream_pool_s{
	YY_E_MEM_MAGIC_PREFIX_DEFINE;
    yy_f_alloc_t * alloc;					/* �ڴ������ */
	yy_p_thr_mutex_t lock;					/* ������ */
	size_t max_us_count;					/* �������֧�ֵ�http���������� */
	//����
    yy_s_list_t * list_run;					/* ���ڴ����http�������� */
    yy_s_list_t * list_delete;				/* �ȴ�ɾ����http�������� */
	YY_E_MEM_MAGIC_SUFFIX_DEFINE;
}yy_g_url_stream_pool_t;

/* ����http������� */
extern yy_g_url_stream_pool_t * yy_g_url_stream_pool_create( yy_f_alloc_t * alloc, size_t max_us_count );
/* ����http������� */
extern void yy_g_url_stream_pool_destroy( yy_g_url_stream_pool_t *usp );
//��ʱ����,���ڴ���ɾ��,��ʱ�ͷŵ��߼�
/* ��ʱ���������ɷ�Ӧ���������������http�������� */
extern void yy_g_url_stream_pool_timer( yy_g_url_stream_pool_t *usp );
/* �ӳ��л�ȡһ����㣬���ڴ����µ�http���� */
extern yy_g_url_stream_t * yy_g_url_stream_pool_get_us( yy_g_url_stream_pool_t *usp, yy_f_reactor_t * r, yy_g_url_stream_state_cb_t f_state_cb, void * user_data);
/* �ӳ��в��������㣬������ӵ��ȴ�ɾ������������ */
extern void yy_g_url_stream_pool_return_us( yy_g_url_stream_pool_t *usp, yy_g_url_stream_t * us );
/* �ж�http��������Ƿ��������������ٽ��������� */
extern int yy_g_url_stream_pool_is_full( yy_g_url_stream_pool_t *usp );
/* ��ȡ���ڴ����http������ */
extern size_t yy_g_url_stream_pool_get_run_us_count( yy_g_url_stream_pool_t *usp );
/* ��ȡ������ӵ�http�������� */
extern size_t yy_g_url_stream_pool_get_idle_us_count( yy_g_url_stream_pool_t *usp );
#endif
