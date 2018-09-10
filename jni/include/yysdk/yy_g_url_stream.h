/* ���ļ�ʵ�ִ���򵥵�http�������� */
#ifndef YY_G_URL_STREAM_H
#define YY_G_URL_STREAM_H
#include "yy_p_type.h"
#include "yy_p_socket.h"
#include "yy_p_stdio.h"
#include "yy_p_inet_addr.h"
#include "yy_f_alloc.h"
#include "yy_f_reactor.h"
#include "yy_f_message_block.h"
#include "yy_e_memcheck.h"
#include "yy_e_http_parser.h"
#include "yy_e_uri_parser.h"

/* http�������״̬�궨�� */
#define YY_GUS_E_UNKNOWN -1							/* ���� */

#define YY_GUS_S_CREATED            1				/* �����Ѵ��� */
#define YY_GUS_S_INITED             2				/* �����ѳ�ʼ�� */
#define YY_GUS_S_PREPARED           3				/* ������׼���� */
#define YY_GUS_S_START              4				/* �����ѿ�ʼ */
#define YY_GUS_S_CONNECTING         5				/* ������ */
#define YY_GUS_S_CONNECTED          6				/* ������ */
#define YY_GUS_S_SEND_HEAD          7				/* ����http����ͷ�� */
#define YY_GUS_S_SEND_CONTENT       8				/* ����http����body */
#define YY_GUS_S_RECV_HEAD          9				/* ����http��Ӧͷ�� */
#define YY_GUS_S_RECV_CONTENT       10				/* ����http��Ӧbody */
#define YY_GUS_S_STOP               11				/* ������ֹͣ */
#define YY_GUS_S_COMPLETE           12				/* ��������� */
#define YY_GUS_S_ERROR              13				/* ���������� */

/* ����״̬�ṹ�� */
typedef struct yy_g_url_stream_state_s{
    int s;											/* ��ǰ״̬ */
    int ex_s;										/* ǰһ״̬ */
}yy_g_url_stream_state_t;

/* ��������� */
typedef struct yy_g_url_stream_err_s{
    int err;										/* ��ǰ������ */
    int ex_err;										/* ǰһ������ */
}yy_g_url_stream_err_t;
struct yy_g_url_stream_s;

/* ����״̬�л��ص����� */
typedef void (*yy_g_url_stream_state_cb_t)( void * user_data, struct yy_g_url_stream_s *us, const yy_g_url_stream_state_t * state, const yy_g_url_stream_err_t * err, const yy_g_url_stream_state_t * pre_state );

/* http������ṹ�� */
typedef struct yy_g_url_stream_s{
    YY_E_MEM_MAGIC_PREFIX_DEFINE;
    yy_f_alloc_t * alloc;							/* �ڴ������ */

    yy_g_url_stream_state_t pre_state;				/* ǰһ״̬ */
    yy_g_url_stream_state_t state;					/* ��ǰ״̬ */
    yy_g_url_stream_err_t err;						/* ������ */
    void * user_data;								/* �������Ϊ�û����� */
    yy_g_url_stream_state_cb_t f_state_cb;			/* ����״̬�л�ʱ�Ļص����� */

	yy_p_uint32 start_ms;							/* ��������ʱ�� */
	yy_p_uint32 connectted_ms;						/* ����ʱ�� */
	yy_p_uint32 last_active_ms;						/* ��һ�λ�Ծʱ�� */

	yy_p_uint32 connectting_timeout_ms;				/* ���ӳ�ʱʱ�� */
	yy_p_uint32 recv_head_timeout_ms;				/* ����http��Ӧͷ����ʱʱ�� */
	yy_p_uint32 active_timeout_ms;					/* ��Ծ��ʱʱ�� */

    //�������
    yy_e_http_parser_t * req;						/* http��������ṹ�� */
    yy_e_uri_parser_t * req_uri;					/* url�����ṹ�� */
    yy_p_inet_addr_t host_addr;						/* Ҫ���ӵ�������ַ */

	//��Ӧ���
    yy_e_http_parser_t * rep;						/* http��Ӧ�����ṹ�� */
    int is_rep_chunked;								/* ��Ӧ�Ƿ�ֿ� ??? */
    int chunked_parse_state;            
    yy_e_http_content_t chunk_size;
    yy_e_http_content_t chunk_readed_size;

    size_t recved_content_len;						/* �ѽ��յ�http body���� */
    yy_f_message_block_t * recv_content;			/* http��Ӧbody���ݽ��ջ��� */

    yy_f_reactor_t * r;								/* ��Ӧ�� */
    yy_f_event_handler_t * ev_timer;				/* ��ʱ�������� */
    yy_f_event_handler_t * ev_read;					/* �ɶ��¼������� */
    yy_f_event_handler_t * ev_write;				/* ��д�¼������� */
    yy_p_socket_t s;								/* �׽ӿ� */
    yy_f_message_block_t * snd_buf;					/* ���ͻ��� */
    yy_f_message_block_t * rcv_buf;					/* ���ջ��� */
    int last_sock_err;								/* �׽ӿڴ����� */
    YY_E_MEM_MAGIC_SUFFIX_DEFINE;
}yy_g_url_stream_t;

/* ����http���������� */
extern yy_g_url_stream_t * yy_g_url_stream_create( yy_f_alloc_t * alloc, yy_f_reactor_t * r, yy_g_url_stream_state_cb_t f_state_cb, void * user_data );
/* �������� */
extern int yy_g_url_stream_start( yy_g_url_stream_t * us );
/* ֹͣ���� */
extern int yy_g_url_stream_stop( yy_g_url_stream_t * us );
/* �ͷ���Դ */
extern void yy_g_url_stream_release( yy_g_url_stream_t * us );

/*
���ܣ����ӳ�ʱ����

*/
extern int yy_g_url_stream_set_connectting_timeout( yy_g_url_stream_t * us, yy_p_uint32 ms );

/*
���ܣ�����ͷ���ճ�ʱ
*/
extern int yy_g_url_stream_set_recv_head_timeout( yy_g_url_stream_t * us, yy_p_uint32 ms );
/* �����ʼ�� */
extern int yy_g_url_stream_init( yy_g_url_stream_t * us, const char * url );
/* ��ȡhttp��������ṹ�� */
extern yy_e_http_parser_t * yy_g_url_stream_req( yy_g_url_stream_t * us );
/* ׼����ʼ */
extern int yy_g_url_stream_prepare_start( yy_g_url_stream_t * us, const char * content_data, size_t content_len );
/* ��ȡ����״̬ */
extern int yy_g_url_stream_get_state( yy_g_url_stream_t * us, yy_g_url_stream_state_t * state, yy_g_url_stream_err_t *err );
/* ��ȡhttp��Ӧ�����ṹ�� */
extern yy_e_http_parser_t * yy_g_url_stream_rep( yy_g_url_stream_t * us );
/* ��ȡhttp��Ӧbody */
extern int yy_g_url_stream_get_rep_content( yy_g_url_stream_t * us, char ** content_data, size_t * content_len );

/* ʹ��������ʽ����http���� */
extern int yy_g_url_stream_block_handle( yy_f_alloc_t * alloc, const char *host, const char *req, const size_t req_len, yy_e_http_parser_t ** rep, yy_f_message_block_t ** recv_content, const yy_p_uint32 time_out_ms);

extern int yy_g_url_stream_validation_test( const char * url );

#endif
