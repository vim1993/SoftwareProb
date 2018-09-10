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

/* 接口参考自ACE,实现参与自libevent,ACE太冗余了 */
/* 什么时候用可读，什么时候用可写 ?? */

#define YY_F_EVENT_READ             1	/* 读事件 */
#define YY_F_EVENT_WRITE            2	/* 写事件 */
#define YY_F_EVENT_TIMER            4	/* 定时器事件 */
#define YY_F_EVENT_IO_PERSIST       8	/* 持续性IO，如套接口持续读或写 */

/* 全部可能的事件 */
#define YY_F_EVENT_EMASK    (YY_F_EVENT_READ|YY_F_EVENT_WRITE|YY_F_EVENT_TIMER)   


#define YY_F_EVENT_FLAG_GUARD        0xC500005C	/* 内存越界检测标志 */
#define YY_F_EVENT_FLAG_IO_LIST      0x00000100	/* 事件标志：事件在IO链表上 */
#define YY_F_EVENT_FLAG_ACTIVE_LIST  0x00000200	/* 事件标志：事件在活跃链表上 */
#define YY_F_EVENT_FLAG_TIMER_LIST   0x00000400	/* 事件标志：事件在定时器链表上 */

/* 事件能被添加到的链表？？？ */
#define YY_F_EVENT_FLAG_ADDED_LIST (YY_F_EVENT_FLAG_IO_LIST|YY_F_EVENT_FLAG_TIMER_LIST)

/* 全部链表的集合：IO链表、活跃链表、定时器链表 */
#define YY_F_EVENT_FLAG_ALL_LIST (YY_F_EVENT_FLAG_IO_LIST|YY_F_EVENT_FLAG_ACTIVE_LIST|YY_F_EVENT_FLAG_TIMER_LIST)

/* 内存越界检测 */
#define YY_F_EVENT_FLAG_CHECK_GUARD_OK( a ) do{ yy_p_assert( ( (a)->flag & YY_F_EVENT_FLAG_GUARD ) == YY_F_EVENT_FLAG_GUARD ); }while(0)

/* 事件回调函数 */
typedef void (*yy_f_event_cb_t)(yy_p_socket_t s, int mask, void *arg, struct yy_f_event_handler_s * ev);

/* 事件处理器结构体 */
typedef struct yy_f_event_handler_s{
    YY_E_MEM_MAGIC_PREFIX_DEFINE;
    volatile yy_p_uint32 flag;		/* 事件所属链表标志 */
    struct yy_f_reactor_s * r;		/* 反应器 */
    yy_p_socket_t s;				/* 套接口 */

    //IO事件
    int event_mask;				/* 事件类型：读、写、定时器 */
    yy_s_lxlist_head_t list_io;		/* IO事件链表 */

    //定时器
    yy_f_timer_id_t timer_id;		/* 定时器ID（若事件为定时器） */
    yy_p_timeval_t time_interval;	/* 定时器触发时间间隔 */
	
    int active_mask;				/* 活跃事件类型：读、写、定时器？？ */
    yy_s_lxlist_head_t list_active;	/* 装载活跃事件链表 */

    //关于回调
    yy_f_event_cb_t cb_func;		/* 事件回调函数 */
    void * cb_arg;				/* 回调函数参数 */

    YY_E_MEM_MAGIC_SUFFIX_DEFINE;
}yy_f_event_handler_t;

/* 反应器状态统计结构体 */
typedef struct yy_f_reactor_stat_s{
    size_t ev_read_count;		/* 可读事件个数 */
    size_t ev_write_count;		/* 可写事件个数 */
    size_t ev_timer_count;		/* 定时器事件个数 */
    size_t add_event_count;	/* 添加事件个数 */
    size_t remove_event_count;	/* 移除事件个数 */

    //定时器队列中的异常
    yy_f_timer_queue_stat_t timer_stat;	/* 定时器状态统计 */
}yy_f_reactor_stat_t;

