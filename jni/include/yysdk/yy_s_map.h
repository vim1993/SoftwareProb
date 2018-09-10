#ifndef YY_S_MAP_H
#define YY_S_MAP_H
#include "yy_f_alloc.h"
#include "yy_f_ref_count.h"

/**   
*	�Ժ����ʵ��map
*	��������ԣ�
*    1��ÿ�����Ҫô�Ǻ�ģ�Ҫô�Ǻڵġ�
*    2��������Ǻڵġ�
*    3��ÿ��Ҷ��㣬���ս�㣨NIL���Ǻڵġ�
*    4�����һ������Ǻ�ģ���ô�����������Ӷ��Ǻڵġ�
*    5����ÿ����㣬�Ӹý�㵽�������������·���ϰ�����ͬ��Ŀ�ĺڽ�㡣
*
*    ���ú������Ϊ�˲��ҷ��㣬��Ϊ����ͨ�����£�����һ����������Ҫ O(n)��ʱ�临��
*    �ȣ��������ȴʼ��Ϊ O��ln n��
*/


/* map��key����һ����㣩��λ�� */
#define YY_S_MAP_FIRST_PTR( m, n ) (void *)((char *)n+(m)->node_head_size_aligned )
/* map��value���ڶ�����㣩��λ�� */
#define YY_S_MAP_SECOND_PTR( m, n ) (void *)((char *)n+(m)->node_head_size_aligned+(m)->first_size_aligned )

/* ��ȡkey */
#define YY_S_MAP_FIRST_R( m, n, p ) do{ yy_p_memcpy( p, YY_S_MAP_FIRST_PTR( m, n ), (m)->first_size ); }while(0)
/* дvalue */
#define YY_S_MAP_SECOND_W( m, n, p ) do{ yy_p_memcpy( YY_S_MAP_SECOND_PTR( m, n ), p, (m)->second_size ); }while(0)
/* ��value */
#define YY_S_MAP_SECOND_R( m, n, p ) do{ yy_p_memcpy( p, YY_S_MAP_SECOND_PTR( m, n ), (m)->second_size ); }while(0)

/* �ص�������map������ʱ��key�ȽϺ��� */
typedef int (*yy_s_map_nodecmp_func_t)(const void * left_first_ptr, const void * right_first_ptr );

/* �������㶨�� */
typedef struct yy_s_map_node_s{
    struct yy_s_map_node_s * rb_left;			/* ���ӽ�� */
    struct yy_s_map_node_s * rb_right;			/* ���ӽ�� */
    struct yy_s_map_node_s * rb_parent;			/* ����� */
    yy_p_intat rb_color;						/* �����ɫ */
	//2015/10/08 sk:Ϊ������hash_map����Ҫ������һ�����ڵ���û�����ָ��
	void * hash_table_ptr;						/* ָ��hash��ڵ��ָ�� */
}yy_s_map_node_t;


typedef struct yy_s_map_s{
    YY_E_MEM_MAGIC_PREFIX_DEFINE;
    YY_E_OBJ_MAGIC_DEFINE;
    yy_s_map_node_t * rb_node;					/* map����� */
    yy_s_map_nodecmp_func_t f_nodecmp;			/* ������ʱ��key�ȽϺ��� */
    size_t used_node_num;						/* ����� */
    size_t max_node_num;						/* map��������� */
    yy_f_alloc_t * alloc_map_node;				/* map��node���ڴ������ */
    yy_f_alloc_t * alloc_thiz;					/* ���ṹ���ڴ������ */
    size_t first_size;							/* �����key�Ĵ�С */
    size_t second_size;							/* �����value�Ĵ�С */
    size_t first_size_aligned;					/* �����key�ڴ�����Ĵ�С */
    size_t second_size_aligned;					/* �����value�ڴ�����Ĵ�С */
    size_t node_size_aligned;					/* map���(yy_s_map_node_t+ key + value)�ڴ�����Ĵ�С */
    size_t node_head_size_aligned;				/* ���ͷ(yy_s_map_node_t)�ڴ�����Ĵ�С */

    int is_use_ref;                             //�Ƿ�ʹ�����ü�������ָ���MAP�����ü���
    yy_f_ref_count_t ref;                       //���ʹ�ã��������ü���COUNT
    YY_E_MEM_MAGIC_SUFFIX_DEFINE ;
}yy_s_map_t;


/* ����map, �����ü��� */
extern yy_s_map_t * yy_s_map_create_with_ref( size_t max_node_num, size_t first_size, size_t second_size, yy_s_map_nodecmp_func_t f_nodecmp, yy_f_alloc_t * alloc_map_node, yy_f_alloc_t * alloc_thiz );

/* ǳ���ƣ�������ü���*/
extern yy_s_map_t * yy_s_map_duplicate( yy_s_map_t * m );

/* �������ʱ���������ü�����  */
extern void yy_s_map_release( yy_s_map_t * m );




/* ����map */
extern yy_s_map_t * yy_s_map_create( size_t max_node_num, size_t first_size, size_t second_size, yy_s_map_nodecmp_func_t f_nodecmp, yy_f_alloc_t * alloc_map_node, yy_f_alloc_t * alloc_thiz );


/* ����map */
extern void yy_s_map_destroy( yy_s_map_t * m );




/* ��ʼ��map */
extern int yy_s_map_init( yy_s_map_t * m, size_t max_node_num, size_t first_size, size_t second_size, yy_s_map_nodecmp_func_t f_nodecmp, yy_f_alloc_t * alloc_map_node );

/* �ͷ�map��Դ */
extern void yy_s_map_uninit( yy_s_map_t * m );

/* ��ӽ�� */
extern yy_s_map_node_t * yy_s_map_insert( yy_s_map_t * m, const void * first_ptr, const void * second_ptr );

/* ɾ����� */
extern yy_s_map_node_t * yy_s_map_erase( yy_s_map_t * m, yy_s_map_node_t * n );

/* ������н�� */
extern void yy_s_map_clear( yy_s_map_t * m );

/* ���ص�һ����� */
extern yy_s_map_node_t * yy_s_map_first( yy_s_map_t * m );

/* �������һ����� */
extern yy_s_map_node_t * yy_s_map_last( yy_s_map_t * m );

/* ����node������һ����� */
extern yy_s_map_node_t * yy_s_map_next( yy_s_map_t * m, yy_s_map_node_t * node );

/* ����node������һ����� */
extern yy_s_map_node_t * yy_s_map_prev( yy_s_map_t * m, yy_s_map_node_t * node );

/* ����map������ */
extern size_t yy_s_map_size( yy_s_map_t * m );

/* ������������ҵ�һ��С��first_ptr�Ľ�� */
extern yy_s_map_node_t * yy_s_map_lower_bound_by_firstptr( yy_s_map_t * m, const void * first_ptr );

/* ͨ��keyָ����ҽ�� */
extern yy_s_map_node_t * yy_s_map_find_by_firstptr( yy_s_map_t * m, const void * first_ptr );

/* ͨ��keyֵ���ҽ�� */
extern yy_s_map_node_t * yy_s_map_find_by_firstvalue( yy_s_map_t * m, const void * first_value );




extern int yy_s_map_validation_test(void);

#endif
