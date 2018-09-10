#ifndef YY_E_HTTP_H
#define YY_E_HTTP_H
#include "yy_p_type.h"
#include "yy_f_alloc.h"

#if defined( YY_E_HTTP_CONTENT_32 )
	typedef yy_p_uint32 yy_e_http_content_t;		/* 用32位表示http内容长度 */
	#define YY_E_PRI_HTTP_CONTENT_T "%u"
#else
	typedef yy_p_uint64 yy_e_http_content_t;
	#define YY_E_PRI_HTTP_CONTENT_T "%llu"		/* 用64位表示http内容长度 */
#endif

#define YY_E_INVALID_HTTP_CONTENT_T (yy_e_http_content_t)-1

    typedef enum yy_e_http_range_type_e{
        yy_e_http_range_type_null,
        yy_e_http_range_type_start,			//RANGE只有开始,没有指定结束
        yy_e_http_range_type_start_end,		//RANGE指定了开始与结束
		yy_e_http_range_type_end_start,		//RANGE指定了从结束反向下载内容
		yy_e_http_range_type_auto_full		//请求了全部数据,所以不需要指定开始与结束		
    }yy_e_http_range_type_t;

	/* 解析range字段的结构体 */
    typedef struct yy_e_http_range_s
    {
        yy_e_http_range_type_t type;	/* range的类型 */
        yy_e_http_content_t start;		/* range的开始 */
        yy_e_http_content_t end;		/* range的结束 */
        yy_e_http_content_t content;	/* range字段所指的长度 */
    }yy_e_http_range_t;
/*
The following are two example URIs and their component parts:
foo://example.com:8042/over/there?name=ferret#nose
\_/ \______________/\_________/ \_________/ \__/
| | | | |
scheme authority path query fragment
| _____________________|__
/ \ / \
urn:example:animal:ferret:nose
*/
/* 获取uri中的host字段，即主机:端口(example.com:8042)，端口号非必需 */
extern const char * yy_e_http_parse_host( const char * uri, size_t uri_len, size_t *ret_len );

/* 获取uri中的模式字段，如http, ftp, rtsp */
extern const char * yy_e_http_parse_scheme( const char * uri, size_t uri_len, size_t *ret_len );

/* 获取uri中的资源请求串,即ip字段后面的所有字符串(over/there?name=ferret#nose) */
extern const char * yy_e_http_parse_req( const char * uri, size_t uri_len, size_t *ret_len );

/* 获取range字段值中的开始和结束位置 */
extern int yy_e_http_parse_range( const char * range, size_t len, yy_e_http_range_t * v );

/* 检测http的buf是否正确(即http请求buf和http相应buf) */
extern size_t yy_e_http_parse_head_ok( const char * buf, size_t len );

/* 检测一行数据是否完整(即是否以\r\n结尾) */
extern size_t yy_e_http_parse_line_ok( const char * buf, size_t len );

/* 判断buf是否包含http请求或者http相应 */
extern size_t yy_e_http_parse_packet_ok( const char * buf, size_t len );

//20150830 terry 此函数功能未完成，不要使用
/* 检测http消息字符串head中的某一行是不是以name字符串为开始 */
extern const char * yy_e_http_parse_head_value( const char * head, size_t len, const char * name, size_t * ret_len );

/* 获取line中的code字段，即两个空格' '之间的数据(一般是获取http请求第一行中的uri) */
extern const char * yy_e_http_parse_code( const char * line, size_t len, size_t *ret_len );

/* 将字符串s转化成十进制数字(遇到第一个非数字字符即停止) */
extern yy_e_http_content_t yy_e_http_str_to_content_len( const char * s );

/* 将十进制输出到buf字符数组中 */
extern int yy_e_http_content_len_to_str( yy_e_http_content_t v, char * buf, size_t len );

/* 返回HTTP格式时间 */
extern int yy_e_http_get_date( char * str, size_t len, time_t t );

/* URL解码,解码后的串只可能变短 */
extern int yy_e_uri_decode( const char * uri, char * decoded );

/* URL编码,编码后的串可能变长 */
extern int yy_e_uri_encode( const char * uri, char * encoded, size_t en_buf_len );


#endif
