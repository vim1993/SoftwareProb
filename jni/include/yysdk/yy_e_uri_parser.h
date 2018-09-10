#ifndef YY_E_URI_PARSER_H
#define YY_E_URI_PARSER_H
#include "yy_e_http.h"
#include "yy_e_memcheck.h"
#include "yy_s_lxlist.h"
#include "yy_f_alloc.h"

/* ö��uri������״̬���� */
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

/* header�ṹ��( ��?a=b&c=d#fragment����ȡ���е�a=b��c=d) */
typedef struct yy_e_uri_header_s{
    yy_s_lxlist_head_t list_query;	/* ����ͷ���������ҵ�uri�����ṹ���� */
    char * name_encoded;			/* δ����ǰ��name */
    char * value_encoded;			/* δ����ǰ��name��ֵ */
    char * name_decoded;			/* ������name */
    char * value_decoded;			/* ������name��ֵ(����ı���ʱ��ʮ������ת���ɶ�Ӧ���ַ�) */
}yy_e_uri_header_t;

/* ·��Ŀ¼�ṹ��(��url path��ǩ�еĶ༶Ŀ¼ /001/002/003.m3u8,��ȡ���е�001��002) */
typedef struct yy_e_uri_path_index_s{
	yy_s_lxlist_head_t list_path;	/* ����ͷ�����ڹ��ص�uri�����ṹ���� */
	char * path_encoded;			/* δ����ǰ��path */
	char * path_decoded;			/* ������path */
}yy_e_uri_path_index_t;

/* uri�����ṹ�� */
typedef struct yy_e_uri_parser_s{
    YY_E_MEM_MAGIC_PREFIX_DEFINE;    
    yy_f_alloc_t * alloc_nfp;		/* �ڴ������ */

	//����״̬��
    yy_e_uri_parser_state_t pre_state;	/* ���ڱ���uri������ǰһ��״̬ */
    yy_e_uri_parser_state_t state;	/* uri������ǰ״̬ */
   

	//����
    yy_s_lxlist_head_t query;		/* ����ͷ�����ڹ���header�ṹ�� */
	yy_s_lxlist_head_t path_index;	/* ����ͷ�����ڹ���path�ṹ�� */
  
    char * uri_part[16];			 /* �洢��Ӧ��ǩδ�����ֵ */
    char * uri_part_decoded[16];	/* �洢��Ӧ��ǩ���������ֵ */

    //char * url_path_filename_noext;

    //������ʱ
    size_t parsed_len;			/* uri�ĳ��� */
    const char * tmp_pb;		/* ��ʱ���ݵ�ַ��ʼ */
    const char * tmp_pe;		/* ��ʱ���ݵ�ַ���� */
    char * tmp_name;			/* ��ʱ����name */
    char * tmp_value;			/* ��ʱ���ݶ�Ӧ��ֵ */

    YY_E_MEM_MAGIC_SUFFIX_DEFINE;
}yy_e_uri_parser_t;

/* ��ָ���ķ��������� */
extern yy_e_uri_parser_t * yy_e_uri_parser_create( yy_f_alloc_t * alloc_thiz, size_t block_size );

/* ��һ��ָ�����ڴ��Ͻ��д���,һ��Ϊ��̬ջ�ռ� */
extern yy_e_uri_parser_t * yy_e_uri_parser_create2( char * buf, size_t block_size );

/* �ݻ�uri�����ṹ��eup */
extern void yy_e_uri_parser_destroy( yy_e_uri_parser_t * eup );

/* �����Ѿ������˵ĳ��� */
extern size_t yy_e_uri_parser_parsed_len( yy_e_uri_parser_t * eup );

/* ͨ��uri�����ṹ��eup����uri */
extern int yy_e_uri_parser_parse( yy_e_uri_parser_t * eup, const char * buf, size_t len );

/* ��uri�����ṹ���л�ȡhostport */
extern const char * yy_e_uri_parser_get_hostport( yy_e_uri_parser_t * eup );

/* ����uri�����ṹ��eup�е�hostport */
extern int yy_e_uri_parser_set_hostport( yy_e_uri_parser_t * eup, const char * hostport );

