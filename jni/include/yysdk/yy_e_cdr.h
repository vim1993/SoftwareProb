#ifndef YY_E_CDR_H
#define YY_E_CDR_H
#include "yy_p_type.h"
#include "yy_e_memcheck.h"

#ifdef  __cplusplus
extern "C" {
#endif

/**
*   �ο�ACE��CDR,���ڴ����������������,�Ƚϼ򵥣�����ע��
*/
#define YY_E_CDR_M_NULL		0
#define YY_E_CDR_M_LITTLE	1   //С��,���ֽڷ��ڿ�ʼ��ַ
#define YY_E_CDR_M_BIG		2   //���,���ֽڷ��ڿ�ʼ��ַ

/* ����������ṹ�� */
typedef struct yy_e_cdr_s
{
	YY_E_OBJ_MAGIC_DEFINE;
	char * buf;
	size_t len;
	size_t pos;

	int mode;
	int is_error;
	
}yy_e_cdr_t;

/* ��ֵvд�뵽buf�ַ����� */
extern void yy_e_cdr_p_w1( char * buf, yy_p_uint8 v, int mode );

/* ��ֵvд�뵽buf�ַ����� */
extern void yy_e_cdr_p_w2( char * buf, yy_p_uint16 v, int mode );

/* ��ֵvд�뵽buf�ַ����� */
extern void yy_e_cdr_p_w4( char * buf, yy_p_uint32 v, int mode );

/* ��ֵvд�뵽buf�ַ����� */
extern void yy_e_cdr_p_w8( char * buf, yy_p_uint64 v, int mode );

/* ��ȡbuf�ַ����е�ֵ */
extern yy_p_uint8  yy_e_cdr_p_r1( const char * buf, int mode );

/* ��ȡbuf�ַ����е�ֵ */
extern yy_p_uint16 yy_e_cdr_p_r2( const char * buf, int mode );

/* ��ȡbuf�ַ����е�ֵ */
extern yy_p_uint32 yy_e_cdr_p_r4( const char * buf, int mode );

/* ��ȡbuf�ַ����е�ֵ */
extern yy_p_uint64 yy_e_cdr_p_r8( const char * buf, int mode );


/* mode���л�ģʽ,��ָ����Ҫ��������л� */
extern void yy_e_cdr_init( yy_e_cdr_t * c, int mode, char * buf, size_t len );

/* ��ȡ�������ַ����ĳ��� */
extern size_t yy_e_cdr_buf_len( yy_e_cdr_t * c );

/* ��ȡ�������ַ����˿̽�����λ�� */
extern size_t yy_e_cdr_data_pos( yy_e_cdr_t * c );

/* ��ȡ�������ַ���ʣ��ĳ��� */
extern size_t yy_e_cdr_space_len( yy_e_cdr_t * c );

/* �ñ�������ṹ���ж�дλ��pos��ֵ */
extern int yy_e_cdr_skip( yy_e_cdr_t * c, int skip );

/* ��ȡ������ṹ�����ַ�������buf */
extern char * yy_e_cdr_buf_ptr( yy_e_cdr_t * c );

/* ��ȡ������ṹ���е�ǰ��дλ��pos */
extern char * yy_e_cdr_data_ptr( yy_e_cdr_t * c );

/* ��ȡbuf�������ַ����Ƿ��д� */
extern int yy_e_cdr_is_error( yy_e_cdr_t * c );

/* ��������ṹ���buf��д���ַ��� */
extern int yy_e_cdr_wx( yy_e_cdr_t * c, const char * v, size_t len );

/* ��������ṹ���buf��д���ַ� */
extern int yy_e_cdr_w1( yy_e_cdr_t * c, yy_p_uint8 v );

/* ��������ṹ���buf��д���ַ� */
extern int yy_e_cdr_w2( yy_e_cdr_t * c, yy_p_uint16 v );

/* ��������ṹ���buf��д��ֵ */
extern int yy_e_cdr_w4( yy_e_cdr_t * c, yy_p_uint32 v );

/*ʹ��4�ֽ�ͷ��Ϊ����ͷ*/
extern int yy_e_cdr_wstr( yy_e_cdr_t * c, const char * str );

/* ��ȡ������ṹ����posλ��len���ȵ��ַ�����v�� */
extern int yy_e_cdr_rx( yy_e_cdr_t * c, char * v, size_t len );

/* ��������ṹ���л�ȡposλ�õ�ֵ��v�� */
extern int yy_e_cdr_r1( yy_e_cdr_t * c, yy_p_uint8 * v );

/* ��������ṹ���л�ȡposλ�õ�ֵ��v�� */
extern int yy_e_cdr_r2( yy_e_cdr_t * c, yy_p_uint16 * v );

/* ��������ṹ���л�ȡposλ�õ�ֵ��v�� */
extern int yy_e_cdr_r4( yy_e_cdr_t * c, yy_p_uint32 * v );

/*ʹ��4�ֽ�ͷ��Ϊ����ͷ*/
extern int yy_e_cdr_rstr( yy_e_cdr_t * c, char * str, size_t len );

extern int yy_e_cdr_validation_test();

#ifdef  __cplusplus
}
#endif

#endif
