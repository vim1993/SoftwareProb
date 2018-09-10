#ifndef YY_F_REACTOR_H
#define YY_F_REACTOR_H
#include "yy_p_thread.h"
#include "yy_f_reactor_imp_if.h"
#include "yy_s_lxlist.h"
#include "yy_f_alloc.h"
#include "yy_f_timer_queue.h"
#include "yy_e_memcheck.h"

#ifdef  __cplusplus
extern "C" {
#endif

/* �ӿڲο���ACE,ʵ�ֲ�����libevent,ACE̫������ */
/* ʲôʱ���ÿɶ���ʲôʱ���ÿ�д ?? */

#define YY_F_EVENT_READ             1	/* ���¼� */
#define YY_F_EVENT_WRITE            2	/* д�¼� */
#define YY_F_EVENT_TIMER            4	/* ��ʱ���¼� */
#define YY_F_EVENT_IO_PERSIST       8	/* ������IO�����׽ӿڳ�������д */

/* ȫ�����ܵ��¼� */
#define YY_F_EVENT_EMASK    (YY_F_EVENT_READ|YY_F_EVENT_WRITE|YY_F_EVENT_TIMER)   


#define YY_F_EVENT_FLAG_GUARD        0xC500005C	/* �ڴ�Խ�����־ */
#define YY_F_EVENT_FLAG_IO_LIST      0x00000100	/* �¼���־���¼���IO������ */
#define YY_F_EVENT_FLAG_ACTIVE_LIST  0x00000200	/* �¼���־���¼��ڻ�Ծ������ */
#define YY_F_EVENT_FLAG_TIMER_LIST   0x00000400	/* �¼���־���¼��ڶ�ʱ�������� */

/* �¼��ܱ���ӵ����������� */
#define YY_F_EVENT_FLAG_ADDED_LIST (YY_F_EVENT_FLAG_IO_LIST|YY_F_EVENT_FLAG_TIMER_LIST)

/* ȫ������ļ��ϣ�IO������Ծ������ʱ������ */
#define YY_F_EVENT_FLAG_ALL_LIST (YY_F_EVENT_FLAG_IO_LIST|YY_F_EVENT_FLAG_ACTIVE_LIST|YY_F_EVENT_FLAG_TIMER_LIST)

/* �ڴ�Խ���� */
#define YY_F_EVENT_FLAG_CHECK_GUARD_OK( a ) do{ yy_p_assert( ( (a)->flag & YY_F_EVENT_FLAG_GUARD ) == YY_F_EVENT_FLAG_GUARD ); }while(0)

/* �¼��ص����� */
typedef void (*yy_f_event_cb_t)(yy_p_socket_t s, int mask, void *arg, struct yy_f_event_handler_s * ev);

/* �¼��������ṹ�� */
typedef struct yy_f_event_handler_s{
    YY_E_MEM_MAGIC_PREFIX_DEFINE;
    volatile yy_p_uint32 flag;		/* �¼����������־ */
    struct yy_f_reactor_s * r;		/* ��Ӧ�� */
    yy_p_socket_t s;				/* �׽ӿ� */

    //IO�¼�
    int event_mask;				/* �¼����ͣ�����д����ʱ�� */
    yy_s_lxlist_head_t list_io;		/* IO�¼����� */

    //��ʱ��
    yy_f_timer_id_t timer_id;		/* ��ʱ��ID�����¼�Ϊ��ʱ���� */
    yy_p_timeval_t time_interval;	/* ��ʱ������ʱ���� */
	
    int active_mask;				/* ��Ծ�¼����ͣ�����д����ʱ������ */
    yy_s_lxlist_head_t list_active;	/* װ�ػ�Ծ�¼����� */

    //���ڻص�
    yy_f_event_cb_t cb_func;		/* �¼��ص����� */
    void * cb_arg;				/* �ص��������� */

    YY_E_MEM_MAGIC_SUFFIX_DEFINE;
}yy_f_event_handler_t;

/* ��Ӧ��״̬ͳ�ƽṹ�� */
typedef struct yy_f_reactor_stat_s{
    size_t ev_read_count;		/* �ɶ��¼����� */
    size_t ev_write_count;		/* ��д�¼����� */
    size_t ev_timer_count;		/* ��ʱ���¼����� */
    size_t add_event_count;	/* ����¼����� */
    size_t remove_event_count;	/* �Ƴ��¼����� */

    //��ʱ�������е��쳣
    yy_f_timer_queue_stat_t timer_stat;	/* ��ʱ��״̬ͳ�� */
}yy_f_reactor_stat_t;

/* ��Ӧ���ṹ���� */
typedef struct yy_f_reactor_s{
    YY_E_MEM_MAGIC_PREFIX_DEFINE;
    yy_p_thr_mutex_t r_lock;	/* �� */
    volatile int is_wait_exit;	/* �ȴ��˳���־����0���˳���Ӧ�� */
    yy_s_lxlist_head_t io_list;	/* IO�¼����� */
    yy_s_lxlist_head_t active_list;	/* ��Ծ�¼����� */

    //��ʱ��
    yy_f_timer_queue_t * tq;	/* ��ʱ������ */

    //ʵ��
    yy_f_reactor_imp_if_t * imp_if;	/* ��Ӧ���ӿ�ʵ�֣�selectģ�ͻ�epollģ�� */
    yy_f_reactor_imp_cb_t iml_cb;	/* �¼�����ص� */

    //������
    yy_f_alloc_t * alloc_event;		/* �¼��ڴ������ */
    yy_f_alloc_t * alloc_thiz;		/* ���ṹ�ڴ������ */

    volatile size_t bind_connection_count;	/* ��ǰ������ */

    //״̬ͳ��
    yy_f_reactor_stat_t stat;		/* ͳ�� */
    YY_E_MEM_MAGIC_SUFFIX_DEFINE;
}yy_f_reactor_t;

/* �����¼�������(�ɶ��¼�����д�¼�����ʱ���¼�) */
extern yy_f_event_handler_t * yy_f_reactor_create_event( yy_f_reactor_t * r );

/* �����¼������� */
extern void yy_f_reactor_destroy_event( yy_f_reactor_t * r, yy_f_event_handler_t * ev );

/* �����¼������� */
extern int yy_f_reactor_set_event( yy_f_event_handler_t * ev, yy_p_socket_t s, int mask, yy_f_event_cb_t cb_func, void * cb_arg );

/* ���ö�ʱ���¼� */
extern int yy_f_reactor_set_timer( yy_f_event_handler_t * ev, yy_p_socket_t s, yy_f_event_cb_t cb_func, void * cb_arg, yy_p_uint32 interval_ms );

/* ����¼�����������Ӧ���� */
extern int yy_f_reactor_add_event( yy_f_reactor_t * r, yy_f_event_handler_t * ev );

/* �ӷ�Ӧ���Ƴ��¼�������  */
extern int yy_f_reactor_remove_event( yy_f_reactor_t * r, yy_f_event_handler_t * ev );

/* �ж��¼��������Ƿ�����ӵ���Ӧ���У�IO�����ʱ������ */
extern int yy_f_reactor_is_event_added( yy_f_reactor_t * r, yy_f_event_handler_t * ev );

/* ���ѡ��select֮�����Ϊimpl,��Ҫע��event_num������ */
/* ������Ӧ�� */
extern yy_f_reactor_t * yy_f_reactor_create( const char * impl, size_t max_event_num, int is_use_lock );

/* ���ٷ�Ӧ�� */
extern void yy_f_reactor_destroy( yy_f_reactor_t * r );

/* ������ʱ����IO�¼�����һ�֣� */
extern int yy_f_reactor_loop_once( yy_f_reactor_t * r,  yy_p_uint32 max_wait_ms );

/* ��Ӧ������ѭ����ֱ����Ҫ���˳� */
extern int yy_f_reactor_loop_forever( yy_f_reactor_t * r );

/* �˳���Ӧ�� */
extern int yy_f_reactor_exit_loop( yy_f_reactor_t * r );

/* ��ȡ��Ӧ��ͳ����Ϣ */
extern int yy_f_reactor_get_stat( yy_f_reactor_t * r, yy_f_reactor_stat_t *stat );

/* һ��connection����BINDһ��R/W/E�¼���һ��.���ڼ��������� */

/* ���ӷ�Ӧ����connection���� */
extern void yy_f_reactor_inc_bind_connection( yy_f_reactor_t * r );

/* ���ٷ�Ӧ����connection���� */
extern void yy_f_reactor_dec_bind_connection( yy_f_reactor_t * r );

/* ��ȡ��Ӧ����connection���� */
extern size_t yy_f_reactor_get_bind_connection( yy_f_reactor_t * r );

/* ��ȡ����²⣩��Ӧ��������ļ����������� */
extern size_t yy_f_reactor_guess_fd_size( const char * reactor_name, size_t max_fd, size_t max_conn, size_t reactor_num );

/* �������� */
extern int yy_f_reactor_validation_test();

#ifdef  __cplusplus
}
#endif

#endif
