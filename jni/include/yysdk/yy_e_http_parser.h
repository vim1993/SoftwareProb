#ifndef YY_E_HTTP_PARSER_H
#define YY_E_HTTP_PARSER_H
#include "yy_f_alloc.h"
#include "yy_e_string.h"
#include "yy_e_memcheck.h"
#include "yy_s_lxlist.h"
#include "yy_e_http.h"

/* 解析http的状态码 GET /abc HTTP/1.1\r\nVA1\r\nVA2 :\r\nVA3:BB\r\n\r\n */
typedef enum yy_e_http_parser_state_e{
    yy_ehps_error = -1,
    yy_ehps_ok = 0,
    yy_ehps_start,
    yy_ehps_l1_v0,
    yy_ehps_l1_sp_bf_v1,
    yy_ehps_l1_v1,
    yy_ehps_l1_sp_bf_v2,
    yy_ehps_l1_v2,
    yy_ehps_l1_sp_af_v2,
    yy_ehps_header_lf,
	yy_ehps_header_start,
	yy_ehps_header_name,
	yy_ehps_sp_bf_value,
	yy_ehps_header_value,
	yy_ehps_sp_af_value,
	yy_ehps_last_header_lf
}yy_e_http_parser_state_t;

/* http头域结构体 */
typedef struct yy_e_http_header_s{
    yy_s_lxlist_head_t list_header;	/* 链表 */
    char * name;					/* 头域名字 */
    char * value;					/* 头域对应的值 */
}yy_e_http_header_t;

/* http解析结构体 */
typedef struct yy_e_http_parser_s{
    YY_E_MEM_MAGIC_PREFIX_DEFINE;
    //第一行的前3个参数
    yy_f_alloc_t * alloc_thiz;      /* 用于结构体本身基本池 */
    yy_f_alloc_t * alloc_nfp;       /* 用于分配内存池 */
    char * line1_v[4];			 /* 第一行的前3个参数 */
    
    yy_s_lxlist_head_t header;		/* 装载头域的链表 */

    yy_e_http_parser_state_t pre_state;	/* 上一个分析状态 */
    yy_e_http_parser_state_t state;  /* 当前的分析状态 */
    size_t parsed_len;  /* 已经分析了的长度 */


    //分析过程中的缓存信息
    char * tmp_name;			/* 临时字段 */
    char * tmp_value;			/* 临时字段的值 */
    const char * tmp_pb;		/* 临时字段开始位置 */
    const char * tmp_pe;		/* 临时字段结束位置 */

    YY_E_MEM_MAGIC_SUFFIX_DEFINE;
}yy_e_http_parser_t;

/* 创建http解析结构体yy_e_http_parser_t */
extern yy_e_http_parser_t * yy_e_http_parser_create( yy_f_alloc_t * alloc_thiz, size_t block_size );

/* 摧毁http解析结构体ehp */
extern void yy_e_http_parser_destroy( yy_e_http_parser_t * ehp );

/* 通过http解析结构体ehp解析http消息buf */
extern int yy_e_http_parser_parse( yy_e_http_parser_t * ehp, const char * buf, size_t len, size_t *thiz_parsed_len );

/* 获取http消息的大小 */
extern size_t yy_e_http_parser_parsed_len( yy_e_http_parser_t * ehp );

/* 获取http消息第一行对应字段index的值 */
extern const char * yy_e_http_parser_get_line1_v( yy_e_http_parser_t * ehp, size_t index );

/* 设置http消息第一行第index字段的值 */
extern int yy_e_http_parser_set_line1_v( yy_e_http_parser_t * ehp, size_t index, const char * vv );

/* 获取name头域在http解析结构体ehp中对应的值 */
extern const char * yy_e_http_parser_get_header( yy_e_http_parser_t * ehp, const char * name );
extern const char * yy_e_http_parser_get_header2( yy_e_http_parser_t * ehp, const size_t index, const char * name );

/* 将http解析结构体ehp中name头域对应的值换成value，如果没有name头域，就创建一个新的头域 */
extern int yy_e_http_parser_set_header( yy_e_http_parser_t * ehp, const char * name, const char * value );

/* 将http解析结构体ehp中name头域对应的值换成value，如果没有name头域，就创建一个新的头域(与上不同在于这个value为整数 */
extern int yy_e_http_parser_set_header_int( yy_e_http_parser_t * ehp, const char * name, int value );

/* 在http解析结构体中添加上一个header头域以及对应的值 */
extern int yy_e_http_parser_add_header( yy_e_http_parser_t * ehp, const char * name, const char * value );

/* 在http解析结构体中添加上一个header头域以及对应的值(整数) */
extern int yy_e_http_parser_add_header_uint32( yy_e_http_parser_t * ehp, const char * name, yy_p_uint32 value );

/* 从http解析结构体中移除包含name头域的节点 */
extern int yy_e_http_parser_remove_header( yy_e_http_parser_t * ehp, const char * name );

/* 检测http解析结构体中是否包含name头域 */
extern int yy_e_http_parser_is_header_exist( yy_e_http_parser_t * ehp, const char * name );

/* 一些特殊用处的头 */
/* 从http解析结构体ehp中获取content_length头域的值 */
extern yy_e_http_content_t yy_e_http_parser_get_content_length( yy_e_http_parser_t * ehp );

/* 设置http解析结构体ehp中content_length头域的值 */
extern int yy_e_http_parser_set_content_length( yy_e_http_parser_t * ehp, yy_e_http_content_t v );

/* 从http解析结构体ehp中移除content_length头域对应的节点 */
extern int yy_e_http_parser_remove_content_length( yy_e_http_parser_t * ehp );

/* 检测http解析结构体ehp中content_length头域对应的值是否存在 */
extern int yy_e_http_parser_has_content_length( yy_e_http_parser_t * ehp );

/* 设置http解析结构体ehp中content_range头域的值 */
extern int yy_e_http_parser_set_content_range( yy_e_http_parser_t * ehp, yy_e_http_range_t v );

/* 从http解析结构体ehp中移除content_range头域对应的节点 */
extern int yy_e_http_parser_remove_content_range( yy_e_http_parser_t * ehp );

/* 生成一个请求或是回应 */
extern int yy_e_http_parser_build_packet( yy_e_http_parser_t * ehp, char * buf, size_t * inout_len );

/***********************************************************************************
*   功能：获取http分析器的第一个header
*   @param :
*           yy_e_http_parser_t *ehp    http分析器实例
*   @return：
*           第一个header指针,如果不存在返回NULL
*   @date：
*           2015/06/04      sk     创建
************************************************************************************/
extern yy_e_http_header_t* yy_e_http_parser_first_header( yy_e_http_parser_t * ehp );

/***********************************************************************************
*   功能：获取http分析器中header的下一个header
*   @param :
*           yy_e_http_parser_t *ehp			http分析器实例
*			yy_e_http_header_t * header		当前的header指针
*   @return：
*           header的下一个headerr指针,如果不存在返回NULL
*   @date：
*           2015/06/04      sk     创建
************************************************************************************/
extern yy_e_http_header_t*  yy_e_http_parser_next_header( yy_e_http_parser_t * ehp, yy_e_http_header_t * header );

/* 测试用例 */
extern int yy_e_http_parser_validation_test();

#endif
