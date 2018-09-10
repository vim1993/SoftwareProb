#ifndef YY_X_TS_H
#define YY_X_TS_H
#include "yy_p_type.h"
#include "yy_p_stdio.h"
#include "yy_f_alloc.h"
#include "yy_x_media.h"
#include "yy_f_file_obj.h"

/*
接口未固定化,请匆使用
*/
//读取指定内存的PCR,读取到第一个后返回.PCR已经格式为毫秒精度
extern yy_p_uint32 yy_x_ts_get_pcr_ms( const char * p, size_t len );
extern yy_p_uint32 yy_x_ts_get_r_pcr_ms( const char * p, size_t len );
extern yy_p_uint32 yy_x_ts_get_r_pcr_ms2( const char * p, yy_p_off_t file_pos, size_t len );

//读取指定内存块的PCR/MS,读取PCR_LEN个或是内存块到头为止,返回成功读取了的个数
extern size_t yy_x_ts_get_pcr_ms_n( const char * p, size_t len, yy_p_uint32 * pcr_ms, size_t pcr_len );
//读取指定内存块的PCR/MS,读取PCR_LEN个或是内存块到头为止,返回成功读取了的个数
extern size_t yy_x_ts_get_r_pcr_ms_n( const char * p, size_t len, yy_p_uint32 * pcr_ms, size_t pcr_len );


extern int yy_x_ts_is_h264_keyframe( const char * data, size_t len );
extern int yy_x_ts_parse_file_info( yy_p_handle_t fd, yy_x_file_info_t * xfi, yy_f_alloc_t * temp_alloc );

extern size_t yy_x_ts_find_h264_key_frame_in_buffer( const char * data, size_t len );
//2016/03/22 sk:查找psi的所在位置
extern size_t yy_x_ts_find_psi( const char * data, size_t len );

//从指定位置开始,查找一个H264的KEYFRAME
extern yy_p_off_t yy_x_ts_find_h264_key_frame_in_file( yy_p_handle_t fd, yy_p_off_t pos, yy_p_off_t dis, yy_f_alloc_t * temp_alloc );


extern yy_p_uint32 yy_x_ts_file_get_pcr_ms( yy_f_file_obj_t * f, yy_p_off_t file_pos, yy_p_off_t * time_pos, yy_f_alloc_t * temp_alloc );

/*
分析ts文件基本信息
*/
extern int yy_x_ts_file_parse_info( yy_f_file_obj_t * f, yy_x_file_info_t * xfi, yy_f_alloc_t * temp_alloc );

/*
以第一个数据包的时间为准,跳过的时间长度,单位为毫秒
*/
extern yy_p_off_t yy_x_ts_file_seek_by_time( yy_f_file_obj_t * f, yy_p_uint32 seek_ms, yy_f_alloc_t * temp_alloc );

/*
查找TS的关键帧,从pos->pos+dis的范围内
*/
extern yy_p_off_t yy_x_ts_file_find_h264_key_frame( yy_f_file_obj_t * f, yy_p_off_t pos, yy_p_off_t dis, yy_f_alloc_t * temp_alloc );

/*
删除ts无效数据包 yjj
*/	   
extern int yy_x_ts_delete_empty_packet(const void * data,const size_t len,  yy_p_uint8 * out_data, size_t *out_len);
#endif
