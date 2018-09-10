#ifndef YY_X_TS_H
#define YY_X_TS_H
#include "yy_p_type.h"
#include "yy_p_stdio.h"
#include "yy_f_alloc.h"
#include "yy_x_media.h"
#include "yy_f_file_obj.h"

/*
�ӿ�δ�̶���,���ʹ��
*/
//��ȡָ���ڴ��PCR,��ȡ����һ���󷵻�.PCR�Ѿ���ʽΪ���뾫��
extern yy_p_uint32 yy_x_ts_get_pcr_ms( const char * p, size_t len );
extern yy_p_uint32 yy_x_ts_get_r_pcr_ms( const char * p, size_t len );
extern yy_p_uint32 yy_x_ts_get_r_pcr_ms2( const char * p, yy_p_off_t file_pos, size_t len );

//��ȡָ���ڴ���PCR/MS,��ȡPCR_LEN�������ڴ�鵽ͷΪֹ,���سɹ���ȡ�˵ĸ���
extern size_t yy_x_ts_get_pcr_ms_n( const char * p, size_t len, yy_p_uint32 * pcr_ms, size_t pcr_len );
//��ȡָ���ڴ���PCR/MS,��ȡPCR_LEN�������ڴ�鵽ͷΪֹ,���سɹ���ȡ�˵ĸ���
extern size_t yy_x_ts_get_r_pcr_ms_n( const char * p, size_t len, yy_p_uint32 * pcr_ms, size_t pcr_len );


extern int yy_x_ts_is_h264_keyframe( const char * data, size_t len );
extern int yy_x_ts_parse_file_info( yy_p_handle_t fd, yy_x_file_info_t * xfi, yy_f_alloc_t * temp_alloc );

extern size_t yy_x_ts_find_h264_key_frame_in_buffer( const char * data, size_t len );
//2016/03/22 sk:����psi������λ��
extern size_t yy_x_ts_find_psi( const char * data, size_t len );

//��ָ��λ�ÿ�ʼ,����һ��H264��KEYFRAME
extern yy_p_off_t yy_x_ts_find_h264_key_frame_in_file( yy_p_handle_t fd, yy_p_off_t pos, yy_p_off_t dis, yy_f_alloc_t * temp_alloc );


extern yy_p_uint32 yy_x_ts_file_get_pcr_ms( yy_f_file_obj_t * f, yy_p_off_t file_pos, yy_p_off_t * time_pos, yy_f_alloc_t * temp_alloc );

/*
����ts�ļ�������Ϣ
*/
extern int yy_x_ts_file_parse_info( yy_f_file_obj_t * f, yy_x_file_info_t * xfi, yy_f_alloc_t * temp_alloc );

/*
�Ե�һ�����ݰ���ʱ��Ϊ׼,������ʱ�䳤��,��λΪ����
*/
extern yy_p_off_t yy_x_ts_file_seek_by_time( yy_f_file_obj_t * f, yy_p_uint32 seek_ms, yy_f_alloc_t * temp_alloc );

/*
����TS�Ĺؼ�֡,��pos->pos+dis�ķ�Χ��
*/
extern yy_p_off_t yy_x_ts_file_find_h264_key_frame( yy_f_file_obj_t * f, yy_p_off_t pos, yy_p_off_t dis, yy_f_alloc_t * temp_alloc );

/*
ɾ��ts��Ч���ݰ� yjj
*/	   
extern int yy_x_ts_delete_empty_packet(const void * data,const size_t len,  yy_p_uint8 * out_data, size_t *out_len);
#endif
