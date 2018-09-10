#ifndef YY_F_ALLOC_NF_H
#define YY_F_ALLOC_NF_H
#include "yy_f_alloc.h"

/**
*   功能:这个池适合分配小块池,且不进行释放
*   适合用在一个函数中,比如申请了很多字符串,最终一次性释放
*/

/* nfp内存池创建(block进行分配,large分配超长) */
extern yy_f_alloc_t * yy_f_alloc_nfp_create1( size_t block_size, yy_f_alloc_t * alloc_block, yy_f_alloc_t * alloc_large );

extern "C" {
/* nfp内存池创建(以nfp_buf作为池的块内存) */
extern yy_f_alloc_t * yy_f_alloc_nfp_create2( size_t block_size, char * nfp_buf, yy_f_alloc_t * alloc_large );
}
/* 测试用例 */
extern int yy_f_alloc_nfp_validation_test();

#endif
