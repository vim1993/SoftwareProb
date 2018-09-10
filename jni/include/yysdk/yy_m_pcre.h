#ifndef YY_M_PCRE_H
#define YY_M_PCRE_H
#include "yy_f_alloc.h"

#ifndef YY_ENV_NOT_M_PCRE


#if defined(WIN32)
#pragma comment( lib, "pcre.lib" )
#endif

extern int yy_m_pcre_check_is_match(const char *pattern, const char *src);
extern void yy_m_pcre_test();

#endif//YY_ENV_NOT_M_PCRE

#endif
