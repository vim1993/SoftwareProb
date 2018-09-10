#ifndef YY_P_MEMORY_H
#define YY_P_MEMORY_H
#include "yy_p_config.h"
#include <memory.h>
#include <stdlib.h>

#if defined(YY_P_IS_WINDOWS) && defined(_DEBUG)
//调试内存泄露，程序退出后，清除所有分配的空间
//#define YY_P_CLEAR_ALL_MEM
#endif

#ifdef  __cplusplus
extern "C" {
#endif

//内存属于stdlib,但比较特殊,与OS关联性也较大,独立一个进行处理
extern void * yy_p_malloc( size_t size );
extern void yy_p_free( void * p );

#define yy_p_memset memset
#define yy_p_memcpy memcpy
#define yy_p_memcmp memcmp
#define yy_p_memmove memmove

extern const char * yy_p_compiled_date();

extern int yy_p_memory_validation_test();

#ifdef  __cplusplus
}
#endif

#endif
