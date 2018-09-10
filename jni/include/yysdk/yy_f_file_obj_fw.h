#ifndef YY_F_FILE_OBJ_FW_H
#define YY_F_FILE_OBJ_FW_H
#include "yy_f_file_obj.h"
/* 
*实现思想：申请由一个内存块构成的缓冲区，数据先写入缓存
*added by gaoqiang, 2015-10-21
*/

/* 功能:针对文件写入的快速优化类 */
yy_f_file_obj_t * yy_f_file_obj_create_fw( yy_f_alloc_t * alloc_thiz, yy_f_alloc_t * alloc_block, size_t block_size, const char * filename, int flag, mode_t perms, LPSECURITY_ATTRIBUTES sa );

/* 测试用例 */
extern int yy_f_file_obj_fw_validation_test( const char * filename );

#endif