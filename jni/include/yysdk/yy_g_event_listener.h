#ifndef YY_G_EVENT_LISTENER_H
#define YY_G_EVENT_LISTENER_H
#include "yy_p_thread.h"
#include "yy_p_inet_addr.h"
#include "yy_e_memcheck.h"
#include "yy_f_reactor.h"

/* 监听的地址数量 */
#define YY_G_EVENT_LISTEN_NUM 64
#define YY_G_EVENT_LISTEN_THREAD_NUM 8      //最多允许8个线程

/* 监听回调函数 */
typedef void (*yy_g_event_listen_cb_t)(yy_p_socket_t listen_s, const yy_p_inet_addr_t * listen_addr, void * user_data, int type );

/* 预先定义结构体，防止编译时warnning */
struct yy_g_event_listener_s;

/* listener地址结构体 */
typedef struct yy_g_event_listener_addr_s{
    YY_E_MEM_MAGIC_PREFIX_DEFINE;
    struct yy_g_event_listener_s *el;		/* listener主结构体 */
    size_t index;							/* 索引 */
    yy_p_socket_t s;						/* 套接口 */
    yy_p_inet_addr_t addr;					/* ip地址 */	
    
    yy_f_event_handler_t *ev_read[YY_G_EVENT_LISTEN_THREAD_NUM];	/* 可读事件处理器 */
    int type;							/* 类型 */
    YY_E_MEM_MAGIC_SUFFIX_DEFINE;
}yy_g_event_listener_addr_t;

/* 线程初始化结构体 */
typedef struct yy_g_event_listener_thread_arg_s{
     struct yy_g_event_listener_s *el;		/* 线程参数 */
     size_t thread_index;					/* 线程索引 */
}yy_g_event_listener_thread_arg_t;

/* 套接口地址状态结构体 */
typedef struct yy_g_event_listener_addr_stat_s{
    volatile size_t event_num;				/* 处理的事件数 */
    yy_p_inet_addr_t addr;					/* socket地址 */
}yy_g_event_listener_addr_stat_t;

/* listener状态结构体 */
typedef struct yy_g_event_listener_stat_s{
    volatile time_t alive_time;				/* 活跃时间 */
    volatile size_t event_num;				/* 事件数 */
    yy_g_event_listener_addr_stat_t addr_stat[YY_G_EVENT_LISTEN_NUM];	/* socket地址 */
}yy_g_event_listener_stat_t;

/* listener初始化参数 */
typedef struct yy_g_event_listener_create_arg_s{
    yy_f_alloc_t *alloc;				/* 内存分配器 */
    void *user_data;					/* 用户自定义数据 */
    yy_g_event_listen_cb_t f_event_listen;	/* 监听回调函数 */
    int backlog;					/* */
    size_t thread_num;          //线程数（用于LISTEN）
}yy_g_event_listener_create_arg_t;


typedef struct yy_g_event_listener_thread_s{
    struct yy_g_event_listener_s *el;	/* listener结构体 */
    size_t thread_index;				/* 线程索引 */
    yy_p_thr_id_t thr_id;				/* 线程id */	
    yy_p_thr_handle_t thr_handle;		/* 线程句柄 */
     yy_f_reactor_t * r;				/* 反应器 */
     yy_f_event_handler_t *ev_timer;	/* 定时器处理器 */
}yy_g_event_listener_thread_t;

/* listener主结构体 */
typedef struct yy_g_event_listener_s{
    YY_E_MEM_MAGIC_PREFIX_DEFINE;
    yy_f_alloc_t *alloc;			/* 内存分配器 */
    void *user_data;				/* 用户自定义数据 */
    yy_g_event_listen_cb_t f_event_listen;	/* 监听回调函数 */
    int backlog;					/* 监听队列长度 */
    size_t thread_num;
    yy_g_event_listener_stat_t stat;	/* listener状态结构体 */

    
    yy_g_event_listener_thread_t threads[YY_G_EVENT_LISTEN_THREAD_NUM];	/* 线程 */

  /*  yy_p_thr_id_t thr_id[YY_G_EVENT_LISTEN_THREAD_NUM];
    yy_p_thr_handle_t thr_handle[YY_G_EVENT_LISTEN_THREAD_NUM];
    yy_f_reactor_t * r[YY_G_EVENT_LISTEN_THREAD_NUM];
    yy_f_event_handler_t *ev_timer[YY_G_EVENT_LISTEN_THREAD_NUM];*/
   
    yy_g_event_listener_addr_t listens[YY_G_EVENT_LISTEN_NUM];	/* 监听地址数组 */
    YY_E_MEM_MAGIC_SUFFIX_DEFINE;
}yy_g_event_listener_t;

/* 创建listener运行主体结构 */
extern yy_g_event_listener_t * yy_g_event_listener_create( yy_g_event_listener_create_arg_t * arg );

/* 摧毁listener结构体  */
extern void yy_g_event_listener_destroy( yy_g_event_listener_t * el );

/* 开启listener中线程，让反应器循环定时工作，接收套接口请求 */
extern int yy_g_event_listener_begin_thread( yy_g_event_listener_t * el );

/* 结束listener中线程，关闭反应器 */
extern int yy_g_event_listener_end_thread( yy_g_event_listener_t * el );

/* 添加listener监听的套接口，并将套接口设置成非阻塞，绑定，监听，同时将套接口可读 */
extern int yy_g_event_listener_add_listen( yy_g_event_listener_t * el, yy_p_inet_addr_t * addr, int type );

/* 获取listener的状态 */
extern void yy_g_event_listener_stat( yy_g_event_listener_t * el, yy_g_event_listener_stat_t * stat );
#endif
