#ifndef YY_E_GUID_H
#define YY_E_GUID_H
#include "yy_p_type.h"
typedef struct yy_e_guid_s{
	char data[16];
}yy_e_guid_t;

typedef struct yy_e_guid_str_s{
#if YY_P_IS_BUS_WIDTH_64
	char data[40];
#else
	char data[36];
#endif
}yy_e_guid_str_t;

/* 生成一个GUID,包含0结尾,所以长度必须为大于等于33 */
extern void yy_e_build_guid_str( yy_e_guid_str_t *s );

/* 将生成的GUID输出到str缓存中 */
extern void yy_e_build_guid_cstr( char * str, size_t len );

/* 生成一个GUID */
extern void yy_e_build_guid( yy_e_guid_t * g );

#endif
