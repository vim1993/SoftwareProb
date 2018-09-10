/*
LOG 系统
1.特定化,实现适合自己格式的
2.适合 嵌入式 服务器 二种方向的应用
3.方便调试
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

/* 每行日志开头的格式 */
#define YY_FLF_TIME_PREFIX			0x00000001		/* 时间前缀 */
#define YY_FLF_DATETIME_PREFIX		0x00000002		/* 日期时间前缀 */
#define YY_FLF_MOD_NAME				0x00000004	/* 模块名 */
#define YY_FLF_LEVEL_NAME			0x00000008		/* 日志级别名，如：DEBUG, INFO */


#define YY_FLF_DATE_FILE_NAME		0x00000010		//日志使用日期作为文件名(适合于每天一个日志的模式)



//指定了此特性时,总是使用prefix中的字符串作为LOG文件名
//如果已经定义了文件名命名模式,以模式为准

#define YY_FLF_TIME_SWITCH       0x00000100		/* 按时间切换日志文件，如1小时或1天一个文件 */
#define YY_FLF_SIZE_SWITCH       0x00000200		/* 按文件大小切换日志文件 */

//输出特性
#define YY_FLF_OUT_CONSOLE       0x00010000		/* 输出日志到控制终端 */
#define YY_FLF_OUT_WINDBG        0x00020000		/* windows调试输出，不太理解？？？ */
#define YY_FLF_OUT_FILE          0x00040000		/* 日志写入文件 */
#define YY_FLF_OUT_CB            0x00080000		/* ？？？ */
#define YY_FLF_OUT_MASK			 0x00ff0000	/* 日志输出方式掩码 */


//临时输出特性控制
#define YY_FLL_NO_PREFIX			0x00000001	/* 日志信息无前缀 */




//输出等级设置
#define YY_FLL_TRACE                0x00000100      //函数调用跟踪信息
#define YY_FLL_DEBUG                0x00000200      //跟踪信息,非常全
#define YY_FLL_INFO                 0x00000400      //
#define YY_FLL_WARNNING             0x00000800      //警报,有可能还能恢复
#define YY_FLL_ERROR                0x00001000      //错误,但还能运行
#define YY_FLL_IMPORTANT            0x00002000      //重要信息,一定打印

#define YY_FLL_OUT_LEVEL_ALL        0x0000FF00		//输出等级分类

#define YY_FLL_ALL                  0xFFFFFF00		//最低8位保留给特性


//新旧兼容
#define YY_FLL_APP1                 YY_FLL_INFO      //
#define YY_FLL_APP2                 YY_FLL_INFO      //
#define YY_FLL_APP3                 YY_FLL_INFO      //
#define YY_FLL_APP4                 YY_FLL_INFO      //
#define YY_FLL_NOTICE               YY_FLL_INFO      //
#define YY_FLL_EMERGENCY            YY_FLL_ERROR      //严重错误,且会引起程序异常,或整体异常

/* 日志主体结构 */
typedef struct yy_f_log_s{
    YY_E_MEM_MAGIC_PREFIX_DEFINE;		/* 内存越界检查标记 */
    //
    yy_p_thr_mutex_t lock;				/* 锁 */
    yy_p_uint32 flag;					/* 日志输出方式，如输出到文件等 */
    yy_p_uint32 level;					/* 日志级别，如;YY_FLL_INFO */

    //int file_mode;
    size_t file_max_num;				/* 日志目录中最多保留的日志文件个数 */
    size_t file_max_size;				/* 一个日志文件的最大大小，超过则切换 */
    time_t file_max_time;				/* 一个日志文件的最大时间，超过则切换 */
    yy_p_handle_t file_fd;				/* 日志文件描述符 */
    int is_first_create_file;			/* 是否第一次创建日志文件 */
    time_t file_try_create_time;		/* 日志再次写入时间 */
    size_t file_cur_pos;				/* 日志文件当前写指针位置 */
    time_t file_begin_time;			//文件第一行写入时间,回滚时,指回滚后的第一行写入时间
	int file_create_day;				//文件创建日期,以本地时间为准

    char file_log_path[YY_P_MAX_PATH];	/* 日志文件输出的路径 */
    char file_prefix[YY_P_MAX_PATH];	/* 日志文件前缀（主要是特性） */
    int is_path_file_ok;				/* 是否设置了日志输出文件，0-未设置，非0-已设置 */
    
    char file_name[YY_P_MAX_PATH];		/* 日志文件输出的名字 */
    
    char file_name_temp1[YY_P_MAX_PATH];/* 日志文件输出临时的名字1 */
    char file_name_temp2[YY_P_MAX_PATH];/* 日志文件输出临时的名字2 */
    
    char log_buf[16*1024];				/* 日志文件输出缓存 */
    YY_E_MEM_MAGIC_SUFFIX_DEFINE;
}yy_f_log_t;

