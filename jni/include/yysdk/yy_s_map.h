#ifndef YY_S_MAP_H
#define YY_S_MAP_H
#include "yy_f_alloc.h"
#include "yy_f_ref_count.h"

/**   
*	以红黑树实现map
*	红黑树特性：
*    1）每个结点要么是红的，要么是黑的。
*    2）根结点是黑的。
*    3）每个叶结点，即空结点（NIL）是黑的。
*    4）如果一个结点是红的，那么它的俩个儿子都是黑的。
*    5）对每个结点，从该结点到其子孙结点的所有路径上包含相同数目的黑结点。
*
*    运用红黑树是为了查找方便，因为在普通的树下，查找一个结点最坏的需要 O(n)的时间复杂
*    度，而红黑树却始终为 O（ln n）
*/


/* map中key（第一个结点）的位置 */
#define YY_S_MAP_FIRST_PTR( m, n ) (void *)((char *)n+(m)->node_head_size_aligned )
/* map中value（第二个结点）的位置 */
#define YY_S_MAP_SECOND_PTR( m, n ) (void *)((char *)n+(m)->node_head_size_aligned+(m)->first_size_aligned )

/* 读取key */
#define YY_S_MAP_FIRST_R( m, n, p ) do{ yy_p_memcpy( p, YY_S_MAP_FIRST_PTR( m, n ), (m)->first_size ); }while(0)
/* 写value */
#define YY_S_MAP_SECOND_W( m, n, p ) do{ yy_p_memcpy( YY_S_MAP_SECOND_PTR( m, n ), p, (m)->second_size ); }while(0)
/* 读value */
#define YY_S_MAP_SECOND_R( m, n, p ) do{ yy_p_memcpy( p, YY_S_MAP_SECOND_PTR( m, n ), (m)->second_size ); }while(0)

/* 回调函数，map结点插入时的key比较函数 */
typedef int (*yy_s_map_nodecmp_func_t)(const void * left_first_ptr, const void * right_first_ptr );

/* 红黑树结点定义 */
typedef struct yy_s_map_node_s{
    struct yy_s_map_node_s * rb_left;			/* 左子结点 */
    struct yy_s_map_node_s * rb_right;			/* 右子结点 */
    struct yy_s_map_node_s * rb_parent;			/* 父结点 */
    yy_p_intat rb_color;						/* 结点颜色 */
	//2015/10/08 sk:为了满足hash_map的需要，增加一个本节点的用户数据指针
	void * hash_table_ptr;						/* 指向hash表节点的指针 */
}yy_s_map_node_t;


typedef struct yy_s_map_s{
    YY_E_MEM_MAGIC_PREFIX_DEFINE;
    YY_E_OBJ_MAGIC_DEFINE;
    yy_s_map_node_t * rb_node;					/* map根结点 */
    yy_s_map_nodecmp_func_t f_nodecmp;			/* 结点插入时的key比较函数 */
    size_t used_node_num;						/* 结点数 */
    size_t max_node_num;						/* map的最大结点数 */
    yy_f_alloc_t * alloc_map_node;				/* map中node的内存分配器 */
    yy_f_alloc_t * alloc_thiz;					/* 本结构的内存分配器 */
    size_t first_size;							/* 结点中key的大小 */
    size_t second_size;							/* 结点中value的大小 */
    size_t first_size_aligned;					/* 结点中key内存对齐后的大小 */
    size_t second_size_aligned;					/* 结点中value内存对齐后的大小 */
    size_t node_size_aligned;					/* map结点(yy_s_map_node_t+ key + value)内存对齐后的大小 */
    size_t node_head_size_aligned;				/* 结点头(yy_s_map_node_t)内存对齐后的大小 */

    int is_use_ref;                             //是否使用引用计数，是指这个MAP的引用计数
    yy_f_ref_count_t ref;                       //如果使用，这是引用计数COUNT
    YY_E_MEM_MAGIC_SUFFIX_DEFINE ;
}yy_s_map_t;


/* 创建map, 带引用计数 */
extern yy_s_map_t * yy_s_map_create_with_ref( size_t max_node_num, size_t first_size, size_t second_size, yy_s_map_nodecmp_func_t f_nodecmp, yy_f_alloc_t * alloc_map_node, yy_f_alloc_t * alloc_thiz );

/* 浅复制，添加引用计数*/
extern yy_s_map_t * yy_s_map_duplicate( yy_s_map_t * m );

/* 如果创建时，带有引用计数，  */
extern void yy_s_map_release( yy_s_map_t * m );




/* 创建map */
extern yy_s_map_t * yy_s_map_create( size_t max_node_num, size_t first_size, size_t second_size, yy_s_map_nodecmp_func_t f_nodecmp, yy_f_alloc_t * alloc_map_node, yy_f_alloc_t * alloc_thiz );


/* 销毁map */
extern void yy_s_map_destroy( yy_s_map_t * m );




/* 初始化map */
extern int yy_s_map_init( yy_s_map_t * m, size_t max_node_num, size_t first_size, size_t second_size, yy_s_map_nodecmp_func_t f_nodecmp, yy_f_alloc_t * alloc_map_node );

/* 释放map资源 */
extern void yy_s_map_uninit( yy_s_map_t * m );

/* 添加结点 */
extern yy_s_map_node_t * yy_s_map_insert( yy_s_map_t * m, const void * first_ptr, const void * second_ptr );

/* 删除结点 */
extern yy_s_map_node_t * yy_s_map_erase( yy_s_map_t * m, yy_s_map_node_t * n );

/* 清除所有结点 */
extern void yy_s_map_clear( yy_s_map_t * m );

/* 返回第一个结点 */
extern yy_s_map_node_t * yy_s_map_first( yy_s_map_t * m );

/* 返回最后一个结点 */
extern yy_s_map_node_t * yy_s_map_last( yy_s_map_t * m );

/* 返回node结点的下一个结点 */
extern yy_s_map_node_t * yy_s_map_next( yy_s_map_t * m, yy_s_map_node_t * node );

/* 返回node结点的上一个结点 */
extern yy_s_map_node_t * yy_s_map_prev( yy_s_map_t * m, yy_s_map_node_t * node );

/* 返回map结点个数 */
extern size_t yy_s_map_size( yy_s_map_t * m );

/* 按中序遍历查找第一个小于first_ptr的结点 */
extern yy_s_map_node_t * yy_s_map_lower_bound_by_firstptr( yy_s_map_t * m, const void * first_ptr );

/* 通过key指针查找结点 */
extern yy_s_map_node_t * yy_s_map_find_by_firstptr( yy_s_map_t * m, const void * first_ptr );

/* 通过key值查找结点 */
extern yy_s_map_node_t * yy_s_map_find_by_firstvalue( yy_s_map_t * m, const void * first_value );




extern int yy_s_map_validation_test(void);

#endif
