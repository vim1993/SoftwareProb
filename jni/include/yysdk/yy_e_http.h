#ifndef YY_E_HTTP_H
#define YY_E_HTTP_H
#include "yy_p_type.h"
#include "yy_f_alloc.h"

#if defined( YY_E_HTTP_CONTENT_32 )
	typedef yy_p_uint32 yy_e_http_content_t;		/* ��32λ��ʾhttp���ݳ��� */
	#define YY_E_PRI_HTTP_CONTENT_T "%u"
#else
	typedef yy_p_uint64 yy_e_http_content_t;
	#define YY_E_PRI_HTTP_CONTENT_T "%llu"		/* ��64λ��ʾhttp���ݳ��� */
#endif

#define YY_E_INVALID_HTTP_CONTENT_T (yy_e_http_content_t)-1

    typedef enum yy_e_http_range_type_e{
        yy_e_http_range_type_null,
        yy_e_http_range_type_start,			//RANGEֻ�п�ʼ,û��ָ������
        yy_e_http_range_type_start_end,		//RANGEָ���˿�ʼ�����
		yy_e_http_range_type_end_start,		//RANGEָ���˴ӽ���������������
		yy_e_http_range_type_auto_full		//������ȫ������,���Բ���Ҫָ����ʼ�����		
    }yy_e_http_range_type_t;

	/* ����range�ֶεĽṹ�� */
    typedef struct yy_e_http_range_s
    {
        yy_e_http_range_type_t type;	/* range������ */
        yy_e_http_content_t start;		/* range�Ŀ�ʼ */
        yy_e_http_content_t end;		/* range�Ľ��� */
        yy_e_http_content_t content;	/* range�ֶ���ָ�ĳ��� */
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
/* ��ȡuri�е�host�ֶΣ�������:�˿�(example.com:8042)���˿ںŷǱ��� */
extern const char * yy_e_http_parse_host( const char * uri, size_t uri_len, size_t *ret_len );

/* ��ȡuri�е�ģʽ�ֶΣ���http, ftp, rtsp */
extern const char * yy_e_http_parse_scheme( const char * uri, size_t uri_len, size_t *ret_len );

/* ��ȡuri�е���Դ����,��ip�ֶκ���������ַ���(over/there?name=ferret#nose) */
extern const char * yy_e_http_parse_req( const char * uri, size_t uri_len, size_t *ret_len );

/* ��ȡrange�ֶ�ֵ�еĿ�ʼ�ͽ���λ�� */
extern int yy_e_http_parse_range( const char * range, size_t len, yy_e_http_range_t * v );

/* ���http��buf�Ƿ���ȷ(��http����buf��http��Ӧbuf) */
extern size_t yy_e_http_parse_head_ok( const char * buf, size_t len );

/* ���һ�������Ƿ�����(���Ƿ���\r\n��β) */
extern size_t yy_e_http_parse_line_ok( const char * buf, size_t len );

/* �ж�buf�Ƿ����http�������http��Ӧ */
extern size_t yy_e_http_parse_packet_ok( const char * buf, size_t len );

//20150830 terry �˺�������δ��ɣ���Ҫʹ��
/* ���http��Ϣ�ַ���head�е�ĳһ���ǲ�����name�ַ���Ϊ��ʼ */
extern const char * yy_e_http_parse_head_value( const char * head, size_t len, const char * name, size_t * ret_len );

/* ��ȡline�е�code�ֶΣ��������ո�' '֮�������(һ���ǻ�ȡhttp�����һ���е�uri) */
extern const char * yy_e_http_parse_code( const char * line, size_t len, size_t *ret_len );

/* ���ַ���sת����ʮ��������(������һ���������ַ���ֹͣ) */
extern yy_e_http_content_t yy_e_http_str_to_content_len( const char * s );

/* ��ʮ���������buf�ַ������� */
extern int yy_e_http_content_len_to_str( yy_e_http_content_t v, char * buf, size_t len );

/* ����HTTP��ʽʱ�� */
extern int yy_e_http_get_date( char * str, size_t len, time_t t );

/* URL����,�����Ĵ�ֻ���ܱ�� */
extern int yy_e_uri_decode( const char * uri, char * decoded );

/* URL����,�����Ĵ����ܱ䳤 */
extern int yy_e_uri_encode( const char * uri, char * encoded, size_t en_buf_len );


#endif
