#ifndef YY_F_ALLOC_CBP_H
#define YY_F_ALLOC_CBP_H
#include "yy_f_alloc.h"
/**
*   �ص���Ӧ����: �ʺ�1KB��,���ǹ̶����ȵ��ڴ�ط���
*   ����һ��������ʽ�ĳ�,�ʺ�һЩ�ϴ���ڴ�鹹��һ����,��512KB��һ��BLOCK��С
*   ��G_DATAʱ,ʵ������Ŀռ���block_size��һ��ALIGNMENT
*/

/**
*   flag: ֧��,YY_F_ALLOC_FLAG_LOCK(����),YY_F_ALLOC_FLAG_GDATA(��д������)
*   block_size:���С
*   init_block_num:��ʼ�����(���Ӧ��grow_block_num�ı���,���С��grow_block_num,�ᱻ����Ϊgrow_block_num)
*   grow_block_num:�غľ�ʱ,ÿ�����������
*   max_block_num: ������������,0Ϊ������
*/
/* ����cbp�ڴ�� */
extern yy_f_alloc_t * yy_f_alloc_cbp_create( yy_p_uint32 flag, size_t block_size, size_t init_block_num, size_t grow_block_num, size_t max_block_num, yy_f_alloc_t * alloc_block );

/* �������� */
extern int yy_f_alloc_cbp_validation_test();
#endif
