#ifndef YY_E_MEMCHECK_H
#define YY_E_MEMCHECK_H
#include "yy_p_assert.h"

#define YY_E_MEM_MAGIC_INIT_PREFIX 0x01
#define YY_E_MEM_MAGIC_INIT_SUFFIX 0x02
#define YY_E_MEM_MAGIC_UNINIT_PREFIX 0x03
#define YY_E_MEM_MAGIC_UNINIT_SUFFIX 0x04


//简易内存写益出检查
#define YY_E_MEM_MAGIC_PREFIX_DEFINE void * yy_e_mem_magic_prefix
#define YY_E_MEM_MAGIC_SUFFIX_DEFINE void * yy_e_mem_magic_suffix
//将数据区二边溢出守卫设成初始值
#define YY_E_MEM_MAGIC_INIT( m ) do{ (m)->yy_e_mem_magic_prefix = (char *)(m)+YY_E_MEM_MAGIC_INIT_PREFIX;(m)->yy_e_mem_magic_suffix = (char *)(m)+YY_E_MEM_MAGIC_INIT_SUFFIX; }while(0)
//将数据区二边溢出守卫设成初始值, 同时将数据区设为0
#define YY_E_MEM_MAGIC_INIT_DZ( m ) do{  yy_p_memset( m, 0, (char *)( &(m)->yy_e_mem_magic_suffix ) - (char *)( &(m)->yy_e_mem_magic_prefix ) + sizeof(void *) ) ;(m)->yy_e_mem_magic_prefix = (char *)(m)+YY_E_MEM_MAGIC_INIT_PREFIX;(m)->yy_e_mem_magic_suffix = (char *)(m)+YY_E_MEM_MAGIC_INIT_SUFFIX; }while(0)
//内存释放前,清除守卫设置
#define YY_E_MEM_MAGIC_UNINIT( m ) do{ (m)->yy_e_mem_magic_prefix = (char *)(m)+YY_E_MEM_MAGIC_UNINIT_PREFIX;(m)->yy_e_mem_magic_suffix = (char *)(m)+YY_E_MEM_MAGIC_UNINIT_SUFFIX; }while(0)
//内存溢出检查
#define YY_E_MEM_MAGIC_CHECK( m ) do{ yy_p_assert( (m) != NULL ); yy_p_assert( (m)->yy_e_mem_magic_prefix == (char *)(m)+YY_E_MEM_MAGIC_INIT_PREFIX );yy_p_assert( (m)->yy_e_mem_magic_suffix == (char *)(m)+YY_E_MEM_MAGIC_INIT_SUFFIX  );}while(0)


//本地对家象初始化检查
#define YY_E_OBJ_MAGIC_DEFINE           void * yy_e_obj_init
#define YY_E_OBJ_MAGIC_INIT(s)          do{ (s)->yy_e_obj_init = (void *)0xa55a; }while(0)
#define YY_E_OBJ_MAGIC_UNINIT(s)        do{ (s)->yy_e_obj_init = (void *)0x5aa5; }while(0)
#define YY_E_OBJ_MAGIC_CHECK(s)         do{ yy_p_assert( (s)->yy_e_obj_init = (void *)0xa55a ); }while(0)
#define YY_E_OBJ_MAGIC_IS_INITED(s)     ( (s) != NULL && (s)->yy_e_obj_init == (void *)0xa55a )
#define YY_E_OBJ_MAGIC_IS_UNINITED(s)   ( (s)->yy_e_obj_init == (void *)0x5aa5 )
#define YY_E_OBJ_MAGIC_IS_UNSET(s)      ( !( ( (s)->yy_e_obj_init == (void *)0xa55a ) && ( (s)->yy_e_obj_init == (void *)0x5aa5 ) ) )

#endif
