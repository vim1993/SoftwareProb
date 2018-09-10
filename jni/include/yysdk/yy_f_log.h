/*
LOG ϵͳ
1.�ض���,ʵ���ʺ��Լ���ʽ��
2.�ʺ� Ƕ��ʽ ������ ���ַ����Ӧ��
3.�������
*/

#ifndef YY_F_LOG_H
#define YY_F_LOG_H
#include "yy_p_config.h"
#include "yy_p_type.h"
#include "yy_p_time.h"
#include "yy_p_thread.h"
#include "yy_p_stdio.h"
#include "yy_p_test.h"

#include "yy_e_memcheck.h"

/* ÿ����־��ͷ�ĸ�ʽ */
#define YY_FLF_TIME_PREFIX			0x00000001		/* ʱ��ǰ׺ */
#define YY_FLF_DATETIME_PREFIX		0x00000002		/* ����ʱ��ǰ׺ */
#define YY_FLF_MOD_NAME				0x00000004	/* ģ���� */
#define YY_FLF_LEVEL_NAME			0x00000008		/* ��־���������磺DEBUG, INFO */


#define YY_FLF_DATE_FILE_NAME		0x00000010		//��־ʹ��������Ϊ�ļ���(�ʺ���ÿ��һ����־��ģʽ)



//ָ���˴�����ʱ,����ʹ��prefix�е��ַ�����ΪLOG�ļ���
//����Ѿ��������ļ�������ģʽ,��ģʽΪ׼

#define YY_FLF_TIME_SWITCH       0x00000100		/* ��ʱ���л���־�ļ�����1Сʱ��1��һ���ļ� */
#define YY_FLF_SIZE_SWITCH       0x00000200		/* ���ļ���С�л���־�ļ� */

//�������
#define YY_FLF_OUT_CONSOLE       0x00010000		/* �����־�������ն� */
#define YY_FLF_OUT_WINDBG        0x00020000		/* windows�����������̫��⣿���� */
#define YY_FLF_OUT_FILE          0x00040000		/* ��־д���ļ� */
#define YY_FLF_OUT_CB            0x00080000		/* ������ */
#define YY_FLF_OUT_MASK			 0x00ff0000	/* ��־�����ʽ���� */


//��ʱ������Կ���
#define YY_FLL_NO_PREFIX			0x00000001	/* ��־��Ϣ��ǰ׺ */




//����ȼ�����
#define YY_FLL_TRACE                0x00000100      //�������ø�����Ϣ
#define YY_FLL_DEBUG                0x00000200      //������Ϣ,�ǳ�ȫ
#define YY_FLL_INFO                 0x00000400      //
#define YY_FLL_WARNNING             0x00000800      //����,�п��ܻ��ָܻ�
#define YY_FLL_ERROR                0x00001000      //����,����������
#define YY_FLL_IMPORTANT            0x00002000      //��Ҫ��Ϣ,һ����ӡ

#define YY_FLL_OUT_LEVEL_ALL        0x0000FF00		//����ȼ�����

#define YY_FLL_ALL                  0xFFFFFF00		//���8λ����������


//�¾ɼ���
#define YY_FLL_APP1                 YY_FLL_INFO      //
#define YY_FLL_APP2                 YY_FLL_INFO      //
#define YY_FLL_APP3                 YY_FLL_INFO      //
#define YY_FLL_APP4                 YY_FLL_INFO      //
#define YY_FLL_NOTICE               YY_FLL_INFO      //
#define YY_FLL_EMERGENCY            YY_FLL_ERROR      //���ش���,�һ���������쳣,�������쳣

/* ��־����ṹ */
typedef struct yy_f_log_s{
    YY_E_MEM_MAGIC_PREFIX_DEFINE;		/* �ڴ�Խ������ */
    //
    yy_p_thr_mutex_t lock;				/* �� */
    yy_p_uint32 flag;					/* ��־�����ʽ����������ļ��� */
    yy_p_uint32 level;					/* ��־������;YY_FLL_INFO */

    //int file_mode;
    size_t file_max_num;				/* ��־Ŀ¼����ౣ������־�ļ����� */
    size_t file_max_size;				/* һ����־�ļ�������С���������л� */
    time_t file_max_time;				/* һ����־�ļ������ʱ�䣬�������л� */
    yy_p_handle_t file_fd;				/* ��־�ļ������� */
    int is_first_create_file;			/* �Ƿ��һ�δ�����־�ļ� */
    time_t file_try_create_time;		/* ��־�ٴ�д��ʱ�� */
    size_t file_cur_pos;				/* ��־�ļ���ǰдָ��λ�� */
    time_t file_begin_time;			//�ļ���һ��д��ʱ��,�ع�ʱ,ָ�ع���ĵ�һ��д��ʱ��
	int file_create_day;				//�ļ���������,�Ա���ʱ��Ϊ׼

    char file_log_path[YY_P_MAX_PATH];	/* ��־�ļ������·�� */
    char file_prefix[YY_P_MAX_PATH];	/* ��־�ļ�ǰ׺����Ҫ�����ԣ� */
    int is_path_file_ok;				/* �Ƿ���������־����ļ���0-δ���ã���0-������ */
    
    char file_name[YY_P_MAX_PATH];		/* ��־�ļ���������� */
    
    char file_name_temp1[YY_P_MAX_PATH];/* ��־�ļ������ʱ������1 */
    char file_name_temp2[YY_P_MAX_PATH];/* ��־�ļ������ʱ������2 */
    
    char log_buf[16*1024];				/* ��־�ļ�������� */
    YY_E_MEM_MAGIC_SUFFIX_DEFINE;
}yy_f_log_t;

