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
	#define YY_P_NONBLOCK O_NDELAY		/* O_NONBLOCK和O_NDELAY都代表非阻塞 */
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

/* socket初始化 */
extern int yy_p_socket_init();

/* socket资源释放 */
extern int yy_p_socket_uninit();

/* af:AF_INET, AF_INET6 type:SOCK_DGRAM,SOCK_STREAM, SOCK_SEQPACKET protocol:默认0，TCP，IPPROTO_TCP, IPPROTO_UDP, IPPROTO_SCTP */

/* 创建套接字 */
extern yy_p_socket_t yy_p_socket( int af, int type, int protocol );

/* 关闭套接口 */
extern int yy_p_closesocket( yy_p_socket_t s );

/* 接收连接 */
extern yy_p_socket_t yy_p_accept (yy_p_socket_t s, struct sockaddr *addr, yy_p_socklen_t *addrlen);

/* 套接口绑定 */
extern int yy_p_bind (yy_p_socket_t s, const struct sockaddr *addr, yy_p_socklen_t addrlen);

/* 监听套接口(服务端) */
extern int yy_p_listen(yy_p_socket_t s, int backlog );

/* 发起连接 */
extern int yy_p_connect (yy_p_socket_t s, const struct sockaddr *addr,yy_p_socklen_t addrlen);

/* 建立一对匿名的已经连接的套接字 */
extern int yy_p_socketpair( int domain, int type, int protocol, yy_p_socket_t s[2] );

/* 返回主机名 */
extern int yy_p_gethostname( char * name, int namelen );

/* 设置套接口选项 */
extern int yy_p_setsockopt( yy_p_socket_t s, int level, int optname, const char *optval, yy_p_socklen_t optlen);

/* 获取套接口选项 */
extern int yy_p_getsockopt( yy_p_socket_t s, int level, int optname, char *optval, yy_p_socklen_t *optlen);

/* 返回套接口绑定的地址 */
extern int yy_p_getsockname( yy_p_socket_t s, struct sockaddr *addr, yy_p_socklen_t * addrlen);

/* 获取对端地址 */
extern int yy_p_getpeername( yy_p_socket_t s, struct sockaddr *addr, yy_p_socklen_t * addrlen);

/* 获取本机Ipv4地址列表，包括本地地址127.0.0.1 */
extern int yy_p_get_localip_list_v4( yy_p_uint32 ip_list[], size_t max );

/* 由于旧版本的WINDOWS并不支持这二个特性,暂时不使用 */
#if YY_P_HAS_IPV6
    
/* 字符串ip地址转换为网络地址 */
    extern int yy_p_inet_pton(int af, const char *src, void *dst);

/* ip地址转换为字符串 */
    extern const char *yy_p_inet_ntop(int af, const void *src, char *dst, yy_p_socklen_t cnt);
#endif

/* 将点分十进制ipv4地址字符串转换为网络字节序的二进制数值，仅用于ipv4地址（见函数定义详细解释） */
extern yy_p_uint32 yy_p_inet_addr( const char * cp );

/* 将点分十进制ipv4地址转换为网络字节序地址 */
extern int yy_p_inet_aton( const char *cp, struct in_addr *inp );

/* 将网络字节序的ipv4地址转换为点分十进制地址形式 */
extern char * yy_p_inet_ntoa( const struct in_addr addr );

/* 设置或取消套接口非阻塞读写标记，is_nonblock = 0,为非阻塞， =1，为阻塞 */
extern int yy_p_set_socket_nonblock( yy_p_socket_t s, int is_nonblock );

/* 获取套接口错误 */
extern int yy_p_get_socket_error( yy_p_socket_t s );

/* 通过主机名获取主机信息（主要是Ip地址)，仅用于ipv4 */
extern struct hostent *yy_p_gethostbyname (const char *name);

/* 通过主机名获取ip地址，仅用于ipv4 */
extern yy_p_uint32 yy_p_get_dns_ipv4( const char * dns );

/* 发送数据 */
extern ssize_t yy_p_send( yy_p_socket_t s, const void * buf, size_t len, int flags );

/* 用于向目的地址发送数据，适用于未建立连接，即UDP */
extern ssize_t yy_p_sendto( yy_p_socket_t s, const void * buf, size_t len, int flags, const struct sockaddr *to, yy_p_socklen_t tolen );

/* 接收数据，与yy_p_send对应 */
extern ssize_t yy_p_recv(yy_p_socket_t s, void *buf, size_t len, int flags );

/* 接收数据，适用于未建立连接，与yy_p_sendto对应 */
extern ssize_t yy_p_recvfrom(yy_p_socket_t s, void *buf, size_t len, int flags,  struct sockaddr *addr, yy_p_socklen_t *addrlen );

/* 多路读写复用 */
extern int yy_p_select(int width, fd_set *rfds, fd_set *wfds, fd_set *efds, const yy_p_timeval_t *tv);

/* 克隆文件描述符集合 */
extern int yy_p_fd_set_copy( fd_set *t ,const fd_set * s );

extern int yy_p_socket_validation_test();

#ifdef  __cplusplus
}
#endif


#endif
