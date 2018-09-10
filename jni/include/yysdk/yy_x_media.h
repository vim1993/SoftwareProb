#ifndef YY_X_MEDIA_H
#define YY_X_MEDIA_H
#include "yy_p_type.h"
#include "yy_p_stdio.h"
typedef struct yy_x_file_info_s{
    yy_p_uint32 time_begin; //文件内容的第一个数据包时间,MS
    yy_p_uint32 time_end;   //文件内容的最后一个数据包时间,MS
    yy_p_uint32 time_len;   //文件总时长,MS
    yy_p_off_t file_len;    //文件总长
	yy_p_uint32 byte_rate;	//码率
	time_t clock_time_begin;	//文件针对真实时间的开始时间（对一些录制格式文件有用),秒
}yy_x_file_info_t;
#endif