/* 反应器结构定义 */
typedef struct yy_f_reactor_s{
    YY_E_MEM_MAGIC_PREFIX_DEFINE;
    yy_p_thr_mutex_t r_lock;	/* 锁 */
    volatile int is_wait_exit;	/* 等待退出标志，非0则退出反应器 */
    yy_s_lxlist_head_t io_list;	/* IO事件链表 */
    yy_s_lxlist_head_t active_list;	/* 活跃事件链表 */

    //定时器
    yy_f_timer_queue_t * tq;	/* 定时器队列 */

    //实现
    yy_f_reactor_imp_if_t * imp_if;	/* 反应器接口实现：select模型或epoll模型 */
    yy_f_reactor_imp_cb_t iml_cb;	/* 事件激活回调 */

    //分配器
    yy_f_alloc_t * alloc_event;		/* 事件内存分配器 */
    yy_f_alloc_t * alloc_thiz;		/* 本结构内存分配器 */

    volatile size_t bind_connection_count;	/* 当前连接数 */

    //状态统计
    yy_f_reactor_stat_t stat;		/* 统计 */
    YY_E_MEM_MAGIC_SUFFIX_DEFINE;
}yy_f_reactor_t;

/* 创建事件处理器(可读事件、可写事件、定时器事件) */
extern yy_f_event_handler_t * yy_f_reactor_create_event( yy_f_reactor_t * r );

/* 销毁事件处理器 */
extern void yy_f_reactor_destroy_event( yy_f_reactor_t * r, yy_f_event_handler_t * ev );

/* 设置事件处理器 */
extern int yy_f_reactor_set_event( yy_f_event_handler_t * ev, yy_p_socket_t s, int mask, yy_f_event_cb_t cb_func, void * cb_arg );

/* 设置定时器事件 */
extern int yy_f_reactor_set_timer( yy_f_event_handler_t * ev, yy_p_socket_t s, yy_f_event_cb_t cb_func, void * cb_arg, yy_p_uint32 interval_ms );

/* 添加事件处理器到反应器上 */
extern int yy_f_reactor_add_event( yy_f_reactor_t * r, yy_f_event_handler_t * ev );

/* 从反应器移除事件处理器  */
extern int yy_f_reactor_remove_event( yy_f_reactor_t * r, yy_f_event_handler_t * ev );

/* 判断事件处理器是否已添加到反应器中（IO链表或定时器链表） */
extern int yy_f_reactor_is_event_added( yy_f_reactor_t * r, yy_f_event_handler_t * ev );

/* 如果选择select之类的作为impl,需要注意event_num的数量 */
/* 创建反应器 */
extern yy_f_reactor_t * yy_f_reactor_create( const char * impl, size_t max_event_num, int is_use_lock );

/* 销毁反应器 */
extern void yy_f_reactor_destroy( yy_f_reactor_t * r );

/* 触发定时器和IO事件处理（一轮） */
extern int yy_f_reactor_loop_once( yy_f_reactor_t * r,  yy_p_uint32 max_wait_ms );

/* 反应器无限循环，直至被要求退出 */
extern int yy_f_reactor_loop_forever( yy_f_reactor_t * r );

/* 退出反应器 */
extern int yy_f_reactor_exit_loop( yy_f_reactor_t * r );

/* 获取反应器统计信息 */
extern int yy_f_reactor_get_stat( yy_f_reactor_t * r, yy_f_reactor_stat_t *stat );

/* 一组connection可以BIND一个R/W/E事件各一个.用于计数？？？ */

/* 增加反应器中connection个数 */
extern void yy_f_reactor_inc_bind_connection( yy_f_reactor_t * r );

/* 减少反应器中connection个数 */
extern void yy_f_reactor_dec_bind_connection( yy_f_reactor_t * r );

/* 获取反应器中connection个数 */
extern size_t yy_f_reactor_get_bind_connection( yy_f_reactor_t * r );

/* 获取（或猜测）反应器中最大文件描述符数量 */
extern size_t yy_f_reactor_guess_fd_size( const char * reactor_name, size_t max_fd, size_t max_conn, size_t reactor_num );

/* 测试用例 */
extern int yy_f_reactor_validation_test();

#ifdef  __cplusplus
}
#endif

#endif
