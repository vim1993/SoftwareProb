#ifndef YY_E_URI_PARSER_H
#define YY_E_URI_PARSER_H
#include "yy_e_http.h"
#include "yy_e_memcheck.h"
#include "yy_s_lxlist.h"
#include "yy_f_alloc.h"

/* 枚举uri解析的状态类型 */
typedef enum yy_e_uri_parser_state_e{
    yy_eups_error = -1,
    yy_eups_ok,
    yy_eups_start,
    yy_eups_scheme,
    yy_eups_scheme_colon,
    yy_eups_scheme_slash,
    yy_eups_scheme_slash2,
    yy_eups_hostport,
    yy_eups_url_path,
    yy_eups_query_start,
    yy_eups_query_name,
    yy_eups_query_value,
    //yy_eups_fragment_start,
    yy_eups_fragment

}yy_e_uri_parser_state_t;

/* header结构体( 即?a=b&c=d#fragment，获取其中的a=b，c=d) */
typedef struct yy_e_uri_header_s{
    yy_s_lxlist_head_t list_query;	/* 链表头，用于悬挂到uri解析结构体中 */
    char * name_encoded;			/* 未编码前的name */
    char * value_encoded;			/* 未编码前的name的值 */
    char * name_decoded;			/* 编码后的name */
    char * value_decoded;			/* 编码后的name的值(这里的编码时将十六进制转化成对应的字符) */
}yy_e_uri_header_t;

/* 路径目录结构体(即url path标签中的多级目录 /001/002/003.m3u8,获取其中的001，002) */
typedef struct yy_e_uri_path_index_s{
	yy_s_lxlist_head_t list_path;	/* 链表头，用于挂载到uri解析结构体中 */
	char * path_encoded;			/* 未编码前的path */
	char * path_decoded;			/* 解码后的path */
}yy_e_uri_path_index_t;

/* uri解析结构体 */
typedef struct yy_e_uri_parser_s{
    YY_E_MEM_MAGIC_PREFIX_DEFINE;    
    yy_f_alloc_t * alloc_nfp;		/* 内存分配器 */

	//分析状态机
    yy_e_uri_parser_state_t pre_state;	/* 用于保存uri解析的前一个状态 */
    yy_e_uri_parser_state_t state;	/* uri解析当前状态 */
   

	//参数
    yy_s_lxlist_head_t query;		/* 链表头，用于挂载header结构体 */
	yy_s_lxlist_head_t path_index;	/* 链表头，用于挂载path结构体 */
  
    char * uri_part[16];			 /* 存储对应标签未解码的值 */
    char * uri_part_decoded[16];	/* 存储对应标签解码解码后的值 */

    //char * url_path_filename_noext;

    //分析临时
    size_t parsed_len;			/* uri的长度 */
    const char * tmp_pb;		/* 临时数据地址起始 */
    const char * tmp_pe;		/* 临时数据地址结束 */
    char * tmp_name;			/* 临时数据name */
    char * tmp_value;			/* 临时数据对应的值 */

    YY_E_MEM_MAGIC_SUFFIX_DEFINE;
}yy_e_uri_parser_t;

/* 从指定的分配器生成 */
extern yy_e_uri_parser_t * yy_e_uri_parser_create( yy_f_alloc_t * alloc_thiz, size_t block_size );

/* 从一定指定的内存上进行创建,一般为静态栈空间 */
extern yy_e_uri_parser_t * yy_e_uri_parser_create2( char * buf, size_t block_size );

/* 摧毁uri解析结构体eup */
extern void yy_e_uri_parser_destroy( yy_e_uri_parser_t * eup );

/* 返回已经分析了的长度 */
extern size_t yy_e_uri_parser_parsed_len( yy_e_uri_parser_t * eup );

/* 通过uri解析结构体eup解析uri */
extern int yy_e_uri_parser_parse( yy_e_uri_parser_t * eup, const char * buf, size_t len );

/* 从uri解析结构体中获取hostport */
extern const char * yy_e_uri_parser_get_hostport( yy_e_uri_parser_t * eup );

