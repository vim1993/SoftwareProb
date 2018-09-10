#ifndef YY_E_M3U8_PARSER_H
#define YY_E_M3U8_PARSER_H


#include "yy_e_memcheck.h"
#include "yy_s_lxlist.h"
#include "yy_f_alloc.h"


#define YY_E_M3U8_TAG_X_ENDLIST "EXT-X-ENDLIST"

#define YY_E_M3U8_LINE_NULL     0
#define YY_E_M3U8_LINE_TAG      1
#define YY_E_M3U8_LINE_BLANK    2
#define YY_E_M3U8_LINE_URI      3

typedef enum yy_e_m3u8_parser_state_e{
    yy_emps_error = -1,
    yy_emps_ok = 0,
    yy_emps_start,
    yy_emps_line_start,
    yy_emps_tag_name_start,
    yy_emps_tag_name,
    yy_emps_tag_bf_value,
    yy_emps_tag_value,
    yy_emps_tag_sp_af_value,
    yy_emps_line_uri,
    yy_emps_line_blank,
    yy_emps_line_lf
}yy_e_m3u8_parser_state_t;


typedef struct yy_e_m3u8_line_s{
    yy_s_lxlist_head_t list_header;
    yy_p_uint32 line_no;                    //行号，从0开始
    int type;
    char * tag_name;
    char * tag_value;
    char * line;
}yy_e_m3u8_line_t;

typedef struct yy_e_m3u8_parser_s{
    YY_E_MEM_MAGIC_PREFIX_DEFINE;    
    yy_f_alloc_t * alloc_nfp;


    yy_s_lxlist_head_t lines;
    yy_s_lxlist_head_t uris;

    yy_e_m3u8_parser_state_t pre_state;
    yy_e_m3u8_parser_state_t state;

    size_t parsed_len;
    size_t last_parsed_len;

    size_t uri_count;

    int version;
    int targetduartion;
    int is_endlist;
    yy_p_uint32 media_sequence;
    int is_multi_stream;

    yy_p_uint32 cur_line_no;
    const char * line_start;
    const char * tag_name_start;
    const char * tag_name_end;
    const char * tag_value_start;
    const char * tag_value_end;


    YY_E_MEM_MAGIC_SUFFIX_DEFINE;
}yy_e_m3u8_parser_t;


extern yy_e_m3u8_parser_t * yy_e_m3u8_parser_create( yy_f_alloc_t * alloc_thiz, size_t block_size );
extern void yy_e_m3u8_parser_destroy( yy_e_m3u8_parser_t * emp );
extern int yy_e_m3u8_parser_parse( yy_e_m3u8_parser_t * emp, const char * buf, size_t len );
extern int yy_e_m3u8_parser_parse_complete_file( yy_e_m3u8_parser_t * emp, const char * buf, size_t len );
extern size_t yy_e_m3u8_parser_parsed_len( yy_e_m3u8_parser_t * emp );
extern size_t yy_e_m3u8_parser_last_parsed_len( yy_e_m3u8_parser_t * emp );

extern int yy_e_m3u8_parser_is_complete(  yy_e_m3u8_parser_t * emp );

extern int yy_e_m3u8_parser_is_tag_exist( yy_e_m3u8_parser_t * emp, const char * tag );
extern const char * yy_e_m3u8_parser_get_tag( yy_e_m3u8_parser_t * emp, const char * tag );

//行迭代器
extern yy_e_m3u8_line_t * yy_e_m3u8_parser_first_line( yy_e_m3u8_parser_t * emp );
extern yy_e_m3u8_line_t *  yy_e_m3u8_parser_next_line( yy_e_m3u8_parser_t * emp, yy_e_m3u8_line_t * line );

//uri迭代器
extern size_t yy_e_m3u8_parser_uri_count( yy_e_m3u8_parser_t * emp );
extern yy_e_m3u8_line_t * yy_e_m3u8_parser_first_uri( yy_e_m3u8_parser_t * emp );
extern yy_e_m3u8_line_t *  yy_e_m3u8_parser_next_uri( yy_e_m3u8_parser_t * emp, yy_e_m3u8_line_t * uri );




//特殊属性，相关的定义及读取
extern int yy_e_m3u8_parser_get_x_version( yy_e_m3u8_parser_t * emp );
extern int yy_e_m3u8_parser_get_x_targetduartion( yy_e_m3u8_parser_t * emp );
extern int yy_e_m3u8_parser_is_x_endlist( yy_e_m3u8_parser_t * emp );
extern yy_p_uint32 yy_e_m3u8_parser_media_sequence( yy_e_m3u8_parser_t * emp );
extern int yy_e_m3u8_parser_is_multi_stream( yy_e_m3u8_parser_t * emp );


//
extern int yy_e_m3u8_parser_validation_test( const char * file );

#endif
