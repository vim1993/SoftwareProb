#ifndef YY_P_CONFIG_H
#define YY_P_CONFIG_H

#define YY_P_LIB_VER  "yy_sdk"//__DATE__

/* ���������� */
#define YY_P_COMPILER_MSVC 0x0100
#define YY_P_COMPILER_GCC  0x0200

#define YY_P_COMPILER_MSVC6     0x01
#define YY_P_COMPILER_MSVC7     0x02
#define YY_P_COMPILER_MSVC71    0x03
#define YY_P_COMPILER_MSVC8     0x04
#define YY_P_COMPILER_MSVC9     0x05
#define YY_P_COMPILER_MSVC10    0x06

#if defined( _MSC_VER )
    #if (_MSC_VER<=1200 )
        #define YY_P_COMPILER (YY_P_COMPILER_MSVC|YY_P_COMPILER_MSVC6)
        #define YY_P_COMPILER_NAME "MSVC/VC6"
    #elif (_MSC_VER<=1300 )
        #define YY_P_COMPILER (YY_P_COMPILER_MSVC|YY_P_COMPILER_MSVC7)
        #define YY_P_COMPILER_NAME "MSVC/VC7"
    #elif (_MSC_VER<=1310 )
        #define YY_P_COMPILER (YY_P_COMPILER_MSVC|YY_P_COMPILER_MSVC71)
        #define YY_P_COMPILER_NAME "MSVC/VC71"
    #elif (_MSC_VER<=1400 )
        #define YY_P_COMPILER (YY_P_COMPILER_MSVC|YY_P_COMPILER_MSVC8)
        #define YY_P_COMPILER_NAME "MSVC/VC8"
    #elif (_MSC_VER<=1500 )
        #define YY_P_COMPILER (YY_P_COMPILER_MSVC|YY_P_COMPILER_MSVC9)
        #define YY_P_COMPILER_NAME "MSVC/VC9"
    #else
        #define YY_P_COMPILER (YY_P_COMPILER_MSVC|YY_P_COMPILER_MSVC10)
        #define YY_P_COMPILER_NAME "MSVC/VC10"
    #endif
#elif defined( __GNUC__ )
    #define YY_P_COMPILER (YY_P_COMPILER_GCC|0)
    #define YY_P_COMPILER_NAME "GCC/Default"
#else
    #error "COMPILER not defined, YY_ENV_MSVC..."
#endif

#define YY_P_IS_MSVC ((YY_P_COMPILER&0xff00) == YY_P_COMPILER_MSVC )
#define YY_P_IS_GCC ((YY_P_COMPILER&0xff00) == YY_P_COMPILER_GCC )

#define _YY_P_MACRO_TO_STRING(x) #x
#define YY_P_MACRO_TO_STRING(x) _YY_P_MACRO_TO_STRING(x)

/* CPU���� */
#define YY_P_CPU_ARM    0x0100
#define YY_P_CPU_MIPS   0x0200
#define YY_P_CPU_X86    0x0300

#if defined( YY_ENV_ARM )
    #define YY_P_CPU YY_P_CPU_ARM
    #define YY_P_CPU_NAME "ARM"
#elif defined( YY_ENV_MIPS )
    #define YY_P_CPU YY_P_CPU_MIPS
    #define YY_P_CPU_NAME "MIPS"
#elif defined( YY_ENV_X86 )
    #define YY_P_CPU YY_P_CPU_X86
    #define YY_P_CPU_NAME "x86"
#elif !defined( YY_ENV_NOT_AUTO_CONFIG )
    #define YY_P_CPU YY_P_CPU_X86
    #define YY_P_CPU_NAME "x86"
#else
    #error "CPU not config"
#endif

#define YY_P_IS_CPU_ARM     (YY_P_CPU == YY_P_CPU_ARM)
#define YY_P_IS_CPU_MIPS    (YY_P_CPU == YY_P_CPU_MIPS)
#define YY_P_IS_CPU_X86     (YY_P_CPU == YY_P_CPU_X86)

#define YY_P_BYTE_ORDER_LITTLE  1
#define YY_P_BYTE_ORDER_BIG     2

