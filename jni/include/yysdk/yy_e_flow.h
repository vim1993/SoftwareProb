#ifndef YY_E_FLOW_H
#define YY_E_FLOW_H
#include "yy_p_type.h"
#include "yy_p_thread.h"
#include "yy_e_time.h"
#include "yy_e_memcheck.h"

#define YY_E_FLOW_NODE_INDEX_MASK    0x3F		/* ���ö�Ӧ 0~63��node����Ӧ�����MAX_NUM */
#define YY_E_FLOW_NODE_MAX_NUM		 64			//����С��ͳ�����ڵı�������


#if defined( YY_E_FLOW_USE_64BIT )
	typedef yy_p_uint64 yy_e_flow_size_t;
	#define YY_E_PRI_FLOW_SIZE_T "%llu"
#else
	typedef yy_p_uint32 yy_e_flow_size_t;
	#define YY_E_PRI_FLOW_SIZE_T "%u"
#endif

/* ͳ�������ӽڵ�ṹ�� */
typedef struct yy_e_flow_node_s{
	yy_e_flow_size_t bytes;         /* ��ǰ��Ƭ���ֽ��� */
	yy_e_flow_size_t packs;         /* ��ǰ��Ƭ�İ��� */
	yy_e_flow_size_t max_packet_size;   /* �������ֽ��� */
	yy_e_flow_size_t min_packet_size;   /* ��С�����ֽ��� */
	yy_p_uint32 splice_index;       /* ��ǰ��Ƭ������ */
}yy_e_flow_node_t;

/* ����ͳ�ƽṹ�� */
typedef struct yy_e_flow_s{
    YY_E_OBJ_MAGIC_DEFINE;
    yy_p_thr_mutex_t lock;			/* ������ */
    time_t start_time;				/* ��ʼʱ�� */
    //��ʱ����
    yy_p_uint32 cycle_ms;			/* ��ʱ���� */
    yy_p_uint32 cycle_fixed_ms;		/* ͨ��cycle_ms�������splice_count���������� */
    yy_p_uint32 splice_ms;			/* ÿ��splice������ */
    yy_p_uint32 splice_count;		/* splice�ĸ��� */

	//��ǰ�ķ�Ƭ����ֵ��ʱ��
    yy_p_uint32 current_splice_index;/* ��ǰ��Ƭ����ֵ */
	yy_p_uint32 current_splice_ms;	/* ��ǰ��Ƭʱ�� */

    yy_e_flow_node_t nodes[YY_E_FLOW_NODE_MAX_NUM];
    //

    yy_e_flow_size_t total_bytes;	/* �ܵ�����(��λ:�ֽ�) */
    yy_e_flow_size_t total_packs;	/* �ܵİ��ĸ��� */
    
}yy_e_flow_t;

/*
cycle_ms:��ʱ����,�Ժ���Ϊ��λ
use_lock:�ǲ���ʹ��������
*/
/* ��ʼ������ͳ�ƽṹ�� */
extern void yy_e_flow_init( yy_e_flow_t * stat, yy_p_uint32 cycle_ms, int use_lock );

/* ����ʼ��ͳ�����ṹ�� */
extern void yy_e_flow_uninit( yy_e_flow_t * stat ); 

/*
bytes:������
packs:����
now_ms:��ǰʱ��(����),ʹ��0�������ڲ�����
*/
/* ͳ�ƴ����bytes��packs����������ֵ��ӵ�����ͳ�ƽṹ���� */
extern void yy_e_flow_log(  yy_e_flow_t * stat, size_t bytes, size_t packs, yy_p_uint32 now_ms );

/* ��ȡ�ֽ����ʣ�����Ϊ��λ */
extern yy_e_flow_size_t yy_e_flow_bps(const  yy_e_flow_t * stat, yy_p_uint32 now_ms );

/* ��ȡ���ʣ�����Ϊ��λ */
extern yy_e_flow_size_t yy_e_flow_pps( const yy_e_flow_t * stat, yy_p_uint32 now_ms );

/* ��ȡ�ֽ�����,�ӿ�ʼ�����ֵ�ǰ */
extern yy_e_flow_size_t yy_e_flow_total_bps(const  yy_e_flow_t * stat );

/* ��ȡ�ֽ����ʣ��Լ�ʱ���� */
extern yy_e_flow_size_t yy_e_flow_bpc(const  yy_e_flow_t * stat, yy_p_uint32 now_ms );

/* ��ȡ����,�Լ�ʱ���� */
extern yy_e_flow_size_t yy_e_flow_ppc( const yy_e_flow_t * stat, yy_p_uint32 now_ms );

/* �����ʱ�����ڣ�����ƽ����С */
extern yy_e_flow_size_t yy_e_flow_avg_packet_size_pc( const yy_e_flow_t * stat, yy_p_uint32 now_ms );

/* �����ʱ�����ڣ������Ĵ�С */
extern yy_e_flow_size_t yy_e_flow_max_packet_size_pc( const yy_e_flow_t * stat, yy_p_uint32 now_ms );

/* �ۼ��ֽ��� */
extern yy_e_flow_size_t yy_e_flow_total_bytes( const yy_e_flow_t * stat );

/* �ۼư����� */
extern yy_e_flow_size_t yy_e_flow_total_packs( const yy_e_flow_t * stat );

/* ������������ */
extern void yy_e_flow_reset( yy_e_flow_t * stat, yy_e_flow_size_t bps, yy_e_flow_size_t pps);

/* ��ʼʱ�� */
extern time_t yy_e_flow_start_time( const yy_e_flow_t * stat );

/* �������� */
extern int yy_e_flow_validation_test( );
#endif
