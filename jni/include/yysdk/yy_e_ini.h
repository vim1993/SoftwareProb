#ifndef YY_E_INI_H
#define YY_E_INI_H
#include "yy_p_type.h"
#include "yy_p_stdio.h"
#include "yy_p_stdlib.h"
#include "yy_s_string.h"
#include "yy_s_lxlist.h"

/**
*   简易的配置类,主要用于加载配置文件，读取配置文件中的参数
*/

/* 读取配置文件时，一行的数据 */
typedef struct yy_e_ini_line_s{
    yy_s_lxlist_head_t list_line;	/* 链表头，用于挂载在yy_e_ini_s的链表中 */
    char * key;					/* 参数名 */
    char * value;					/* 该参数的值(比如：key = value这样的形式) */
    char * memo;					/**/ 
    
}yy_e_ini_line_t;

/* 读取配置文件结构体 */
typedef struct yy_e_ini_s{
    yy_f_alloc_t * alloc;			/* 内存分配器 */
    char filename[YY_P_MAX_PATH];	/* 读取的文件名 */
    yy_s_lxlist_head_t list_line_head;	/* 链表，用于装载每行的数据(因为每行数据即为不同的一个参数) */
}yy_e_ini_t;

/* 加载指定文件名的配置文件，该文件必须存在 */
extern yy_e_ini_t * yy_e_ini_load_from_file( yy_f_alloc_t * alloc, const char * filename );

/* 加载名为filename的配置文件，该配置文件不确定是否存在，只是创建一个结构体 */
extern yy_e_ini_t * yy_e_ini_create_file( yy_f_alloc_t * alloc, const char * filename );

/* 将配置文件中管理链表中所有节点中的参数和值输出到文件中 */
extern int yy_e_init_save_to_file( yy_e_ini_t * ini );

/* 摧毁配置文件结构体 */
extern void yy_e_ini_destroy( yy_e_ini_t * ini );

/* 从配置文件结构体中获取参数key对应的值 */
extern const char * yy_e_ini_get_value( yy_e_ini_t * ini, const char * key );

/* 从配置文件结构体中获取参数key对应的值，需要将值转化成整型 */
extern int yy_e_ini_get_value_int( yy_e_ini_t * ini, const char * key );

/* 在配置文件结构体中查找key，如果有这个节点，则替换该节点对应的值，如果没有，则插入新的节点 */
extern int yy_e_ini_set_value( yy_e_ini_t * ini, const char * key, const char * value );

/* 判断配置文件结构体中是否有节点包含key参数 */
extern int yy_e_ini_is_key_exist( yy_e_ini_t * ini, const char * key );

/* 判断配置文件结构体中是否有节点包含key，以及key对应的值是否存在 */
extern int yy_e_ini_is_key_value_exist( yy_e_ini_t * ini, const char * key );

/* 判断配置文件结构体中是否有节点包含key，如果有，则将该key所在节点删除 */
extern void yy_e_ini_remove_key( yy_e_ini_t * ini, const char * key );

#endif
