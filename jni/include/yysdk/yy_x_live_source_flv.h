#ifndef YY_X_LIVE_SOURCE_FLV_H
#define YY_X_LIVE_SOURCE_FLV_H
#include "yy_x_live_source.h"
#include "yy_e_memcheck.h"

/* 根据初始化参数创建live_flv结构体 */
extern yy_x_live_source_t * yy_x_live_source_flv_create( const yy_x_live_source_arg_t * arg );

/* 测试用例 */
extern int yy_x_live_source_flv_validation_test( const char * url );
#endif
