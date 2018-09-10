#ifndef YY_P_ASSERT_H
#define YY_P_ASSERT_H
/**
*   功能：关于C语言assert定义的平台适配
*   修订：2013-4-14 czy创建
*/

#include "yy_p_config.h"
#include <assert.h>

#ifdef  __cplusplus
extern "C" {
#endif


/**
*   功能：与标准assert相同
*/

#ifdef YY_P_NO_ASSERT
    #define yy_p_assert do{;}while(0)
#else
    #define yy_p_assert assert
#endif

#ifdef  __cplusplus
}
#endif

#endif