/* CPUʹ�õ��ֽ���,δ����ʱĬ��ΪС���� */
#if defined( YY_ENV_BIG )
    #define YY_P_BYTE_ORDER YY_P_BYTE_ORDER_BIG
    #define YY_P_BYTE_ORDER_VALUE "Big"
#elif defined( YY_ENV_LITTLE )
    #define YY_P_BYTE_ORDER YY_P_BYTE_ORDER_LITTLE
    #define YY_P_BYTE_ORDER_VALUE "Little"
#elif !defined( YY_ENV_NOT_AUTO_CONFIG )
    #define YY_P_BYTE_ORDER YY_P_BYTE_ORDER_LITTLE
    #define YY_P_BYTE_ORDER_VALUE "Little"
#else
    #error "Byte Order not defined"
#endif

#define YY_P_IS_BYTE_ORDER_BIG ( YY_P_BYTE_ORDER==YY_P_BYTE_ORDER_BIG )
#define YY_P_IS_BYTE_ORDER_LITTLE ( YY_P_BYTE_ORDER==YY_P_BYTE_ORDER_LITTLE )

/* ����λ��16,32,64δ����ʱ����Ĭ��Ϊ32 */
#if defined( YY_ENV_M16 )
    #define YY_P_BUS_WIDTH 16
#elif defined( YY_ENV_M32 )
    #define YY_P_BUS_WIDTH 32
#elif defined( YY_ENV_M64 )
    #define YY_P_BUS_WIDTH 64
#elif !defined( YY_ENV_NOT_AUTO_CONFIG )
    #define YY_P_BUS_WIDTH 32
#else
    #error "Bus Width not defined"
#endif

#define YY_P_IS_BUS_WIDTH_16 (YY_P_BUS_WIDTH==16)
#define YY_P_IS_BUS_WIDTH_32 (YY_P_BUS_WIDTH==32)
#define YY_P_IS_BUS_WIDTH_64 (YY_P_BUS_WIDTH==64)

/* OS���� */
#define YY_P_WINODOWS  0x0100
#define YY_P_NIX       0x0200
#define YY_P_VXWORKS   0x0300

#define YY_P_WIN32 0x0001
#define YY_P_WINCE 0x0002
#define YY_P_WIN64 0x0003
#define YY_P_LINUX 0x0010

/* ��������,����������� */
#if defined( YY_ENV_WIN32 ) || ( defined( WIN32 ) && !defined(WINCE) && ! defined(_WIN32_WCE) && !defined( YY_ENV_NOT_AUTO_CONFIG ) )
    #define YY_P_OS (YY_P_WINODOWS|YY_P_WIN32)
    #define YY_P_BUS_WIDTH 32
    #define YY_P_OS_NAME "Windows/Win32"
#elif defined( YY_ENV_WIN64 ) || ( defined( WIN64 ) && !defined(WINCE) && ! defined(_WIN32_WCE) && !defined( YY_ENV_NOT_AUTO_CONFIG ) )
    #define YY_P_OS (YY_P_WINODOWS|YY_P_WIN64)
    #define YY_P_BUS_WIDTH 64
    #define YY_P_OS_NAME "Windows/Win64"
#elif defined( YY_ENV_WINCE ) || ( ( defined(WINCE) || defined(_WIN32_WCE) ) && !defined( YY_ENV_NOT_AUTO_CONFIG ) )
    #define YY_P_OS (YY_P_WINODOWS|YY_P_WINCE)
    #define YY_P_OS_NAME "Windows/WinCE"
#elif defined( YY_ENV_LINUX ) || ( defined( __linux__ ) && !defined( YY_ENV_NOT_AUTO_CONFIG ) )
    #define YY_P_OS (YY_P_NIX|YY_P_LINUX)
    #define YY_P_OS_NAME "Nix/Linux"
#else
    #error "OS not defined, YY_ENV_WIN32..."
#endif

