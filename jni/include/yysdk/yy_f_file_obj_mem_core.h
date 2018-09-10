#ifndef YY_F_FILE_OBJ_MEM_CORE_H
#define YY_F_FILE_OBJ_MEM_CORE_H
#include "yy_p_stdio.h"
#include "yy_p_thread.h"
#include "yy_e_memcheck.h"
//#include "yy_f_ref_count.h"
#include "yy_f_alloc.h"

/* 内存缓存区中数据块 */
typedef struct yy_f_file_obj_mem_chunk_s{
	char * data;
}yy_f_file_obj_mem_chunk_t;

/* 内存缓冲区结构体 */
typedef struct yy_f_file_obj_mem_core_s{
	YY_E_MEM_MAGIC_PREFIX_DEFINE;
	yy_f_alloc_t * alloc_thiz;		/* 本结构体的内存分配器 */
	yy_f_alloc_t * alloc_chunk;		/* 内存缓存区的内存分配器 */
	yy_p_thr_mutex_t lock;			/* 互斥锁 */
	int ref_count;				/* 对该内存缓存区的引用计数 */
	size_t max_file_size;			/* 最大文件大小 */
	size_t chunk_size;				/* 每个内存块的大小 */
	size_t chunk_count;			/* 内存块的个数 */
	size_t last_chunk_data_size;	/* 最后一个内存块中的数据大小 */
	size_t last_chunk_index;		/* 最后一个内存的索引号 */
	yy_f_file_obj_mem_chunk_t *chunks;/* 内存块数组 */
	YY_E_MEM_MAGIC_SUFFIX_DEFINE;
}yy_f_file_obj_mem_core_t;

/* 创建内存缓存区，创建出来时,引用计数初始为1 */
extern yy_f_file_obj_mem_core_t * yy_f_file_obj_mem_core_create( yy_f_alloc_t * alloc_thiz, yy_f_alloc_t * alloc_chunk,  size_t max_file_size, size_t chunk_size, int is_use_lock );

/* 增加内存缓存区的引用计数 */
extern yy_f_file_obj_mem_core_t * yy_f_file_obj_mem_core_add_ref( yy_f_file_obj_mem_core_t * core );

/* 释放内存缓存区 */
extern void yy_f_file_obj_mem_core_release( yy_f_file_obj_mem_core_t * core );

/* 往内存缓存区中写数据 */
extern size_t yy_f_file_obj_mem_core_write( yy_f_file_obj_mem_core_t * core, size_t pos, const char * buf, size_t size );

/* 从内存缓存区中读数据 */
extern size_t yy_f_file_obj_mem_core_read( yy_f_file_obj_mem_core_t * core, size_t pos, char * buf, size_t size );

/* 获取内存缓存区中的数据大小 */
extern size_t yy_f_file_obj_mem_core_file_size( yy_f_file_obj_mem_core_t * core );

/* 设置文件大小，只能设小，不能设大 */
extern size_t yy_f_file_obj_mem_core_set_file_size( yy_f_file_obj_mem_core_t * core, size_t size );

/* 释放缓冲区中所有内存块 */
extern int yy_f_file_obj_mem_core_clear( yy_f_file_obj_mem_core_t * core );

/* 获取内存缓存区的引用计数 */
extern int yy_f_file_obj_mem_core_get_ref_count( yy_f_file_obj_mem_core_t * core );
#endif
