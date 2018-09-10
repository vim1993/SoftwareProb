#ifndef YY_P__TEST_H
#define YY_P__TEST_H
#include "yy_p_config.h"
#include <assert.h>
#include <stdio.h>

#if !defined( __FILE__ )
    #define __FILE__ "unsup"
#endif

#if !defined( __LINE__ )
    #define __LINE__ 0
#endif

//������ʹ�õ����
#define yy_p_t_printf printf

//����ͨ�ú�
#define YY_P_T_BEGIN( tag ) char pt_func[]= tag; yy_p_t_printf( "%s begin\n", pt_func );
#define YY_P_T_END() do{ yy_p_t_printf( "%s end success \n", pt_func ); return 0; }while(0)
#define YY_P_T_ERROR( a ) do{ yy_p_t_printf( "error:%s\n", a ); yy_p_t_printf("file:%s, line:%u\n", __FILE__, __LINE__);return -1; }while(0)


extern int yy_p_config_validation_test();

#endif
