#ifndef YY_F_FILE_OBJ_MEM_CORE_H
#define YY_F_FILE_OBJ_MEM_CORE_H
#include "yy_p_stdio.h"
#include "yy_p_thread.h"
#include "yy_e_memcheck.h"
//#include "yy_f_ref_count.h"
#include "yy_f_alloc.h"

/* �ڴ滺���������ݿ� */
typedef struct yy_f_file_obj_mem_chunk_s{
	char * data;
}yy_f_file_obj_mem_chunk_t;

/* �ڴ滺�����ṹ�� */
typedef struct yy_f_file_obj_mem_core_s{
	YY_E_MEM_MAGIC_PREFIX_DEFINE;
	yy_f_alloc_t * alloc_thiz;		/* ���ṹ����ڴ������ */
	yy_f_alloc_t * alloc_chunk;		/* �ڴ滺�������ڴ������ */
	yy_p_thr_mutex_t lock;			/* ������ */
	int ref_count;				/* �Ը��ڴ滺���������ü��� */
	size_t max_file_size;			/* ����ļ���С */
	size_t chunk_size;				/* ÿ���ڴ��Ĵ�С */
	size_t chunk_count;			/* �ڴ��ĸ��� */
	size_t last_chunk_data_size;	/* ���һ���ڴ���е����ݴ�С */
	size_t last_chunk_index;		/* ���һ���ڴ�������� */
	yy_f_file_obj_mem_chunk_t *chunks;/* �ڴ������ */
	YY_E_MEM_MAGIC_SUFFIX_DEFINE;
}yy_f_file_obj_mem_core_t;

/* �����ڴ滺��������������ʱ,���ü�����ʼΪ1 */
extern yy_f_file_obj_mem_core_t * yy_f_file_obj_mem_core_create( yy_f_alloc_t * alloc_thiz, yy_f_alloc_t * alloc_chunk,  size_t max_file_size, size_t chunk_size, int is_use_lock );

/* �����ڴ滺���������ü��� */
extern yy_f_file_obj_mem_core_t * yy_f_file_obj_mem_core_add_ref( yy_f_file_obj_mem_core_t * core );

/* �ͷ��ڴ滺���� */
extern void yy_f_file_obj_mem_core_release( yy_f_file_obj_mem_core_t * core );

/* ���ڴ滺������д���� */
extern size_t yy_f_file_obj_mem_core_write( yy_f_file_obj_mem_core_t * core, size_t pos, const char * buf, size_t size );

/* ���ڴ滺�����ж����� */
extern size_t yy_f_file_obj_mem_core_read( yy_f_file_obj_mem_core_t * core, size_t pos, char * buf, size_t size );

/* ��ȡ�ڴ滺�����е����ݴ�С */
extern size_t yy_f_file_obj_mem_core_file_size( yy_f_file_obj_mem_core_t * core );

/* �����ļ���С��ֻ����С��������� */
extern size_t yy_f_file_obj_mem_core_set_file_size( yy_f_file_obj_mem_core_t * core, size_t size );

/* �ͷŻ������������ڴ�� */
extern int yy_f_file_obj_mem_core_clear( yy_f_file_obj_mem_core_t * core );

/* ��ȡ�ڴ滺���������ü��� */
extern int yy_f_file_obj_mem_core_get_ref_count( yy_f_file_obj_mem_core_t * core );
#endif
