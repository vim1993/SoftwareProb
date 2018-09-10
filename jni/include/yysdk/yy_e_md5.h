#ifndef YY_E_MD5_H
#define YY_E_MD5_H

#include "yy_p_type.h"
#include "yy_e_md5_v2.h"

/* md5结构体 */
typedef struct yy_e_md5_ctx_s {
    yy_p_uint32 state[4];	/* 初始化参数以及md5运算后的数组 */
	size_t curlen;		/* 当前的进行md5预算的字节数 */
	yy_p_uint64 length;	/* 进行md5预算的字符串长度 */
    yy_p_uint8 buf[64];	/* 进行md5预算的字符串 */
}yy_e_md5_ctx_t;

/* md5结构体初始化 */
extern void yy_e_md5_init( yy_e_md5_ctx_t * md5 );

/* 判断输入的字符串是否能够进行md5运算 */
extern void yy_e_md5_process( yy_e_md5_ctx_t * md5, const yy_p_uint8 *buf, size_t len );

/* 将md5运算结构体输出到字符串 */
extern void yy_e_md5_done( yy_e_md5_ctx_t * md5, yy_p_uint8 *hash );

/* 对buf做位运算 */
extern void yy_e_md5_digest_bin_out( const char * buf, size_t len, char * bin_out );

/* 转换为字符串输出，因此strhex_out至少要有33字节的空间，存储最后的结尾0 */
extern void yy_e_md5_digest_strhex_out( const char * buf, size_t len, char * strhex_out, int is_lowercase );

/* 测试用例 */
extern int yy_e_md5_validation_test( const char * test_str );

#endif
