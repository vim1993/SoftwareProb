#ifndef YY_PC_STDLIB_H
#define YY_PC_STDLIB_H
#include "yy_p_config.h"
#include <stdlib.h>
#include <math.h>
#include "yy_p_type.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define yy_p_rand rand      /* ����һ��0-RAND_MAX֮���α������� */
#define yy_p_srand srand    /* ��srand�Ĳ���Ϊ���Ӳ���α����� */

#define yy_p_system system  /* ִ��һ��DOS������� Shell���� */
#define yy_p_getenv getenv  /* ��ȡ����������ֵ */

#define yy_p_strtol strtol  /* ������nptr�ַ�������base��ת���ɳ������� */
#define yy_p_strtoul strtoul    /* ������nptr�ַ�������baseת�����޷��ŵĳ������� */
#define yy_p_atoi atoi      /*  ���ַ���ת����int�� */
#define yy_p_atol atol      /* ���ַ���ת����long */
#define yy_p_atof atof      /* ���ַ���ת����float�� */
#define yy_p_ceil ceil
/*********************************************************************
*�������ܣ���ȡ������ʹ�õľ������
*����������
*	��
*����ֵ��
*	�������
*�汾��ʷ��
*	2015/05/11	sk	---		����
**********************************************************************/
extern yy_p_uint32 yy_p_get_used_fd_count();

/*********************************************************************
*�������ܣ�����yylib��İ汾��
*����������
*	��
*����ֵ��
*	����yylib��İ汾��
*�汾��ʷ��
*	2015/10/28	sk	---		����
**********************************************************************/
const char * yy_p_get_yylib_version();

/*��������*/
extern int yy_p_stdlib_validation_test();

#ifdef  __cplusplus
}
#endif

#endif
