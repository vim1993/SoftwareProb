#ifndef YY_S_STRING_H
#define YY_S_STRING_H
#include "yy_e_string.h"
#include "yy_f_alloc.h"

typedef struct yy_s_string_s{
    yy_f_alloc_t * alloc;
    char * buf;
    size_t len;		/* �ַ������ȣ�����δ������β��'\0',��C/C++ͨ��Լ��һ�� */
    size_t size;	/* �ڴ泤�� */
}yy_s_string_t;

/* ����Ĭ�ϴ�С���ַ������棬�޳�ֵ */
extern yy_s_string_t * yy_s_string_create( yy_f_alloc_t * alloc );

/* �����ַ�������,��ʼֵΪstr����С����str�����Զ����� */
extern yy_s_string_t * yy_s_string_create1( const char * str, yy_f_alloc_t * alloc );

/* �����ַ������棬��sstr�ǿ��������ݿ������»��棬allocΪ�������sstr���ڴ������ */
extern yy_s_string_t * yy_s_string_create2( const yy_s_string_t * sstr, yy_f_alloc_t * alloc );

/* ����alloc�ڴ�����������ַ������棬��ֵΪmem */
extern yy_s_string_t * yy_s_string_create3( const char * mem, size_t len, yy_f_alloc_t * alloc );

/* �����ַ������� */
extern void yy_s_string_destroy( yy_s_string_t * sstr );

/* ��¡�ַ������� */
extern yy_s_string_t * yy_s_string_clone( const yy_s_string_t * sstr, yy_f_alloc_t * new_alloc );

/*�����ַ���������ڴ������ */
extern yy_f_alloc_t * yy_s_string_get_alloc( const yy_s_string_t * sstr );

/* ��ȡ�ַ�����������ݳ��� */
extern size_t yy_s_string_length( const yy_s_string_t * sstr );

/* ��ȡ�ַ��������С */
extern size_t yy_s_string_size( const yy_s_string_t * sstr );

/* �����ַ������������׵�ַ */
extern const char * yy_s_string_c_str( const yy_s_string_t * sstr );

/* ��size���ڵ�ǰ�������ַ������ȣ������·��仺��ռ� */
extern int yy_s_string_reserved( yy_s_string_t * sstr, size_t size );

/* ���ַ���������index���count���ַ����ӵ���ǰ����ĩβ���ռ䲻�������·��� */
extern yy_s_string_t * yy_s_string_substr( const yy_s_string_t * sstr1, size_t index, size_t count );

/* ���ַ���memory������sstr����ĩβ,�������ʣ��ռ䲻�㣬���������룬�ַ���memory��Ϊ�գ������κβ����� */
extern int yy_s_string_append( yy_s_string_t * sstr, const char * memory, size_t len );

/* C������չ */

/* ���Ҳ��������е��ַ������ӵ���������Ҳ�����Ϊ�գ����κβ��������� */
extern int yy_s_string_strcat1( yy_s_string_t * sstr1, const yy_s_string_t * sstr2 );

/* ���ַ������ӵ������У��ַ�����Ϊ�գ����κβ��������� */
extern int yy_s_string_strcat2( yy_s_string_t * sstr1, const char * str );

/* �Ƚ��ַ������棨ʹ�����д洢���ַ��������ַ��� */
extern int yy_s_string_strcmp1( const yy_s_string_t * sstr1, const char * str2 );

/* �Ƚ������ַ������棨ʹ�����д洢���ַ����� */
extern int yy_s_string_strcmp2( const yy_s_string_t * sstr1, const yy_s_string_t * sstr2 );

/* ��sstr1�в���c���״γ��ֵ����ƫ�Ƶ�ַ */
extern size_t yy_s_string_strchr( const yy_s_string_t * sstr1, char c );

/* test */
extern int yy_s_string_validation_test();

#endif
