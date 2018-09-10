#ifndef YY_P_TYPE_H
#define YY_P_TYPE_H

#include "yy_p_config.h"
#if YY_P_IS_WINDOWS
	#include <winsock2.h>
	#include <windows.h>
#else
	#include <sys/types.h>
	#include <sys/socket.h>
	// #include <unistd.h>
#endif
#include <limits.h>
#include <stddef.h>
#include <stdint.h>

/* �������Ͷ���,��ҪĿ������Ӧ���ܲ�ͬƽ̨,������,��C�ؼ��ֳ�����Ϊ��һ�� */
typedef unsigned char yy_p_uint8;
typedef char yy_p_int8;
typedef unsigned short yy_p_uint16;
typedef short yy_p_int16;
typedef unsigned int yy_p_uint32;
typedef int yy_p_int32;
typedef unsigned long long int yy_p_uint64;
typedef long long int yy_p_int64;

#define YY_P_PRI_INT64_T		"%lld"
#define YY_P_PRI_UINT64_T		"%llu"


/* �Զ����͵�char */
typedef char yy_p_tchar;

#define YY_P_UINT8_MAX UCHAR_MAX
#define YY_P_UINT16_MAX USHRT_MAX
#define YY_P_UINT32_MAX UINT_MAX
#define YY_P_INT32_MAX	INT_MAX
#define YY_P_UINT64_MAX ULLONG_MAX


/* ����ʱ���ͼ��,��ֹ���ʹ��� */
#if SHRT_MAX != 32767           /* �����ֽڣ�15λ�����λΪ����λ */
    #error "short is not 2byte"
#endif
#if INT_MAX != 2147483647
    #error "int is not 4byte"
#endif
#if defined( LLONG_MAX ) && LLONG_MAX == 2147483647
    #error "long long int is not 8byte"
#endif

/* ����һ�������ͬ�������� */
#if YY_P_IS_BUS_WIDTH_16
    typedef short yy_p_intat;
    typedef unsigned short yy_p_uintat;
#elif YY_P_IS_BUS_WIDTH_32
    typedef int yy_p_intat;
    typedef unsigned int yy_p_uintat;
#elif YY_P_IS_BUS_WIDTH_64
    typedef long long int yy_p_intat;
    typedef unsigned long long int yy_p_uintat;
#else
    typedef int yy_p_intat;
    typedef unsigned int yy_p_uintat;
#endif

/* ����ACE6.0.0 */
#if YY_P_IS_WINDOWS
    #if YY_P_IS_WIN64
        typedef SSIZE_T ssize_t;
        #define YY_P_PRI_SIZE_T "%lu"
    #else
        typedef int ssize_t;
        #define YY_P_PRI_SIZE_T "%u"
    #endif
    #define YY_P_PRI_PTR "%p"
#else
    #define YY_P_PRI_SIZE_T "%zu"
    #define YY_P_PRI_PTR "%p"
#endif

#define YY_P_INVLIAD_SIZE_T (size_t)-1
#if YY_P_IS_BUS_WIDTH_64
	#define YY_P_SIZE_T_MAX YY_P_UINT64_MAX
#else
	#define YY_P_SIZE_T_MAX YY_P_UINT32_MAX
#endif

/**
*    (TYPE *)0 ��ʾ���ݶλ�ַǿ��ת����TYPE���ͣ�Ҳ����TYPE����ʼ��ַ
*    &((TYPE *)0->MEMBER���õ�MEMBER��Ա������ʼ��ַ��ƫ�Ƶ�ַ��Ҳ����
*   MEMBER�ĵ�ַ�����ֵ��0~N��
*/
#define YY_P_OFFSETOF(TYPE, MEMBER) ((size_t) &(((TYPE *)0)->MEMBER))   /* ȡ�ṹ���Ա���ṹ����ʼ��ַ��ƫ���� */
#if YY_P_IS_GCC
	#define YY_P_CONTAINER_OF(PTR, TYPE, MEMBER) ({			\
        const typeof( ((TYPE *)0)->MEMBER )*__mptr = (PTR);	\
        (TYPE *)( (char *)__mptr - YY_P_OFFSETOF(TYPE,MEMBER) );})
#else
     /**
     *   (char *)(ptr)- YY_P_OFFSETOF(TYPE,MEMBER)����(char *)��Ϊ�˽�������Ϊһ���ֽڣ�
     *    ����: PTR = &a.member; b = YY_P_CONTAINER_OF(PTR,TYPE,member), ���b��ָ��a��
     *    ��a.member�ľ��Ե�ַ��ȥ��Ե�ַ����a����ʼ��ַ���ڴ��ַ��
     */
	#define YY_P_CONTAINER_OF(PTR, TYPE, MEMBER) (TYPE *)( (char *)(PTR) - YY_P_OFFSETOF(TYPE,MEMBER) ) /* ��һ���ṹ�ĳ�Աָ���ҵ���������ָ�� */
#endif


