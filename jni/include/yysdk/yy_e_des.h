#ifndef YY_E_DES_H
#define YY_E_DES_H

#include "yy_p_type.h"

//DES������8�ֽڶ���
#define YY_E_DES_ALIGN(d) YY_P_ALIGN( d, 8 )

#ifdef  __cplusplus
extern "C" {
#endif

/* DES����,��ԿkeyΪ8�ֽڣ�ͬ������Կһ���� */
extern void yy_e_des_encode( const char * data_in, size_t len, char * data_out, char * key );

/* DES���ܣ���ԿkeyΪ8�ֽ� */
extern void yy_e_des_decode( const char * data_in, size_t len, char * data_out, char * key );

/* ��������ļ��ܽ��ܣ���μ����ڽ��ܣ��ڼ��� */
extern void yy_e_3des_encode( const char * data_in, size_t len, char * data_out, char * key );

/* ��������ļ��ܽ��ܣ���ν����ڼ��ܣ��ڽ��� */
extern void yy_e_3des_decode( const char * data_in, size_t len, char * data_out, char * key );

//3DES�ӽ���,keyΪ16�ֽ�
extern int yy_e_des_validation_test( );

#ifdef  __cplusplus
}
#endif

#endif
