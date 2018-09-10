#ifndef YY_F_ALLOC_H
#define YY_F_ALLOC_H
#include "yy_p_type.h"
#include "yy_p_memory.h"
#include "yy_p_assert.h"
#include "yy_p_test.h"
#include "yy_e_memcheck.h"

/**
*   �ڴ����,ģ��C++���
*   ��16λͳһʹ��,��16λ������ÿ�����Գ��Լ�ʹ��
*	�ڴ��ͨ�ýṹ���ӿڶ��壺added by gaoqiang, 2015-06-10
*/

#define YY_F_ALLOC_FLAG_NULL	0x0000000	//������
#define YY_F_ALLOC_FLAG_LOCK    0x00000001	//�ش��� 
#define YY_F_ALLOC_FLAG_GBASE   0x00000002  //�˹���ʹ��YY_E_MEMORY_CHECK
#define YY_F_ALLOC_FLAG_GDATA   0x00000004	//�ض��ڴ�д������о����ܵ�У��,������ʵ����ȷ���ǲ���ʵ��ȫ������

/* �ص�״̬ͳ�� */
typedef struct yy_f_alloc_stat_s{
    void * alloc_ptr;			           //�ػ�׼ָ��
    char alloc_type[16];                   //�ص���������,3���ַ�
    yy_p_uint32 alloc_flag;                //��׼����
    
    size_t max_size;                       //�����Է���Ŀռ�,0Ϊ������
    size_t malloced_size;                  //�Ѿ���ϵͳ�����˵Ŀռ�
    size_t used_size;                      //�Ѿ���ʹ���˵�

    size_t malloc_success_count;			/* ����ɹ����� */
    size_t malloc_failure_count;			/* ����ʧ�ܴ��� */
    size_t free_success_count;				/* �ͷųɹ����� */
    size_t free_failure_count;				/* �ͷ�ʧ�ܴ��� */
	size_t error_count; 				/* ������� */
	int last_errno;							/* ���һ�δ����� */
}yy_f_alloc_stat_t;

/* ����ָ�룺�ͷ��ڴ�ؼ���Ӧ���ݽṹ */
typedef void (*yy_f_alloc_release_t)(void * thiz );

/* ����ָ�룺���ڴ�ط����ڴ�� */
typedef void * (*yy_f_alloc_malloc_t)(void * thiz, size_t size );

/* ����ָ�룺���ڴ��黹���ڴ�� */
typedef void (*yy_f_alloc_free_t)( void * thiz, void * p );

/* ����ָ�룺��ȡ�ڴ�ػ�����Ϣ��ʹ�������д���ַ������� */
typedef int (*yy_f_alloc_desc_t)(void * thiz, char * desc, size_t size );

/* ����ָ�룺��ȡ�ڴ��ͳ����Ϣ��������Ϣ�ͳ�ʹ�����ͳ�ƣ� */
typedef int (*yy_f_alloc_get_stat_t)(void * thiz, yy_f_alloc_stat_t * stat );

/* �����ӿڽṹ���� */
typedef struct yy_f_alloc_op_s{	
	char alloc_type[16];					/* �����ͻ����� */
    yy_f_alloc_release_t f_realse;			/* �ͷ��ڴ�ؼ���Ӧ���ݽṹ */
	yy_f_alloc_malloc_t f_malloc;			/* ���ڴ�ط����ڴ�� */
	yy_f_alloc_free_t f_free;				/* ���ڴ��黹���ڴ�� */
    yy_f_alloc_desc_t f_desc;				/* ��ȡ�ڴ�ػ�����Ϣ��ʹ�������д���ַ������� */
    yy_f_alloc_get_stat_t f_stat;			/* ��ȡ�ڴ��ͳ����Ϣ��������Ϣ�ͳ�ʹ�����ͳ�ƣ� */
}yy_f_alloc_op_t;

/* �ڴ�������ṹ�� */
typedef struct yy_f_alloc_s{
	void * thiz;							/* �ض��ڴ�������ṹָ�� */
	yy_f_alloc_op_t * op;					/* ���ڴ��������Ӧ�Ĺ����ӿڽṹָ�� */
}yy_f_alloc_t;

#define YY_F_ALLOC_MALLOC( alloc, size )        (alloc)->op->f_malloc( (alloc)->thiz, size )		/* ���ڴ�ط����ڴ��� */
#define YY_F_ALLOC_FREE( alloc, ptr )           (alloc)->op->f_free( (alloc)->thiz, ptr )			/* �黹�ڴ����ڴ�غ� */
#define YY_F_ALLOC_RELEASE( alloc )             (alloc)->op->f_realse( (alloc)->thiz )				/* �ͷ��ڴ�ؼ����ݽṹ�� */
#define YY_F_ALLOC_DESC( alloc, desc, size )    (alloc)->op->f_desc( (alloc)->thiz, desc, size )	/* ��ȡ�ڴ�ػ�����Ϣ��ʹ��������ַ������ */
#define YY_F_ALLOC_STAT( alloc, stat )          (alloc)->op->f_stat( (alloc)->thiz, stat )			/* ��ȡ�ڴ�ػ�����Ϣ��ʹ�����ͳ�ƺ� */


/* C����ʱ���malloc,free��װ */
/* �õ��ڴ������ */
extern yy_f_alloc_t * yy_f_alloc_get_c();

/* �����Զ���صķ�װ,�ṩһ��ȫ�ֵ��ڴ��滻�� */
extern yy_f_alloc_t * yy_f_alloc_get_my();

/* ��ʽ������ڴ����info  */
extern int yy_f_alloc_show_info( char * info, size_t size, const yy_f_alloc_stat_t * stat );

extern int yy_f_alloc_validation_test();
#endif