/* 设置uri解析结构体eup中的hostport */
extern int yy_e_uri_parser_set_hostport( yy_e_uri_parser_t * eup, const char * hostport );

/* 读取URL中，host之后，?之前的字符串 */
extern const char * yy_e_uri_parser_get_url_path( yy_e_uri_parser_t * eup, int is_decoded );

/* 从uri解析结构体eup中获取第index的path */
extern const char * yy_e_uri_parser_get_url_path_index( yy_e_uri_parser_t * eup, size_t index, int is_decoded ); 

/* 从uri解析结构体eup中获取after_url_path */
extern const char * yy_e_uri_parser_get_all_after_url_path( yy_e_uri_parser_t * eup, int is_decoded );

/* 从uri解析结构体eup中获取filename */
extern const char * yy_e_uri_parser_get_filename( yy_e_uri_parser_t * eup, int is_decoded );

/* 从uri解析结构体eup中获取filename_noext */
extern const char * yy_e_uri_parser_get_filename_noext( yy_e_uri_parser_t * eup, int is_decoded );

/* 从uri解析结构体eup中获取fileext */
extern const char * yy_e_uri_parser_get_fileext( yy_e_uri_parser_t * eup, int is_decoded );

/* 从uri解析结构体eup中获取full_url_path */
extern const char * yy_e_uri_parser_get_full_url_path( yy_e_uri_parser_t * eup, int is_decoded );

/* 从uri解析结构体eup中获取name对应的值 */
extern const char * yy_e_uri_parser_get_query( yy_e_uri_parser_t * eup, const char * name, int is_decoded );

/* 从uri解析结构体eup中获取name1对应的值，如果值为NULL，则继续获取name2对应的值,返回name2的值，如果不为NULL，则返回name1的值 */
extern const char * yy_e_uri_parser_get_mquery( yy_e_uri_parser_t * eup, const char * name1, const char * name2, int is_decoded );

/* 增加一个从3个参数查询的功能，前面任一个查找到后，不执行后续的查询 */
extern const char * yy_e_uri_parser_get_mquery3( yy_e_uri_parser_t * eup, const char * name1, const char * name2, const char * name3, int is_decoded );

/* 从uri解析结构体eup中获取scheme */
extern const char * yy_e_uri_parser_get_scheme( yy_e_uri_parser_t * eup, int is_decoded );

/* 添加name和name对应的值添加到uri解析结构体eup链表query中 */
extern int yy_e_uri_parser_add_query( yy_e_uri_parser_t * eup, const char * name, const char * value, int is_encoded );

/* 添加name和name对应的值添加到uri解析结构体eup链表query中(这里的value是整数型) */
extern int yy_e_uri_parser_add_query_int( yy_e_uri_parser_t * eup, const char * name, int value, int is_encoded );

/* 从uri解析结构体eup链表query中删除包含name的节点 */
extern int yy_e_uri_parser_del_query( yy_e_uri_parser_t * eup, const char * name );

/* 从uri解析结构体eup链表query中获取第一个节点 */
extern yy_e_uri_header_t * yy_e_uri_parser_query_first( yy_e_uri_parser_t * eup );

/* 从uri解析结构体eup链表query中获取h节点的下一个节点 */
extern yy_e_uri_header_t * yy_e_uri_parser_query_next( yy_e_uri_parser_t * eup, yy_e_uri_header_t * h );

/*
SK,生成已经编码了的地址
http://10.1.1.1:80/abc/xxx.ts
成功，返回0
失败 
inout_len 进是缓冲长度，出是已经写入长度
*/
extern int yy_e_uri_parser_build_full_uri( yy_e_uri_parser_t * eup, char * buf, size_t * inout_len );

/* 未完整实现,暂匆使用 */
extern int yy_e_uri_parser_build_uri( yy_e_uri_parser_t * eup, char * buf, size_t * inout_len );

/* 测试用例 http://127.0.0.1:9906/abc/def/g.aa?a=b&c=d#eee */
extern int yy_e_uri_parser_validation_test();

#endif
