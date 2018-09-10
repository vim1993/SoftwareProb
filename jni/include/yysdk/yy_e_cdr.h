#ifndef YY_E_CDR_H
#define YY_E_CDR_H
#include "yy_p_type.h"
#include "yy_e_memcheck.h"

#ifdef  __cplusplus
extern "C" {
#endif

/**
*   参考ACE的CDR,用于处理网络序及相关问题,比较简单，粗略注释
*/
#define YY_E_CDR_M_NULL		0
#define YY_E_CDR_M_LITTLE	1   //小端,低字节放在开始地址
#define YY_E_CDR_M_BIG		2   //大端,高字节放在开始地址

/* 处理网络序结构体 */
typedef struct yy_e_cdr_s
{
	YY_E_OBJ_MAGIC_DEFINE;
	char * buf;
	size_t len;
	size_t pos;

	int mode;
	int is_error;
	
}yy_e_cdr_t;

/* 将值v写入到buf字符串中 */
extern void yy_e_cdr_p_w1( char * buf, yy_p_uint8 v, int mode );

/* 将值v写入到buf字符串中 */
extern void yy_e_cdr_p_w2( char * buf, yy_p_uint16 v, int mode );

/* 将值v写入到buf字符串中 */
extern void yy_e_cdr_p_w4( char * buf, yy_p_uint32 v, int mode );

/* 将值v写入到buf字符串中 */
extern void yy_e_cdr_p_w8( char * buf, yy_p_uint64 v, int mode );

/* 获取buf字符串中的值 */
extern yy_p_uint8  yy_e_cdr_p_r1( const char * buf, int mode );

/* 获取buf字符串中的值 */
extern yy_p_uint16 yy_e_cdr_p_r2( const char * buf, int mode );

/* 获取buf字符串中的值 */
extern yy_p_uint32 yy_e_cdr_p_r4( const char * buf, int mode );

/* 获取buf字符串中的值 */
extern yy_p_uint64 yy_e_cdr_p_r8( const char * buf, int mode );


/* mode序列化模式,按指定的要求进行序列化 */
extern void yy_e_cdr_init( yy_e_cdr_t * c, int mode, char * buf, size_t len );

/* 获取网络序字符串的长度 */
extern size_t yy_e_cdr_buf_len( yy_e_cdr_t * c );

/* 获取网络序字符串此刻解析的位置 */
extern size_t yy_e_cdr_data_pos( yy_e_cdr_t * c );

/* 获取网络序字符串剩余的长度 */
extern size_t yy_e_cdr_space_len( yy_e_cdr_t * c );

/* 该变网络序结构体中读写位置pos的值 */
extern int yy_e_cdr_skip( yy_e_cdr_t * c, int skip );

/* 获取网络序结构体中字符串缓存buf */
extern char * yy_e_cdr_buf_ptr( yy_e_cdr_t * c );

/* 获取网络序结构体中当前读写位置pos */
extern char * yy_e_cdr_data_ptr( yy_e_cdr_t * c );

/* 获取buf网络序字符串是否有错 */
extern int yy_e_cdr_is_error( yy_e_cdr_t * c );

/* 往网络序结构体的buf中写入字符串 */
extern int yy_e_cdr_wx( yy_e_cdr_t * c, const char * v, size_t len );

/* 往网络序结构体的buf中写入字符 */
extern int yy_e_cdr_w1( yy_e_cdr_t * c, yy_p_uint8 v );

/* 往网络序结构体的buf中写入字符 */
extern int yy_e_cdr_w2( yy_e_cdr_t * c, yy_p_uint16 v );

/* 往网络序结构体的buf中写入值 */
extern int yy_e_cdr_w4( yy_e_cdr_t * c, yy_p_uint32 v );

/*使用4字节头作为长度头*/
extern int yy_e_cdr_wstr( yy_e_cdr_t * c, const char * str );

/* 获取网络序结构体中pos位置len长度的字符串到v中 */
extern int yy_e_cdr_rx( yy_e_cdr_t * c, char * v, size_t len );

/* 从网络序结构体中获取pos位置的值到v中 */
extern int yy_e_cdr_r1( yy_e_cdr_t * c, yy_p_uint8 * v );

/* 从网络序结构体中获取pos位置的值到v中 */
extern int yy_e_cdr_r2( yy_e_cdr_t * c, yy_p_uint16 * v );

/* 从网络序结构体中获取pos位置的值到v中 */
extern int yy_e_cdr_r4( yy_e_cdr_t * c, yy_p_uint32 * v );

/*使用4字节头作为长度头*/
extern int yy_e_cdr_rstr( yy_e_cdr_t * c, char * str, size_t len );

extern int yy_e_cdr_validation_test();

#ifdef  __cplusplus
}
#endif

#endif
