#ifndef YY_P_REACTOR_EPOLL_H
#define YY_P_REACTOR_EPOLL_H
#include "yy_f_reactor_imp_if.h"
#if YY_P_IS_NIX
extern yy_f_reactor_imp_if_t * yy_f_reactor_epoll_create( size_t max_fd_size, struct yy_f_reactor_imp_cb_s * imp_cb );
#endif
#endif
