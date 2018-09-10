#ifndef YY_P_UNISTD_H
#define YY_P_UNISTD_H
#include "yy_p_config.h"
#include "yy_p_type.h"
#if YY_P_IS_NIX
	#include <unistd.h>
#endif

/* ��pathָ���ĳ����滻��ǰ���������ģ������µĳ��򣬽���PID���� */
extern int yy_p_execv( const char * path, char * const argv[] );

/* �����ӽ��̣��ӽ����Ǹ����̵ĸ��� */
extern yy_p_pid_t yy_p_fork();

/* ��ֹ���̣��ر������ļ������� */
extern void yy_p_exit( int s );

/* ��������ܴ򿪵��ļ����������� */
extern int yy_p_getdtablesize();

/*  �õ���ǰ���̵Ľ���ID */
extern yy_p_pid_t yy_p_getpid();
#endif
