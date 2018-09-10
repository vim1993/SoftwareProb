#ifndef YY_M_LIBXML2_H
#define YY_M_LIBXML2_H
#include "yy_p_type.h"
#include "yy_f_alloc.h"
#include "yy_p_stdio.h"

#ifndef YY_ENV_NOT_M_LIBXML2

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlmemory.h>

/* 结构体，详情请查看sdk/libxml_vs2005sp1/libxml/tree.h */
typedef xmlDoc yy_m_lx2_doc_t;  
typedef xmlNode yy_m_lx2_node_t;
typedef char yy_m_lx2_char_t;

/* xml解析初始化 */
extern int yy_m_lx2_init();

/* xml解析资源释放 */
extern int yy_m_lx2_uninit();

/* 释放字符串buf（buf由lx2库解析时分配) */
extern void yy_m_lx2_free_buff( yy_m_lx2_char_t * buf );

/* 创建xml解析结构体 */
extern yy_m_lx2_doc_t * yy_m_lx2_create_doc( const yy_m_lx2_char_t * root_name );

/* 从内存数据创建xml解析结构体，使用完毕之后，需要用xmlFreeDoc()来释放资源 */
extern yy_m_lx2_doc_t * yy_m_lx2_parse_doc( const char * buf, size_t len );

/* 从文件创建xml解析结构体，并且生成DOM树。使用完毕之后，需要用xmlFreeDoc()来释放资源 */
extern yy_m_lx2_doc_t * yy_m_lx2_load_doc( const char * filename );

/* 释放xml解析结构  */
extern void yy_m_lx2_free_doc( yy_m_lx2_doc_t * doc );

/* 将xml结构（树）导出到内存中，形成一个XML格式的数据，返回的内存使用完后手动释放  */
extern yy_m_lx2_char_t * yy_m_lx2_doc_to_memory( yy_m_lx2_doc_t * doc , size_t * len );

/* 将内存中的DOM树，保存到硬盘上，生成一个带格式的XML文件 */
extern int yy_m_lx2_doc_to_file( yy_m_lx2_doc_t * doc, const char * filename, int format );

/* 将xml结点保存到文件 */
extern int yy_m_lx2_node_to_file( yy_m_lx2_node_t * n, const char * filename, int format );

/* 获取xml根节点 */
extern yy_m_lx2_node_t * yy_m_lx2_get_root( yy_m_lx2_doc_t * doc );

/* 返回子节点，name为子节点名字 */
extern yy_m_lx2_node_t * yy_m_lx2_subnode( yy_m_lx2_node_t * node, const yy_m_lx2_char_t * name );

/* 获取给定名字的兄弟节点 */
extern yy_m_lx2_node_t * yy_m_lx2_nextnode( yy_m_lx2_node_t * node, const yy_m_lx2_char_t * name );

/* 创建子节点 */
extern yy_m_lx2_node_t * yy_m_lx2_create_subnode( yy_m_lx2_node_t * node, const yy_m_lx2_char_t * name, const yy_m_lx2_char_t * content );

/* 创建子节点，子节点内容的类型为size_t */
extern yy_m_lx2_node_t * yy_m_lx2_create_subnode_content_size_t( yy_m_lx2_node_t * node, const yy_m_lx2_char_t * name, size_t content );

/* 解析字符串xml，并将其作为子节点插入node下 */
extern yy_m_lx2_node_t * yy_m_lx2_create_subnode_parse( yy_m_lx2_node_t * node, const char * xml, size_t len );

/* 将xml节点转换为字符串，使用完后须释放字符串空间 */
extern yy_m_lx2_char_t * yy_m_lx2_node_to_memory( yy_m_lx2_node_t * node , size_t * len );

/* 根据节点名和属性名、属性值查找子节点 */
extern yy_m_lx2_node_t * yy_m_lx2_find_node_by_prop( yy_m_lx2_node_t * node, const yy_m_lx2_char_t * name, const yy_m_lx2_char_t * prop_name, const yy_m_lx2_char_t * prop_value );

/* 删除xml节点 */
extern void yy_m_lx2_unlink_node( yy_m_lx2_node_t * node );

/* 删除子节点 */
extern void yy_m_lx2_unlink_subnode( yy_m_lx2_node_t * node, const yy_m_lx2_char_t * name );

/* 获取节点内容，使用完后须手动释放返回的内存空间 */
extern yy_m_lx2_char_t * yy_m_lx2_get_content( yy_m_lx2_node_t * node );

/* 设置节点内容 */
extern void yy_m_lx2_set_content( yy_m_lx2_node_t * node, const yy_m_lx2_char_t * content );

/* 设置节点内容，内容类型为size_t */
extern void yy_m_lx2_set_content_size_t( yy_m_lx2_node_t * node, size_t content );

/* 设置节点内容，内容类型为64位无符号整形 */
extern void yy_m_lx2_set_content_u64( yy_m_lx2_node_t * node, yy_p_uint64 content );

/* 设置节点属性 */
extern void yy_m_lx2_set_prop( yy_m_lx2_node_t * node, const yy_m_lx2_char_t * prop, const yy_m_lx2_char_t * value );

/* 设置节点属性，属性值类型为int */
extern void yy_m_lx2_set_prop_int( yy_m_lx2_node_t * node, const yy_m_lx2_char_t * prop, int value );

/* 设置节点属性，属性值类型为32位无符号整形 */
extern void yy_m_lx2_set_prop_uint32( yy_m_lx2_node_t * node, const yy_m_lx2_char_t * prop, yy_p_uint32 value );

/* 设置节点属性，属性值类型为size_t */
extern void yy_m_lx2_set_prop_size_t( yy_m_lx2_node_t * node, const yy_m_lx2_char_t * prop, size_t value );

/* 设置节点属性，属性值类型为yy_p_off_t */
extern void yy_m_lx2_set_prop_off_t( yy_m_lx2_node_t * node, const yy_m_lx2_char_t * prop, yy_p_off_t value );

/* 获取节点属性值 */
extern yy_m_lx2_char_t * yy_m_lx2_get_prop( yy_m_lx2_node_t * node, const yy_m_lx2_char_t * prop );

/* 获取节点属性值，转换为int类型 */
extern int yy_m_lx2_get_prop_int( yy_m_lx2_node_t * node, const yy_m_lx2_char_t * prop );

/* 获取节点属性值，转换为yy_p_off_t类型 */
extern yy_p_off_t yy_m_lx2_get_prop_off_t( yy_m_lx2_node_t * node, const yy_m_lx2_char_t * prop );

/* 置空节点属性值，是否正确？？ */
extern void yy_m_lx2_unset_node_prop( yy_m_lx2_node_t * node, const yy_m_lx2_char_t * prop );

/* 检查节点是否存在指定属性 */
extern int yy_m_lx2_is_have_prop( yy_m_lx2_node_t * node, const yy_m_lx2_char_t * prop );

/*  字符编码转换 */
extern int yy_m_lx2_charset_transfer( const char * src, char * dst, size_t dst_len, const char * charset_src, const char * charset_dst );

/* 将字符串拷贝到新申请的内存中 */
extern yy_m_lx2_char_t * yy_m_lx2_cf_buff( yy_f_alloc_t * alloc, yy_m_lx2_char_t * buff );

/* 将字符串拷贝到新申请的内存中 */
#define YY_MLX2_CFB( alloc, buff ) yy_m_lx2_cf_buff( alloc, buff )

/* 释放内存 */
#define YY_MLX2_FREEB( a ) do{ if( (a) != NULL ) {  yy_m_lx2_free_buff( a ); (a) = NULL; } } while(0)

#endif
#endif
