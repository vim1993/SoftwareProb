#ifndef YY_P_STRING_H
#define YY_P_STRING_H
#include "yy_p_config.h"
#include <string.h>
#define yy_p_strcmp strcmp
#define yy_p_strcpy strcpy
#define yy_p_strcat strcat
#define yy_p_strlen strlen
#define yy_p_strchr strchr      /* 查找字符串s中c字符首次出现的地方 */
#define yy_p_strstr strstr      /* 查找字符串s1中首次出现s2字符串的地方 */
#define yy_p_strrchr strrchr    /* 查找字符c在字符串s中最后一次出现的位置 */
#define yy_p_strdup strdup      /* 字符串拷贝函数，一般和free函数成对出现 */


//打印字符串指针时的安全模式
#define YY_P_PRI_CSTR(a) ( (a)!=NULL?(a):"null_str" )
#define YY_P_PRI_EMPTY_STR(a) ( (a)!=NULL?(a):"" )



/* 测试用例 */
extern int yy_p_string_validation_test();
#endif
