#ifndef YY_S_LIST_H
#define YY_S_LIST_H
#include "yy_f_alloc.h"
/**
*   设计思想参考至LINUX LIST,接口参考STL
*   每一个结点需要二个指针大小的空间,用于存储相关链表
*/


/* 链表数据结点地址，n为链表结点（结点与数据在相邻的内存块） */
#define YY_S_LIST_DATA_PTR( n ) (void *)((char *)(n)+sizeof(yy_s_list_node_t) )

typedef struct yy_s_list_node_s{
    struct yy_s_list_node_s * prev;
    struct yy_s_list_node_s * next;
}yy_s_list_node_t;

typedef struct yy_s_list_s{
    YY_E_MEM_MAGIC_PREFIX_DEFINE;
    yy_f_alloc_t * alloc_thiz;			/* 本结构体内存分配器 */
    yy_f_alloc_t * alloc_list_node;		/* 链表结点内存分配器 */
    yy_s_list_node_t head;				/* 链表头 */
    size_t node_data_len;               /* 每个结点包含的数据长度 */
    size_t node_size_aligned;           /* 内存对齐后的链表结点大小 */
    size_t max_node_num;				/* 最大链表结点数量 */
    size_t used_node_num;				/* 当前链表结点数量 */
    YY_E_MEM_MAGIC_SUFFIX_DEFINE;
}yy_s_list_t;

/* 回调函数，结点插入比较函数 */
typedef int (*yy_s_list_node_sort_cmp_t)( yy_s_list_t * l, yy_s_list_node_t * left, yy_s_list_node_t * right );

/* 创建链表 */
extern yy_s_list_t * yy_s_list_create( size_t max_node_num, size_t data_len, yy_f_alloc_t * alloc_list_node, yy_f_alloc_t * alloc_thiz );

/* 销毁链表 */
extern void yy_s_list_destroy( yy_s_list_t * l );

/* 链表克隆 */
extern yy_s_list_t * yy_s_list_clone( yy_s_list_t * l );

/* 返回链表结点数 */
extern size_t yy_s_list_size( yy_s_list_t * l );

/* 删除结点 */
extern yy_s_list_node_t * yy_s_list_erase( yy_s_list_t * l, yy_s_list_node_t * n );

/* 使用指定比较函数对整个链表排序 */
extern void yy_s_list_sort( yy_s_list_t * l, yy_s_list_node_sort_cmp_t func_cmp );

/* 结点插入（函数内会为data_in分配内存） */
extern yy_s_list_node_t * yy_s_list_push_back(  yy_s_list_t * l, const void * data_in );

/* 结点插入，指定数据长度（函数内会为data_in分配内存） */
extern yy_s_list_node_t * yy_s_list_push_back2(  yy_s_list_t * l, const void * data_in, size_t in_len );

/* 结点插入，指定数据长度，结点数据为字符串（函数内会为data_in分配内存） */
extern yy_s_list_node_t * yy_s_list_push_back3(  yy_s_list_t * l, const void * data_in, size_t in_len );

/* 结点数据长度 */
extern size_t yy_s_list_data_len( yy_s_list_t * l );

/* 删除链表头结点（先进先出） */
extern void yy_s_list_pop_front( yy_s_list_t * l );

/* 返回n结点的前一个结点 */
extern yy_s_list_node_t * yy_s_list_prev( yy_s_list_t * l, yy_s_list_node_t * n );

/* 返回n结点的下一个结点 */
extern yy_s_list_node_t * yy_s_list_next( yy_s_list_t * l, yy_s_list_node_t * n );

/* 返回第一个结点 */
extern yy_s_list_node_t * yy_s_list_first( yy_s_list_t * l );

/* 返回最后一个结点 */
extern yy_s_list_node_t * yy_s_list_last( yy_s_list_t * l );

/* 随机返回一个结点 */
extern yy_s_list_node_t * yy_s_list_rand( yy_s_list_t * l );

/* 删除所有结点 */
extern void yy_s_list_clear( yy_s_list_t * l );

/* 返回结点数据地址 */
extern void * yy_s_list_data_ptr( yy_s_list_t *l, yy_s_list_node_t * n );

/* 从结点读取数据，写入data_out */
extern int yy_s_list_read_data( yy_s_list_t *l, yy_s_list_node_t * n, void * data_out );

/* 向结点写数据 */
extern int yy_s_list_write_data( yy_s_list_t *l, yy_s_list_node_t * n, const void * data_in );

extern int yy_s_list_validation_test();
#endif
