#ifndef YY_X_LIVE_SOURCE_H
#define YY_X_LIVE_SOURCE_H
#include "yy_p_type.h"
#include "yy_f_log.h"
#include "yy_f_alloc.h"
#include "yy_f_reactor.h"

#define YY_X_LIVE_SOURCE_E_UNKNOWN -1

#define YY_X_LIVE_SOURCE_S_NULL                 0
#define YY_X_LIVE_SOURCE_S_INITED               1
#define YY_X_LIVE_SOURCE_S_STARTED              2
#define YY_X_LIVE_SOURCE_S_RESOLVE_DNS          3
#define YY_X_LIVE_SOURCE_S_CONNECTING           4
#define YY_X_LIVE_SOURCE_S_CONNECTTED           5
#define YY_X_LIVE_SOURCE_S_PREPARING_META       6
#define YY_X_LIVE_SOURCE_S_META_READY           7
#define YY_X_LIVE_SOURCE_S_RECV_DATA            8
#define YY_X_LIVE_SOURCE_S_INTERRUPT            9
#define YY_X_LIVE_SOURCE_S_END                  10
#define YY_X_LIVE_SOURCE_S_ERROR                11

typedef enum yy_x_live_source_data_type_s
{
	yy_x_live_source_data_type_mp3=1,
	yy_x_live_source_data_type_aac,
	yy_x_live_source_data_type_h264,
}yy_x_live_source_data_type_t;

typedef struct yy_x_live_source_pack_data_s
{
	yy_x_live_source_data_type_t data_type;
	yy_p_uint64 decode_ms;
	yy_p_uint64 picture_ms;
	yy_p_uint8 *head_data;
	yy_p_uint32 head_data_len;
	yy_p_uint8 *data;//����
	yy_p_uint32 data_len;//���ݳ���
	int is_keyframe;//1:�ؼ�֡
}yy_x_live_source_pack_data_t;


//���ͬʱ֧��16����ַ
#define YY_X_LIVE_SOURCE_URLS_MAX 16

//����
#define YY_X_LIVE_SOURCE_DATA_TYPE_DATA					0
//���ļ�ͷ
#define YY_X_LIVE_SOURCE_DATA_TYPE_STREAM_HEADER		1
//�ֿ�����ͷ
#define YY_X_LIVE_SOURCE_DATA_TYPE_CHUNK_HEADER			2
//�������
#define YY_X_LIVE_SOURCE_DATA_TYPE_PACK_DATA			3 /*ֵΪyy_x_live_source_packdata_t�ṹ*/



//��Ƭ��Ӧ��M3U8�ļ�����
#define CHUNK_M3U8_DATA_LEN            (1024*2)       // ��Ƭ��Ӧ��M3U8���ݳ���
#define CHUNK_M3U8_HEADER_LEN          1024           // ��Ƭ��Ӧ��M3U8ͷ�ĳ��ȣ���һ��#EXTINF��ǩǰ�������
#define M3U8_KEY_LEN		           256            // M3U8��Կ��Ϣ���ȣ�#EXT-X-KEY��ǩð�ź��������
#define M3U8_PROGRAM_DATE_TIME_LEN     64             // #EXT-X-PROGRAM-DATE-TIME ��ǩ���ı�����

typedef struct yy_x_live_source_data_type_chunk_header_s
{
	time_t		t_chunk;	//�ֿ�Ŀ�ʼʱ��,���û�У���ֵΪ0
	size_t		s_chunk;	//�ֿ�����ݳ���
	yy_p_uint32 t_len;	//�ֿ��ʱ�䳤��
	yy_p_uint64	seq;		//�ֿ����к�
	
	//���²������ڼ��㴫���ӳ�
	time_t chunk_ts_recv_time_s;          //���Ľ��յ���Ƭ�Ŀ�ʼʱ��(��)
	yy_p_uint32 chunk_ts_recv_time_ms;    //�����γɷ�Ƭ��ʱ��(���벿��)

	//����Ϊ����DRM��������
	char chunk_m3u8_data[CHUNK_M3U8_DATA_LEN];     // ��Ƭ��Ӧ��m3u8�ļ�����
	
	char chunk_ts_filename[YY_P_MAX_PATH];	       // ts��Ƭ���ļ���
	char chunk_m3u8_key[M3U8_KEY_LEN];			   // ��Ƭ����Կ��Ϣ��#EXT-X-KEY��ǩð�ź�����ַ���

}yy_x_live_source_data_type_chunk_header_t;