#define YY_F_LOG_AGENT_OUT_MAX 4		/* 一条日志最多能输出到max个设备，如文件、终端等 */

/* 日志代理输出结构体 */
typedef struct yy_f_log_agent_out_s{
	yy_p_uint32 level;			/* 日志输出等级 */
	yy_f_log_t * log;			/* 日志文件结构 */
}yy_f_log_agent_out_t;

/* 日志代理结构体，不同代码模块可通过此代理写日志以示区分 */
typedef struct yy_f_log_agent_s{
    YY_E_MEM_MAGIC_PREFIX_DEFINE;
    YY_E_OBJ_MAGIC_DEFINE;


    int is_log_agent_disabled;

	yy_f_log_agent_out_t out[YY_F_LOG_AGENT_OUT_MAX];

	//模块命，理论上不应太长，占用太多内存空间
	//czy 2013/5/27 从1024->512
#if YY_P_IS_BUS_WIDTH_64
    char mod_name[1024-4*8-YY_F_LOG_AGENT_OUT_MAX*16];
#else
    char mod_name[1024-4*4-YY_F_LOG_AGENT_OUT_MAX*8];
#endif  
    YY_E_MEM_MAGIC_SUFFIX_DEFINE;
}yy_f_log_agent_t;

/* 创建日志结构 */
extern yy_f_log_t * yy_f_log_create( yy_p_uint32 flag, int use_lock );

/* 摧毁日志结构 */
extern int yy_f_log_destroy( yy_f_log_t * log );

/* 设置日志输出特性 */
extern int yy_f_log_set_flag( yy_f_log_t * log, yy_p_uint32 new_flag );

/* 设置日志级别 */
extern void yy_f_log_set_level( yy_f_log_t * log, yy_p_uint32 level );

/* 修改日志输出特性，可移除旧特性，增加新特性 */
extern int yy_f_log_modify_flag(yy_f_log_t * log, yy_p_uint32 remove_flag, yy_p_uint32 add_flag );

/* 获取当前日志输出文件名	*/
extern const char * yy_f_log_get_file_name( yy_f_log_t * log );

/*
功能:外部定时器调用,间隔为1-60秒即可,主要作用为防止某次写入LOG时正好切换文件,导致LOG性能低下
另外一个是没有LOG写入时,这种某式也能正常切换文件.
针对只有一个LOG文件的,并不需要调用这个接口,并没有价值.
*/
extern void yy_f_log_timer( yy_f_log_t * log );

/*
功能:需要文件输出,请配置此项,一般应在LOG create,set_flag之后,就配置,尽可能不要在后期修改
参数:
	max_time:0代表不进行时间限制
	max_num:YY_P_SIZE_T_MAX代表不限制文件个数,并不进行删除, 0,1代表限制一个
	log_path:建议为独立目录,不和其它相关内容共用
	file_name:指定LOG的文件名,如果为自动模式,这个值将会作为前缀,当使用了YY_FLF_DATE_FILE_NAME标记时,这个将作为文件名的前缀
*/
extern int yy_f_log_set_file( yy_f_log_t * log, const char * log_path, const char * file_name, size_t max_size, time_t max_time, size_t max_num  );

/* 功能:写日志，使用变参字符串 */
extern int yy_f_log_log_x( yy_f_log_t * log, yy_p_uint32 level , const char * mod_name, const char * format, ... );

/* 功能:写日志，使用变参列表 */
extern int yy_f_log_log_v( yy_f_log_t * log, yy_p_uint32 level ,const char * mod_name, const char * format, va_list arg_list );

