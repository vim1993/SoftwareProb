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

/* ip��ַ������󳤶� */
#define YY_P_IPS_MAX_LEN 64

#if YY_P_IS_BYTE_ORDER_BIG		/* �Ƿ�Ϊ��� */
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
*       short sin_family;        Addressfamily һ����˵AF_INET(��ַ��)PF_INET(Э����)
*       unsigned short sin_port; �˿�(����Ϊ�������ݸ�ʽ)
*       struct in_addr sin_addr; ip��ַ
*       unsigned char sin_zero[8]; Ϊ���ڴ����
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
typedef struct yy_p_inet_addr_s{		/* �����ַ�ṹ */
  
   union
  {
    struct sockaddr_in  in4_;		/* 32λipv4��ַ�������ֽ��� */
#if defined (YY_P_HAS_IPV6)
    struct sockaddr_in6 in6_;
#endif /* ACE_HAS_IPV6 */
  } inet_addr_;
   int af_type;						/* ��ַ�壬�磺AF_INET, AF_INET6�� */
}yy_p_inet_addr_t;

//���ڵ�ַ��ͳһ����

/* ��ַ����init */
extern int yy_p_inet_addr_init( yy_p_inet_addr_t * addr, int af_type );

/* ���õ�ַ�����õ�ַ�� */
extern int yy_p_inet_addr_reset( yy_p_inet_addr_t * addr );

/* �õ�ʹ�õ�Э���� */
extern int yy_p_inet_addr_get_type( yy_p_inet_addr_t * addr );

/* �õ�ip��ַ����32λipv4��ַ�������ֽ��� */
extern void * yy_p_inet_addr_get_addr( yy_p_inet_addr_t * addr );

/* �õ�ip��ַ�Ĵ�С */
extern yy_p_socklen_t yy_p_inet_addr_get_size( yy_p_inet_addr_t * addr );

/* ��ȡ�˿ں�*/
extern yy_p_uint16 yy_p_inet_addr_get_port_number( yy_p_inet_addr_t * addr );

/* ���ö˿ں� */
extern int yy_p_inet_addr_set_port_number( yy_p_inet_addr_t * addr, yy_p_uint16 port, int encode );

/* ��ȡipv4��ַ�������ֽ��� */
extern yy_p_uint32 yy_p_inet_addr_get_ipv4( yy_p_inet_addr_t * addr );

/* ����ַת��Ϊ�ַ�����ʽ */
extern int yy_p_inet_addr_get_host_addr( yy_p_inet_addr_t * addr, char * host_addr ,size_t len );

/**
*   ����:ת��һ��IPV4��ַ
*   ����:
*	addr:ת��������
*	ipv4:IP��ַ
*	port:�˿�
*	encode:�Ƿ���Ҫ�����ֽ���ת��
*/

/* ����ip��ַ�Ͷ˿ں� */
extern int yy_p_inet_addr_set_by_ipv4_port( yy_p_inet_addr_t * addr, yy_p_uint32 ipv4, yy_p_uint16 port, int encode );
#if defined( YY_P_HAS_IPV6 )
extern int yy_p_inet_addr_set_by_ip_and_service( yy_p_inet_addr_t * addr, const char * ip, const char * service_name );
//2016/1/4 sk: ��ipv4����ipv6���ַ���ת��Ϊyy_p_inet_addr_t
extern int yy_p_inet_addr_set_by_ips( yy_p_inet_addr_t * addr, const char * ips );
#else
#define yy_p_inet_addr_set_by_ips( addr, ips )  yy_p_inet_addr_set_by_string_ips_v4( addr, ips )
#endif

/* ����ip��ַ�Ͷ˿ڣ�ͨ���ַ���(ipv4) */
extern int yy_p_inet_addr_set_by_stripv4_port( yy_p_inet_addr_t * addr, const char * ipv4_str, yy_p_uint16 port, int encode );

/* ͨ����IP:�˿ڡ����������ַ */
extern int yy_p_inet_addr_set_by_string_ips_v4( yy_p_inet_addr_t * addr, const char * ipv4_str );

/* ͨ����������:�˿ڡ����õ�ַ */
extern int yy_p_inet_addr_set_by_string_dnsport_v4( yy_p_inet_addr_t * addr, const char * dns_ips );

/* ͨ�����������˿����õ�ַ */
extern int yy_p_inet_addr_set_by_strdns_port_v4( yy_p_inet_addr_t * addr, const char * dns, yy_p_uint16 port );

#if defined( YY_P_HAS_IPV6 )

/* ͨ��ipv6��ַ�����������ַ */
extern int yy_p_inet_addr_set_by_string_ips_v6( yy_p_inet_addr_t * addr, const char * ipv6_str );

/* ����interface(ipv6�ṹ�����һ����Ա) */
extern int yy_p_inet_addr_set_interface ( yy_p_inet_addr_t * addr, const char *intf_name );
#endif

/* ��ַת��Ϊ��IP���˿ڡ��� */
extern int yy_p_inet_addr_to_string( yy_p_inet_addr_t * addr, char * ips_str, size_t len );

/* �ж��Ƿ�Ϊ�ಥ��ַ */
extern int yy_p_inet_addr_is_multiaddr( yy_p_inet_addr_t * inet );

//socket����������

/* ��ȡ�Զ˵�ַ */
extern int yy_e_getpeername_ips( yy_p_socket_t s, char * ips_str, size_t len );
/* ��ȡ�Զ˵�ַ��֧��IPV6 */
extern int yy_e_getpeername_ips2( yy_p_socket_t s, int af_type,  char * ips_str, size_t len );

/* ��ȡ���ص�ַ */
extern int yy_e_getsockname_ips( yy_p_socket_t s, char * ips_str, size_t len );
/* ��ȡ�Զ˵�ַ��֧��IPV6 */
extern int yy_e_getsockname_ips2( yy_p_socket_t s, int af_type,  char * ips_str, size_t len );

/* �������ݣ��ɲ�ָ��Ŀ�ĵ�ַ */
extern ssize_t yy_e_sendto( yy_p_socket_t s, const void * buf, size_t len, int flags, yy_p_inet_addr_t * addr );

/* �������ݣ��ɲ�ָ��Դ��ַ����yy_e_sendto��Ӧ */
extern ssize_t yy_e_recvfrom(yy_p_socket_t s, void *buf, size_t len, int flags, yy_p_inet_addr_t * addr );
 
/* �ж��Ƿ�Ϊ��������ַ */
extern int yy_p_inet_addr_is_wan(yy_p_inet_addr_t *addr);

/*2016/1/5 sk:�Ƚ����������ַ��addr1=addr2:0,addr1<addr2:-1,add1>addr2:1*/
int yy_p_inet_addr_cmp( yy_p_inet_addr_t * addr1, yy_p_inet_addr_t * addr2);

/* �������� */
extern int yy_p_inet_addr_validation_test();

#ifdef  __cplusplus
}
#endif

#endif