/* ��ǰ״̬�ṹ�� */
typedef struct yy_x_live_source_state_s{
    int s;					/* ��ǰ��״̬�� */
	int ex_s;				/* ��һ��״̬�� */
}yy_x_live_source_state_t;

/* ����״̬�ṹ�� */
typedef struct yy_x_live_source_err_s{
    int e_code;				/* ��ǰ������ */
    int ex_e_code;			/* ��һ�������� */
}yy_x_live_source_err_t;

/*ͳ��״̬�ṹ��*/
typedef enum yy_x_enum_live_source_status_s
{
	yy_x_enum_live_source_ok = 0,               //��Դ����
	yy_x_enum_live_source_unknown_error,        //δ֪����
	yy_x_enum_live_source_connect_overtime,     //�������ӳ�ʱ
	yy_x_enum_live_source_recv_data_overtime,   //�������ݳ�ʱ
}yy_x_enum_live_source_status_t;

/*ͳ��״̬*/
typedef struct yy_x_live_source_stat_s{
	char url[1024];				//��ǰ����ʹ�õ�URL��ַ
	size_t url_index;           //��ǰURL������
    size_t flow_recv_kbps;      //��������
    size_t flow_recv_pps;       //ÿ����յİ�����(UDPЭ�����ʱ,�м�ֵ)
    time_t start_time;          //����ʼ���е�ʱ��
    size_t connect_times;       //���Ӽ���
	time_t last_connect_time;   //���һ�����ӵ�ʱ��
	size_t today_connect_times;	//�����Ѿ����ӵļ���
	size_t today_error_times;   //����������
	char reason[1024];          //����ԭ��

	yy_x_enum_live_source_status_t status_code;  //״̬��
    yy_x_live_source_state_t state;	/* ״̬�ṹ�� */
    yy_x_live_source_err_t err;		/* ����ṹ�� */
}yy_x_live_source_stat_t;

/* ���������ݳɹ��ص� */
typedef void (*yy_x_live_source_data_cb_t)( void * user_data, int type, const void * data, size_t len );

/* ��ʱ����ʱ�ص� */
typedef void (*yy_x_live_source_timer_cb_t)( void * user_data );

/* ״̬�ı�ص� */
typedef void (*yy_x_live_source_state_cb_t)( void * user_data, const yy_x_live_source_state_t * pre_state, const yy_x_live_source_state_t * state, yy_x_live_source_err_t * err );

/* ��ʼ��������Ƶ�ṹ��Ľṹ�� */
typedef struct yy_x_live_source_arg_s{
    yy_f_alloc_t * alloc;			/* �ڴ������ */
    const char * reactor_name;		/* ��Ӧ��ģʽ */
    size_t reactor_fd_size;		/* ��Ӧ���ܴ���ľ���� */
    void * user_data;				/* �û��Զ������� */
    yy_f_log_t * log;				/* ��־ */

    yy_x_live_source_data_cb_t f_data_cb;		/* ���ݻص����� */ 
    yy_x_live_source_state_cb_t f_state_cb;		/* ״̬�ص����� */
    yy_x_live_source_timer_cb_t f_timer_cb;		/* ��ʱ����ʱ�ص����� */

    size_t data_cb_size;		//���Բ��ָ�ʽ����,����TS,���ֵ������188����
    const char * url;			/* Ƶ����Դ��ַ������ж������;�ֿ� */
	
	const char * id;			/* ����id */
	const char * file_type;	/* �ļ����� */
	
	
	int is_save_to_file;		/* �Ƿ񱣴���ļ� */
	const char * data_path;	/* ����Ŀ¼ */
	yy_p_uint32 disk_time_delay;/* ֧�ֵ�ʱ�ӳ���,��,���̵���������� */
    yy_p_uint32 disk_file_time_len;	/* �ļ��ķ�Ƭ����,Ϊ�� */  
	
	int is_save_ts_url;       //�Ƿ񱣴�ԭʼ��Ƭ��ַ
	int is_create_hls_data_time_tag; //2015/12/30 sk:hlsֱ�����#EXT-X-PROGRAM-DATE-TIME������,�Ƿ���������
}yy_x_live_source_arg_t;


