/*
1.针对TCP连接的一个多线程分派器,实现负载的动太均衡
2.集成部分关于模块的设计思想.
3.目标是基于此,提供WEB Server/Media Server等相关业务的通用支持层
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
1.针对TCP连接的一个多线程分派器,实现负载的动太均衡
2.集成部分关于模块的设计思想.
3.目标是基于此,提供WEB Server/Media Server等相关业务的通用支持层
*/

#define YY_G_EVENT_SERVER_MAX_THREAD_NUM 128

/* 用户请求结构体，主要是listener监听的用户请求传过来的消息 */
typedef struct yy_g_event_queue_connection_s{
    yy_p_socket_t s;		/* 用户请求的套接口 */
    int type;			/* 用户请求的类型 */
    void * user_data;		/* 用户请求的数据 */
	int af_type;
    //int is_delay_accept;        //这个功能已经取消，现在是由LISTEN多线程来直接获取的。是否DELAY ACCEPT，如果打开了这个功能，会有业务线程来收
    //yy_p_socket_t listen_s;
	//size_t thread_index;		//指定线程进行分派,暂时未实现
}yy_g_event_queue_connection_t;

/* 预先定义，防止编译出现warnning */
struct yy_g_event_server_s;
struct yy_g_event_connection_s;

/* server一次连接所触发的回调函数 */
typedef void (*yy_g_event_connection_event_cb_t)( struct yy_g_event_connection_s * ec, int event_type, void * user_data );

/* 一次连接结构体 */
typedef struct yy_g_event_connection_s{
    YY_E_MEM_MAGIC_PREFIX_DEFINE;
    struct yy_g_event_server_s *es;	/* server结构体 */
    yy_p_socket_t s;				/* 连接的套接口 */
    int type;					/* 连接的类型 */
    yy_f_reactor_t * r;			/* 连接的反应器 */
    size_t thread_index;			/* 连接所在的线程的索引 */
    yy_f_event_handler_t * ev_read;	/* 连接中可读事件处理器 */
    yy_f_event_handler_t * ev_write;	/* 连接中可写事件处理器 */
    yy_f_event_handler_t * ev_timer;/* 连接中定时器事件处理器 */
    //
    yy_g_event_connection_event_cb_t f_event_cb;	/* 这次连接中所触发的回调函数 */
    void *  user_data;			/* 自定义数据 */
    YY_E_MEM_MAGIC_SUFFIX_DEFINE;
}yy_g_event_connection_t;

/* 二个典型的回调,成功回调函数，用于设置最后的处理函数(yy_g_event_connection_event_cb_t) */
typedef int (*yy_g_event_server_create_connection_success_t)( struct yy_g_event_server_s *es, yy_g_event_queue_connection_t * eqc, yy_g_event_connection_t * ec );
/* 失败的回调,与上面的成功回调正好相反 */
typedef void (*yy_g_event_server_create_connection_error_t)( struct yy_g_event_server_s *es, yy_g_event_queue_connection_t * eqc, int err );

/* 线程状态结构体 */
typedef struct yy_g_event_server_thread_stat_s{
	yy_p_thr_id_t thr_id;		/* 线程的id */
	time_t alive_time;			/* 线程的最新活跃时间 */
	size_t dispath_num;		/* 线程的执行请求次数 */
	size_t connection_num;		/* 线程的接收的连接次数 */
	yy_f_reactor_stat_t r_stat;	/* 线程反应器状态 */

}yy_g_event_server_thread_stat_t;

/* server状态结构体 */
typedef struct yy_g_event_server_stat_s{
	size_t create_queue_size;		/* server队列长度 */
	size_t dispath_count;			/* 线程执行次数 */
    size_t notify_error_count;		/* notify的错误次数 */	
    size_t notify_ok_count;		/* notify的正确次数 */
	size_t thread_num;				/* 线程的个数 */
	yy_g_event_server_thread_stat_t t_stat[YY_G_EVENT_SERVER_MAX_THREAD_NUM];	/* 线程的状态结构体 */

}yy_g_event_server_stat_t;

/* 线程结构体 */
typedef struct yy_g_event_thread_s{    
    size_t index;					/* 线程索引 */
    struct yy_g_event_server_s * es;	/* server主体结构体 */
    //size_t 
    yy_f_reactor_t * r;			/* 反应器 */
    yy_f_event_handler_t *ev_timer; /* 用pair socket作为通知机制更佳,但WINDOWS没这个东西,FT */
    yy_f_event_handler_t *ev_read_notify; /* 仅在LINUX使用的通知机制 */
    yy_p_socket_t notify_s[2];		/* 套接口 */
    yy_p_thr_id_t thr_id;			/* 线程id */
    yy_p_thr_handle_t thr_handle;	/* 线程句柄 */
	
	time_t alive_time;				/* 线程活跃时间 */
    size_t dispath_count;			/* 线程执行次数 */
	char buf[64*124];				/* 没有用处 */
}yy_g_event_thread_t;