#define YY_F_LOG_AGENT_OUT_MAX 4		/* һ����־����������max���豸�����ļ����ն˵� */

/* ��־��������ṹ�� */
typedef struct yy_f_log_agent_out_s{
	yy_p_uint32 level;			/* ��־����ȼ� */
	yy_f_log_t * log;			/* ��־�ļ��ṹ */
}yy_f_log_agent_out_t;

/* ��־����ṹ�壬��ͬ����ģ���ͨ���˴���д��־��ʾ���� */
typedef struct yy_f_log_agent_s{
    YY_E_MEM_MAGIC_PREFIX_DEFINE;
    YY_E_OBJ_MAGIC_DEFINE;


    int is_log_agent_disabled;

	yy_f_log_agent_out_t out[YY_F_LOG_AGENT_OUT_MAX];

	//ģ�����������ϲ�Ӧ̫����ռ��̫���ڴ�ռ�
	//czy 2013/5/27 ��1024->512
#if YY_P_IS_BUS_WIDTH_64
    char mod_name[1024-4*8-YY_F_LOG_AGENT_OUT_MAX*16];
#else
    char mod_name[1024-4*4-YY_F_LOG_AGENT_OUT_MAX*8];
#endif  
    YY_E_MEM_MAGIC_SUFFIX_DEFINE;
}yy_f_log_agent_t;

/* ������־�ṹ */
extern yy_f_log_t * yy_f_log_create( yy_p_uint32 flag, int use_lock );

/* �ݻ���־�ṹ */
extern int yy_f_log_destroy( yy_f_log_t * log );

/* ������־������� */
extern int yy_f_log_set_flag( yy_f_log_t * log, yy_p_uint32 new_flag );

/* ������־���� */
extern void yy_f_log_set_level( yy_f_log_t * log, yy_p_uint32 level );

/* �޸���־������ԣ����Ƴ������ԣ����������� */
extern int yy_f_log_modify_flag(yy_f_log_t * log, yy_p_uint32 remove_flag, yy_p_uint32 add_flag );

/* ��ȡ��ǰ��־����ļ���	*/
extern const char * yy_f_log_get_file_name( yy_f_log_t * log );

/*
����:�ⲿ��ʱ������,���Ϊ1-60�뼴��,��Ҫ����Ϊ��ֹĳ��д��LOGʱ�����л��ļ�,����LOG���ܵ���
����һ����û��LOGд��ʱ,����ĳʽҲ�������л��ļ�.
���ֻ��һ��LOG�ļ���,������Ҫ��������ӿ�,��û�м�ֵ.
*/
extern void yy_f_log_timer( yy_f_log_t * log );

/*
����:��Ҫ�ļ����,�����ô���,һ��Ӧ��LOG create,set_flag֮��,������,�����ܲ�Ҫ�ں����޸�
����:
	max_time:0��������ʱ������
	max_num:YY_P_SIZE_T_MAX���������ļ�����,��������ɾ��, 0,1��������һ��
	log_path:����Ϊ����Ŀ¼,��������������ݹ���
	file_name:ָ��LOG���ļ���,���Ϊ�Զ�ģʽ,���ֵ������Ϊǰ׺,��ʹ����YY_FLF_DATE_FILE_NAME���ʱ,�������Ϊ�ļ�����ǰ׺
*/
extern int yy_f_log_set_file( yy_f_log_t * log, const char * log_path, const char * file_name, size_t max_size, time_t max_time, size_t max_num  );

/* ����:д��־��ʹ�ñ���ַ��� */
extern int yy_f_log_log_x( yy_f_log_t * log, yy_p_uint32 level , const char * mod_name, const char * format, ... );

