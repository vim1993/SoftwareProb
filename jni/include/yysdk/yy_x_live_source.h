#ifndef YY_X_LIVE_SOURCE_H
#define YY_X_LIVE_SOURCE_H
#include "yy_p_type.h"
#include "yy_f_log.h"
#include "yy_f_alloc.h"
#include "yy_f_reactor.h"

#define YY_X_LIVE_SOURCE_E_UNKNOWN -1

#define YY_X_LIVE_SOURCE_S_NULL                 0
#define YY_X_LIVE_SOURCE_S_INITED               1
#define YY_X_LIVE_SOURCE_S_STARTED              2
#define YY_X_LIVE_SOURCE_S_RESOLVE_DNS          3
#define YY_X_LIVE_SOURCE_S_CONNECTING           4
#define YY_X_LIVE_SOURCE_S_CONNECTTED           5
#define YY_X_LIVE_SOURCE_S_PREPARING_META       6
#define YY_X_LIVE_SOURCE_S_META_READY           7
#define YY_X_LIVE_SOURCE_S_RECV_DATA            8
#define YY_X_LIVE_SOURCE_S_INTERRUPT            9
#define YY_X_LIVE_SOURCE_S_END                  10
#define YY_X_LIVE_SOURCE_S_ERROR                11

typedef enum yy_x_live_source_data_type_s
{
	yy_x_live_source_data_type_mp3=1,
	yy_x_live_source_data_type_aac,
	yy_x_live_source_data_type_h264,
}yy_x_live_source_data_type_t;

typedef struct yy_x_live_source_pack_data_s
{
	yy_x_live_source_data_type_t data_type;
	yy_p_uint64 decode_ms;
	yy_p_uint64 picture_ms;
	yy_p_uint8 *head_data;
	yy_p_uint32 head_data_len;
	yy_p_uint8 *data;//数据
	yy_p_uint32 data_len;//数据长度
	int is_keyframe;//1:关键帧
}yy_x_live_source_pack_data_t;


//最多同时支持16个地址
#define YY_X_LIVE_SOURCE_URLS_MAX 16

//数据
#define YY_X_LIVE_SOURCE_DATA_TYPE_DATA					0
//流文件头
#define YY_X_LIVE_SOURCE_DATA_TYPE_STREAM_HEADER		1
//分块数据头
#define YY_X_LIVE_SOURCE_DATA_TYPE_CHUNK_HEADER			2
//打包数据
#define YY_X_LIVE_SOURCE_DATA_TYPE_PACK_DATA			3 /*值为yy_x_live_source_packdata_t结构*/



//分片对应的M3U8文件参数
#define CHUNK_M3U8_DATA_LEN            (1024*2)       // 分片对应的M3U8数据长度
#define CHUNK_M3U8_HEADER_LEN          1024           // 分片对应的M3U8头的长度，第一个#EXTINF标签前面的内容
#define M3U8_KEY_LEN		           256            // M3U8密钥信息长度，#EXT-X-KEY标签冒号后面的内容
#define M3U8_PROGRAM_DATE_TIME_LEN     64             // #EXT-X-PROGRAM-DATE-TIME 标签的文本长度

typedef struct yy_x_live_source_data_type_chunk_header_s
{
	time_t		t_chunk;	//分块的开始时间,如果没有，赋值为0
	size_t		s_chunk;	//分块的数据长度
	yy_p_uint32 t_len;	//分块的时间长度
	yy_p_uint64	seq;		//分块序列号
	
	//以下参数用于计算传输延迟
	time_t chunk_ts_recv_time_s;          //中心接收到分片的开始时间(秒)
	yy_p_uint32 chunk_ts_recv_time_ms;    //中心形成分片的时间(毫秒部分)

	//以下为兼容DRM新增内容
	char chunk_m3u8_data[CHUNK_M3U8_DATA_LEN];     // 分片对应的m3u8文件内容
	
	char chunk_ts_filename[YY_P_MAX_PATH];	       // ts分片的文件名
	char chunk_m3u8_key[M3U8_KEY_LEN];			   // 分片的密钥信息，#EXT-X-KEY标签冒号后面的字符串

}yy_x_live_source_data_type_chunk_header_t;

/* 当前状态结构体 */
typedef struct yy_x_live_source_state_s{
    int s;					/* 当前的状态码 */
	int ex_s;				/* 上一个状态码 */
}yy_x_live_source_state_t;

/* 错误状态结构体 */
typedef struct yy_x_live_source_err_s{
    int e_code;				/* 当前错误码 */
    int ex_e_code;			/* 上一个错误码 */
}yy_x_live_source_err_t;

/*统计状态结构体*/
typedef enum yy_x_enum_live_source_status_s
{
	yy_x_enum_live_source_ok = 0,               //信源正常
	yy_x_enum_live_source_unknown_error,        //未知错误
	yy_x_enum_live_source_connect_overtime,     //网络连接超时
	yy_x_enum_live_source_recv_data_overtime,   //接收数据超时
}yy_x_enum_live_source_status_t;

/*统计状态*/
typedef struct yy_x_live_source_stat_s{
	char url[1024];				//当前正在使用的URL地址
	size_t url_index;           //当前URL的索引
    size_t flow_recv_kbps;      //接收码流
    size_t flow_recv_pps;       //每秒接收的包数量(UDP协议接收时,有价值)
    time_t start_time;          //流开始运行的时间
    size_t connect_times;       //连接计数
	time_t last_connect_time;   //最近一次连接的时间
	size_t today_connect_times;	//当天已经连接的计数
	size_t today_error_times;   //当天错误次数
	char reason[1024];          //错误原因

	yy_x_enum_live_source_status_t status_code;  //状态码
    yy_x_live_source_state_t state;	/* 状态结构体 */
    yy_x_live_source_err_t err;		/* 错误结构体 */
}yy_x_live_source_stat_t;

