#include "UtilsCommon.h"
#include "DataProviderFactory.h"

DataProviderCreateFactory::DataProviderCreateFactory() {
      LOGE("[%s][%d]!\n", __func__, __LINE__);
}

~DataProviderCreateFactory::DataProviderCreateFactory() {
      LOGE("[%s][%d]!\n", __func__, __LINE__);
}

IDataProvider * DataProviderCreateFactory::createDataProvider(unsigned int _product) {

      IDataProvider * _provider = NULL;

      switch (_product)
      {
            case CREATE_JNI_PRODUCT:
                  _provider = DataProviderAndroid::getInstance();
                  break;

            case CREATE_NATIVE_PRODUCT:
                  _provider = DataProviderNative::getInstance();
                  break;

            default:
                  LOGE("input param error, please check\n");
                  break;
      }

      return _provider;
}