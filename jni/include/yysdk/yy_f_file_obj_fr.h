#ifndef YY_F_FILE_OBJ_FR_H
#define YY_F_FILE_OBJ_FR_H
#include "yy_f_file_obj.h"
/* 
*实现思想：申请由一个内存块构成的缓冲区，一次性读取部分文件数据到缓冲区，后续读则可在缓冲区中进行 
*added by gaoqiang, 2015-10-21
*/

/* 功能:针对文件读取的快速优化类,使用block_size为块对齐读取加载数据,进行优化 */
yy_f_file_obj_t * yy_f_file_obj_create_fr( yy_f_alloc_t * alloc_thiz, yy_f_alloc_t * alloc_block, size_t block_size, const char * filename, int flag, mode_t perms, LPSECURITY_ATTRIBUTES sa );
#endif
