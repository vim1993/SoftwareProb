#ifndef minidpi_h
#define minidpi_h

#include<stdint.h>
#include<sys/time.h>

//支持Android 4.4
//*****************重要提醒***********************
//抓包只针对一个网口，可以用set_cap_device设置或让其自选
//不支持动态的切换网口，如果网口变化，需要重新开始抓包
//***********************************************


struct pkthdr {
        struct timeval ts;   /* time stamp */
        uint32_t caplen;     /* length of portion present */
        uint32_t len;        /* length this packet (off wire) */
};

struct flow_key{
        uint32_t addr1;  //IP地址1
        uint32_t addr2;  //IP地址2
        uint16_t port1;  //IP地址1同端的端口
        uint16_t port2;  //IP地址2同端的端口
};

struct flow_stat{
        uint32_t start_time;  //连接开始时间，秒
        uint32_t pkt_count;   //包总数
        uint32_t last_pkt_time;  //最后一个包时间
        uint32_t last_stat_time; //最后一次上报stat时间
        uint32_t byte_count;   //连接字节总数
        uint32_t byte_count5m; //5秒内连接上字节总数
        uint32_t unorder[2]; //乱序包个数，分方向
        uint32_t retrans[2]; //重传包个数，分方向
};

struct sys_stat{
        uint32_t queue_full_cnt; //队列满的次数，即丢包个数。指从抓包后没有空间入到处理队列
        uint32_t enqueue_cnt;//加入到队列的包总数
        uint32_t dequeue_cnt;//从队列取出的包总数
        uint32_t empty_cnt;
        //---以上3个是实时更新，下面几个指标是阶段更新
        uint32_t start_time;//系统开始时间
        uint32_t stat_time;//取状态的时间，为了不受影响，底层是一段时间取一次，不是每次调用都取
        uint32_t recv_cnt;//收到了多少个包
        uint32_t drop_cnt;//处理丢了多少个包，指未能被抓到
        uint32_t ifdrop_cnt;//在网口上丢了多少包
};

enum event_type{
	  UNKONW_TRFFIC=0,
    HTTP=1,
    RTSP=2,
    TCP_RST=8,  //TCP连接收到RST标志时上报
    TCP_FIN=9,  //TCP连接收到FIN标志时上报
    TCP_ERR=10, //组包失败通知，停止顺序上报报文
    FLOW_TIMEOUT=40,//流超时结束时上报
    SYS_ERR=49, //系统错误，内存不足
    OTHER=0 //作为前一版定义，为兼容保留，后续移除
};

enum direction{
    DIR_ONE,  //方向标识，本机发往其它服务器的包
    DIR_TWO   //方向标识，其它服务器发往本机的包
};


//上报抓到的包
typedef int(*cap_callback)(const struct pkthdr *hdr, const unsigned char *pkt);

//上报流情况，5秒一次
typedef int(*stat_callback)(struct flow_key *key, struct flow_stat *stat);

//建立TCP连接后传内容时上报
//上报TCP_RST/TCP_FIN时，start为NULL,len为0
//返回值：0->不监测此连接，2->监测此连接，其它->同0处理。监测含义为顺序上报报文
typedef int(*event_callback)(struct flow_key *key, struct flow_stat *stat, const unsigned char *start, int len,enum event_type type);

//顺序上报报文
//返回值: 0->正常返回  1->终止监测此连接
typedef int(*content_callback)(struct flow_key *key,const struct pkthdr *hdr, const unsigned char *pkt, unsigned char * content_start, int len, enum direction dir);

//设置每流重组包缓存,默认5个
int set_flow_cache(int pkt);

//过滤规则，BPF语法，如 tcp and port 80 or 8080
int set_filter(char *buf);

///////////////////////////////////////////////////////////
//*以下四个回调函数不能阻塞，及时返回，以免影响抓包，影响会导致丢包*//
///////////////////////////////////////////////////////////

//对抓到的每个包，通过handle上报
int register_cap_handle(cap_callback handle);

//每个连接5秒钟上报一次
int register_stat_handle(stat_callback handle);

//对HTTP，请求或响应，回调
int register_event_handle(event_callback handle);

//对抓到的TCP有承载内容的第一个包，使用此接口上报
int register_content_handle(content_callback handle);

//开始抓包
int start_captrue();

//停止抓包
int stop_captrue();

//返回编译的日期时间，以便调试核对
char *get_version_info();

//返回系统信息，包括启动时间、丢包数、抓到的包数等
struct sys_stat* get_sys_stat();

struct sys_stat* get_rt_stat();

int set_cap_device(char *interface);

//设置抓包线程和处理线程间队列缓存大小
int set_queue_buffer_size(int size);

//重新获取IP信息，用于切换wifi后调用，以正确判断方向
int reinit_ip_info();

//取队列信息
char* get_queue_info();

#endif
