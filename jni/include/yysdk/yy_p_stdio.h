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

#define YY_P_FILE_DEFAULT_ACCESS    0744		/* �û���дִ�С������������ */
#define YY_P_FILE_OWNER_ACCESS      0700		/* �û���дִ�� */
#define YY_P_FILE_ALL_ACCESS		0777		/* �û����顢�������ɶ�����д����ִ�� */


//C���Բ���
//FILE*����
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

/* �����ļ������ü�����inode�ϣ�����������������ɾ���ļ� */
extern int yy_p_unlink( const char * filename );

/* �ӱ�׼�����ȡ��һ���ַ� */
extern int yy_p_getchar();

/* �ɱ������ʽ�������һ���ַ������� */
extern int yy_p_vsnprintf(char *dst_buf, size_t max_count, const char *format, va_list arg_list );

/* �ɱ������ʽ�������һ���ַ������� */
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
    #define YY_P_MAX_PATH MAX_PATH				/* ���·������ */
    #define YY_P_PATH_SEP "\\"					/* ·���ָ�� */
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


/* WINDOWSû�ж�����Щ��,NUX�ж���, */
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

/*  ���ļ� */
extern yy_p_handle_t yy_p_open(const char *filename, int flag, mode_t perms, LPSECURITY_ATTRIBUTES sa );

/* �ر��ļ������� */
extern int yy_p_close( yy_p_handle_t fd );

/* ���ļ���ȡ���ݵ����� */
extern yy_p_off_t yy_p_read( yy_p_handle_t fd,  void *buf, yy_p_off_t len );

/* ��buf�е�����д���ļ� */
extern yy_p_off_t yy_p_write( yy_p_handle_t fd,  const void *buf, yy_p_off_t len );

/* �����ļ�ָ��λ�� */
extern yy_p_off_t yy_p_lseek( yy_p_handle_t fd, yy_p_off_t offset, int whence );

/* ��ȡ�ļ���С */
extern yy_p_off_t yy_p_file_size( yy_p_handle_t fd );

/* ͨ���ļ�·����ȡ�ļ���С */
extern yy_p_off_t yy_p_file_size_by_name( const char * file_name );

/* ���ַ�������ת����yy_p_off_t����ֵ */
extern yy_p_off_t yy_p_ato_off_t( const char * s );

/* ���ַ�������ת����yy_p_uint64����ֵ */
extern yy_p_uint64 yy_p_ato_uint64( const char * s );

/* ����Ŀ¼����ĳ���м�Ŀ¼������Ҳ���� */
extern int yy_p_create_dir( const char *path );

/* �����ļ�����֧��windows */
extern int yy_p_copy( const char * src, const char * dst );

/* ����ļ���Ŀ¼��Ȩ�޻�״̬ */
extern int yy_p_access(const char * filename, int mode);

/* ����Ŀ¼��ָ������Ȩ�� */
extern int yy_p_mkdir( const char* path, mode_t mode );

/* ɾ����Ŀ¼ */
extern int yy_p_rmdir ( const char * path );

/* ��ȡ�ļ�״̬��file status�� */
extern int yy_p_stat( const char * file, yy_p_stat_t * s );

/* ��ȡָ��Ŀ¼�������̵��ܿռ�Ϳ��ÿռ��С����MBΪ��λ */
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

/* ��Ŀ¼ */
extern yy_p_dir_t * yy_p_opendir( const char * path );

/* �ر�Ŀ¼ */
extern void yy_p_closedir( yy_p_dir_t * d );

/* ��ȡĿ¼d�е���һ���ļ��� */
extern int yy_p_readdir( yy_p_dir_t * d, char * basename );

/* �������� */
extern int yy_p_stdio_validation_test();

#ifdef  __cplusplus
}
#endif
#endif
