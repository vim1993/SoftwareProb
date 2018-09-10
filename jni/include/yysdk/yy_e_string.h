#ifndef YY_E_STRING_H
#define YY_E_STRING_H
#include "yy_p_string.h"
#include "yy_f_alloc.h"
#include "yy_p_stdio.h"

#ifdef  __cplusplus
extern "C" {
#endif

/* ��ֵ�ַ���ת��Ϊ���������ת��len���ַ���������һ����������ֹͣת�� */
extern int yy_e_atoi_s( const char * str, size_t len );

/* ��׼C��atoi()����չ��ת��Ϊ32λ�޷������� */
extern yy_p_uint32 yy_e_atou32( const char * str );

/* ��׼C��atof()����չ��ת��Ϊ������ */
extern double yy_e_atof( const char * str );

/*  strcpy����չ���ַ���������Ŀ��ռ����ſ��� */ 
extern int yy_e_strcpy_s( char * dst, size_t dst_len, const char * src );

/* strcat����չ��Ŀ�Ŀռ��������� */
extern int yy_e_strcat_s( char * dst, size_t dst_len, const char * src );

/*  strcat����չ��Ŀ�Ŀռ��������ӣ����ӳ���Ϊmin(strlen(src), max_src_len) */
extern int yy_e_strcatn_s( char * dst, size_t dst_len, const char * src, size_t max_src_len );

/*  ��size_t vת��Ϊ�ַ���,��������dst���� */
extern int yy_e_strcat_size_t_s( char * dst, size_t dst_len, size_t v );

/* ��yy_p_off_t vת��Ϊ�ַ���,��������dst���� */
extern int yy_e_strcat_off_t_s( char * dst, size_t dst_len, yy_p_off_t v );

/*  ��int vת��Ϊ�ַ���,��������dst����  */
extern int yy_e_strcat_int_s( char * dst, size_t dst_len, int v );

/* Ŀ�Ŀռ��㹻������£����ַ�s������dst�� */
extern int yy_e_strcat_chr_s( char * dst, size_t dst_len, char s );

/* strcat����չ��Ŀ�Ŀռ���������½���δ����ӵ�dst�� */
extern int yy_e_strcat_x_s( char * dst, size_t dst_len, const char *format, ... );

/* ���ַ����в����ַ�c��һ�γ��ֵ�λ��,str���������� */
extern const char * yy_e_strchr_s( const char * str, size_t len, int c );

/* strstr����չ�������Ӵ���Դ���е�һ�γ��ֵ�λ�ã�����Դ���������� */
extern const char *yy_e_strstrn_s(const char *src, size_t len, const char *sub );

/* �����ڴ�ռ䲢�����ַ��������ظ��ƺ���ַ����Ŀռ��׵�ַ(���yy_e_strfree_alloc ���ʹ��) */
extern char * yy_e_strdup_alloc( const char * str, yy_f_alloc_t * alloc );

/* �ͷ���yy_e_strdup_alloc()������ڴ�ռ� */
extern void yy_e_strfree_alloc( char * str, yy_f_alloc_t * alloc );

/* ��ȡ�ַ�������,�մ���NULL����Ϊ0 */
extern size_t yy_e_strlen( const char * str );

/* �ַ����Ƚ�,���Դ�Сд */
extern int yy_e_strcmp_case( const char *str1, const char * str2 );

/*  ���ַ����������ַ�src�滻��dst */
extern int yy_e_str_replace( char * str1, char src, char dst );

/* ȥ���ַ���ͷβ���ַ�c,һ�������Ƴ��ո� */
extern int yy_e_str_trim( char * str , char c );

/* ���ַ����еĴ�д��ĸת����Сд */
void yy_e_str_tolower(char * str);

/* ���һ���ڴ��ǲ�����ָ�����ַ�����ʼ, is_case=1���ִ�Сд,=0������ */
extern int yy_e_mem_is_str_begin( const char * mem, size_t len, const char * str, int is_case );

/* �ڴ�鿽�������Ŀ�Ŀռ��Ƿ��㹻 */
extern int yy_e_strcpy_from_mem_s( char * str, size_t str_len, const char * mem, size_t len );

/*  ���һ�����ǲ�����һ���Ӵ���β */
extern int yy_e_str_is_end_str( const char * str, const char * end_str );

/* ���һ�����ǲ�����һ���Ӵ���ʼ */
extern int yy_e_str_is_begin_str( const char * str, const char * begin_str );

/* ���һ�����ǲ�����һ���Ӵ���ʼ�����Դ�Сд */
extern int yy_e_str_is_begin_str_nocase( const char * str, const char * begin_str );

/* ȥ���ַ���β�ظ����ַ�ch */
extern int yy_e_str_right_trim( char * str, int ch );

/* ���str�ǲ��Ǵ���str_array�У�sepΪ�ָ��� */
extern int yy_e_is_str_in_str_array( const char * str_array, const char * str, char sep );

/*  ���طָ���֮ǰ���Ӵ����ǿ��Ӵ� */
extern const char * yy_e_str_array_get_str( const char * str_array, char sep, size_t * vl );

/* BASE64���� */
extern int yy_e_base64_de(const char *data_in , size_t in_len , char *data_out, size_t * out_len );

/* BASE64���� */
extern int yy_e_base64_en(const char *data_in , size_t in_len , char *data_out, size_t * out_len );
 
/* ��BASE64����,ʹ���˲���URL�����ַ� */
extern int yy_e_x64_de(const char *data_in , size_t in_len , char *data_out, size_t * out_len );

/*  ��BASE64����,ʹ���˲���URL�����ַ� */
extern int yy_e_x64_en(const char *data_in , size_t in_len , char *data_out, size_t * out_len );


/* ��ԭʼ�ַ�������XML���루ת�崦����<>/'" 5���ؼ��ַ�) */
extern int yy_e_xml_en(const char *data_in , size_t in_len , char *data_out, size_t * out_len );

/* ����:XML�����ַ������룬��ʱδʵ�� */
extern int yy_e_xml_de(const char *data_in , size_t in_len , char *data_out, size_t * out_len );

/* ��������ת����16���� */
extern int yy_e_bin_to_hex( const char * data_in,  size_t in_len , char *data_out, size_t * out_len, int is_lowercase );

/* 16����ת���ɶ����� */
extern int yy_e_hex_to_bin( const char * data_in,  size_t in_len , char *data_out, size_t * out_len );

/* ���Դ����ָ���ַ����ֵĴ��� */
extern size_t yy_e_strchr_count( const char * str, char ch );

/* ����ַ����Ƿ��Ǵ����� */
extern int yy_e_is_numeric(const char * str);

/* ����ַ����Ƿ��Ǵ������ַ��ַ���a~z || A~Z,is_case = 0,�����ִ�С��,is_case = 1,���ִ�Сд */
extern int yy_e_is_char_string(const char *str, int is_case);

extern int yy_e_string_validation_test();

#ifdef  __cplusplus
}
#endif

#endif

