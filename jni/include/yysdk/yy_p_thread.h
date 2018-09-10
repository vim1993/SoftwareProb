#ifndef YY_P_THREAD_H
#define YY_P_THREAD_H
//线程库, WTHREAD(WIN32), PTHREAD, Vxworks
#include "yy_p_config.h"
#include "yy_p_type.h"
#include "yy_p_test.h"

#ifdef  __cplusplus
extern "C" {
#endif

//相关定义请参照ACE
#if YY_P_IS_WTHREAD
    #if YY_P_IS_WINCE
		    typedef DWORD yy_p_thr_ret_t;
		    typedef DWORD yy_p_thr_id_t;
    #else
		    #include <process.h>
		    typedef unsigned int yy_p_thr_ret_t;
		    typedef unsigned int yy_p_thr_id_t;
    #endif

	#define YY_P_THR_CALL __stdcall
	typedef HANDLE yy_p_thr_handle_t;
	typedef void* yy_p_thr_arg_t;
    #define YY_P_INVALID_THR_HANDLE INVALID_HANDLE_VALUE
    #define YY_P_PRI_THR_ID "%u"
#elif YY_P_IS_PTHREAD
	#include <pthread.h>
	typedef void* yy_p_thr_ret_t;
	typedef void* yy_p_thr_arg_t;
	typedef pthread_t yy_p_thr_id_t;
	typedef pthread_t yy_p_thr_handle_t;
	#define YY_P_THR_CALL 
    #define YY_P_INVALID_THR_HANDLE (yy_p_thr_handle_t)-1
    #define YY_P_PRI_THR_ID "%u"
#else
    typedef int yy_p_thr_ret_t;
	typedef void* yy_p_thr_arg_t;
	typedef int yy_p_thr_id_t;
	typedef int yy_p_thr_handle_t;
	#define YY_P_THR_CALL 
    #define YY_P_INVALID_THR_HANDLE -1
    #define YY_P_PRI_THR_ID "%d"
#endif

#define YY_P_THR_RET_IS_TYPE 1

#define YY_P_INVALID_THR_ID (yy_p_thr_id_t)-1
typedef yy_p_thr_ret_t (YY_P_THR_CALL *yy_p_thr_func_t )(yy_p_thr_arg_t);

//锁
//默认为不可重入锁
#define YY_P_THR_MUTEX_LOCK_MODE_DEFAULT   0  
//假锁,不起实际的作用
#define YY_P_THR_MUTEX_LOCK_MODE_FAKE      157
#if YY_P_IS_WTHREAD
	typedef struct yy_p_thr_mutex_s{		
        CRITICAL_SECTION lock;
        int lock_mode;
		int state;
		
	}yy_p_thr_mutex_t;

	#define YY_P_THR_PRIORITY_ABOVE_NORMAL THREAD_PRIORITY_ABOVE_NORMAL
#elif YY_P_IS_PTHREAD
	typedef struct yy_p_thr_mutex_s{
		pthread_mutex_t lock;
        int lock_mode;
		int state;		
	}yy_p_thr_mutex_t;
	#define YY_P_THR_PRIORITY_ABOVE_NORMAL 0
#else
    typedef struct yy_p_thr_mutex_s{
		volatile int calls;
        int lock_mode;
		int state;		
	}yy_p_thr_mutex_t;
	#define YY_P_THR_PRIORITY_ABOVE_NORMAL 0
#endif
    
    extern int yy_p_thr_create( yy_p_thr_id_t * thr_id, yy_p_thr_handle_t * thr_handle, yy_p_thr_func_t thr_func, void * arg_list, long flags ,void * stack_buf, size_t stacksize );
	extern void yy_p_thr_exit( yy_p_thr_ret_t status );
	extern yy_p_thr_id_t yy_p_thr_self();
	extern int yy_p_thr_join( yy_p_thr_handle_t thr_handle, int wait_ms, yy_p_thr_ret_t * status );
    extern int yy_p_thr_terminate( yy_p_thr_handle_t thr_handle, yy_p_thr_ret_t status );
    extern int yy_p_thr_equal( yy_p_thr_id_t t1, yy_p_thr_id_t t2 );


	extern int yy_p_thr_mutex_init( yy_p_thr_mutex_t *m, int lock_mode );
	extern int yy_p_thr_mutex_uninit( yy_p_thr_mutex_t *m );
	extern int yy_p_thr_mutex_lock( yy_p_thr_mutex_t *m );
	extern int yy_p_thr_mutex_unlock( yy_p_thr_mutex_t *m );

    extern int yy_p_thr_mutex_validation_test();
#ifdef  __cplusplus
}
#endif

#endif
