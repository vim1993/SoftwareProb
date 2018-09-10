/*
1.���TCP���ӵ�һ�����̷߳�����,ʵ�ָ��صĶ�̫����
2.���ɲ��ֹ���ģ������˼��.
3.Ŀ���ǻ��ڴ�,�ṩWEB Server/Media Server�����ҵ���ͨ��֧�ֲ�
*/
#ifndef YY_G_EVENT_SERVER_H
#define YY_G_EVENT_SERVER_H
#include "yy_p_type.h"
#include "yy_p_socket.h"
#include "yy_p_thread.h"
#include "yy_e_memcheck.h"
#include "yy_f_reactor.h"
#include "yy_s_list.h"

/*
1.���TCP���ӵ�һ�����̷߳�����,ʵ�ָ��صĶ�̫����
2.���ɲ��ֹ���ģ������˼��.
3.Ŀ���ǻ��ڴ�,�ṩWEB Server/Media Server�����ҵ���ͨ��֧�ֲ�
*/

#define YY_G_EVENT_SERVER_MAX_THREAD_NUM 128

/* �û�����ṹ�壬��Ҫ��listener�������û����󴫹�������Ϣ */
typedef struct yy_g_event_queue_connection_s{
    yy_p_socket_t s;		/* �û�������׽ӿ� */
    int type;			/* �û���������� */
    void * user_data;		/* �û���������� */
	int af_type;
    //int is_delay_accept;        //��������Ѿ�ȡ������������LISTEN���߳���ֱ�ӻ�ȡ�ġ��Ƿ�DELAY ACCEPT���������������ܣ�����ҵ���߳�����
    //yy_p_socket_t listen_s;
	//size_t thread_index;		//ָ���߳̽��з���,��ʱδʵ��
}yy_g_event_queue_connection_t;

/* Ԥ�ȶ��壬��ֹ�������warnning */
struct yy_g_event_server_s;
struct yy_g_event_connection_s;

/* serverһ�������������Ļص����� */
typedef void (*yy_g_event_connection_event_cb_t)( struct yy_g_event_connection_s * ec, int event_type, void * user_data );

/* һ�����ӽṹ�� */
typedef struct yy_g_event_connection_s{
    YY_E_MEM_MAGIC_PREFIX_DEFINE;
    struct yy_g_event_server_s *es;	/* server�ṹ�� */
    yy_p_socket_t s;				/* ���ӵ��׽ӿ� */
    int type;					/* ���ӵ����� */
    yy_f_reactor_t * r;			/* ���ӵķ�Ӧ�� */
    size_t thread_index;			/* �������ڵ��̵߳����� */
    yy_f_event_handler_t * ev_read;	/* �����пɶ��¼������� */
    yy_f_event_handler_t * ev_write;	/* �����п�д�¼������� */
    yy_f_event_handler_t * ev_timer;/* �����ж�ʱ���¼������� */
    //
    yy_g_event_connection_event_cb_t f_event_cb;	/* ����������������Ļص����� */
    void *  user_data;			/* �Զ������� */
    YY_E_MEM_MAGIC_SUFFIX_DEFINE;
}yy_g_event_connection_t;

/* �������͵Ļص�,�ɹ��ص������������������Ĵ�����(yy_g_event_connection_event_cb_t) */
typedef int (*yy_g_event_server_create_connection_success_t)( struct yy_g_event_server_s *es, yy_g_event_queue_connection_t * eqc, yy_g_event_connection_t * ec );
/* ʧ�ܵĻص�,������ĳɹ��ص������෴ */
typedef void (*yy_g_event_server_create_connection_error_t)( struct yy_g_event_server_s *es, yy_g_event_queue_connection_t * eqc, int err );

/* �߳�״̬�ṹ�� */
typedef struct yy_g_event_server_thread_stat_s{
	yy_p_thr_id_t thr_id;		/* �̵߳�id */
	time_t alive_time;			/* �̵߳����»�Ծʱ�� */
	size_t dispath_num;		/* �̵߳�ִ��������� */
	size_t connection_num;		/* �̵߳Ľ��յ����Ӵ��� */
	yy_f_reactor_stat_t r_stat;	/* �̷߳�Ӧ��״̬ */

}yy_g_event_server_thread_stat_t;

/* server״̬�ṹ�� */
typedef struct yy_g_event_server_stat_s{
	size_t create_queue_size;		/* server���г��� */
	size_t dispath_count;			/* �߳�ִ�д��� */
    size_t notify_error_count;		/* notify�Ĵ������ */	
    size_t notify_ok_count;		/* notify����ȷ���� */
	size_t thread_num;				/* �̵߳ĸ��� */
	yy_g_event_server_thread_stat_t t_stat[YY_G_EVENT_SERVER_MAX_THREAD_NUM];	/* �̵߳�״̬�ṹ�� */

}yy_g_event_server_stat_t;

/* �߳̽ṹ�� */
typedef struct yy_g_event_thread_s{    
    size_t index;					/* �߳����� */
    struct yy_g_event_server_s * es;	/* server����ṹ�� */
    //size_t 
    yy_f_reactor_t * r;			/* ��Ӧ�� */
    yy_f_event_handler_t *ev_timer; /* ��pair socket��Ϊ֪ͨ���Ƹ���,��WINDOWSû�������,FT */
    yy_f_event_handler_t *ev_read_notify; /* ����LINUXʹ�õ�֪ͨ���� */
    yy_p_socket_t notify_s[2];		/* �׽ӿ� */
    yy_p_thr_id_t thr_id;			/* �߳�id */
    yy_p_thr_handle_t thr_handle;	/* �߳̾�� */
	
	time_t alive_time;				/* �̻߳�Ծʱ�� */
    size_t dispath_count;			/* �߳�ִ�д��� */
	char buf[64*124];				/* û���ô� */
}yy_g_event_thread_t;

