#ifndef YY_E_ARGV_H
#define YY_E_ARGV_H

/**
*   ��ģ����Ҫ���ڳ�ʼ������������Ǳ�׼,ʹ��ʱ���Ҳο�
*/

#include "yy_p_type.h"
#include "yy_e_memcheck.h"

typedef struct yy_e_argv_s{
    YY_E_OBJ_MAGIC_DEFINE;
    int argc;                   /* ��������ĸ��� */
    yy_p_tchar * const * argv;  /* ��������ַ��� */
}yy_e_argv_t;

/* ����������ַ����͸�����ӵ�av�ṹ���� */
extern int yy_e_argv_init( yy_e_argv_t *  av, int argc, yy_p_tchar * const * argv );

/* �ӳ�ʼ���ṹ���л�ȡ����name��ֵ */
extern const yy_p_tchar * yy_e_argv_get_arg_by_name( yy_e_argv_t *  av, const yy_p_tchar * name );

/* ��ȡ��ʼ���ṹ���ж�Ӧindexλ�õĲ��� */
extern const yy_p_tchar * yy_e_argv_get_arg_by_index( yy_e_argv_t *  av, int index );

/* �ж�����������Ƿ����name���� */
extern int yy_e_argv_is_arg_exist( yy_e_argv_t *  av, const yy_p_tchar * name );

#endif