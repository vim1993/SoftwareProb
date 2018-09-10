#ifndef YY_F_FILE_obj_H
#define YY_F_FILE_obj_H
#include "yy_p_stdio.h"
#include "yy_e_memcheck.h"
#include "yy_f_alloc.h"

/*
*��ģ�����ڶ����ļ����󣬰������Ⱪ¶���ļ�����Ķ���͹��������ӿ�ԭ������
*����ʹ�õ��ļ�����ĵط�����ѭ�˴�����Ķ���ṹ�ͽӿ�ԭ��
*added by gaoqiang, 2015/09/30
*/

/* �ļ���������ӿ�ԭ������ */
/* �ļ������ͷ� */
typedef void (*yy_f_file_obj_op_release_t)(void *thiz);
/* ���ļ� */
typedef yy_p_off_t (*yy_f_file_obj_op_read_t)(void *thiz, void * buf, yy_p_off_t size);
/* д�ļ� */
typedef yy_p_off_t (*yy_f_file_obj_op_write_t)(void *thiz, const void * buf, yy_p_off_t size);
/* �ƶ��ļ�ָ�� */
typedef yy_p_off_t (*yy_f_file_obj_op_lseek_t)(void *thiz, yy_p_off_t offset, int whence );
/* ��ȡ�ļ���С */
typedef yy_p_off_t (*yy_f_file_obj_op_file_size_t)(void *thiz );
/* ��ȡ�ļ������� */
typedef yy_p_handle_t (*yy_f_file_obj_op_fd_t)(void * thiz );
/* flush���ϴ�ļ��� */
typedef int (*yy_f_file_obj_op_flush_t)(void * thiz );
/* �Զ�������ӿ� */
typedef int (*yy_f_file_obj_op_ctrl_t)(void * thiz, int cmd, void * buf, size_t * size );

/* �����ӿڶ��� */
typedef struct yy_f_file_obj_op_s{    
    char name[16];					/* �ļ������� */
    yy_f_file_obj_op_release_t f_release; /* �ͷ��ļ����� */
    yy_f_file_obj_op_read_t f_read;		/* ���ļ� */
    yy_f_file_obj_op_write_t f_write;	/* д�ļ� */
    yy_f_file_obj_op_lseek_t f_lseek;	/* �ƶ��ļ�ָ�� */
    yy_f_file_obj_op_file_size_t f_file_size;	/* ��ȡ�ļ���С */
    yy_f_file_obj_op_fd_t f_fd;			/* ��ȡ�ļ������� */
	yy_f_file_obj_op_flush_t f_flush;	/* flush���ϴ�ļ��� */
	yy_f_file_obj_op_ctrl_t f_ctrl;		/* �Զ�������ӿ� */
}yy_f_file_obj_op_t;

/* ���Ⱪ¶���ļ�����ṹ�� */
typedef struct yy_f_file_obj_s{       
    void * thiz;				/* �����ļ�����ṹ�壬���ڴ��ļ����� */
    yy_f_file_obj_op_t *op;	/* �����ļ���������ӿ�ʵ�� */
}yy_f_file_obj_t;

/* �����ӿڵ��ú궨�� */
/* �ͷ��ļ����� */
#define YY_F_FILE_OBJ_RELEASE( obj ) (obj)->op->f_release( (obj)->thiz )

/* ���ļ� */
#define YY_F_FILE_OBJ_READ( obj, buf, size ) (obj)->op->f_read( (obj)->thiz, buf, size )

/* д�ļ� */
#define YY_F_FILE_OBJ_WRITE( obj, buf, size ) (obj)->op->f_write( (obj)->thiz, buf, size )

/* �ƶ��ļ�ָ�� */
#define YY_F_FILE_OBJ_LSEEK( obj, offset, whence ) (obj)->op->f_lseek( (obj)->thiz, offset, whence )

/* ��ȡ�ļ���С */
#define YY_F_FILE_OBJ_FILE_SIZE( obj ) (obj)->op->f_file_size( (obj)->thiz )

/* ��ȡ�ļ������� */
#define YY_F_FILE_OBJ_FD( obj ) (obj)->op->f_fd( (obj)->thiz )

/* flush���ϴ�ļ��� */
#define YY_F_FILE_OBJ_FLUSH( obj ) (obj)->op->f_flush( (obj)->thiz )

/* �Զ�������ӿ� */
#define YY_F_FILE_OBJ_CTRL( obj, cmd, buf, size ) (obj)->op->f_ctrl( (obj)->thiz, cmd, buf, size )

/* �������б�׼�������ļ����󣨻����Ĭ���ļ����󣩣��磺����д��seek���� */
extern yy_f_file_obj_t * yy_f_file_obj_create_default( yy_f_alloc_t * alloc, const char * filename, int flag, mode_t perms, LPSECURITY_ATTRIBUTES sa );

#endif
