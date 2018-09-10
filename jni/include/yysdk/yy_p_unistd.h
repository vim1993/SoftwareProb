#ifndef YY_P_UNISTD_H
#define YY_P_UNISTD_H
#include "yy_p_config.h"
#include "yy_p_type.h"
#if YY_P_IS_NIX
	#include <unistd.h>
#endif

/* 由path指定的程序替换当前进程上下文，运行新的程序，进程PID不变 */
extern int yy_p_execv( const char * path, char * const argv[] );

/* 创建子进程，子进程是父进程的副本 */
extern yy_p_pid_t yy_p_fork();

/* 终止进程，关闭所有文件描述符 */
extern void yy_p_exit( int s );

/* 进程最多能打开的文件描述符个数 */
extern int yy_p_getdtablesize();

/*  得到当前进程的进程ID */
extern yy_p_pid_t yy_p_getpid();
#endif
