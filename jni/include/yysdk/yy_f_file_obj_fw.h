#ifndef YY_F_FILE_OBJ_FW_H
#define YY_F_FILE_OBJ_FW_H
#include "yy_f_file_obj.h"
/* 
*ʵ��˼�룺������һ���ڴ�鹹�ɵĻ�������������д�뻺��
*added by gaoqiang, 2015-10-21
*/

/* ����:����ļ�д��Ŀ����Ż��� */
yy_f_file_obj_t * yy_f_file_obj_create_fw( yy_f_alloc_t * alloc_thiz, yy_f_alloc_t * alloc_block, size_t block_size, const char * filename, int flag, mode_t perms, LPSECURITY_ATTRIBUTES sa );

/* �������� */
extern int yy_f_file_obj_fw_validation_test( const char * filename );

#endif