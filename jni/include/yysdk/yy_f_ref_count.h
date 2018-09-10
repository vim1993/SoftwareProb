#ifndef YY_F_REF_COUNT_H
#define YY_F_REF_COUNT_H
#include "yy_p_type.h"
#include "yy_p_thread.h"
#include "yy_p_test.h"
#include "yy_e_memcheck.h"

/*
*引用计数，主要用于对多个模块或线程共享的数据进行引用计数
*added by gaoqiang, 2015-07-29
*/
typedef struct yy_f_ref_count_s{
    YY_E_MEM_MAGIC_PREFIX_DEFINE;
    YY_E_OBJ_MAGIC_DEFINE;
    yy_p_thr_mutex_t lock;		/* 读写锁 */
    int ref_count;			/* 引用计数值 */
    
    YY_E_MEM_MAGIC_SUFFIX_DEFINE;
}yy_f_ref_count_t;

/* 初始化引用计数 */
extern int yy_f_ref_count_init( yy_f_ref_count_t * ref, int is_use_lock );

/* uninit引用计数 */
extern int yy_f_ref_count_uninit( yy_f_ref_count_t * ref );

/* 增加引用计数 */
extern int yy_f_ref_count_add_ref( yy_f_ref_count_t * ref );

/* 减少引用计数 */
extern int yy_f_ref_count_release_ref( yy_f_ref_count_t * ref );

/* 获取当前引用计数 */
extern int yy_f_ref_count_get_count( yy_f_ref_count_t * ref );

/* 测试用例 */
extern int yy_f_ref_count_validation_test();
#endif
