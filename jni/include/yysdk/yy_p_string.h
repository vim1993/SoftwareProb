#ifndef YY_P_STRING_H
#define YY_P_STRING_H
#include "yy_p_config.h"
#include <string.h>
#define yy_p_strcmp strcmp
#define yy_p_strcpy strcpy
#define yy_p_strcat strcat
#define yy_p_strlen strlen
#define yy_p_strchr strchr      /* �����ַ���s��c�ַ��״γ��ֵĵط� */
#define yy_p_strstr strstr      /* �����ַ���s1���״γ���s2�ַ����ĵط� */
#define yy_p_strrchr strrchr    /* �����ַ�c���ַ���s�����һ�γ��ֵ�λ�� */
#define yy_p_strdup strdup      /* �ַ�������������һ���free�����ɶԳ��� */


//��ӡ�ַ���ָ��ʱ�İ�ȫģʽ
#define YY_P_PRI_CSTR(a) ( (a)!=NULL?(a):"null_str" )
#define YY_P_PRI_EMPTY_STR(a) ( (a)!=NULL?(a):"" )



/* �������� */
extern int yy_p_string_validation_test();
#endif
