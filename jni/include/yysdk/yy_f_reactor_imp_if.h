#ifndef YY_F_REACTOR_IMP_IF_H
#define YY_F_REACTOR_IMP_IF_H
#include "yy_p_socket.h"
#include "yy_p_time.h"
#include "yy_e_memcheck.h"
#include "yy_s_lxlist.h"
struct yy_f_reactor_s;
struct yy_f_event_handler_s;
struct yy_f_reactor_imp_if_s;
struct yy_f_reactor_imp_cb_s;

/* 
*��ͷ�ļ�����selectģʽ��epollģʽ��Ӧ���Ĺ����ӿںͺ�
*added by gaoqiang, 2015-08-03
*/

/* �����¼��ص���������Ҫ�ǽ��¼����ص���Ӧ���Ļ�Ծ���� */
typedef int (*yy_f_reactor_active_event_t)(struct yy_f_reactor_s *r, struct yy_f_event_handler_s * ev, int mask );

/* �����¼��Ļص��ṹ */
typedef struct yy_f_reactor_imp_cb_s{
    struct yy_f_reactor_s * r;			/* ��Ӧ�� */
    yy_f_reactor_active_event_t f_active_event;	/* �����¼��Ļص����� */
}yy_f_reactor_imp_cb_t;

/* �ͷŷ�Ӧ�� */
typedef void (*yy_f_reactor_imp_release_t)(void * thiz );

/* ����¼�����������Ӧ�� */
typedef int (*yy_f_reactor_imp_add_event_t)(void * thiz, struct yy_f_event_handler_s * ev );

/* �ӷ�Ӧ�����Ƴ��¼������� */
typedef int (*yy_f_reactor_imp_remove_event_t)(void * thiz, struct yy_f_event_handler_s * ev );

/* ���ɣ�������������¼������� */
typedef int (*yy_f_reactor_imp_dispath_event_t)(void * thiz, const yy_p_timeval_t * tv  );

/* ��Ӧ��ʵ�ֹ����ӿڶ��壺����������Ӧ��ʵ�ּ�ָselectģ�ͻ�epollģ�͵�IO��·���� */
typedef struct yy_f_reactor_imp_if_s{
    char name[16];				/* ��Ӧ������ */
    void * thiz;					/* ��Ӧ��ʵ�ֵ�ָ�룬��select��epoll��Ӧ��ָ�� */
    //some func...
    yy_f_reactor_imp_release_t f_release;	/* �ͷŷ�Ӧ��ʵ�� */
    yy_f_reactor_imp_add_event_t f_add_event;	/* ����¼�����������Ӧ��ʵ���� */
    yy_f_reactor_imp_remove_event_t f_remove_event;	/* �ӷ�Ӧ��ʵ�����Ƴ��¼������� */
    yy_f_reactor_imp_dispath_event_t f_dispath_event;	/* ���ɣ�������������¼������� */
}yy_f_reactor_imp_if_t;

/* �����ӿڶ�Ӧ�ĺ궨�壬select��epoll��ʵ�־���ʹ����Щ�� */
#define YY_F_REACTOR_IMP_RELEASE( a )           (a)->f_release( (a)->thiz )
#define YY_F_REACTOR_IMP_ADD_EVENT( a, ev )     (a)->f_add_event( (a)->thiz,  ev )
#define YY_F_REACTOR_IMP_REMOVE_EVENT( a, ev )  (a)->f_remove_event( (a)->thiz,  ev )
#define YY_F_REACTOR_IMP_DISPATH_EVENT( a, tv ) (a)->f_dispath_event( (a)->thiz, tv )
/*create sample
extern yy_f_reactor_imp_if_t * yy_f_reactor_impl_create_select( size_t max_fd_size, struct yy_f_reactor_imp_cb_s * imp_cb );
*/

#endif
