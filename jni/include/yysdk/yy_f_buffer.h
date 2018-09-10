#ifndef YY_F_BUFFER_H
#define YY_F_BUFFER_H
#include "yy_f_alloc.h"

/*
*缓冲区实现
*added by gaoqiang, 2015-06-25
*/

/* 缓冲区结构定义 */
typedef struct yy_f_buffer_s{
    yy_f_alloc_t * alloc_data;	/* 分配缓冲区的内存分配器 */
    char * data_ptr;			/* 缓冲区起始地址 */


    size_t pos;				/* 写指针位置，0~N */
    size_t size;				/* 缓冲区大小 */

    YY_E_OBJ_MAGIC_DEFINE;
}yy_f_buffer_t;

/* 缓冲区初始化 */
extern int yy_f_buffer_init( yy_f_buffer_t * buf, yy_f_alloc_t * alloc_data, size_t size );

/* 缓冲区资源释放 */
extern int yy_f_buffer_uninit( yy_f_buffer_t * buf );

/* 获取缓冲区数据长度 */
extern size_t yy_f_buffer_data_len( yy_f_buffer_t * buf );

/* 获取缓冲区剩余空间大小 */
extern size_t yy_f_buffer_space_len( yy_f_buffer_t * buf );

/* 获取缓冲区总空间大小 */
extern size_t yy_f_buffer_buf_size( yy_f_buffer_t * buf );

/* 调整缓冲区大小，新的缓冲区大小不能小于当前缓冲区中数据大小 */
extern int yy_f_buffer_resize( yy_f_buffer_t * buf, size_t new_size );

/* 丢弃缓冲区中前面一段数据 */
extern int yy_f_buffer_drop( yy_f_buffer_t * buf, size_t drop_size );

/* 未实现 */
extern void yy_f_buffer_truncate( yy_f_buffer_t * buf );

/* 获取缓冲区写指针位置 */
extern char * yy_f_buffer_data_ptr( yy_f_buffer_t * buf );

/* 获取缓冲区读指针位置 */
extern char * yy_f_buffer_buf_ptr( yy_f_buffer_t * buf );
extern void yy_f_buffer_set_data_len( yy_f_buffer_t * buf, size_t data_len );

/* 增加写指针位置 */
extern void yy_f_buffer_data_pos_add( yy_f_buffer_t * buf, size_t pos );


#endif
