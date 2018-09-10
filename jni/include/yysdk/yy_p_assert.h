#ifndef YY_P_ASSERT_H
#define YY_P_ASSERT_H
/**
*   ���ܣ�����C����assert�����ƽ̨����
*   �޶���2013-4-14 czy����
*/

#include "yy_p_config.h"
#include <assert.h>

#ifdef  __cplusplus
extern "C" {
#endif


/**
*   ���ܣ����׼assert��ͬ
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
