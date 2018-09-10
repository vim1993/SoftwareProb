#ifndef YY_M_LIBXML2_H
#define YY_M_LIBXML2_H
#include "yy_p_type.h"
#include "yy_f_alloc.h"
#include "yy_p_stdio.h"

#ifndef YY_ENV_NOT_M_LIBXML2

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlmemory.h>

/* �ṹ�壬������鿴sdk/libxml_vs2005sp1/libxml/tree.h */
typedef xmlDoc yy_m_lx2_doc_t;  
typedef xmlNode yy_m_lx2_node_t;
typedef char yy_m_lx2_char_t;

/* xml������ʼ�� */
extern int yy_m_lx2_init();

/* xml������Դ�ͷ� */
extern int yy_m_lx2_uninit();

/* �ͷ��ַ���buf��buf��lx2�����ʱ����) */
extern void yy_m_lx2_free_buff( yy_m_lx2_char_t * buf );

/* ����xml�����ṹ�� */
extern yy_m_lx2_doc_t * yy_m_lx2_create_doc( const yy_m_lx2_char_t * root_name );

/* ���ڴ����ݴ���xml�����ṹ�壬ʹ�����֮����Ҫ��xmlFreeDoc()���ͷ���Դ */
extern yy_m_lx2_doc_t * yy_m_lx2_parse_doc( const char * buf, size_t len );

/* ���ļ�����xml�����ṹ�壬��������DOM����ʹ�����֮����Ҫ��xmlFreeDoc()���ͷ���Դ */
extern yy_m_lx2_doc_t * yy_m_lx2_load_doc( const char * filename );

/* �ͷ�xml�����ṹ  */
extern void yy_m_lx2_free_doc( yy_m_lx2_doc_t * doc );

/* ��xml�ṹ�������������ڴ��У��γ�һ��XML��ʽ�����ݣ����ص��ڴ�ʹ������ֶ��ͷ�  */
extern yy_m_lx2_char_t * yy_m_lx2_doc_to_memory( yy_m_lx2_doc_t * doc , size_t * len );

/* ���ڴ��е�DOM�������浽Ӳ���ϣ�����һ������ʽ��XML�ļ� */
extern int yy_m_lx2_doc_to_file( yy_m_lx2_doc_t * doc, const char * filename, int format );

/* ��xml��㱣�浽�ļ� */
extern int yy_m_lx2_node_to_file( yy_m_lx2_node_t * n, const char * filename, int format );

/* ��ȡxml���ڵ� */
extern yy_m_lx2_node_t * yy_m_lx2_get_root( yy_m_lx2_doc_t * doc );

/* �����ӽڵ㣬nameΪ�ӽڵ����� */
extern yy_m_lx2_node_t * yy_m_lx2_subnode( yy_m_lx2_node_t * node, const yy_m_lx2_char_t * name );

/* ��ȡ�������ֵ��ֵܽڵ� */
extern yy_m_lx2_node_t * yy_m_lx2_nextnode( yy_m_lx2_node_t * node, const yy_m_lx2_char_t * name );

/* �����ӽڵ� */
extern yy_m_lx2_node_t * yy_m_lx2_create_subnode( yy_m_lx2_node_t * node, const yy_m_lx2_char_t * name, const yy_m_lx2_char_t * content );

/* �����ӽڵ㣬�ӽڵ����ݵ�����Ϊsize_t */
extern yy_m_lx2_node_t * yy_m_lx2_create_subnode_content_size_t( yy_m_lx2_node_t * node, const yy_m_lx2_char_t * name, size_t content );

/* �����ַ���xml����������Ϊ�ӽڵ����node�� */
extern yy_m_lx2_node_t * yy_m_lx2_create_subnode_parse( yy_m_lx2_node_t * node, const char * xml, size_t len );

/* ��xml�ڵ�ת��Ϊ�ַ�����ʹ��������ͷ��ַ����ռ� */
extern yy_m_lx2_char_t * yy_m_lx2_node_to_memory( yy_m_lx2_node_t * node , size_t * len );

/* ���ݽڵ�����������������ֵ�����ӽڵ� */
extern yy_m_lx2_node_t * yy_m_lx2_find_node_by_prop( yy_m_lx2_node_t * node, const yy_m_lx2_char_t * name, const yy_m_lx2_char_t * prop_name, const yy_m_lx2_char_t * prop_value );