/* ��ȡURL�У�host֮��?֮ǰ���ַ��� */
extern const char * yy_e_uri_parser_get_url_path( yy_e_uri_parser_t * eup, int is_decoded );

/* ��uri�����ṹ��eup�л�ȡ��index��path */
extern const char * yy_e_uri_parser_get_url_path_index( yy_e_uri_parser_t * eup, size_t index, int is_decoded ); 

/* ��uri�����ṹ��eup�л�ȡafter_url_path */
extern const char * yy_e_uri_parser_get_all_after_url_path( yy_e_uri_parser_t * eup, int is_decoded );

/* ��uri�����ṹ��eup�л�ȡfilename */
extern const char * yy_e_uri_parser_get_filename( yy_e_uri_parser_t * eup, int is_decoded );

/* ��uri�����ṹ��eup�л�ȡfilename_noext */
extern const char * yy_e_uri_parser_get_filename_noext( yy_e_uri_parser_t * eup, int is_decoded );

/* ��uri�����ṹ��eup�л�ȡfileext */
extern const char * yy_e_uri_parser_get_fileext( yy_e_uri_parser_t * eup, int is_decoded );

/* ��uri�����ṹ��eup�л�ȡfull_url_path */
extern const char * yy_e_uri_parser_get_full_url_path( yy_e_uri_parser_t * eup, int is_decoded );

/* ��uri�����ṹ��eup�л�ȡname��Ӧ��ֵ */
extern const char * yy_e_uri_parser_get_query( yy_e_uri_parser_t * eup, const char * name, int is_decoded );

/* ��uri�����ṹ��eup�л�ȡname1��Ӧ��ֵ�����ֵΪNULL���������ȡname2��Ӧ��ֵ,����name2��ֵ�������ΪNULL���򷵻�name1��ֵ */
extern const char * yy_e_uri_parser_get_mquery( yy_e_uri_parser_t * eup, const char * name1, const char * name2, int is_decoded );

/* ����һ����3��������ѯ�Ĺ��ܣ�ǰ����һ�����ҵ��󣬲�ִ�к����Ĳ�ѯ */
extern const char * yy_e_uri_parser_get_mquery3( yy_e_uri_parser_t * eup, const char * name1, const char * name2, const char * name3, int is_decoded );

/* ��uri�����ṹ��eup�л�ȡscheme */
extern const char * yy_e_uri_parser_get_scheme( yy_e_uri_parser_t * eup, int is_decoded );

/* ���name��name��Ӧ��ֵ��ӵ�uri�����ṹ��eup����query�� */
extern int yy_e_uri_parser_add_query( yy_e_uri_parser_t * eup, const char * name, const char * value, int is_encoded );

/* ���name��name��Ӧ��ֵ��ӵ�uri�����ṹ��eup����query��(�����value��������) */
extern int yy_e_uri_parser_add_query_int( yy_e_uri_parser_t * eup, const char * name, int value, int is_encoded );

/* ��uri�����ṹ��eup����query��ɾ������name�Ľڵ� */
extern int yy_e_uri_parser_del_query( yy_e_uri_parser_t * eup, const char * name );

/* ��uri�����ṹ��eup����query�л�ȡ��һ���ڵ� */
extern yy_e_uri_header_t * yy_e_uri_parser_query_first( yy_e_uri_parser_t * eup );

/* ��uri�����ṹ��eup����query�л�ȡh�ڵ����һ���ڵ� */
extern yy_e_uri_header_t * yy_e_uri_parser_query_next( yy_e_uri_parser_t * eup, yy_e_uri_header_t * h );

/*
SK,�����Ѿ������˵ĵ�ַ
http://10.1.1.1:80/abc/xxx.ts
�ɹ�������0
ʧ�� 
inout_len ���ǻ��峤�ȣ������Ѿ�д�볤��
*/
extern int yy_e_uri_parser_build_full_uri( yy_e_uri_parser_t * eup, char * buf, size_t * inout_len );

/* δ����ʵ��,�ݴ�ʹ�� */
extern int yy_e_uri_parser_build_uri( yy_e_uri_parser_t * eup, char * buf, size_t * inout_len );

/* �������� http://127.0.0.1:9906/abc/def/g.aa?a=b&c=d#eee */
extern int yy_e_uri_parser_validation_test();

#endif
