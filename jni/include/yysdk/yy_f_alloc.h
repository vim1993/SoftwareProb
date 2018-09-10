#ifndef YY_F_ALLOC_H
#define YY_F_ALLOC_H
#include "yy_p_type.h"
#include "yy_p_memory.h"
#include "yy_p_assert.h"
#include "yy_p_test.h"
#include "yy_e_memcheck.h"

/**
*   内存分配,模似C++风格
*   低16位统一使用,高16位保留给每个特性池自己使用
*	内存池通用结构、接口定义：added by gaoqiang, 2015-06-10
*/

#define YY_F_ALLOC_FLAG_NULL	0x0000000	//无属性
#define YY_F_ALLOC_FLAG_LOCK    0x00000001	//池带锁 
#define YY_F_ALLOC_FLAG_GBASE   0x00000002  //此功能使用YY_E_MEMORY_CHECK
#define YY_F_ALLOC_FLAG_GDATA   0x00000004	//池对内存写溢出进行尽可能的校验,最终由实际来确定是不是实现全部功能

/* 池的状态统计 */
typedef struct yy_f_alloc_stat_s{
    void * alloc_ptr;			           //池基准指针
    char alloc_type[16];                   //池的类型描述,3个字符
    yy_p_uint32 alloc_flag;                //基准特性
    
    size_t max_size;                       //最大可以分配的空间,0为不限制
    size_t malloced_size;                  //已经从系统申请了的空间
    size_t used_size;                      //已经被使用了的

    size_t malloc_success_count;			/* 分配成功次数 */
    size_t malloc_failure_count;			/* 分配失败次数 */
    size_t free_success_count;				/* 释放成功次数 */
    size_t free_failure_count;				/* 释放失败次数 */
	size_t error_count; 				/* 错误次数 */
	int last_errno;							/* 最近一次错误码 */
}yy_f_alloc_stat_t;

/* 函数指针：释放内存池及相应数据结构 */
typedef void (*yy_f_alloc_release_t)(void * thiz );

/* 函数指针：从内存池分配内存块 */
typedef void * (*yy_f_alloc_malloc_t)(void * thiz, size_t size );

/* 函数指针：将内存块归还给内存池 */
typedef void (*yy_f_alloc_free_t)( void * thiz, void * p );

/* 函数指针：获取内存池基本信息和使用情况，写入字符数组中 */
typedef int (*yy_f_alloc_desc_t)(void * thiz, char * desc, size_t size );

/* 函数指针：获取内存池统计信息（基本信息和池使用情况统计） */
typedef int (*yy_f_alloc_get_stat_t)(void * thiz, yy_f_alloc_stat_t * stat );

/* 公共接口结构定义 */
typedef struct yy_f_alloc_op_s{	
	char alloc_type[16];					/* 池类型或名字 */
    yy_f_alloc_release_t f_realse;			/* 释放内存池及相应数据结构 */
	yy_f_alloc_malloc_t f_malloc;			/* 从内存池分配内存块 */
	yy_f_alloc_free_t f_free;				/* 将内存块归还给内存池 */
    yy_f_alloc_desc_t f_desc;				/* 获取内存池基本信息和使用情况，写入字符数组中 */
    yy_f_alloc_get_stat_t f_stat;			/* 获取内存池统计信息（基本信息和池使用情况统计） */
}yy_f_alloc_op_t;

/* 内存分配器结构体 */
typedef struct yy_f_alloc_s{
	void * thiz;							/* 特定内存分配器结构指针 */
	yy_f_alloc_op_t * op;					/* 该内存分配器对应的公共接口结构指针 */
}yy_f_alloc_t;

#define YY_F_ALLOC_MALLOC( alloc, size )        (alloc)->op->f_malloc( (alloc)->thiz, size )		/* 从内存池分配内存块宏 */
#define YY_F_ALLOC_FREE( alloc, ptr )           (alloc)->op->f_free( (alloc)->thiz, ptr )			/* 归还内存块给内存池宏 */
#define YY_F_ALLOC_RELEASE( alloc )             (alloc)->op->f_realse( (alloc)->thiz )				/* 释放内存池及数据结构宏 */
#define YY_F_ALLOC_DESC( alloc, desc, size )    (alloc)->op->f_desc( (alloc)->thiz, desc, size )	/* 获取内存池基本信息和使用情况到字符数组宏 */
#define YY_F_ALLOC_STAT( alloc, stat )          (alloc)->op->f_stat( (alloc)->thiz, stat )			/* 获取内存池基本信息和使用情况统计宏 */


/* C运行时库的malloc,free封装 */
/* 得到内存分配器 */
extern yy_f_alloc_t * yy_f_alloc_get_c();

/* 基础自定义池的封装,提供一个全局的内存替换点 */
extern yy_f_alloc_t * yy_f_alloc_get_my();

/* 格式化输出内存分配info  */
extern int yy_f_alloc_show_info( char * info, size_t size, const yy_f_alloc_stat_t * stat );

extern int yy_f_alloc_validation_test();
#endif
