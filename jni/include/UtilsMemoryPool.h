#ifndef __UTILS_MEMORY_POOL_H__
#define __UTILS_MEMORY_POOL_H__

#include "yysdk/yy_f_alloc_nfp.h"
#include "yysdk/yy_f_alloc.h"

char *buf_mem = NULL;
yy_f_alloc_t * alloc = NULL;

inline int sdk_mem_init(void)
{
      buf_mem = (char *)malloc( 1024*1024*5 );
      if(buf_mem == NULL)
      {
            return 0;
      }
      alloc = yy_f_alloc_nfp_create2( 1024*1024*5, buf_mem, NULL );
      if( alloc == NULL )
      {
            return 0;
      }
      return 1;
}


inline void *sdk_mem_malloc(size_t len)
{
      return YY_F_ALLOC_MALLOC( alloc, len );
}

inline void sdk_mem_free(char *buf)
{
      YY_F_ALLOC_FREE(alloc,buf);
}

inline void sdk_mem_deinit(void)
{
      YY_F_ALLOC_RELEASE( alloc );
      free( buf_mem );
}

#endif