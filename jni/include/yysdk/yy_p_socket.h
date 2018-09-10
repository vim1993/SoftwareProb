#ifndef YY_PO_SOCKET_H
#define YY_PO_SOCKET_H
#include "yy_p_config.h"
#include "yy_p_type.h"
#include "yy_p_time.h"
#include "yy_p_test.h"

#if YY_P_IS_NIX	
	#include <netinet/tcp.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <sys/ioctl.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <net/if.h>
    #include <netdb.h>
	#include <unistd.h>
	#include <fcntl.h>
	typedef socklen_t yy_p_socklen_t;
#elif YY_P_IS_WINDOWS
	#include <Ws2tcpip.h>	
	typedef int yy_p_socklen_t;
#else

#endif

#if YY_P_IS_WINDOWS
	#define YY_P_NONBLOCK 1
#else
	#define YY_P_NONBLOCK O_NDELAY		/* O_NONBLOCK��O_NDELAY����������� */
#endif

#if YY_P_IS_NIX
#elif YY_P_IS_WINDOWS
    #if YY_P_IS_WIN32OR64
        #pragma comment( lib, "ws2_32.lib" )
    #endif
#else

#endif

#ifdef  __cplusplus
extern "C" {
#endif

#define YY_P_INADDR_ANY INADDR_ANY
#define YY_P_INADDR_NONE INADDR_NONE

/* socket��ʼ�� */
extern int yy_p_socket_init();

/* socket��Դ�ͷ� */
extern int yy_p_socket_uninit();

/* af:AF_INET, AF_INET6 type:SOCK_DGRAM,SOCK_STREAM, SOCK_SEQPACKET protocol:Ĭ��0��TCP��IPPROTO_TCP, IPPROTO_UDP, IPPROTO_SCTP */

/* �����׽��� */
extern yy_p_socket_t yy_p_socket( int af, int type, int protocol );

/* �ر��׽ӿ� */
extern int yy_p_closesocket( yy_p_socket_t s );

/* �������� */
extern yy_p_socket_t yy_p_accept (yy_p_socket_t s, struct sockaddr *addr, yy_p_socklen_t *addrlen);

/* �׽ӿڰ� */
extern int yy_p_bind (yy_p_socket_t s, const struct sockaddr *addr, yy_p_socklen_t addrlen);

/* �����׽ӿ�(�����) */
extern int yy_p_listen(yy_p_socket_t s, int backlog );

/* �������� */
extern int yy_p_connect (yy_p_socket_t s, const struct sockaddr *addr,yy_p_socklen_t addrlen);

/* ����һ���������Ѿ����ӵ��׽��� */
extern int yy_p_socketpair( int domain, int type, int protocol, yy_p_socket_t s[2] );

/* ���������� */
extern int yy_p_gethostname( char * name, int namelen );

/* �����׽ӿ�ѡ�� */
extern int yy_p_setsockopt( yy_p_socket_t s, int level, int optname, const char *optval, yy_p_socklen_t optlen);

/* ��ȡ�׽ӿ�ѡ�� */
extern int yy_p_getsockopt( yy_p_socket_t s, int level, int optname, char *optval, yy_p_socklen_t *optlen);

/* �����׽ӿڰ󶨵ĵ�ַ */
extern int yy_p_getsockname( yy_p_socket_t s, struct sockaddr *addr, yy_p_socklen_t * addrlen);

/* ��ȡ�Զ˵�ַ */
extern int yy_p_getpeername( yy_p_socket_t s, struct sockaddr *addr, yy_p_socklen_t * addrlen);

/* ��ȡ����Ipv4��ַ�б��������ص�ַ127.0.0.1 */
extern int yy_p_get_localip_list_v4( yy_p_uint32 ip_list[], size_t max );

/* ���ھɰ汾��WINDOWS����֧�����������,��ʱ��ʹ�� */
#if YY_P_HAS_IPV6
    
/* �ַ���ip��ַת��Ϊ�����ַ */
    extern int yy_p_inet_pton(int af, const char *src, void *dst);

/* ip��ַת��Ϊ�ַ��� */
    extern const char *yy_p_inet_ntop(int af, const void *src, char *dst, yy_p_socklen_t cnt);
#endif

/* �����ʮ����ipv4��ַ�ַ���ת��Ϊ�����ֽ���Ķ�������ֵ��������ipv4��ַ��������������ϸ���ͣ� */
extern yy_p_uint32 yy_p_inet_addr( const char * cp );

/* �����ʮ����ipv4��ַת��Ϊ�����ֽ����ַ */
extern int yy_p_inet_aton( const char *cp, struct in_addr *inp );

/* �������ֽ����ipv4��ַת��Ϊ���ʮ���Ƶ�ַ��ʽ */
extern char * yy_p_inet_ntoa( const struct in_addr addr );

/* ���û�ȡ���׽ӿڷ�������д��ǣ�is_nonblock = 0,Ϊ�������� =1��Ϊ���� */
extern int yy_p_set_socket_nonblock( yy_p_socket_t s, int is_nonblock );

/* ��ȡ�׽ӿڴ��� */
extern int yy_p_get_socket_error( yy_p_socket_t s );

/* ͨ����������ȡ������Ϣ����Ҫ��Ip��ַ)��������ipv4 */
extern struct hostent *yy_p_gethostbyname (const char *name);

/* ͨ����������ȡip��ַ��������ipv4 */
extern yy_p_uint32 yy_p_get_dns_ipv4( const char * dns );

/* �������� */
extern ssize_t yy_p_send( yy_p_socket_t s, const void * buf, size_t len, int flags );

/* ������Ŀ�ĵ�ַ�������ݣ�������δ�������ӣ���UDP */
extern ssize_t yy_p_sendto( yy_p_socket_t s, const void * buf, size_t len, int flags, const struct sockaddr *to, yy_p_socklen_t tolen );

/* �������ݣ���yy_p_send��Ӧ */
extern ssize_t yy_p_recv(yy_p_socket_t s, void *buf, size_t len, int flags );

/* �������ݣ�������δ�������ӣ���yy_p_sendto��Ӧ */
extern ssize_t yy_p_recvfrom(yy_p_socket_t s, void *buf, size_t len, int flags,  struct sockaddr *addr, yy_p_socklen_t *addrlen );

/* ��·��д���� */
extern int yy_p_select(int width, fd_set *rfds, fd_set *wfds, fd_set *efds, const yy_p_timeval_t *tv);

/* ��¡�ļ����������� */
extern int yy_p_fd_set_copy( fd_set *t ,const fd_set * s );

extern int yy_p_socket_validation_test();

#ifdef  __cplusplus
}
#endif


#endif
