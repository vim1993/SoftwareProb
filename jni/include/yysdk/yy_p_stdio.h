#ifndef YY_P_STDIO_H
#define YY_P_STDIO_H
#include "yy_p_config.h"
#include "yy_p_type.h"
#include <stdio.h>
#include <stdarg.h>
#include <fcntl.h>

//#if YY_P_IS_WINDOWS
    #include <sys/stat.h>
//#endif

#if YY_P_IS_NIX
    #include <dirent.h>
#endif

#ifdef  __cplusplus
extern "C" {
#endif

#define YY_P_FILE_DEFAULT_ACCESS    0744		/* 用户读写执行、组读、其它读 */
#define YY_P_FILE_OWNER_ACCESS      0700		/* 用户读写执行 */
#define YY_P_FILE_ALL_ACCESS		0777		/* 用户、组、其它均可读、可写、可执行 */


//C语言层面
//FILE*处理
typedef FILE yy_p_file_t;
#define yy_p_fopen fopen
#define yy_p_fclose fclose
#define yy_p_fread fread
#define yy_p_fwrite fwrite
#define yy_p_fflush fflush
#define yy_p_fseek fseek
#define yy_p_ftell ftell
#define yy_p_fprintf fprintf
#define yy_p_fgets fgets
#define yy_p_freopen freopen
#define yy_p_setvbuf setvbuf
#define yy_p_printf printf
#define yy_p_gets gets

#define yy_p_rename rename

/* 减少文件的引用计数（inode上），若无其它引用则删除文件 */
extern int yy_p_unlink( const char * filename );

/* 从标准输入读取下一个字符 */
extern int yy_p_getchar();

/* 可变参数格式化输出到一个字符数组中 */
extern int yy_p_vsnprintf(char *dst_buf, size_t max_count, const char *format, va_list arg_list );

/* 可变参数格式化输出到一个字符数组中 */
extern int yy_p_snprintf(char *dst_buf, size_t max_count, const char *format, ... );

//OS Layer
//RAW UNIX FILE and Windows(CreateFile,ReadFile,WriteFile,CloseHandle)
#if YY_P_IS_WINDOWS
    #include <io.h>
    #if YY_P_IS_WINCE
        typedef DWORD yy_p_off_t;
        #define YY_P_PRI_OFF_T "%u"
		#define YY_P_OFF_T_MAX 0xffffffff
    #else
        typedef yy_p_int64 yy_p_off_t;
        #define YY_P_PRI_OFF_T "%lld"
		#define YY_P_OFF_T_MAX 0x7fffffffffffffffLL
    #endif
    typedef DWORD mode_t ;
    #define YY_P_FILE_PERMS_READ FILE_SHARE_READ
    #define YY_P_FILE_PERMS_ALL (FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE)
    #define YY_P_FILE_FLAG_CREATION_OPEN 0
    #define YY_P_FILE_FLAG_CREATION_CREATE (_O_CREAT | _O_TRUNC)
    #define YY_P_MAX_PATH MAX_PATH				/* 最大路径长度 */
    #define YY_P_PATH_SEP "\\"					/* 路径分割符 */
    #define YY_P_PATH_SEP_CHAR '\\'
    typedef struct _stat yy_p_stat_t;
#else
#if defined (_FILE_OFFSET_BITS ) && ( _FILE_OFFSET_BITS == 64 )
    typedef off64_t yy_p_off_t;
    #define YY_P_PRI_OFF_T "%lld"
	#define YY_P_OFF_T_MAX 0x7fffffffffffffffLL
#else
    typedef off_t yy_p_off_t;
    #define YY_P_PRI_OFF_T "%d"
	#define YY_P_OFF_T_MAX 0x7fffffff
#endif
    typedef void * LPSECURITY_ATTRIBUTES;    //LINUX DONT'T HAVE THIS
    #define YY_P_FILE_PERMS_READ 0444
    #define YY_P_FILE_PERMS_ALL  0777
    #define YY_P_FILE_FLAG_CREATION_OPEN 0
    #define YY_P_FILE_FLAG_CREATION_CREATE (O_CREAT | O_TRUNC)
    #define YY_P_MAX_PATH 512
    #define YY_P_PATH_SEP "/"
    #define YY_P_PATH_SEP_CHAR '/'
    typedef struct stat yy_p_stat_t;
#endif

#define YY_P_INVALID_FILE_SIZE  (yy_p_off_t)(-1)
#define YY_P_INVALID_OFF_T      (yy_p_off_t)(-1)


/* WINDOWS没有定义这些宏,NUX有定义, */
# if !defined (R_OK)
    #   define R_OK    04      /* Test for Read permission. */
# endif /* R_OK */

# if !defined (W_OK)
    #   define W_OK    02      /* Test for Write permission. */
# endif /* W_OK */

# if !defined (X_OK)
    #   define X_OK    01      /* Test for eXecute permission. */
# endif /* X_OK */

#if !defined (F_OK)
    #define F_OK    0		   /* Test for existence of File. */
#endif /* F_OK */

#if YY_P_IS_WINDOWS
    #define S_IFDIR _S_IFDIR
#endif

/*  打开文件 */
extern yy_p_handle_t yy_p_open(const char *filename, int flag, mode_t perms, LPSECURITY_ATTRIBUTES sa );

/* 关闭文件描述符 */
extern int yy_p_close( yy_p_handle_t fd );

/* 从文件读取数据到缓存 */
extern yy_p_off_t yy_p_read( yy_p_handle_t fd,  void *buf, yy_p_off_t len );

/* 将buf中的数据写入文件 */
extern yy_p_off_t yy_p_write( yy_p_handle_t fd,  const void *buf, yy_p_off_t len );

/* 设置文件指针位置 */
extern yy_p_off_t yy_p_lseek( yy_p_handle_t fd, yy_p_off_t offset, int whence );

/* 获取文件大小 */
extern yy_p_off_t yy_p_file_size( yy_p_handle_t fd );

/* 通过文件路径获取文件大小 */
extern yy_p_off_t yy_p_file_size_by_name( const char * file_name );

/* 将字符串数字转化成yy_p_off_t类型值 */
extern yy_p_off_t yy_p_ato_off_t( const char * s );

/* 将字符串数字转化成yy_p_uint64类型值 */
extern yy_p_uint64 yy_p_ato_uint64( const char * s );

/* 创建目录，若某个中间目录不存在也创建 */
extern int yy_p_create_dir( const char *path );

/* 复制文件，仅支持windows */
extern int yy_p_copy( const char * src, const char * dst );

/* 检查文件或目录的权限或状态 */
extern int yy_p_access(const char * filename, int mode);

/* 创建目录并指定访问权限 */
extern int yy_p_mkdir( const char* path, mode_t mode );

/* 删除空目录 */
extern int yy_p_rmdir ( const char * path );

/* 获取文件状态（file status） */
extern int yy_p_stat( const char * file, yy_p_stat_t * s );

/* 获取指定目录所属磁盘的总空间和可用空间大小，以MB为单位 */
extern int yy_p_disk_stat( const char * disk_path, yy_p_uint32 * total_mb, yy_p_uint32 * free_mb );

#if YY_P_IS_NIX
    typedef DIR yy_p_dir_t;
#else
    typedef struct yy_p_dir_s{
	    yy_p_handle_t h;
	    int is_first_readed;
	    char path[MAX_PATH];
    }yy_p_dir_t;
#endif

/* 打开目录 */
extern yy_p_dir_t * yy_p_opendir( const char * path );

/* 关闭目录 */
extern void yy_p_closedir( yy_p_dir_t * d );

/* 获取目录d中的下一个文件名 */
extern int yy_p_readdir( yy_p_dir_t * d, char * basename );

/* 测试用例 */
extern int yy_p_stdio_validation_test();

#ifdef  __cplusplus
}
#endif
#endif
