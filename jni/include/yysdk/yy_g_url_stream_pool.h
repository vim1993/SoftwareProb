/* 本文件用于实现简单的http请求处理池，即池中可保持多个http请求 */
#ifndef YY_G_URL_STREAM_POOL_H
#define YY_G_URL_STREAM_POOL_H
#include "yy_g_url_stream.h"
#include "yy_s_list.h"
#include "yy_p_thread.h"

/* http请求处理池结构体 */
typedef struct yy_g_url_stream_pool_s{
	YY_E_MEM_MAGIC_PREFIX_DEFINE;
    yy_f_alloc_t * alloc;					/* 内存分配器 */
	yy_p_thr_mutex_t lock;					/* 互斥锁 */
	size_t max_us_count;					/* 池最多能支持的http请求任务数 */
	//队列
    yy_s_list_t * list_run;					/* 正在处理的http任务链表 */
    yy_s_list_t * list_delete;				/* 等待删除的http任务链表 */
	YY_E_MEM_MAGIC_SUFFIX_DEFINE;
}yy_g_url_stream_pool_t;

/* 创建http请求处理池 */
extern yy_g_url_stream_pool_t * yy_g_url_stream_pool_create( yy_f_alloc_t * alloc, size_t max_us_count );
/* 销毁http请求处理池 */
extern void yy_g_url_stream_pool_destroy( yy_g_url_stream_pool_t *usp );
//定时调用,用于处理删除,定时释放等逻辑
/* 定时器函数，由反应器驱动，处理池中http请求任务 */
extern void yy_g_url_stream_pool_timer( yy_g_url_stream_pool_t *usp );
/* 从池中获取一个结点，用于处理新的http请求 */
extern yy_g_url_stream_t * yy_g_url_stream_pool_get_us( yy_g_url_stream_pool_t *usp, yy_f_reactor_t * r, yy_g_url_stream_state_cb_t f_state_cb, void * user_data);
/* 从池中查找任务结点，将其添加到等待删除任务链表中 */
extern void yy_g_url_stream_pool_return_us( yy_g_url_stream_pool_t *usp, yy_g_url_stream_t * us );
/* 判断http请求处理池是否已满，即不能再接收新任务 */
extern int yy_g_url_stream_pool_is_full( yy_g_url_stream_pool_t *usp );
/* 获取正在处理的http任务数 */
extern size_t yy_g_url_stream_pool_get_run_us_count( yy_g_url_stream_pool_t *usp );
/* 获取还能添加的http任务数量 */
extern size_t yy_g_url_stream_pool_get_idle_us_count( yy_g_url_stream_pool_t *usp );
#endif
