#ifndef YY_F_REACTOR_IMP_IF_H
#define YY_F_REACTOR_IMP_IF_H
#include "yy_p_socket.h"
#include "yy_p_time.h"
#include "yy_e_memcheck.h"
#include "yy_s_lxlist.h"
struct yy_f_reactor_s;
struct yy_f_event_handler_s;
struct yy_f_reactor_imp_if_s;
struct yy_f_reactor_imp_cb_s;

/* 
*本头文件定义select模式和epoll模式反应器的公共接口和宏
*added by gaoqiang, 2015-08-03
*/

/* 激活事件回调函数（主要是将事件挂载到反应器的活跃链表） */
typedef int (*yy_f_reactor_active_event_t)(struct yy_f_reactor_s *r, struct yy_f_event_handler_s * ev, int mask );

/* 激活事件的回调结构 */
typedef struct yy_f_reactor_imp_cb_s{
    struct yy_f_reactor_s * r;			/* 反应器 */
    yy_f_reactor_active_event_t f_active_event;	/* 激活事件的回调函数 */
}yy_f_reactor_imp_cb_t;

/* 释放反应器 */
typedef void (*yy_f_reactor_imp_release_t)(void * thiz );

/* 添加事件处理器到反应器 */
typedef int (*yy_f_reactor_imp_add_event_t)(void * thiz, struct yy_f_event_handler_s * ev );

/* 从反应器中移除事件处理器 */
typedef int (*yy_f_reactor_imp_remove_event_t)(void * thiz, struct yy_f_event_handler_s * ev );

/* 分派（或称作触发）事件处理器 */
typedef int (*yy_f_reactor_imp_dispath_event_t)(void * thiz, const yy_p_timeval_t * tv  );

/* 反应器实现公共接口定义：这里所述反应器实现即指select模型或epoll模型的IO多路复用 */
typedef struct yy_f_reactor_imp_if_s{
    char name[16];				/* 反应器名字 */
    void * thiz;					/* 反应器实现的指针，如select或epoll反应器指针 */
    //some func...
    yy_f_reactor_imp_release_t f_release;	/* 释放反应器实现 */
    yy_f_reactor_imp_add_event_t f_add_event;	/* 添加事件处理器到反应器实现上 */
    yy_f_reactor_imp_remove_event_t f_remove_event;	/* 从反应器实现上移除事件处理器 */
    yy_f_reactor_imp_dispath_event_t f_dispath_event;	/* 分派（或称作触发）事件处理器 */
}yy_f_reactor_imp_if_t;

/* 公共接口对应的宏定义，select和epoll的实现均可使用这些宏 */
#define YY_F_REACTOR_IMP_RELEASE( a )           (a)->f_release( (a)->thiz )
#define YY_F_REACTOR_IMP_ADD_EVENT( a, ev )     (a)->f_add_event( (a)->thiz,  ev )
#define YY_F_REACTOR_IMP_REMOVE_EVENT( a, ev )  (a)->f_remove_event( (a)->thiz,  ev )
#define YY_F_REACTOR_IMP_DISPATH_EVENT( a, tv ) (a)->f_dispath_event( (a)->thiz, tv )
/*create sample
extern yy_f_reactor_imp_if_t * yy_f_reactor_impl_create_select( size_t max_fd_size, struct yy_f_reactor_imp_cb_s * imp_cb );
*/

#endif
