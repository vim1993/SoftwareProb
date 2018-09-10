/*
һ�����ڴ湹�ɵ��ļ�
*/
#ifndef YY_F_FILE_OBJ_MEM_H
#define YY_F_FILE_OBJ_MEM_H
#include "yy_f_file_obj.h"
#include "yy_p_test.h"

/* �����ļ������ṹ */
extern yy_f_file_obj_t * yy_f_file_obj_mem_create( yy_f_alloc_t * alloc_thiz, yy_f_alloc_t * alloc_chunk, size_t max_file_size, size_t chunk_size , int is_use_lock);

/* ǳCOPY,һ���������һ�����ļ�ʵ��Ķ�,ͬʱ��һ������д�� */
extern yy_f_file_obj_t * yy_f_file_obj_mem_duplicate( yy_f_file_obj_t * f, yy_f_alloc_t * alloc_thiz );

//������������ͷ��ļ����ڴ�,������������ʧ��
extern int yy_f_file_obj_mem_clear( yy_f_file_obj_t * f );

extern int yy_f_file_obj_mem_validation_test();
#endif
