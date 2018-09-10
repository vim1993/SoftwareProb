#ifndef YY_X_LIVE_SOURCE_TS_H
#define YY_X_LIVE_SOURCE_TS_H
#include "yy_x_live_source.h"
#include "yy_e_memcheck.h"

/* 创建ts直播源结构体 */
extern yy_x_live_source_t * yy_x_live_source_ts_create( const yy_x_live_source_arg_t * arg );

/* 测试用例 */
extern int yy_x_live_source_ts_validation_test( const char * url );
#endif
