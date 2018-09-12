#include "UtilsMemoryPool.h"

int memory_pool::sdk_mem_init(void)
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


void * memory_pool::sdk_mem_malloc(size_t len)
{
      if(buf_mem == NULL) {
            sdk_mem_init();
      }

      return YY_F_ALLOC_MALLOC( alloc, len );
}

void memory_pool::sdk_mem_free(char *buf)
{
      YY_F_ALLOC_FREE(alloc,buf);
}

void memory_pool::sdk_mem_deinit(void)
{
      YY_F_ALLOC_RELEASE( alloc );
      free( buf_mem );
}