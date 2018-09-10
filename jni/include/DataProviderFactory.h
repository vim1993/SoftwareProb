#ifndef __DATA_PROVIDER_FACTORY_H__
#define __DATA_PROVIDER_FACTORY_H__

#include "DataProvider.h"

using namespace std;

enum{
      CREATE_JNI_PRODUCT,
      CREATE_NATIVE_PRODUCT
};

class IDataProviderCreateFactory {

      public:
            virtual IDataProvider * createDataProvider(unsigned int _product) = 0;
};

class DataProviderCreateFactory {

      public:
            DataProviderCreateFactory();
            ~DataProviderCreateFactory();

            IDataProvider * createDataProvider(unsigned int _product = 0);
};

#endif