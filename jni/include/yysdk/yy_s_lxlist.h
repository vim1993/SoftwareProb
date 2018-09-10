#ifndef YY_S_LXLIST_H
#define YY_S_LXLIST_H
#include "yy_p_test.h"
#include "yy_p_type.h"
#include "yy_p_assert.h"
/**
*   �ο���LINUX�ں��й�������Ķ��弰ʹ��,���־���
*   ����ͷ�����������������ͷ������Ľṹ�壬��Ҫ���ڹ�������
*/
typedef struct yy_s_lxlist_head_s{
	struct yy_s_lxlist_head_s *next;
	struct yy_s_lxlist_head_s *prev;
}yy_s_lxlist_head_t;

/* ���������ǰ��ָ��Ϊ����ֵ */
#define YY_S_LXLIST_POSITION_PREV (yy_s_lxlist_head_t *)( sizeof(void *))
#define YY_S_LXLIST_POSITION_NEXT (yy_s_lxlist_head_t *)( 2*sizeof(void *))

/* ������ͷ����prev��next֮�� */
extern void  yy_s_lxlist_add( yy_s_lxlist_head_t *new_n, yy_s_lxlist_head_t *prev, yy_s_lxlist_head_t *next );

/* ɾ��del_n����ͷ������prev��next�������� */
extern void yy_s_lxlist_del( yy_s_lxlist_head_t *del_n, yy_s_lxlist_head_t * prev, yy_s_lxlist_head_t * next);

/* ��ʼ������ͷ */
#define YY_S_LXLIST_HEAD_INIT( a ) do{ (a)->next = (a)->prev = (a) ;}while(0)

/* ������ͷnew_n���뵽����ͷl֮�� */
#define YY_S_LXLIST_ADD_HEAD( l, new_n ) do{  yy_p_assert( l != new_n ); yy_s_lxlist_add( new_n, (l), (l)->next );}while(0)

/* ������ͷnew_n���뵽����ͷl֮ǰ */
#define YY_S_LXLIST_ADD_TAIL( l, new_n ) do{  yy_p_assert( l != new_n ); yy_s_lxlist_add( new_n, (l)->prev, (l) );}while(0)

/* �������ͷָ�� */
#define YY_S_LXLIST_CLR_NODE( n ) do{  yy_p_assert( n != NULL ); (n)->prev = YY_S_LXLIST_POSITION_PREV; (n)->next = YY_S_LXLIST_POSITION_NEXT; }while(0)

/* ���del_n����ͷ������������������ */
#define YY_S_LXLIST_DEL( l, del_n ) do { yy_p_assert( (del_n) != NULL );yy_p_assert( (del_n) != l );yy_s_lxlist_del( (del_n), (del_n)->prev, (del_n)->next ); }while(0)

/* �ж�����ͷ�Ƿ�Ϊ�� */
#define YY_S_LXLIST_IS_EMPTY( l ) ( (l)->next == (l) )

/* �õ�����ͷ����ĵ�һ���ڵ㣬���򷵻ؿ�  */
#define YY_S_LXLIST_FIRST( l ) ( ( (l)!= NULL && (l)->next != (l) )?(l)->next:NULL )

/*  �õ�n�������һ���ڵ㣬���򷵻ؿ� */
#define YY_S_LXLIST_NEXT( l, n ) (( (l) != NULL && (n) != NULL && (n)->next != (l) )?(n)->next:NULL)

/* ���ptr��Ϊ�գ��򷵻�member�����ṹ��ָ�룬���򷵻�NULL */
#define YY_S_LXLIST_ENTRY( ptr, type, member) ( (ptr) != NULL ? ( YY_P_CONTAINER_OF( ptr, type, member ) ):NULL )

/**
*   l		����ͷ
*   type	�ڵ�ʵ������
*   member  �����ڽڵ��еĳ�Ա����
*/
/* ���ص�һ�����ָ�� */
#define YY_S_LXLIST_FIRST_ENTRY( l, type, member) YY_S_LXLIST_ENTRY( (l)->next, type, member )

/*
*   l		����ͷ
*   type	�ڵ�ʵ������
*   member  �����ڽڵ��еĳ�Ա����
*/
/* �������һ�����ָ�� */
#define YY_S_LXLIST_LAST_ENTRY( l, type, member)  YY_S_LXLIST_ENTRY( (l)->prev, type, member )



/** * list_for_each_entry_safe - iterate over list of given type safe against removal of list entry 
* @pos:    the type * to use as a loop cursor. 
* @tmp:    another type * to use as temporary storage 
* @l:      the head for your list. 
* @type:
* @member: the name of the list_struct within the struct. 
*/

/** 
*   pos�ǵõ�ָ��l->next��ָ��
*   tmpΪ���ڵ���һ���ڵ��ָ��
*   ��Ҫ���ڰ�ȫ�������� */
#define YY_S_LXLIST_FOR_EACH_ENTRY_SAFE(l ,pos, tmp, type, member)  for( pos = YY_S_LXLIST_ENTRY((l)->next, type, member),tmp = YY_S_LXLIST_ENTRY(pos->member.next, type, member); &pos->member != (l);pos = tmp, tmp = YY_S_LXLIST_ENTRY(tmp->member.next, type, member) )

extern int yy_s_lxlist_validation_test();
#endif
