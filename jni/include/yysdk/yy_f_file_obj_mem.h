/*
一个由内存构成的文件
*/
#ifndef YY_F_FILE_OBJ_MEM_H
#define YY_F_FILE_OBJ_MEM_H
#include "yy_f_file_obj.h"
#include "yy_p_test.h"

/* 创建文件操作结构 */
extern yy_f_file_obj_t * yy_f_file_obj_mem_create( yy_f_alloc_t * alloc_thiz, yy_f_alloc_t * alloc_chunk, size_t max_file_size, size_t chunk_size , int is_use_lock);

/* 浅COPY,一般用来获得一个对文件实体的读,同时另一个正在写入 */
extern yy_f_file_obj_t * yy_f_file_obj_mem_duplicate( yy_f_file_obj_t * f, yy_f_alloc_t * alloc_thiz );

//这个操作将会释放文件块内存,导致其它读的失败
extern int yy_f_file_obj_mem_clear( yy_f_file_obj_t * f );

extern int yy_f_file_obj_mem_validation_test();
#endif
