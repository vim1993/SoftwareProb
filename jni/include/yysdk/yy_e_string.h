#ifndef YY_E_STRING_H
#define YY_E_STRING_H
#include "yy_p_string.h"
#include "yy_f_alloc.h"
#include "yy_p_stdio.h"

#ifdef  __cplusplus
extern "C" {
#endif

/* 数值字符串转换为整数，最多转换len个字符，遇到第一个非数字则停止转换 */
extern int yy_e_atoi_s( const char * str, size_t len );

/* 标准C库atoi()的扩展，转换为32位无符号整形 */
extern yy_p_uint32 yy_e_atou32( const char * str );

/* 标准C库atof()的扩展，转换为浮点数 */
extern double yy_e_atof( const char * str );

/*  strcpy的扩展，字符串拷贝，目标空间充足才拷贝 */ 
extern int yy_e_strcpy_s( char * dst, size_t dst_len, const char * src );

/* strcat的扩展，目的空间充足才连接 */
extern int yy_e_strcat_s( char * dst, size_t dst_len, const char * src );

/*  strcat的扩展，目的空间充足才连接，连接长度为min(strlen(src), max_src_len) */
extern int yy_e_strcatn_s( char * dst, size_t dst_len, const char * src, size_t max_src_len );

/*  将size_t v转换为字符串,并连接在dst后面 */
extern int yy_e_strcat_size_t_s( char * dst, size_t dst_len, size_t v );

/* 将yy_p_off_t v转换为字符串,并连接在dst后面 */
extern int yy_e_strcat_off_t_s( char * dst, size_t dst_len, yy_p_off_t v );

/*  将int v转换为字符串,并连接在dst后面  */
extern int yy_e_strcat_int_s( char * dst, size_t dst_len, int v );

/* 目的空间足够的情况下，将字符s连接在dst后 */
extern int yy_e_strcat_chr_s( char * dst, size_t dst_len, char s );

/* strcat的扩展，目的空间充足的情况下将变参串连接到dst后 */
extern int yy_e_strcat_x_s( char * dst, size_t dst_len, const char *format, ... );

/* 在字符串中查找字符c第一次出现的位置,str长度有限制 */
extern const char * yy_e_strchr_s( const char * str, size_t len, int c );

/* strstr的扩展，查找子串在源串中第一次出现的位置，考虑源串长度限制 */
extern const char *yy_e_strstrn_s(const char *src, size_t len, const char *sub );

/* 申请内存空间并复制字符串，返回复制后的字符串的空间首地址(须和yy_e_strfree_alloc 配对使用) */
extern char * yy_e_strdup_alloc( const char * str, yy_f_alloc_t * alloc );

/* 释放由yy_e_strdup_alloc()申请的内存空间 */
extern void yy_e_strfree_alloc( char * str, yy_f_alloc_t * alloc );

/* 获取字符串长度,空串或NULL长度为0 */
extern size_t yy_e_strlen( const char * str );

/* 字符串比较,忽略大小写 */
extern int yy_e_strcmp_case( const char *str1, const char * str2 );

/*  将字符串中所有字符src替换成dst */
extern int yy_e_str_replace( char * str1, char src, char dst );

/* 去掉字符串头尾的字符c,一般用来移除空格 */
extern int yy_e_str_trim( char * str , char c );

/* 把字符串中的大写字母转换成小写 */
void yy_e_str_tolower(char * str);

/* 检查一块内存是不是以指定的字符串开始, is_case=1区分大小写,=0不区分 */
extern int yy_e_mem_is_str_begin( const char * mem, size_t len, const char * str, int is_case );

/* 内存块拷贝，检测目的空间是否足够 */
extern int yy_e_strcpy_from_mem_s( char * str, size_t str_len, const char * mem, size_t len );

/*  检查一个串是不是以一个子串结尾 */
extern int yy_e_str_is_end_str( const char * str, const char * end_str );

/* 检查一个串是不是以一个子串开始 */
extern int yy_e_str_is_begin_str( const char * str, const char * begin_str );

/* 检查一个串是不是以一个子串开始，忽略大小写 */
extern int yy_e_str_is_begin_str_nocase( const char * str, const char * begin_str );

/* 去除字符串尾重复的字符ch */
extern int yy_e_str_right_trim( char * str, int ch );

/* 检查str是不是处于str_array中，sep为分隔符 */
extern int yy_e_is_str_in_str_array( const char * str_array, const char * str, char sep );

/*  返回分隔符之前的子串，非空子串 */
extern const char * yy_e_str_array_get_str( const char * str_array, char sep, size_t * vl );

/* BASE64解码 */
extern int yy_e_base64_de(const char *data_in , size_t in_len , char *data_out, size_t * out_len );

/* BASE64编码 */
extern int yy_e_base64_en(const char *data_in , size_t in_len , char *data_out, size_t * out_len );
 
/* 类BASE64解码,使用了不是URL敏感字符 */
extern int yy_e_x64_de(const char *data_in , size_t in_len , char *data_out, size_t * out_len );

/*  类BASE64编码,使用了不是URL敏感字符 */
extern int yy_e_x64_en(const char *data_in , size_t in_len , char *data_out, size_t * out_len );


/* 对原始字符串进行XML编码（转义处理了<>/'" 5个关键字符) */
extern int yy_e_xml_en(const char *data_in , size_t in_len , char *data_out, size_t * out_len );

/* 功能:XML编码字符串解码，暂时未实现 */
extern int yy_e_xml_de(const char *data_in , size_t in_len , char *data_out, size_t * out_len );

/* 二进制数转换成16进制 */
extern int yy_e_bin_to_hex( const char * data_in,  size_t in_len , char *data_out, size_t * out_len, int is_lowercase );

/* 16进制转换成二进制 */
extern int yy_e_hex_to_bin( const char * data_in,  size_t in_len , char *data_out, size_t * out_len );

/* 检测源串中指定字符出现的次数 */
extern size_t yy_e_strchr_count( const char * str, char ch );

/* 检测字符串是否是纯数字 */
extern int yy_e_is_numeric(const char * str);

/* 检测字符串是否是纯正的字符字符串a~z || A~Z,is_case = 0,不区分大小的,is_case = 1,区分大小写 */
extern int yy_e_is_char_string(const char *str, int is_case);

extern int yy_e_string_validation_test();

#ifdef  __cplusplus
}
#endif

#endif

