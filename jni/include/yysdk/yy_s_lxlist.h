#ifndef YY_S_LXLIST_H
#define YY_S_LXLIST_H
#include "yy_p_test.h"
#include "yy_p_type.h"
#include "yy_p_assert.h"
/**
*   参考自LINUX内核中关于链表的定义及使用,部分精简
*   链表头，链表两个概念，链表头即下面的结构体，主要用于管理链表
*/
typedef struct yy_s_lxlist_head_s{
	struct yy_s_lxlist_head_s *next;
	struct yy_s_lxlist_head_s *prev;
}yy_s_lxlist_head_t;

/* 置链表结点的前后指针为特殊值 */
#define YY_S_LXLIST_POSITION_PREV (yy_s_lxlist_head_t *)( sizeof(void *))
#define YY_S_LXLIST_POSITION_NEXT (yy_s_lxlist_head_t *)( 2*sizeof(void *))

/* 将链表头插入prev与next之间 */
extern void  yy_s_lxlist_add( yy_s_lxlist_head_t *new_n, yy_s_lxlist_head_t *prev, yy_s_lxlist_head_t *next );

/* 删除del_n链表头，并将prev和next连接起来 */
extern void yy_s_lxlist_del( yy_s_lxlist_head_t *del_n, yy_s_lxlist_head_t * prev, yy_s_lxlist_head_t * next);

/* 初始化链表头 */
#define YY_S_LXLIST_HEAD_INIT( a ) do{ (a)->next = (a)->prev = (a) ;}while(0)

/* 将链表头new_n插入到链表头l之后 */
#define YY_S_LXLIST_ADD_HEAD( l, new_n ) do{  yy_p_assert( l != new_n ); yy_s_lxlist_add( new_n, (l), (l)->next );}while(0)

/* 将链表头new_n插入到链表头l之前 */
#define YY_S_LXLIST_ADD_TAIL( l, new_n ) do{  yy_p_assert( l != new_n ); yy_s_lxlist_add( new_n, (l)->prev, (l) );}while(0)

/* 清除链表头指针 */
#define YY_S_LXLIST_CLR_NODE( n ) do{  yy_p_assert( n != NULL ); (n)->prev = YY_S_LXLIST_POSITION_PREV; (n)->next = YY_S_LXLIST_POSITION_NEXT; }while(0)

/* 清除del_n链表头，并将断链连接起来 */
#define YY_S_LXLIST_DEL( l, del_n ) do { yy_p_assert( (del_n) != NULL );yy_p_assert( (del_n) != l );yy_s_lxlist_del( (del_n), (del_n)->prev, (del_n)->next ); }while(0)

/* 判断链表头是否为空 */
#define YY_S_LXLIST_IS_EMPTY( l ) ( (l)->next == (l) )

/* 得到链表头链表的第一个节点，否则返回空  */
#define YY_S_LXLIST_FIRST( l ) ( ( (l)!= NULL && (l)->next != (l) )?(l)->next:NULL )

/*  得到n链表的下一个节点，否则返回空 */
#define YY_S_LXLIST_NEXT( l, n ) (( (l) != NULL && (n) != NULL && (n)->next != (l) )?(n)->next:NULL)

/* 如果ptr不为空，则返回member所属结构体指针，否则返回NULL */
#define YY_S_LXLIST_ENTRY( ptr, type, member) ( (ptr) != NULL ? ( YY_P_CONTAINER_OF( ptr, type, member ) ):NULL )

/**
*   l		链表头
*   type	节点实体类型
*   member  链表在节点中的成员名称
*/
/* 返回第一个结点指针 */
#define YY_S_LXLIST_FIRST_ENTRY( l, type, member) YY_S_LXLIST_ENTRY( (l)->next, type, member )

/*
*   l		链表头
*   type	节点实体类型
*   member  链表在节点中的成员名称
*/
/* 返回最后一个结点指针 */
#define YY_S_LXLIST_LAST_ENTRY( l, type, member)  YY_S_LXLIST_ENTRY( (l)->prev, type, member )



/** * list_for_each_entry_safe - iterate over list of given type safe against removal of list entry 
* @pos:    the type * to use as a loop cursor. 
* @tmp:    another type * to use as temporary storage 
* @l:      the head for your list. 
* @type:
* @member: the name of the list_struct within the struct. 
*/

/** 
*   pos是得到指向l->next的指针
*   tmp为相邻的下一个节点的指针
*   主要用于安全遍历链表 */
#define YY_S_LXLIST_FOR_EACH_ENTRY_SAFE(l ,pos, tmp, type, member)  for( pos = YY_S_LXLIST_ENTRY((l)->next, type, member),tmp = YY_S_LXLIST_ENTRY(pos->member.next, type, member); &pos->member != (l);pos = tmp, tmp = YY_S_LXLIST_ENTRY(tmp->member.next, type, member) )

extern int yy_s_lxlist_validation_test();
#endif
