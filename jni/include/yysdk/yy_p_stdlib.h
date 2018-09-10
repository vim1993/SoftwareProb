#ifndef YY_PC_STDLIB_H
#define YY_PC_STDLIB_H
#include "yy_p_config.h"
#include <stdlib.h>
#include <math.h>
#include "yy_p_type.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define yy_p_rand rand      /* 生成一个0-RAND_MAX之间的伪随机整数 */
#define yy_p_srand srand    /* 以srand的参数为种子产生伪随机数 */

#define yy_p_system system  /* 执行一个DOS命令或者 Shell命令 */
#define yy_p_getenv getenv  /* 获取环境变量的值 */

#define yy_p_strtol strtol  /* 将参数nptr字符串根据base来转换成长整型数 */
#define yy_p_strtoul strtoul    /* 将参数nptr字符串根据base转换成无符号的长整型数 */
#define yy_p_atoi atoi      /*  将字符串转换成int型 */
#define yy_p_atol atol      /* 将字符串转换成long */
#define yy_p_atof atof      /* 将字符串转换成float型 */
#define yy_p_ceil ceil
/*********************************************************************
*函数功能：获取本程序使用的句柄数量
*函数参数：
*	无
*返回值：
*	句柄数量
*版本历史：
*	2015/05/11	sk	---		创建
**********************************************************************/
extern yy_p_uint32 yy_p_get_used_fd_count();

/*********************************************************************
*函数功能：返回yylib库的版本号
*函数参数：
*	无
*返回值：
*	返回yylib库的版本号
*版本历史：
*	2015/10/28	sk	---		创建
**********************************************************************/
const char * yy_p_get_yylib_version();

/*测试用例*/
extern int yy_p_stdlib_validation_test();

#ifdef  __cplusplus
}
#endif

#endif