typedef yy_f_reactor_t* (*yy_x_live_source_get_reactor)(void * thiz );
typedef void (*yy_x_live_source_release_t)(void * thiz );
typedef int (*yy_x_live_source_begin_thread_t)(void * thiz );
typedef int (*yy_x_live_source_end_thread_t)(void * thiz );
typedef int (*yy_x_live_source_get_state_t)(void * thiz, yy_x_live_source_state_t * state, yy_x_live_source_state_t * pre_state, yy_x_live_source_err_t * err );
typedef int (*yy_x_live_source_get_meta_t)(void * thiz, int type, void * buf, size_t * inout_len );
typedef int (*yy_x_live_source_get_stat_t)(void * thiz, yy_x_live_source_stat_t * stat );
typedef int (*yy_x_live_source_modify_t)(void * thiz , yy_x_live_source_arg_t * arg );

typedef struct yy_x_live_source_op_s{
	char type[16];							/* live_source������ */
	yy_x_live_source_get_reactor f_get_reactor;	/* ��ȡ��Ӧ�� */
	yy_x_live_source_release_t f_release;		/* �ͷ�source�ṹ�� */
	yy_x_live_source_begin_thread_t f_begin_thread;/* �����߳� */
	yy_x_live_source_end_thread_t f_end_thread;	/* �����߳� */
	yy_x_live_source_get_state_t f_get_state;	/* ��ȡ��ǰ״̬����һ��״̬������״̬ */
	yy_x_live_source_get_meta_t f_get_meta;		/* ��ȡͷ�ļ���Ϣ���С */
	yy_x_live_source_get_stat_t f_get_stat;		/* ��ȡ���������е�״̬��������state */ 
	yy_x_live_source_modify_t f_modify;
}yy_x_live_source_op_t;
typedef struct yy_x_live_source_s{    
    void *thiz;					/* ָ������Ľṹ�� */
	yy_x_live_source_op_t * op;		/* ��λ�ڲ�ͬ�Ĳ��� */
}yy_x_live_source_t;

#define YY_X_LIVE_SOURCE_REACTOR( ls )        (ls)->op->f_get_reactor( (ls)->thiz )
#define YY_X_LIVE_SOURCE_RELEASE( ls )        (ls)->op->f_release( (ls)->thiz )
#define YY_X_LIVE_SOURCE_BEGIN_THREAD( ls )   (ls)->op->f_begin_thread( (ls)->thiz )
#define YY_X_LIVE_SOURCE_END_THREAD( ls )     (ls)->op->f_end_thread( (ls)->thiz )
#define YY_X_LIVE_SOURCE_GET_STATE( ls, state, pre_state, err )      (ls)->op->f_get_state( (ls)->thiz, state, pre_state, err )
#define YY_X_LIVE_SOURCE_GET_META( ls, type, buf, inout_len )        (ls)->op->f_get_meta( (ls)->thiz, type, buf, inout_len )
#define YY_X_LIVE_SOURCE_GET_STAT( ls, stat )        (ls)->op->f_get_stat( (ls)->thiz, stat )
#define YY_X_LIVE_SOURCE_MODIFY( ls, arg )        (ls)->op->f_modify( (ls)->thiz, arg )

/* ��ȡ��ǰ���ŵ�״̬ */
extern const char * yy_x_live_source_state_2_string( int s );
#endif
