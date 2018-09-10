#ifndef YY_E_MD5_H
#define YY_E_MD5_H

#include "yy_p_type.h"
#include "yy_e_md5_v2.h"

/* md5�ṹ�� */
typedef struct yy_e_md5_ctx_s {
    yy_p_uint32 state[4];	/* ��ʼ�������Լ�md5���������� */
	size_t curlen;		/* ��ǰ�Ľ���md5Ԥ����ֽ��� */
	yy_p_uint64 length;	/* ����md5Ԥ����ַ������� */
    yy_p_uint8 buf[64];	/* ����md5Ԥ����ַ��� */
}yy_e_md5_ctx_t;

/* md5�ṹ���ʼ�� */
extern void yy_e_md5_init( yy_e_md5_ctx_t * md5 );

/* �ж�������ַ����Ƿ��ܹ�����md5���� */
extern void yy_e_md5_process( yy_e_md5_ctx_t * md5, const yy_p_uint8 *buf, size_t len );

/* ��md5����ṹ��������ַ��� */
extern void yy_e_md5_done( yy_e_md5_ctx_t * md5, yy_p_uint8 *hash );

/* ��buf��λ���� */
extern void yy_e_md5_digest_bin_out( const char * buf, size_t len, char * bin_out );

/* ת��Ϊ�ַ�����������strhex_out����Ҫ��33�ֽڵĿռ䣬�洢���Ľ�β0 */
extern void yy_e_md5_digest_strhex_out( const char * buf, size_t len, char * strhex_out, int is_lowercase );

/* �������� */
extern int yy_e_md5_validation_test( const char * test_str );

#endif