#define YY_P_IS_WINDOWS ( (YY_P_OS&0xff00) == YY_P_WINODOWS )
#define YY_P_IS_WIN32   ( ( (YY_P_OS&0xff00) == YY_P_WINODOWS ) && ( (YY_P_OS&0x00ff) == YY_P_WIN32 ) )
#define YY_P_IS_WIN64   ( ( (YY_P_OS&0xff00) == YY_P_WINODOWS ) && ( (YY_P_OS&0x00ff) == YY_P_WIN64 ) )
#define YY_P_IS_WINCE   ( ( (YY_P_OS&0xff00) == YY_P_WINODOWS ) && ( (YY_P_OS&0x00ff) == YY_P_WINCE ) )
#define YY_P_IS_WIN32OR64 ( YY_P_IS_WIN32 || YY_P_IS_WIN64 )
#define YY_P_IS_NIX     ( (YY_P_OS&0xff00) == YY_P_NIX )

/* �߳�,�п���WIN32,PTHREAD������ģ��һ��ʹ��? */
#define YY_P_THREAD_NTHREAD 0x0000
#define YY_P_THREAD_PTHREAD 0x0001
#define YY_P_THREAD_WTHREAD 0x0002
#if defined( YY_ENV_PTHREAD ) || YY_P_IS_NIX
    #define YY_P_THREAD YY_P_THREAD_PTHREAD
#elif ( YY_P_IS_WINDOWS )
    #define YY_P_THREAD YY_P_THREAD_WTHREAD
#else
    #define YY_P_THREAD YY_P_THREAD_NTHREAD
#endif

#define YY_P_IS_WTHREAD ( YY_P_THREAD == YY_P_THREAD_WTHREAD )
#define YY_P_IS_PTHREAD ( YY_P_THREAD == YY_P_THREAD_PTHREAD )
#define YY_P_IS_NTHREAD ( YY_P_THREAD == YY_P_THREAD_NTHREAD )

#if defined( YY_ENV_IPV6 )
    #define YY_P_HAS_IPV6 1
#endif

#if defined( YY_ENV_RELEASE )
    #define YY_P_RELASE 1
#endif

/* �ر�ASSERT */
#if defined( YY_ENV_NO_ASSERT )
    #define YY_P_NO_ASSERT 1
#endif

#if YY_P_IS_WINDOWS
	#if defined(FD_SETSIZE)
		#undef FD_SETSIZE
	#endif
	#define FD_SETSIZE 1024
#endif


/* ���·ǻ�����ȡ */
#if YY_P_IS_MSVC
    #ifndef _SCL_SECURE_NO_WARNINGS
    #	define _SCL_SECURE_NO_WARNINGS
    #endif
    #ifndef _CRT_SECURE_NO_WARNINGS
    #	define _CRT_SECURE_NO_WARNINGS
    #endif
    #ifndef _CRT_SECURE_NO_DEPRECATE
    #	define  _CRT_SECURE_NO_DEPRECATE
    #endif
    #ifndef _CRT_NONSTDC_NO_WARNINGS
    #	define _CRT_NONSTDC_NO_WARNINGS
    #endif
#endif

/**
*   #if yy_p_is_msvc
*       #pragma message( "yy_p_cpu_name:"yy_p_cpu_name )
*       #pragma message( "yy_p_os_name:"yy_p_os_name )
*       #pragma message( "yy_p_compiler_name:"yy_p_compiler_name )
*       #pragma message( "yy_p_byte_order_value:"yy_p_byte_order_value )
*       #pragma message( "yy_p_bus_width:"yy_p_macro_to_string(yy_p_bus_width) )
*   #elif yy_p_is_gcc
*       #warning __line__
*       #warning  "yy_p_os_name:"yy_p_macro_to_string(yy_p_os_name)
*       #warning "yy_p_compiler_name:"yy_p_macro_to_string(yy_p_compiler_name
*       #warning "yy_p_byte_order_value:"yy_p_macro_to_string(yy_p_byte_order_value
*       #warning "yy_p_bus_width:"yy_p_macro_to_string(yy_p_bus_width)
*   #endif
*/

/* ��ʱ���� */
#define YY_E_FLOW_USE_64BIT 1

#endif
