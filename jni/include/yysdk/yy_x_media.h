#ifndef YY_X_MEDIA_H
#define YY_X_MEDIA_H
#include "yy_p_type.h"
#include "yy_p_stdio.h"
typedef struct yy_x_file_info_s{
    yy_p_uint32 time_begin; //�ļ����ݵĵ�һ�����ݰ�ʱ��,MS
    yy_p_uint32 time_end;   //�ļ����ݵ����һ�����ݰ�ʱ��,MS
    yy_p_uint32 time_len;   //�ļ���ʱ��,MS
    yy_p_off_t file_len;    //�ļ��ܳ�
	yy_p_uint32 byte_rate;	//����
	time_t clock_time_begin;	//�ļ������ʵʱ��Ŀ�ʼʱ�䣨��һЩ¼�Ƹ�ʽ�ļ�����),��
}yy_x_file_info_t;
#endif
