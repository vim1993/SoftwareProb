
/**
*   yy_e_xx.h 这样的函数都是在实际的某些项目中需要才被添加到基础库中的，
*   不具备通用性（因此不必深究-_-）
*/

#ifndef YY_E_STDIO_H
#define YY_E_STDIO_H
#include "yy_p_stdio.h"

/* 将fullname中最后一个\\后的类容拷贝到basename后面，否则全部拷贝 */
extern int yy_e_file_basename( const char * fullname, char * basename );

/* 将fullname中最后一个\\后的类容拷贝到basename后面，否则全部拷贝,并修改basename_noext中的'.'为‘、0’ */
extern int yy_e_file_basename_noext( const char * fullname, char * basename_noext );

/* 将fullname字符串复制到path，并将'\\'改为'\0'，去掉这后面的内容 */
extern int yy_e_file_path( const char * fullname, char * path );

/* 将fullname字符串'\\'后的内容复制到ext的最后，但是'\\'最后一次出现‘.'后的内容要被去掉 */
extern int yy_e_file_ext( const char * fullname, char * ext );
#endif
