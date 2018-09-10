/* 本文件实现处理简单的http请求任务 */
#ifndef YY_G_URL_STREAM_H
#define YY_G_URL_STREAM_H
#include "yy_p_type.h"
#include "yy_p_socket.h"
#include "yy_p_stdio.h"
#include "yy_p_inet_addr.h"
#include "yy_f_alloc.h"
#include "yy_f_reactor.h"
#include "yy_f_message_block.h"
#include "yy_e_memcheck.h"
#include "yy_e_http_parser.h"
#include "yy_e_uri_parser.h"

/* http任务处理各状态宏定义 */
#define YY_GUS_E_UNKNOWN -1							/* 错误 */

#define YY_GUS_S_CREATED            1				/* 任务已创建 */
#define YY_GUS_S_INITED             2				/* 任务已初始化 */
#define YY_GUS_S_PREPARED           3				/* 任务已准备好 */
#define YY_GUS_S_START              4				/* 任务已开始 */
#define YY_GUS_S_CONNECTING         5				/* 连接中 */
#define YY_GUS_S_CONNECTED          6				/* 已连接 */
#define YY_GUS_S_SEND_HEAD          7				/* 发送http请求头部 */
#define YY_GUS_S_SEND_CONTENT       8				/* 发送http请求body */
#define YY_GUS_S_RECV_HEAD          9				/* 接收http响应头部 */
#define YY_GUS_S_RECV_CONTENT       10				/* 接收http响应body */
#define YY_GUS_S_STOP               11				/* 任务已停止 */
#define YY_GUS_S_COMPLETE           12				/* 任务已完成 */
#define YY_GUS_S_ERROR              13				/* 任务发生错误 */

/* 任务状态结构体 */
typedef struct yy_g_url_stream_state_s{
    int s;											/* 当前状态 */
    int ex_s;										/* 前一状态 */
}yy_g_url_stream_state_t;

/* 任务错误码 */
typedef struct yy_g_url_stream_err_s{
    int err;										/* 当前错误码 */
    int ex_err;										/* 前一错误码 */
}yy_g_url_stream_err_t;
struct yy_g_url_stream_s;

/* 任务状态切换回调函数 */
typedef void (*yy_g_url_stream_state_cb_t)( void * user_data, struct yy_g_url_stream_s *us, const yy_g_url_stream_state_t * state, const yy_g_url_stream_err_t * err, const yy_g_url_stream_state_t * pre_state );

/* http请求处理结构体 */
typedef struct yy_g_url_stream_s{
    YY_E_MEM_MAGIC_PREFIX_DEFINE;
    yy_f_alloc_t * alloc;							/* 内存分配器 */

    yy_g_url_stream_state_t pre_state;				/* 前一状态 */
    yy_g_url_stream_state_t state;					/* 当前状态 */
    yy_g_url_stream_err_t err;						/* 错误码 */
    void * user_data;								/* 参数或称为用户数据 */
    yy_g_url_stream_state_cb_t f_state_cb;			/* 任务状态切换时的回调函数 */

	yy_p_uint32 start_ms;							/* 任务启动时间 */
	yy_p_uint32 connectted_ms;						/* 连接时间 */
	yy_p_uint32 last_active_ms;						/* 上一次活跃时间 */

	yy_p_uint32 connectting_timeout_ms;				/* 连接超时时间 */
	yy_p_uint32 recv_head_timeout_ms;				/* 接收http响应头部超时时间 */
	yy_p_uint32 active_timeout_ms;					/* 活跃超时时间 */

    //请求相关
    yy_e_http_parser_t * req;						/* http请求解析结构体 */
    yy_e_uri_parser_t * req_uri;					/* url解析结构体 */
    yy_p_inet_addr_t host_addr;						/* 要连接的主机地址 */

	//回应相关
    yy_e_http_parser_t * rep;						/* http响应解析结构体 */
    int is_rep_chunked;								/* 响应是否分块 ??? */
    int chunked_parse_state;            
    yy_e_http_content_t chunk_size;
    yy_e_http_content_t chunk_readed_size;

    size_t recved_content_len;						/* 已接收的http body长度 */
    yy_f_message_block_t * recv_content;			/* http响应body数据接收缓存 */

    yy_f_reactor_t * r;								/* 反应器 */
    yy_f_event_handler_t * ev_timer;				/* 定时器处理器 */
    yy_f_event_handler_t * ev_read;					/* 可读事件处理器 */
    yy_f_event_handler_t * ev_write;				/* 可写事件处理器 */
    yy_p_socket_t s;								/* 套接口 */
    yy_f_message_block_t * snd_buf;					/* 发送缓存 */
    yy_f_message_block_t * rcv_buf;					/* 接收缓存 */
    int last_sock_err;								/* 套接口错误码 */
    YY_E_MEM_MAGIC_SUFFIX_DEFINE;
}yy_g_url_stream_t;

/* 创建http请求处理任务 */
extern yy_g_url_stream_t * yy_g_url_stream_create( yy_f_alloc_t * alloc, yy_f_reactor_t * r, yy_g_url_stream_state_cb_t f_state_cb, void * user_data );
/* 启动任务 */
extern int yy_g_url_stream_start( yy_g_url_stream_t * us );
/* 停止任务 */
extern int yy_g_url_stream_stop( yy_g_url_stream_t * us );
/* 释放资源 */
extern void yy_g_url_stream_release( yy_g_url_stream_t * us );

/*
功能：连接超时设置

*/
extern int yy_g_url_stream_set_connectting_timeout( yy_g_url_stream_t * us, yy_p_uint32 ms );

/*
功能：数据头接收超时
*/
extern int yy_g_url_stream_set_recv_head_timeout( yy_g_url_stream_t * us, yy_p_uint32 ms );
/* 任务初始化 */
extern int yy_g_url_stream_init( yy_g_url_stream_t * us, const char * url );
/* 获取http请求解析结构体 */
extern yy_e_http_parser_t * yy_g_url_stream_req( yy_g_url_stream_t * us );
/* 准备开始 */
extern int yy_g_url_stream_prepare_start( yy_g_url_stream_t * us, const char * content_data, size_t content_len );
/* 获取任务状态 */
extern int yy_g_url_stream_get_state( yy_g_url_stream_t * us, yy_g_url_stream_state_t * state, yy_g_url_stream_err_t *err );
/* 获取http响应解析结构体 */
extern yy_e_http_parser_t * yy_g_url_stream_rep( yy_g_url_stream_t * us );
/* 获取http响应body */
extern int yy_g_url_stream_get_rep_content( yy_g_url_stream_t * us, char ** content_data, size_t * content_len );

/* 使用阻塞方式处理http请求 */
extern int yy_g_url_stream_block_handle( yy_f_alloc_t * alloc, const char *host, const char *req, const size_t req_len, yy_e_http_parser_t ** rep, yy_f_message_block_t ** recv_content, const yy_p_uint32 time_out_ms);

extern int yy_g_url_stream_validation_test( const char * url );

#endif
