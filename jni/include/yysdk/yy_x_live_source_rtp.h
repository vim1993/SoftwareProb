#ifndef YY_X_LIVE_SOURCE_TS_H
#define YY_X_LIVE_SOURCE_TS_H
#include "yy_x_live_source.h"
#include "yy_e_memcheck.h"
/* ͨ�����õ�SDP�ļ���������ݽ���. */

/* ����rtpֱ��Դ�ṹ�� */
extern yy_x_live_source_t * yy_x_live_source_rtp_create( const yy_x_live_source_arg_t * arg );

/* �������� */
extern int yy_x_live_source_rtp_validation_test( const char * url );
#endif
