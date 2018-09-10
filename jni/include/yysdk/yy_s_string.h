#ifndef YY_S_STRING_H
#define YY_S_STRING_H
#include "yy_e_string.h"
#include "yy_f_alloc.h"

typedef struct yy_s_string_s{
    yy_f_alloc_t * alloc;
    char * buf;
    size_t len;		/* 字符串长度，长度未包含结尾的'\0',与C/C++通用约定一致 */
    size_t size;	/* 内存长度 */
}yy_s_string_t;

/* 创建默认大小的字符串缓存，无初值 */
extern yy_s_string_t * yy_s_string_create( yy_f_alloc_t * alloc );

/* 创建字符串缓存,初始值为str，大小根据str长度自动调整 */
extern yy_s_string_t * yy_s_string_create1( const char * str, yy_f_alloc_t * alloc );

/* 创建字符串缓存，若sstr非空则将其内容拷贝到新缓存，alloc为空则采用sstr的内存分配器 */
extern yy_s_string_t * yy_s_string_create2( const yy_s_string_t * sstr, yy_f_alloc_t * alloc );

/* 采用alloc内存分配器创建字符串缓存，初值为mem */
extern yy_s_string_t * yy_s_string_create3( const char * mem, size_t len, yy_f_alloc_t * alloc );

/* 销毁字符串缓存 */
extern void yy_s_string_destroy( yy_s_string_t * sstr );

/* 克隆字符串缓存 */
extern yy_s_string_t * yy_s_string_clone( const yy_s_string_t * sstr, yy_f_alloc_t * new_alloc );

/*返回字符串缓存的内存分配器 */
extern yy_f_alloc_t * yy_s_string_get_alloc( const yy_s_string_t * sstr );

/* 获取字符串缓存的数据长度 */
extern size_t yy_s_string_length( const yy_s_string_t * sstr );

/* 获取字符串缓存大小 */
extern size_t yy_s_string_size( const yy_s_string_t * sstr );

/* 返回字符串缓存内容首地址 */
extern const char * yy_s_string_c_str( const yy_s_string_t * sstr );

/* 若size大于当前缓存中字符串长度，则重新分配缓存空间 */
extern int yy_s_string_reserved( yy_s_string_t * sstr, size_t size );

/* 将字符串缓存中index后的count个字符连接到当前缓存末尾，空间不够则重新分配 */
extern yy_s_string_t * yy_s_string_substr( const yy_s_string_t * sstr1, size_t index, size_t count );

/* 将字符串memory拷贝到sstr缓存末尾,如果缓存剩余空间不足，则重新申请，字符串memory可为空（不做任何操作） */
extern int yy_s_string_append( yy_s_string_t * sstr, const char * memory, size_t len );

/* C语言扩展 */

/* 将右参数缓存中的字符串连接到左参数，右参数可为空（无任何操作发生） */
extern int yy_s_string_strcat1( yy_s_string_t * sstr1, const yy_s_string_t * sstr2 );

/* 将字符串连接到缓存中，字符串可为空（无任何操作发生） */
extern int yy_s_string_strcat2( yy_s_string_t * sstr1, const char * str );

/* 比较字符串缓存（使用其中存储的字符串）与字符串 */
extern int yy_s_string_strcmp1( const yy_s_string_t * sstr1, const char * str2 );

/* 比较两个字符串缓存（使用其中存储的字符串） */
extern int yy_s_string_strcmp2( const yy_s_string_t * sstr1, const yy_s_string_t * sstr2 );

/* 在sstr1中查找c的首次出现的相对偏移地址 */
extern size_t yy_s_string_strchr( const yy_s_string_t * sstr1, char c );

/* test */
extern int yy_s_string_validation_test();

#endif
