#ifndef YY_X_LIVE_SOURCE_M3U8_H
#define YY_X_LIVE_SOURCE_M3U8_H

#include "yy_x_live_source.h"
#include "yy_e_memcheck.h"

/* 创建m3u8直播源主结构体 */
extern yy_x_live_source_t * yy_x_live_source_m3u8_create( const yy_x_live_source_arg_t * arg );

/* 测试用例 */
extern int yy_x_live_source_m3u8_validation_test( const char * url );


#endif