/* ����:д��־��ʹ�ñ���б� */
extern int yy_f_log_log_v( yy_f_log_t * log, yy_p_uint32 level ,const char * mod_name, const char * format, va_list arg_list );

/* ����:���������ݰ�16�������,δʵ�� */
extern int yy_f_log_log_binhex( yy_f_log_t * log, yy_p_uint32 level ,const char * mod_name, const char * bin, size_t len );

/* ����:���������ݰ��ַ������ */
extern int yy_f_log_log_binstr( yy_f_log_t * log, yy_p_uint32 level ,const char * mod_name, const char * bin, size_t len );

/* �ⲿģ����ô˺���attach��һ��־�����Բ�ͬ��mode_name������־��� */
extern int yy_f_log_agent_attach( yy_f_log_agent_t * agent, yy_f_log_t * log, const char * mod_name );

/* �ⲿģ�鲻��д��־ʱ�����ô˺����������־����Ĺ��� */
extern int yy_f_log_agent_detach( yy_f_log_agent_t * agent );

/* ������־���ʱ��ģ���� */
extern int yy_f_log_agent_set_mod_name( yy_f_log_agent_t * agent, const char * mod_name );

/* ������־���ʱ��ģ�����ַ��� */
extern int yy_f_log_agent_mod_name_add( yy_f_log_agent_t * agent, const char * mod_ex );

/* ������־���ʱ��ģ�����ַ�����ʹ�ñ�Σ� */
extern int yy_f_log_agent_mod_name_addv( yy_f_log_agent_t * agent, const char * format, ... );

extern void yy_f_log_agent_disable( yy_f_log_agent_t * agent );
extern void yy_f_log_agent_enable( yy_f_log_agent_t * agent );

/* ������־����ṹ�е���־�ȼ�����־�ṹ */
extern int yy_f_log_agent_set_out( yy_f_log_agent_t * agent, size_t index, yy_p_uint32 level, yy_f_log_t * log );

/* ͨ����־�����׼�����LOG */
extern int yy_f_log_agent_log_x( yy_f_log_agent_t * agent, yy_p_uint32 level, const char * format, ... );

/* ͨ����־�����׼�����LOG */
extern int yy_f_log_agent_log_v( yy_f_log_agent_t * agent, yy_p_uint32 level, const char * format, va_list arg_list );

/* ͨ����־��������������16�����������δʵ�֣� */
extern int yy_f_log_agent_log_binhex( yy_f_log_agent_t * agent, yy_p_uint32 level, const char * bin, size_t len );

/* ͨ����־���������������ַ������ */
extern int yy_f_log_agent_log_binstr( yy_f_log_agent_t * agent, yy_p_uint32 level, const char * bin, size_t len );

//��Ϊ�����ƶ�һ��ʹ��
#define yy_flal_x yy_f_log_agent_log_x
#define yy_flal_v yy_f_log_agent_log_v
#define yy_flal_binhex yy_f_log_agent_log_binhex
#define yy_flal_binstr yy_f_log_agent_log_binstr

//������ͬ����д�����ڴ���ʶ��
#define YY_F_LOG_X yy_f_log_agent_log_x
#define YY_F_LOG_V yy_f_log_agent_log_v
#define YY_F_LOG_BH yy_f_log_agent_log_binhex
#define YY_F_LOG_BS yy_f_log_agent_log_binstr

//#define YY_F_

/* ȫ��Ĭ�ϵ�LOGϵͳ,��Ҫ�ⲿ��ʾ�����ƣ����򲢲����� */

/* �õ���־����ȫ�ֱ��� */
extern yy_f_log_agent_t * yy_f_log_agent_get_global();

/* ����ȫ����־���� */
extern void yy_f_log_agent_set_global( yy_f_log_agent_t * la );

/* ͨ����־����ȫ�ֱ�����׼�������־ */
extern int yyi_f_log_agent_log_x_global( yy_f_log_agent_t * agent, yy_p_uint32 level, const char * format, ... );

//��һ�������̶�ΪNULL,Ϊ���ֲ���һ���ԣ����������agent�Ŀղ���
#define YY_F_LOG_GX yyi_f_log_agent_log_x_global
//#define YY_F_LOG_GV( agent, level, format, arg_list ) yy_f_log_agent_log_v( yy_f_log_agent_get_global(), level, , format, arg_list );
#define YY_F_LOG_GBS( agent, level, bin, len ) yy_f_log_agent_log_binstr( yy_f_log_agent_get_global(), level, bin, len )
#define YY_F_LOG_GBH( agent, level, bin, len ) yy_f_log_agent_log_binhex( yy_f_log_agent_get_global(), level, bin, len )

/* �������� */
extern int yy_f_log_validation_test(const char * log_path);

#endif
