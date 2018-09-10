#ifndef YY_P_CTYPE_H
#define YY_P_CTYPE_H
/**
*   功能：关于C语言ctype定义的平台适配
*   修订：2013-4-14 czy创建
*/

#include "yy_p_config.h"
#include <ctype.h>

#ifdef  __cplusplus
extern "C" {
#endif

/**
*   功能：与标准C函数同含义
*/

#define yy_p_isalnum isalnum    /* 判断字符变量c是否为字母或数字 */
#define yy_p_isalpha isalpha    /* 判断字符ch是否为英文字母 */
#define yy_p_isdigit isdigit    /* 判断参数c是否为数字 */
#define yy_p_isxdigit isxdigit  /* 判断蚕食是否为16进制数字 */

#define yy_p_tolower tolower    /* 将字符转换成小写字母，非字母不转换 */
#define yy_p_toupper toupper    /* 将小写字母转换成大写字母 */

/***********************************************************************************
*   功能：测试用例
*   @param：
*           无
*   @return:
*           返回默认值
*   @date :
*           2015/4/29
***********************************************************************************/
extern int yy_p_ctype_validation_test();

#ifdef  __cplusplus
}
#endif

#endif
