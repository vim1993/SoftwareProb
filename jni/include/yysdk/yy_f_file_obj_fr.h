#ifndef YY_F_FILE_OBJ_FR_H
#define YY_F_FILE_OBJ_FR_H
#include "yy_f_file_obj.h"
/* 
*ʵ��˼�룺������һ���ڴ�鹹�ɵĻ�������һ���Զ�ȡ�����ļ����ݵ�������������������ڻ������н��� 
*added by gaoqiang, 2015-10-21
*/

/* ����:����ļ���ȡ�Ŀ����Ż���,ʹ��block_sizeΪ������ȡ��������,�����Ż� */
yy_f_file_obj_t * yy_f_file_obj_create_fr( yy_f_alloc_t * alloc_thiz, yy_f_alloc_t * alloc_block, size_t block_size, const char * filename, int flag, mode_t perms, LPSECURITY_ATTRIBUTES sa );
#endif
