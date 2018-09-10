#ifndef YY_E_INI_H
#define YY_E_INI_H
#include "yy_p_type.h"
#include "yy_p_stdio.h"
#include "yy_p_stdlib.h"
#include "yy_s_string.h"
#include "yy_s_lxlist.h"

/**
*   ���׵�������,��Ҫ���ڼ��������ļ�����ȡ�����ļ��еĲ���
*/

/* ��ȡ�����ļ�ʱ��һ�е����� */
typedef struct yy_e_ini_line_s{
    yy_s_lxlist_head_t list_line;	/* ����ͷ�����ڹ�����yy_e_ini_s�������� */
    char * key;					/* ������ */
    char * value;					/* �ò�����ֵ(���磺key = value��������ʽ) */
    char * memo;					/**/ 
    
}yy_e_ini_line_t;

/* ��ȡ�����ļ��ṹ�� */
typedef struct yy_e_ini_s{
    yy_f_alloc_t * alloc;			/* �ڴ������ */
    char filename[YY_P_MAX_PATH];	/* ��ȡ���ļ��� */
    yy_s_lxlist_head_t list_line_head;	/* ��������װ��ÿ�е�����(��Ϊÿ�����ݼ�Ϊ��ͬ��һ������) */
}yy_e_ini_t;

/* ����ָ���ļ����������ļ������ļ�������� */
extern yy_e_ini_t * yy_e_ini_load_from_file( yy_f_alloc_t * alloc, const char * filename );

/* ������Ϊfilename�������ļ����������ļ���ȷ���Ƿ���ڣ�ֻ�Ǵ���һ���ṹ�� */
extern yy_e_ini_t * yy_e_ini_create_file( yy_f_alloc_t * alloc, const char * filename );

/* �������ļ��й������������нڵ��еĲ�����ֵ������ļ��� */
extern int yy_e_init_save_to_file( yy_e_ini_t * ini );

/* �ݻ������ļ��ṹ�� */
extern void yy_e_ini_destroy( yy_e_ini_t * ini );

/* �������ļ��ṹ���л�ȡ����key��Ӧ��ֵ */
extern const char * yy_e_ini_get_value( yy_e_ini_t * ini, const char * key );

/* �������ļ��ṹ���л�ȡ����key��Ӧ��ֵ����Ҫ��ֵת�������� */
extern int yy_e_ini_get_value_int( yy_e_ini_t * ini, const char * key );

/* �������ļ��ṹ���в���key�����������ڵ㣬���滻�ýڵ��Ӧ��ֵ�����û�У�������µĽڵ� */
extern int yy_e_ini_set_value( yy_e_ini_t * ini, const char * key, const char * value );

/* �ж������ļ��ṹ�����Ƿ��нڵ����key���� */
extern int yy_e_ini_is_key_exist( yy_e_ini_t * ini, const char * key );

/* �ж������ļ��ṹ�����Ƿ��нڵ����key���Լ�key��Ӧ��ֵ�Ƿ���� */
extern int yy_e_ini_is_key_value_exist( yy_e_ini_t * ini, const char * key );

/* �ж������ļ��ṹ�����Ƿ��нڵ����key������У��򽫸�key���ڽڵ�ɾ�� */
extern void yy_e_ini_remove_key( yy_e_ini_t * ini, const char * key );

#endif
