#ifndef YY_E_HTTP_PARSER_H
#define YY_E_HTTP_PARSER_H
#include "yy_f_alloc.h"
#include "yy_e_string.h"
#include "yy_e_memcheck.h"
#include "yy_s_lxlist.h"
#include "yy_e_http.h"

/* ����http��״̬�� GET /abc HTTP/1.1\r\nVA1\r\nVA2 :\r\nVA3:BB\r\n\r\n */
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

/* httpͷ��ṹ�� */
typedef struct yy_e_http_header_s{
    yy_s_lxlist_head_t list_header;	/* ���� */
    char * name;					/* ͷ������ */
    char * value;					/* ͷ���Ӧ��ֵ */
}yy_e_http_header_t;

/* http�����ṹ�� */
typedef struct yy_e_http_parser_s{
    YY_E_MEM_MAGIC_PREFIX_DEFINE;
    //��һ�е�ǰ3������
    yy_f_alloc_t * alloc_thiz;      /* ���ڽṹ�屾������� */
    yy_f_alloc_t * alloc_nfp;       /* ���ڷ����ڴ�� */
    char * line1_v[4];			 /* ��һ�е�ǰ3������ */
    
    yy_s_lxlist_head_t header;		/* װ��ͷ������� */

    yy_e_http_parser_state_t pre_state;	/* ��һ������״̬ */
    yy_e_http_parser_state_t state;  /* ��ǰ�ķ���״̬ */
    size_t parsed_len;  /* �Ѿ������˵ĳ��� */


    //���������еĻ�����Ϣ
    char * tmp_name;			/* ��ʱ�ֶ� */
    char * tmp_value;			/* ��ʱ�ֶε�ֵ */
    const char * tmp_pb;		/* ��ʱ�ֶο�ʼλ�� */
    const char * tmp_pe;		/* ��ʱ�ֶν���λ�� */

    YY_E_MEM_MAGIC_SUFFIX_DEFINE;
}yy_e_http_parser_t;

/* ����http�����ṹ��yy_e_http_parser_t */
extern yy_e_http_parser_t * yy_e_http_parser_create( yy_f_alloc_t * alloc_thiz, size_t block_size );

/* �ݻ�http�����ṹ��ehp */
extern void yy_e_http_parser_destroy( yy_e_http_parser_t * ehp );

/* ͨ��http�����ṹ��ehp����http��Ϣbuf */
extern int yy_e_http_parser_parse( yy_e_http_parser_t * ehp, const char * buf, size_t len, size_t *thiz_parsed_len );

/* ��ȡhttp��Ϣ�Ĵ�С */
extern size_t yy_e_http_parser_parsed_len( yy_e_http_parser_t * ehp );

/* ��ȡhttp��Ϣ��һ�ж�Ӧ�ֶ�index��ֵ */
extern const char * yy_e_http_parser_get_line1_v( yy_e_http_parser_t * ehp, size_t index );

/* ����http��Ϣ��һ�е�index�ֶε�ֵ */
extern int yy_e_http_parser_set_line1_v( yy_e_http_parser_t * ehp, size_t index, const char * vv );

/* ��ȡnameͷ����http�����ṹ��ehp�ж�Ӧ��ֵ */
extern const char * yy_e_http_parser_get_header( yy_e_http_parser_t * ehp, const char * name );
extern const char * yy_e_http_parser_get_header2( yy_e_http_parser_t * ehp, const size_t index, const char * name );

/* ��http�����ṹ��ehp��nameͷ���Ӧ��ֵ����value�����û��nameͷ�򣬾ʹ���һ���µ�ͷ�� */
extern int yy_e_http_parser_set_header( yy_e_http_parser_t * ehp, const char * name, const char * value );

/* ��http�����ṹ��ehp��nameͷ���Ӧ��ֵ����value�����û��nameͷ�򣬾ʹ���һ���µ�ͷ��(���ϲ�ͬ�������valueΪ���� */
extern int yy_e_http_parser_set_header_int( yy_e_http_parser_t * ehp, const char * name, int value );

/* ��http�����ṹ���������һ��headerͷ���Լ���Ӧ��ֵ */
extern int yy_e_http_parser_add_header( yy_e_http_parser_t * ehp, const char * name, const char * value );

/* ��http�����ṹ���������һ��headerͷ���Լ���Ӧ��ֵ(����) */
extern int yy_e_http_parser_add_header_uint32( yy_e_http_parser_t * ehp, const char * name, yy_p_uint32 value );

/* ��http�����ṹ�����Ƴ�����nameͷ��Ľڵ� */
extern int yy_e_http_parser_remove_header( yy_e_http_parser_t * ehp, const char * name );

/* ���http�����ṹ�����Ƿ����nameͷ�� */
extern int yy_e_http_parser_is_header_exist( yy_e_http_parser_t * ehp, const char * name );

/* һЩ�����ô���ͷ */
/* ��http�����ṹ��ehp�л�ȡcontent_lengthͷ���ֵ */
extern yy_e_http_content_t yy_e_http_parser_get_content_length( yy_e_http_parser_t * ehp );

/* ����http�����ṹ��ehp��content_lengthͷ���ֵ */
extern int yy_e_http_parser_set_content_length( yy_e_http_parser_t * ehp, yy_e_http_content_t v );

/* ��http�����ṹ��ehp���Ƴ�content_lengthͷ���Ӧ�Ľڵ� */
extern int yy_e_http_parser_remove_content_length( yy_e_http_parser_t * ehp );

/* ���http�����ṹ��ehp��content_lengthͷ���Ӧ��ֵ�Ƿ���� */
extern int yy_e_http_parser_has_content_length( yy_e_http_parser_t * ehp );

/* ����http�����ṹ��ehp��content_rangeͷ���ֵ */
extern int yy_e_http_parser_set_content_range( yy_e_http_parser_t * ehp, yy_e_http_range_t v );

/* ��http�����ṹ��ehp���Ƴ�content_rangeͷ���Ӧ�Ľڵ� */
extern int yy_e_http_parser_remove_content_range( yy_e_http_parser_t * ehp );

/* ����һ��������ǻ�Ӧ */
extern int yy_e_http_parser_build_packet( yy_e_http_parser_t * ehp, char * buf, size_t * inout_len );

/***********************************************************************************
*   ���ܣ���ȡhttp�������ĵ�һ��header
*   @param :
*           yy_e_http_parser_t *ehp    http������ʵ��
*   @return��
*           ��һ��headerָ��,��������ڷ���NULL
*   @date��
*           2015/06/04      sk     ����
************************************************************************************/
extern yy_e_http_header_t* yy_e_http_parser_first_header( yy_e_http_parser_t * ehp );

/***********************************************************************************
*   ���ܣ���ȡhttp��������header����һ��header
*   @param :
*           yy_e_http_parser_t *ehp			http������ʵ��
*			yy_e_http_header_t * header		��ǰ��headerָ��
*   @return��
*           header����һ��headerrָ��,��������ڷ���NULL
*   @date��
*           2015/06/04      sk     ����
************************************************************************************/
extern yy_e_http_header_t*  yy_e_http_parser_next_header( yy_e_http_parser_t * ehp, yy_e_http_header_t * header );

/* �������� */
extern int yy_e_http_parser_validation_test();

#endif