/* �ֽ�ת�� */
#define YY_P_SWAP_2BYTE(L) ((((L) & 0x00FF) << 8) | (((L) & 0xFF00) >> 8))
#define YY_P_SWAP_4BYTE(L) ((YY_P_SWAP_2BYTE ((L) & 0xFFFF) << 16) | YY_P_SWAP_2BYTE(((L) >> 16) & 0xFFFF))
#define YY_P_SWAP_8BYTE(L) ((YY_P_SWAP_4BYTE (((yy_p_uint64)(L)) & 0xFFFFFFFF) << 32) | YY_P_SWAP_4BYTE((((yy_p_uint64)(L)) >> 32) & 0xFFFFFFFF))

#if YY_P_IS_BYTE_ORDER_LITTLE
    #define YY_P_CDR_BIG_2BYTE( a ) YY_P_SWAP_2BYTE( a )
    #define YY_P_CDR_BIG_4BYTE( a ) YY_P_SWAP_4BYTE( a )
    #define YY_P_CDR_BIG_8BYTE( a ) YY_P_SWAP_8BYTE( a )
	#define YY_P_CDR_LITTLE_2BYTE( a ) (a)
    #define YY_P_CDR_LITTLE_4BYTE( a ) (a)
    #define YY_P_CDR_LITTLE_8BYTE( a ) (a)
#else
    #define YY_P_CDR_BIG_2BYTE( a ) (a)
    #define YY_P_CDR_BIG_4BYTE( a ) (a)
    #define YY_P_CDR_BIG_8BYTE( a ) (a)
	#define YY_P_CDR_LITTLE_2BYTE( a ) YY_P_SWAP_2BYTE( a )
    #define YY_P_CDR_LITTLE_4BYTE( a ) YY_P_SWAP_4BYTE( a )
    #define YY_P_CDR_LITTLE_8BYTE( a ) YY_P_SWAP_8BYTE( a )
#endif

/* λ���� */
#define YY_P_BIT_ENABLED(WORD, BIT) (((WORD) & (BIT)) != 0)
#define YY_P_BIT_DISABLED(WORD, BIT) (((WORD) & (BIT)) == 0)
#define YY_P_SET_BITS(WORD, BITS) (WORD |= (BITS))
#define YY_P_CLR_BITS(WORD, BITS) (WORD &= ~(BITS))

#define YY_P_FOURCC(a, b, c, d) (((yy_p_uint32)(a) << 24) + ((yy_p_uint32)(b) << 16) + ((yy_p_uint32)(c) << 8) +((yy_p_uint32)(d) ))
#define YY_P_TWOCC(a, b) (((yy_p_uint16)(a) << 8) + ((yy_p_uint16)(b) ))

#define YY_P_MIN( a, b ) ((a)>(b)?(b):(a))         /* ��������֮����Сֵ */
#define YY_P_MAX( a, b ) ((a)>(b)?(a):(b))         /* ��������֮�����ֵ */
#define YY_P_ABS( a, b ) ((a)>=(b)?((a)-(b)):((b)-(a)))    /* ��������֮��ľ���ֵ */


#define YY_P_RANGE( min, max, val ) YY_P_MIN( YY_P_MAX( min, val ), max ) /* �����������Χ�ڵ�ֵ */


#define YY_P_ALIGNMENT   sizeof(void *)           /* ָ�볤�ȣ�һ��ȼ��ڻ����ֽ��� */


#define YY_P_ALIGN(value, align)     (((value) + (align - 1)) & ~(align - 1))   /* ���룬 a������2��ָ��ֵ(�ڴ��������������)*/


#define YY_P_ALIGN_PTR(p, a) (char *)(((yy_p_uintat) (p) + ((yy_p_uintat) a - 1)) & ~((yy_p_uintat) a - 1)) 	/* ָ����� */


#define YY_P_LOW_ALIGN( d, a ) ( ((d)/(a))*(a) )       /* ǰһ��������һ��������������,������ȡֵ */


#define YY_P_HIGH_ALIGN( d, a ) ( (((d)+(a)-1)/(a))*(a) ) /* ǰһ��������һ��������������,������ȡֵ������������� */

/* ����ϵͳ���涨��,ͨ��,��˶�������� */
#if YY_P_IS_WINDOWS
    /* ���,ͨ�ò��� */
    typedef HANDLE yy_p_handle_t ;
    #define YY_P_INVALID_HANDLE INVALID_HANDLE_VALUE

    //����ID
    typedef DWORD yy_p_pid_t;
	#define YY_P_INVLIAD_PID -1

    //SOCKET���
    typedef SOCKET yy_p_socket_t;
    #define YY_P_INVALID_SOCKET INVALID_SOCKET
#else
    typedef int yy_p_handle_t ;
    #define YY_P_INVALID_HANDLE -1

    typedef pid_t yy_p_pid_t;
	#define YY_P_INVLIAD_PID -1

    //SOCKET���
    typedef int yy_p_socket_t;
    #define YY_P_INVALID_SOCKET -1
#endif

#endif
