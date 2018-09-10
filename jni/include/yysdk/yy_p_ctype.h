#ifndef YY_P_CTYPE_H
#define YY_P_CTYPE_H
/**
*   ���ܣ�����C����ctype�����ƽ̨����
*   �޶���2013-4-14 czy����
*/

#include "yy_p_config.h"
#include <ctype.h>

#ifdef  __cplusplus
extern "C" {
#endif

/**
*   ���ܣ����׼C����ͬ����
*/

#define yy_p_isalnum isalnum    /* �ж��ַ�����c�Ƿ�Ϊ��ĸ������ */
#define yy_p_isalpha isalpha    /* �ж��ַ�ch�Ƿ�ΪӢ����ĸ */
#define yy_p_isdigit isdigit    /* �жϲ���c�Ƿ�Ϊ���� */
#define yy_p_isxdigit isxdigit  /* �жϲ�ʳ�Ƿ�Ϊ16�������� */

#define yy_p_tolower tolower    /* ���ַ�ת����Сд��ĸ������ĸ��ת�� */
#define yy_p_toupper toupper    /* ��Сд��ĸת���ɴ�д��ĸ */

/***********************************************************************************
*   ���ܣ���������
*   @param��
*           ��
*   @return:
*           ����Ĭ��ֵ
*   @date :
*           2015/4/29
***********************************************************************************/
extern int yy_p_ctype_validation_test();

#ifdef  __cplusplus
}
#endif

#endif