/* ɾ��xml�ڵ� */
extern void yy_m_lx2_unlink_node( yy_m_lx2_node_t * node );

/* ɾ���ӽڵ� */
extern void yy_m_lx2_unlink_subnode( yy_m_lx2_node_t * node, const yy_m_lx2_char_t * name );

/* ��ȡ�ڵ����ݣ�ʹ��������ֶ��ͷŷ��ص��ڴ�ռ� */
extern yy_m_lx2_char_t * yy_m_lx2_get_content( yy_m_lx2_node_t * node );

/* ���ýڵ����� */
extern void yy_m_lx2_set_content( yy_m_lx2_node_t * node, const yy_m_lx2_char_t * content );

/* ���ýڵ����ݣ���������Ϊsize_t */
extern void yy_m_lx2_set_content_size_t( yy_m_lx2_node_t * node, size_t content );

/* ���ýڵ����ݣ���������Ϊ64λ�޷������� */
extern void yy_m_lx2_set_content_u64( yy_m_lx2_node_t * node, yy_p_uint64 content );

/* ���ýڵ����� */
extern void yy_m_lx2_set_prop( yy_m_lx2_node_t * node, const yy_m_lx2_char_t * prop, const yy_m_lx2_char_t * value );

/* ���ýڵ����ԣ�����ֵ����Ϊint */
extern void yy_m_lx2_set_prop_int( yy_m_lx2_node_t * node, const yy_m_lx2_char_t * prop, int value );

/* ���ýڵ����ԣ�����ֵ����Ϊ32λ�޷������� */
extern void yy_m_lx2_set_prop_uint32( yy_m_lx2_node_t * node, const yy_m_lx2_char_t * prop, yy_p_uint32 value );

/* ���ýڵ����ԣ�����ֵ����Ϊsize_t */
extern void yy_m_lx2_set_prop_size_t( yy_m_lx2_node_t * node, const yy_m_lx2_char_t * prop, size_t value );

/* ���ýڵ����ԣ�����ֵ����Ϊyy_p_off_t */
extern void yy_m_lx2_set_prop_off_t( yy_m_lx2_node_t * node, const yy_m_lx2_char_t * prop, yy_p_off_t value );

/* ��ȡ�ڵ�����ֵ */
extern yy_m_lx2_char_t * yy_m_lx2_get_prop( yy_m_lx2_node_t * node, const yy_m_lx2_char_t * prop );

/* ��ȡ�ڵ�����ֵ��ת��Ϊint���� */
extern int yy_m_lx2_get_prop_int( yy_m_lx2_node_t * node, const yy_m_lx2_char_t * prop );

/* ��ȡ�ڵ�����ֵ��ת��Ϊyy_p_off_t���� */
extern yy_p_off_t yy_m_lx2_get_prop_off_t( yy_m_lx2_node_t * node, const yy_m_lx2_char_t * prop );

/* �ÿսڵ�����ֵ���Ƿ���ȷ���� */
extern void yy_m_lx2_unset_node_prop( yy_m_lx2_node_t * node, const yy_m_lx2_char_t * prop );

/* ���ڵ��Ƿ����ָ������ */
extern int yy_m_lx2_is_have_prop( yy_m_lx2_node_t * node, const yy_m_lx2_char_t * prop );

/*  �ַ�����ת�� */
extern int yy_m_lx2_charset_transfer( const char * src, char * dst, size_t dst_len, const char * charset_src, const char * charset_dst );

/* ���ַ�����������������ڴ��� */
extern yy_m_lx2_char_t * yy_m_lx2_cf_buff( yy_f_alloc_t * alloc, yy_m_lx2_char_t * buff );

/* ���ַ�����������������ڴ��� */
#define YY_MLX2_CFB( alloc, buff ) yy_m_lx2_cf_buff( alloc, buff )

/* �ͷ��ڴ� */
#define YY_MLX2_FREEB( a ) do{ if( (a) != NULL ) {  yy_m_lx2_free_buff( a ); (a) = NULL; } } while(0)

#endif
#endif
