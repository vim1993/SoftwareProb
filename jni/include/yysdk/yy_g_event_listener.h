#ifndef YY_G_EVENT_LISTENER_H
#define YY_G_EVENT_LISTENER_H
#include "yy_p_thread.h"
#include "yy_p_inet_addr.h"
#include "yy_e_memcheck.h"
#include "yy_f_reactor.h"

/* �����ĵ�ַ���� */
#define YY_G_EVENT_LISTEN_NUM 64
#define YY_G_EVENT_LISTEN_THREAD_NUM 8      //�������8���߳�

/* �����ص����� */
typedef void (*yy_g_event_listen_cb_t)(yy_p_socket_t listen_s, const yy_p_inet_addr_t * listen_addr, void * user_data, int type );

/* Ԥ�ȶ���ṹ�壬��ֹ����ʱwarnning */
struct yy_g_event_listener_s;

/* listener��ַ�ṹ�� */
typedef struct yy_g_event_listener_addr_s{
    YY_E_MEM_MAGIC_PREFIX_DEFINE;
    struct yy_g_event_listener_s *el;		/* listener���ṹ�� */
    size_t index;							/* ���� */
    yy_p_socket_t s;						/* �׽ӿ� */
    yy_p_inet_addr_t addr;					/* ip��ַ */	
    
    yy_f_event_handler_t *ev_read[YY_G_EVENT_LISTEN_THREAD_NUM];	/* �ɶ��¼������� */
    int type;							/* ���� */
    YY_E_MEM_MAGIC_SUFFIX_DEFINE;
}yy_g_event_listener_addr_t;

/* �̳߳�ʼ���ṹ�� */
typedef struct yy_g_event_listener_thread_arg_s{
     struct yy_g_event_listener_s *el;		/* �̲߳��� */
     size_t thread_index;					/* �߳����� */
}yy_g_event_listener_thread_arg_t;

/* �׽ӿڵ�ַ״̬�ṹ�� */
typedef struct yy_g_event_listener_addr_stat_s{
    volatile size_t event_num;				/* ������¼��� */
    yy_p_inet_addr_t addr;					/* socket��ַ */
}yy_g_event_listener_addr_stat_t;

/* listener״̬�ṹ�� */
typedef struct yy_g_event_listener_stat_s{
    volatile time_t alive_time;				/* ��Ծʱ�� */
    volatile size_t event_num;				/* �¼��� */
    yy_g_event_listener_addr_stat_t addr_stat[YY_G_EVENT_LISTEN_NUM];	/* socket��ַ */
}yy_g_event_listener_stat_t;

/* listener��ʼ������ */
typedef struct yy_g_event_listener_create_arg_s{
    yy_f_alloc_t *alloc;				/* �ڴ������ */
    void *user_data;					/* �û��Զ������� */
    yy_g_event_listen_cb_t f_event_listen;	/* �����ص����� */
    int backlog;					/* */
    size_t thread_num;          //�߳���������LISTEN��
}yy_g_event_listener_create_arg_t;


typedef struct yy_g_event_listener_thread_s{
    struct yy_g_event_listener_s *el;	/* listener�ṹ�� */
    size_t thread_index;				/* �߳����� */
    yy_p_thr_id_t thr_id;				/* �߳�id */	
    yy_p_thr_handle_t thr_handle;		/* �߳̾�� */
     yy_f_reactor_t * r;				/* ��Ӧ�� */
     yy_f_event_handler_t *ev_timer;	/* ��ʱ�������� */
}yy_g_event_listener_thread_t;

/* listener���ṹ�� */
typedef struct yy_g_event_listener_s{
    YY_E_MEM_MAGIC_PREFIX_DEFINE;
    yy_f_alloc_t *alloc;			/* �ڴ������ */
    void *user_data;				/* �û��Զ������� */
    yy_g_event_listen_cb_t f_event_listen;	/* �����ص����� */
    int backlog;					/* �������г��� */
    size_t thread_num;
    yy_g_event_listener_stat_t stat;	/* listener״̬�ṹ�� */

    
    yy_g_event_listener_thread_t threads[YY_G_EVENT_LISTEN_THREAD_NUM];	/* �߳� */

  /*  yy_p_thr_id_t thr_id[YY_G_EVENT_LISTEN_THREAD_NUM];
    yy_p_thr_handle_t thr_handle[YY_G_EVENT_LISTEN_THREAD_NUM];
    yy_f_reactor_t * r[YY_G_EVENT_LISTEN_THREAD_NUM];
    yy_f_event_handler_t *ev_timer[YY_G_EVENT_LISTEN_THREAD_NUM];*/
   
    yy_g_event_listener_addr_t listens[YY_G_EVENT_LISTEN_NUM];	/* ������ַ���� */
    YY_E_MEM_MAGIC_SUFFIX_DEFINE;
}yy_g_event_listener_t;

/* ����listener��������ṹ */
extern yy_g_event_listener_t * yy_g_event_listener_create( yy_g_event_listener_create_arg_t * arg );

/* �ݻ�listener�ṹ��  */
extern void yy_g_event_listener_destroy( yy_g_event_listener_t * el );

/* ����listener���̣߳��÷�Ӧ��ѭ����ʱ�����������׽ӿ����� */
extern int yy_g_event_listener_begin_thread( yy_g_event_listener_t * el );

/* ����listener���̣߳��رշ�Ӧ�� */
extern int yy_g_event_listener_end_thread( yy_g_event_listener_t * el );

/* ���listener�������׽ӿڣ������׽ӿ����óɷ��������󶨣�������ͬʱ���׽ӿڿɶ� */
extern int yy_g_event_listener_add_listen( yy_g_event_listener_t * el, yy_p_inet_addr_t * addr, int type );

/* ��ȡlistener��״̬ */
extern void yy_g_event_listener_stat( yy_g_event_listener_t * el, yy_g_event_listener_stat_t * stat );
#endif
