#ifndef YY_P_MEMORY_H
#define YY_P_MEMORY_H
#include "yy_p_config.h"
#include <memory.h>
#include <stdlib.h>

#if defined(YY_P_IS_WINDOWS) && defined(_DEBUG)
//�����ڴ�й¶�������˳���������з���Ŀռ�
//#define YY_P_CLEAR_ALL_MEM
#endif

#ifdef  __cplusplus
extern "C" {
#endif

//�ڴ�����stdlib,���Ƚ�����,��OS������Ҳ�ϴ�,����һ�����д���
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
