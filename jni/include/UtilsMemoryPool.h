#ifndef __UTILS_MEMORY_POOL_H__
#define __UTILS_MEMORY_POOL_H__

#include "yysdk/yy_f_alloc_nfp.h"
#include "yysdk/yy_f_alloc.h"

class memory_pool {
      private:
            char *buf_mem = NULL;
            yy_f_alloc_t * alloc = NULL;

            static memory_pool mMemeroyPool;

            memory_pool() {

            };

            ~memory_pool() {

            }

            int sdk_mem_init(void);

      public:
            static memory_pool * getInstance(void) {
                  return &mMemeroyPool;
            };

            void *sdk_mem_malloc(size_t len);
            void sdk_mem_free(char *buf);
};
#endif