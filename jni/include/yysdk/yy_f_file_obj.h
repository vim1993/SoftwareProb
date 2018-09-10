#ifndef YY_F_FILE_obj_H
#define YY_F_FILE_obj_H
#include "yy_p_stdio.h"
#include "yy_e_memcheck.h"
#include "yy_f_alloc.h"

/*
*本模块用于定义文件对象，包括对外暴露的文件对象的定义和公共操作接口原型声明
*所有使用到文件对象的地方均遵循此处定义的对象结构和接口原型
*added by gaoqiang, 2015/09/30
*/

/* 文件对象操作接口原型声明 */
/* 文件对象释放 */
typedef void (*yy_f_file_obj_op_release_t)(void *thiz);
/* 读文件 */
typedef yy_p_off_t (*yy_f_file_obj_op_read_t)(void *thiz, void * buf, yy_p_off_t size);
/* 写文件 */
typedef yy_p_off_t (*yy_f_file_obj_op_write_t)(void *thiz, const void * buf, yy_p_off_t size);
/* 移动文件指针 */
typedef yy_p_off_t (*yy_f_file_obj_op_lseek_t)(void *thiz, yy_p_off_t offset, int whence );
/* 获取文件大小 */
typedef yy_p_off_t (*yy_f_file_obj_op_file_size_t)(void *thiz );
/* 获取文件描述符 */
typedef yy_p_handle_t (*yy_f_file_obj_op_fd_t)(void * thiz );
/* flush或冲洗文件流 */
typedef int (*yy_f_file_obj_op_flush_t)(void * thiz );
/* 自定义操作接口 */
typedef int (*yy_f_file_obj_op_ctrl_t)(void * thiz, int cmd, void * buf, size_t * size );

/* 操作接口定义 */
typedef struct yy_f_file_obj_op_s{    
    char name[16];					/* 文件对象名 */
    yy_f_file_obj_op_release_t f_release; /* 释放文件对象 */
    yy_f_file_obj_op_read_t f_read;		/* 读文件 */
    yy_f_file_obj_op_write_t f_write;	/* 写文件 */
    yy_f_file_obj_op_lseek_t f_lseek;	/* 移动文件指针 */
    yy_f_file_obj_op_file_size_t f_file_size;	/* 获取文件大小 */
    yy_f_file_obj_op_fd_t f_fd;			/* 获取文件描述符 */
	yy_f_file_obj_op_flush_t f_flush;	/* flush或冲洗文件流 */
	yy_f_file_obj_op_ctrl_t f_ctrl;		/* 自定义操作接口 */
}yy_f_file_obj_op_t;

/* 对外暴露的文件对象结构体 */
typedef struct yy_f_file_obj_s{       
    void * thiz;				/* 具体文件对象结构体，如内存文件对象 */
    yy_f_file_obj_op_t *op;	/* 具体文件对象操作接口实现 */
}yy_f_file_obj_t;

/* 操作接口调用宏定义 */
/* 释放文件对象 */
#define YY_F_FILE_OBJ_RELEASE( obj ) (obj)->op->f_release( (obj)->thiz )

/* 读文件 */
#define YY_F_FILE_OBJ_READ( obj, buf, size ) (obj)->op->f_read( (obj)->thiz, buf, size )

/* 写文件 */
#define YY_F_FILE_OBJ_WRITE( obj, buf, size ) (obj)->op->f_write( (obj)->thiz, buf, size )

/* 移动文件指针 */
#define YY_F_FILE_OBJ_LSEEK( obj, offset, whence ) (obj)->op->f_lseek( (obj)->thiz, offset, whence )

/* 获取文件大小 */
#define YY_F_FILE_OBJ_FILE_SIZE( obj ) (obj)->op->f_file_size( (obj)->thiz )

/* 获取文件描述符 */
#define YY_F_FILE_OBJ_FD( obj ) (obj)->op->f_fd( (obj)->thiz )

/* flush或冲洗文件流 */
#define YY_F_FILE_OBJ_FLUSH( obj ) (obj)->op->f_flush( (obj)->thiz )

/* 自定义操作接口 */
#define YY_F_FILE_OBJ_CTRL( obj, cmd, buf, size ) (obj)->op->f_ctrl( (obj)->thiz, cmd, buf, size )

/* 创建具有标准操作的文件对象（或称作默认文件对象），如：读、写、seek，等 */
extern yy_f_file_obj_t * yy_f_file_obj_create_default( yy_f_alloc_t * alloc, const char * filename, int flag, mode_t perms, LPSECURITY_ATTRIBUTES sa );

#endif
