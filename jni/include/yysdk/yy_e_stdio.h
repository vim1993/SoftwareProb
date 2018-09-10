
/**
*   yy_e_xx.h �����ĺ���������ʵ�ʵ�ĳЩ��Ŀ����Ҫ�ű���ӵ��������еģ�
*   ���߱�ͨ���ԣ���˲����-_-��
*/

#ifndef YY_E_STDIO_H
#define YY_E_STDIO_H
#include "yy_p_stdio.h"

/* ��fullname�����һ��\\������ݿ�����basename���棬����ȫ������ */
extern int yy_e_file_basename( const char * fullname, char * basename );

/* ��fullname�����һ��\\������ݿ�����basename���棬����ȫ������,���޸�basename_noext�е�'.'Ϊ����0�� */
extern int yy_e_file_basename_noext( const char * fullname, char * basename_noext );

/* ��fullname�ַ������Ƶ�path������'\\'��Ϊ'\0'��ȥ������������ */
extern int yy_e_file_path( const char * fullname, char * path );

/* ��fullname�ַ���'\\'������ݸ��Ƶ�ext����󣬵���'\\'���һ�γ��֡�.'�������Ҫ��ȥ�� */
extern int yy_e_file_ext( const char * fullname, char * ext );
#endif