/* 解析到数据成功回调 */
typedef void (*yy_x_live_source_data_cb_t)( void * user_data, int type, const void * data, size_t len );

/* 定时器超时回调 */
typedef void (*yy_x_live_source_timer_cb_t)( void * user_data );

/* 状态改变回调 */
typedef void (*yy_x_live_source_state_cb_t)( void * user_data, const yy_x_live_source_state_t * pre_state, const yy_x_live_source_state_t * state, yy_x_live_source_err_t * err );

/* 初始化各个视频结构体的结构体 */
typedef struct yy_x_live_source_arg_s{
    yy_f_alloc_t * alloc;			/* 内存分配器 */
    const char * reactor_name;		/* 反应器模式 */
    size_t reactor_fd_size;		/* 反应器能处理的句柄数 */
    void * user_data;				/* 用户自定义数据 */
    yy_f_log_t * log;				/* 日志 */

    yy_x_live_source_data_cb_t f_data_cb;		/* 数据回调函数 */ 
    yy_x_live_source_state_cb_t f_state_cb;		/* 状态回调函数 */
    yy_x_live_source_timer_cb_t f_timer_cb;		/* 定时器超时回调函数 */

    size_t data_cb_size;		//仅对部分格式有用,比如TS,这个值可以是188倍数
    const char * url;			/* 频道的源地址，如果有多个，用;分开 */
	
	const char * id;			/* 内容id */
	const char * file_type;	/* 文件类型 */
	
	
	int is_save_to_file;		/* 是否保存成文件 */
	const char * data_path;	/* 数据目录 */
	yy_p_uint32 disk_time_delay;/* 支持的时延长度,秒,磁盘的最大数据量 */
    yy_p_uint32 disk_file_time_len;	/* 文件的分片长度,为秒 */  
	
	int is_save_ts_url;       //是否保存原始分片地址
	int is_create_hls_data_time_tag; //2015/12/30 sk:hls直播如果#EXT-X-PROGRAM-DATE-TIME不存在,是否主动创建
}yy_x_live_source_arg_t;


typedef yy_f_reactor_t* (*yy_x_live_source_get_reactor)(void * thiz );
typedef void (*yy_x_live_source_release_t)(void * thiz );
typedef int (*yy_x_live_source_begin_thread_t)(void * thiz );
typedef int (*yy_x_live_source_end_thread_t)(void * thiz );
typedef int (*yy_x_live_source_get_state_t)(void * thiz, yy_x_live_source_state_t * state, yy_x_live_source_state_t * pre_state, yy_x_live_source_err_t * err );
typedef int (*yy_x_live_source_get_meta_t)(void * thiz, int type, void * buf, size_t * inout_len );
typedef int (*yy_x_live_source_get_stat_t)(void * thiz, yy_x_live_source_stat_t * stat );
typedef int (*yy_x_live_source_modify_t)(void * thiz , yy_x_live_source_arg_t * arg );

typedef struct yy_x_live_source_op_s{
	char type[16];							/* live_source的名字 */
	yy_x_live_source_get_reactor f_get_reactor;	/* 获取反应器 */
	yy_x_live_source_release_t f_release;		/* 释放source结构体 */
	yy_x_live_source_begin_thread_t f_begin_thread;/* 开启线程 */
	yy_x_live_source_end_thread_t f_end_thread;	/* 结束线程 */
	yy_x_live_source_get_state_t f_get_state;	/* 获取当前状态，上一个状态，错误状态 */
	yy_x_live_source_get_meta_t f_get_meta;		/* 获取头文件信息其大小 */
	yy_x_live_source_get_stat_t f_get_stat;		/* 获取处理流程中的状态，区别于state */ 
	yy_x_live_source_modify_t f_modify;
}yy_x_live_source_op_t;
typedef struct yy_x_live_source_s{    
    void *thiz;					/* 指向外面的结构体 */
	yy_x_live_source_op_t * op;		/* 定位于不同的操作 */
}yy_x_live_source_t;

#define YY_X_LIVE_SOURCE_REACTOR( ls )        (ls)->op->f_get_reactor( (ls)->thiz )
#define YY_X_LIVE_SOURCE_RELEASE( ls )        (ls)->op->f_release( (ls)->thiz )
#define YY_X_LIVE_SOURCE_BEGIN_THREAD( ls )   (ls)->op->f_begin_thread( (ls)->thiz )
#define YY_X_LIVE_SOURCE_END_THREAD( ls )     (ls)->op->f_end_thread( (ls)->thiz )
#define YY_X_LIVE_SOURCE_GET_STATE( ls, state, pre_state, err )      (ls)->op->f_get_state( (ls)->thiz, state, pre_state, err )
#define YY_X_LIVE_SOURCE_GET_META( ls, type, buf, inout_len )        (ls)->op->f_get_meta( (ls)->thiz, type, buf, inout_len )
#define YY_X_LIVE_SOURCE_GET_STAT( ls, stat )        (ls)->op->f_get_stat( (ls)->thiz, stat )
#define YY_X_LIVE_SOURCE_MODIFY( ls, arg )        (ls)->op->f_modify( (ls)->thiz, arg )

/* 获取当前播放的状态 */
extern const char * yy_x_live_source_state_2_string( int s );
#endif
