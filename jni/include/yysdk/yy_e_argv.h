#ifndef YY_E_ARGV_H
#define YY_E_ARGV_H

/**
*   该模块主要用于初始化输入参数，非标准,使用时自我参考
*/

#include "yy_p_type.h"
#include "yy_e_memcheck.h"

typedef struct yy_e_argv_s{
    YY_E_OBJ_MAGIC_DEFINE;
    int argc;                   /* 输入参数的个数 */
    yy_p_tchar * const * argv;  /* 输入参数字符串 */
}yy_e_argv_t;

/* 将输入参数字符串和个数添加到av结构体中 */
extern int yy_e_argv_init( yy_e_argv_t *  av, int argc, yy_p_tchar * const * argv );

/* 从初始化结构体中获取参数name的值 */
extern const yy_p_tchar * yy_e_argv_get_arg_by_name( yy_e_argv_t *  av, const yy_p_tchar * name );

/* 获取初始化结构体中对应index位置的参数 */
extern const yy_p_tchar * yy_e_argv_get_arg_by_index( yy_e_argv_t *  av, int index );

/* 判断输入参数中是否包含name参数 */
extern int yy_e_argv_is_arg_exist( yy_e_argv_t *  av, const yy_p_tchar * name );

#endif