/* server����ṹ�� */
typedef struct yy_g_event_server_s{
    YY_E_MEM_MAGIC_PREFIX_DEFINE;
    yy_f_alloc_t *alloc_thiz;		/* �ṹ����������� */
    yy_f_alloc_t * alloc_conn;		/* ���ڴ���һ�������ڴ������ */
    void * user_data;				/* �����Զ������� */
    size_t thread_num;				/* �̸߳��� */
    size_t max_queue_size;			/* listener��server������list�Ĵ�С */
    size_t max_connection_size;		/* �ܴ������������� */
    yy_g_event_server_create_connection_error_t f_create_error;	/* �����û�����ʧ�ܻص����� */
    yy_g_event_server_create_connection_success_t f_create_success;	/* �����û�����ɹ��ص����� */

    volatile size_t notify_error_count;		/* notify�Ĵ������ */
    volatile size_t notify_ok_count;		/* notify����ȷ���� */

    yy_p_thr_mutex_t lock_create_connection;	/* ������־ */
    yy_s_list_t *list_create_connection;		/* ��������װ���û����� */
    yy_g_event_thread_t * threads;			/* �߳�ָ�� */
    YY_E_MEM_MAGIC_SUFFIX_DEFINE;
}yy_g_event_server_t;

/* server��ʼ���ṹ�� */
typedef struct yy_g_event_server_create_arg_s{
    yy_f_alloc_t *alloc_thiz;				/* �ṹ�������ڴ������ */
    void * user_data;						/* �Զ������� */
    const char * reactor_name;				/* ��Ӧ���ķ�ʽselect or epoll */
    size_t max_reactor_fd_size;				/* ��Ӧ���ܼ����������Ŀ */

    size_t thread_num;						/* �̵߳���Ŀ */
    size_t max_queue_size;					/* listener��server������list�Ĵ�С */
    size_t max_connection_size;				/* �ܴ������������� */
    yy_g_event_server_create_connection_error_t f_create_error;	/* �����û�����ɹ��ص� */
    yy_g_event_server_create_connection_success_t f_create_success;	/* �����û�����ʧ�ܻص� */
}yy_g_event_server_create_arg_t;

/* ����server��������ṹ */
extern yy_g_event_server_t * yy_g_event_server_create( const yy_g_event_server_create_arg_t * arg );

/* �ݻ�server����ṹ */
extern void yy_g_event_server_destroy( yy_g_event_server_t * es );

/* ���û�������eqc��ӵ�es�������У���ѡ��һ�����е��߳� */
extern int yy_g_event_server_queue_create_connection( yy_g_event_server_t * es, const yy_g_event_queue_connection_t * eqc );

/* ��ȡserver�����������(Ҳ����װ���û������list) */
extern size_t yy_g_event_server_queue_create_conn_size( yy_g_event_server_t * es );

/* ���߳�thread_index�д���һ������connection */
extern yy_g_event_connection_t * yy_g_event_server_create_connection_in_thread( yy_g_event_server_t * es, size_t thread_index, const yy_g_event_queue_connection_t * eqc );

/* ����server����ṹ�������߳� */
extern int yy_g_event_server_begin_thread( yy_g_event_server_t * es );

/* ����server����ṹ�е������߳� */
extern int yy_g_event_server_end_thread( yy_g_event_server_t * es );

/* ��ȡserver���嵱ǰ�������ӵ����� */
extern size_t yy_g_event_server_conn_size( yy_g_event_server_t * es );

/* ��ȡserver�����������е�״̬ */
extern void yy_g_event_server_stat( yy_g_event_server_t * es, yy_g_event_server_stat_t * stat );

//Connection��صĲ���
/* ��ǰ�̴߳���һ������ */
extern yy_g_event_connection_t * yy_g_event_connection_create2( yy_g_event_thread_t * et, yy_p_socket_t s, int type );

/* �ݻٵ�ǰ����ec */
extern void yy_g_event_connection_destroy( /*yy_g_event_server_t * es,*/ yy_g_event_connection_t * ec );

/* ���û������󴴽�һ�����ӳɹ������������������ */
extern void yy_g_event_connection_set_event_cb( yy_g_event_connection_t * ec, yy_g_event_connection_event_cb_t f_event_cb, void * user_data );

/* ��õ�ǰ���ӵķ�Ӧ�� */
extern yy_f_reactor_t  * yy_g_event_connection_get_reactor( yy_g_event_connection_t * ec );

/* ��ȡ��ǰ�������ڵ��߳� */
extern yy_g_event_thread_t  * yy_g_event_connection_get_et( yy_g_event_connection_t * ec );

/* ��õ�ǰ���ӵ��׽ӿ� */
extern yy_p_socket_t yy_g_event_connection_socket( yy_g_event_connection_t * ec );

/* ����Ӧ��������¼�, ÿ��ֻ���һ���¼� */
extern int yy_g_event_connection_add_event(  yy_g_event_connection_t * ec, int event_mask, yy_p_uint32 ms );

/* �Ƴ���ǰ�����е��¼�������,��ͬʱ�Ƴ������¼� */
extern int yy_g_event_connection_remove_event(  yy_g_event_connection_t * ec, int event_mask );
//
#endif
