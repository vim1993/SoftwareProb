#ifndef YY_F_ALLOC_NF_H
#define YY_F_ALLOC_NF_H
#include "yy_f_alloc.h"

/**
*   ����:������ʺϷ���С���,�Ҳ������ͷ�
*   �ʺ�����һ��������,���������˺ܶ��ַ���,����һ�����ͷ�
*/

/* nfp�ڴ�ش���(block���з���,large���䳬��) */
extern yy_f_alloc_t * yy_f_alloc_nfp_create1( size_t block_size, yy_f_alloc_t * alloc_block, yy_f_alloc_t * alloc_large );

extern "C" {
/* nfp�ڴ�ش���(��nfp_buf��Ϊ�صĿ��ڴ�) */
extern yy_f_alloc_t * yy_f_alloc_nfp_create2( size_t block_size, char * nfp_buf, yy_f_alloc_t * alloc_large );
}
/* �������� */
extern int yy_f_alloc_nfp_validation_test();

#endif
