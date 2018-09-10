#ifndef YY_P_INET_ADDR_H
#define YY_P_INET_ADDR_H
#include "yy_p_socket.h"
#include "yy_p_type.h"
#include "yy_p_test.h"

#if YY_P_IS_NIX
#include <ifaddrs.h>
#endif

#ifdef  __cplusplus
extern "C" {
#endif

/* ip地址串的最大长度 */
#define YY_P_IPS_MAX_LEN 64

#if YY_P_IS_BYTE_ORDER_BIG		/* 是否为大端 */
    #define YY_P_NTOHS(x) x
    #define YY_P_HTONS(x) x
    #define YY_P_NTOHL(x) x
    #define YY_P_HTONL(x) x
#else
    #define YY_P_NTOHS(x) YY_P_SWAP_2BYTE(x)
    #define YY_P_HTONS(x) YY_P_SWAP_2BYTE(x)
    #define YY_P_NTOHL(x) YY_P_SWAP_4BYTE(x)
    #define YY_P_HTONL(x) YY_P_SWAP_4BYTE(x)
#endif

/**
*   struct sockaddr_in
*   {
*       short sin_family;        Addressfamily 一般来说AF_INET(地址族)PF_INET(协议族)
*       unsigned short sin_port; 端口(必须为网络数据格式)
*       struct in_addr sin_addr; ip地址
*       unsigned char sin_zero[8]; 为了内存对齐
*   };
*
*   typedef struct in_addr      // linux
*   {
*       unsigned long s_addr;
*   };
*
*   typedef struct in_addr      //windows
*   {
*       union
*       {
*           struct {  unsigned char s_b1,s_b2,s_b3,s_b4; } S_un_b;
*           struct {  unsigned short s_w1,s_w2; } S_un_w;
*           unsigned long S_addr;
*       }S_un;
*   }
*/
typedef struct yy_p_inet_addr_s{		/* 网络地址结构 */
  
   union
  {
    struct sockaddr_in  in4_;		/* 32位ipv4地址，网络字节序 */
#if defined (YY_P_HAS_IPV6)
    struct sockaddr_in6 in6_;
#endif /* ACE_HAS_IPV6 */
  } inet_addr_;
   int af_type;						/* 地址族，如：AF_INET, AF_INET6等 */
}yy_p_inet_addr_t;

//关于地址的统一解析

/* 地址解析init */
extern int yy_p_inet_addr_init( yy_p_inet_addr_t * addr, int af_type );

/* 重置地址，设置地址族 */
extern int yy_p_inet_addr_reset( yy_p_inet_addr_t * addr );

/* 得到使用的协议族 */
extern int yy_p_inet_addr_get_type( yy_p_inet_addr_t * addr );

/* 得到ip地址，如32位ipv4地址，网络字节序 */
extern void * yy_p_inet_addr_get_addr( yy_p_inet_addr_t * addr );

/* 得到ip地址的大小 */
extern yy_p_socklen_t yy_p_inet_addr_get_size( yy_p_inet_addr_t * addr );

/* 获取端口号*/
extern yy_p_uint16 yy_p_inet_addr_get_port_number( yy_p_inet_addr_t * addr );

/* 设置端口号 */
extern int yy_p_inet_addr_set_port_number( yy_p_inet_addr_t * addr, yy_p_uint16 port, int encode );

/* 获取ipv4地址，主机字节序 */
extern yy_p_uint32 yy_p_inet_addr_get_ipv4( yy_p_inet_addr_t * addr );

/* 将地址转换为字符串形式 */
extern int yy_p_inet_addr_get_host_addr( yy_p_inet_addr_t * addr, char * host_addr ,size_t len );

/**
*   功能:转换一个IPV4地址
*   参数:
*	addr:转换结果存放
*	ipv4:IP地址
*	port:端口
*	encode:是否需要进行字节序转换
*/

/* 设置ip地址和端口号 */
extern int yy_p_inet_addr_set_by_ipv4_port( yy_p_inet_addr_t * addr, yy_p_uint32 ipv4, yy_p_uint16 port, int encode );
#if defined( YY_P_HAS_IPV6 )
extern int yy_p_inet_addr_set_by_ip_and_service( yy_p_inet_addr_t * addr, const char * ip, const char * service_name );
//2016/1/4 sk: 将ipv4或者ipv6的字符串转换为yy_p_inet_addr_t
extern int yy_p_inet_addr_set_by_ips( yy_p_inet_addr_t * addr, const char * ips );
#else
#define yy_p_inet_addr_set_by_ips( addr, ips )  yy_p_inet_addr_set_by_string_ips_v4( addr, ips )
#endif

/* 设置ip地址和端口，通过字符串(ipv4) */
extern int yy_p_inet_addr_set_by_stripv4_port( yy_p_inet_addr_t * addr, const char * ipv4_str, yy_p_uint16 port, int encode );

/* 通过“IP:端口”设置网络地址 */
extern int yy_p_inet_addr_set_by_string_ips_v4( yy_p_inet_addr_t * addr, const char * ipv4_str );

/* 通过“主机名:端口”设置地址 */
extern int yy_p_inet_addr_set_by_string_dnsport_v4( yy_p_inet_addr_t * addr, const char * dns_ips );

/* 通过主机名、端口设置地址 */
extern int yy_p_inet_addr_set_by_strdns_port_v4( yy_p_inet_addr_t * addr, const char * dns, yy_p_uint16 port );

#if defined( YY_P_HAS_IPV6 )

/* 通过ipv6地址串设置网络地址 */
extern int yy_p_inet_addr_set_by_string_ips_v6( yy_p_inet_addr_t * addr, const char * ipv6_str );

/* 设置interface(ipv6结构体里的一个成员) */
extern int yy_p_inet_addr_set_interface ( yy_p_inet_addr_t * addr, const char *intf_name );
#endif

/* 地址转换为“IP：端口”串 */
extern int yy_p_inet_addr_to_string( yy_p_inet_addr_t * addr, char * ips_str, size_t len );

/* 判断是否为多播地址 */
extern int yy_p_inet_addr_is_multiaddr( yy_p_inet_addr_t * inet );

//socket辅助工作类

/* 获取对端地址 */
extern int yy_e_getpeername_ips( yy_p_socket_t s, char * ips_str, size_t len );
/* 获取对端地址，支持IPV6 */
extern int yy_e_getpeername_ips2( yy_p_socket_t s, int af_type,  char * ips_str, size_t len );

/* 获取本地地址 */
extern int yy_e_getsockname_ips( yy_p_socket_t s, char * ips_str, size_t len );
/* 获取对端地址，支持IPV6 */
extern int yy_e_getsockname_ips2( yy_p_socket_t s, int af_type,  char * ips_str, size_t len );

/* 发送数据，可不指定目的地址 */
extern ssize_t yy_e_sendto( yy_p_socket_t s, const void * buf, size_t len, int flags, yy_p_inet_addr_t * addr );

/* 接收数据，可不指定源地址，与yy_e_sendto对应 */
extern ssize_t yy_e_recvfrom(yy_p_socket_t s, void *buf, size_t len, int flags, yy_p_inet_addr_t * addr );
 
/* 判断是否为广域网地址 */
extern int yy_p_inet_addr_is_wan(yy_p_inet_addr_t *addr);

/*2016/1/5 sk:比较两个网络地址，addr1=addr2:0,addr1<addr2:-1,add1>addr2:1*/
int yy_p_inet_addr_cmp( yy_p_inet_addr_t * addr1, yy_p_inet_addr_t * addr2);

/* 测试用例 */
extern int yy_p_inet_addr_validation_test();

#ifdef  __cplusplus
}
#endif

#endif