/* server主体结构体 */
typedef struct yy_g_event_server_s{
    YY_E_MEM_MAGIC_PREFIX_DEFINE;
    yy_f_alloc_t *alloc_thiz;		/* 结构体自身分配器 */
    yy_f_alloc_t * alloc_conn;		/* 用于创建一次连接内存分配器 */
    void * user_data;				/* 用于自定义数据 */
    size_t thread_num;				/* 线程个数 */
    size_t max_queue_size;			/* listener与server交互的list的大小 */
    size_t max_connection_size;		/* 能处理的最大连接数 */
    yy_g_event_server_create_connection_error_t f_create_error;	/* 处理用户请求失败回调函数 */
    yy_g_event_server_create_connection_success_t f_create_success;	/* 处理用户请求成功回调函数 */

    volatile size_t notify_error_count;		/* notify的错误次数 */
    volatile size_t notify_ok_count;		/* notify的正确次数 */

    yy_p_thr_mutex_t lock_create_connection;	/* 上锁标志 */
    yy_s_list_t *list_create_connection;		/* 链表，用于装载用户请求 */
    yy_g_event_thread_t * threads;			/* 线程指针 */
    YY_E_MEM_MAGIC_SUFFIX_DEFINE;
}yy_g_event_server_t;

/* server初始化结构体 */
typedef struct yy_g_event_server_create_arg_s{
    yy_f_alloc_t *alloc_thiz;				/* 结构体自身内存分配器 */
    void * user_data;						/* 自定义数据 */
    const char * reactor_name;				/* 反应器的方式select or epoll */
    size_t max_reactor_fd_size;				/* 反应器能监听的最大数目 */

    size_t thread_num;						/* 线程的数目 */
    size_t max_queue_size;					/* listener与server交互的list的大小 */
    size_t max_connection_size;				/* 能处理的最大连接数 */
    yy_g_event_server_create_connection_error_t f_create_error;	/* 处理用户请求成功回调 */
    yy_g_event_server_create_connection_success_t f_create_success;	/* 处理用户请求失败回调 */
}yy_g_event_server_create_arg_t;

/* 创建server运行主体结构 */
extern yy_g_event_server_t * yy_g_event_server_create( const yy_g_event_server_create_arg_t * arg );

/* 摧毁server主体结构 */
extern void yy_g_event_server_destroy( yy_g_event_server_t * es );

/* 将用户的请求eqc添加到es的链表中，并选择一个空闲的线程 */
extern int yy_g_event_server_queue_create_connection( yy_g_event_server_t * es, const yy_g_event_queue_connection_t * eqc );

/* 获取server主体的连接数(也就是装载用户请求的list) */
extern size_t yy_g_event_server_queue_create_conn_size( yy_g_event_server_t * es );

/* 在线程thread_index中创建一次连接connection */
extern yy_g_event_connection_t * yy_g_event_server_create_connection_in_thread( yy_g_event_server_t * es, size_t thread_index, const yy_g_event_queue_connection_t * eqc );

/* 开启server主体结构的所有线程 */
extern int yy_g_event_server_begin_thread( yy_g_event_server_t * es );

/* 结束server主体结构中的所有线程 */
extern int yy_g_event_server_end_thread( yy_g_event_server_t * es );

/* 获取server主体当前正在连接的数量 */
extern size_t yy_g_event_server_conn_size( yy_g_event_server_t * es );

/* 获取server主体正在运行的状态 */
extern void yy_g_event_server_stat( yy_g_event_server_t * es, yy_g_event_server_stat_t * stat );

//Connection相关的操作
/* 当前线程创建一次连接 */
extern yy_g_event_connection_t * yy_g_event_connection_create2( yy_g_event_thread_t * et, yy_p_socket_t s, int type );

/* 摧毁当前连接ec */
extern void yy_g_event_connection_destroy( /*yy_g_event_server_t * es,*/ yy_g_event_connection_t * ec );

/* 对用户的请求创建一次连接成功后用于设置最后处理函数 */
extern void yy_g_event_connection_set_event_cb( yy_g_event_connection_t * ec, yy_g_event_connection_event_cb_t f_event_cb, void * user_data );

/* 获得当前连接的反应器 */
extern yy_f_reactor_t  * yy_g_event_connection_get_reactor( yy_g_event_connection_t * ec );

/* 获取当前连接所在的线程 */
extern yy_g_event_thread_t  * yy_g_event_connection_get_et( yy_g_event_connection_t * ec );

/* 获得当前连接的套接口 */
extern yy_p_socket_t yy_g_event_connection_socket( yy_g_event_connection_t * ec );

/* 往反应器中添加事件, 每次只添加一种事件 */
extern int yy_g_event_connection_add_event(  yy_g_event_connection_t * ec, int event_mask, yy_p_uint32 ms );

/* 移除当前连接中的事件处理器,可同时移除多种事件 */
extern int yy_g_event_connection_remove_event(  yy_g_event_connection_t * ec, int event_mask );
//
#endif