/* 功能:二进制数据按16进制输出,未实现 */
extern int yy_f_log_log_binhex( yy_f_log_t * log, yy_p_uint32 level ,const char * mod_name, const char * bin, size_t len );

/* 功能:二进制数据按字符串输出 */
extern int yy_f_log_log_binstr( yy_f_log_t * log, yy_p_uint32 level ,const char * mod_name, const char * bin, size_t len );

/* 外部模块调用此函数attach到一日志对象，以不同的mode_name区分日志输出 */
extern int yy_f_log_agent_attach( yy_f_log_agent_t * agent, yy_f_log_t * log, const char * mod_name );

/* 外部模块不再写日志时，调用此函数解除与日志对象的关联 */
extern int yy_f_log_agent_detach( yy_f_log_agent_t * agent );

/* 设置日志输出时的模块名 */
extern int yy_f_log_agent_set_mod_name( yy_f_log_agent_t * agent, const char * mod_name );

/* 增加日志输出时的模块名字符串 */
extern int yy_f_log_agent_mod_name_add( yy_f_log_agent_t * agent, const char * mod_ex );

/* 增加日志输出时的模块名字符串（使用变参） */
extern int yy_f_log_agent_mod_name_addv( yy_f_log_agent_t * agent, const char * format, ... );

extern void yy_f_log_agent_disable( yy_f_log_agent_t * agent );
extern void yy_f_log_agent_enable( yy_f_log_agent_t * agent );

/* 设置日志代理结构中的日志等级和日志结构 */
extern int yy_f_log_agent_set_out( yy_f_log_agent_t * agent, size_t index, yy_p_uint32 level, yy_f_log_t * log );

/* 通过日志代理标准化输出LOG */
extern int yy_f_log_agent_log_x( yy_f_log_agent_t * agent, yy_p_uint32 level, const char * format, ... );

/* 通过日志代理标准化输出LOG */
extern int yy_f_log_agent_log_v( yy_f_log_agent_t * agent, yy_p_uint32 level, const char * format, va_list arg_list );

/* 通过日志代理将二进制内容16进制输出（暂未实现） */
extern int yy_f_log_agent_log_binhex( yy_f_log_agent_t * agent, yy_p_uint32 level, const char * bin, size_t len );

/* 通过日志代理将二进制内容字符串输出 */
extern int yy_f_log_agent_log_binstr( yy_f_log_agent_t * agent, yy_p_uint32 level, const char * bin, size_t len );

//仅为了名称短一点使用
#define yy_flal_x yy_f_log_agent_log_x
#define yy_flal_v yy_f_log_agent_log_v
#define yy_flal_binhex yy_f_log_agent_log_binhex
#define yy_flal_binstr yy_f_log_agent_log_binstr

//与上相同，大写，便于代码识别
#define YY_F_LOG_X yy_f_log_agent_log_x
#define YY_F_LOG_V yy_f_log_agent_log_v
#define YY_F_LOG_BH yy_f_log_agent_log_binhex
#define YY_F_LOG_BS yy_f_log_agent_log_binstr

//#define YY_F_

/* 全局默认的LOG系统,需要外部显示的配制，否则并不工作 */

/* 得到日志代理全局变量 */
extern yy_f_log_agent_t * yy_f_log_agent_get_global();

/* 设置全局日志代理 */
extern void yy_f_log_agent_set_global( yy_f_log_agent_t * la );

/* 通过日志代理全局变量标准化输出日志 */
extern int yyi_f_log_agent_log_x_global( yy_f_log_agent_t * agent, yy_p_uint32 level, const char * format, ... );

//第一个参数固定为NULL,为保持参数一致性，增加了这个agent的空参数
#define YY_F_LOG_GX yyi_f_log_agent_log_x_global
//#define YY_F_LOG_GV( agent, level, format, arg_list ) yy_f_log_agent_log_v( yy_f_log_agent_get_global(), level, , format, arg_list );
#define YY_F_LOG_GBS( agent, level, bin, len ) yy_f_log_agent_log_binstr( yy_f_log_agent_get_global(), level, bin, len )
#define YY_F_LOG_GBH( agent, level, bin, len ) yy_f_log_agent_log_binhex( yy_f_log_agent_get_global(), level, bin, len )

/* 测试用例 */
extern int yy_f_log_validation_test(const char * log_path);

#endif
