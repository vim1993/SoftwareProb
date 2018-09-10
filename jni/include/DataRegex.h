#ifndef __DATA_REGEX_H__
#define __DATA_REGEX_H__

#include <string>

#include "pcre/pcre.h"
#include "UtilsCommon.h"

#define OVECCOUNT 30
#define SRC_URI_MAX 1024

using namespace std;

class IDataRegex {

      public:
            virtual bool getCheckResult(const char * checkContent, unsigned int contenLen, const char * regexRule) = 0;
};

class DataRegexPcre: public IDataRegex {

      private:
            pcre * regex;

      public:
            DataRegexPcre();
            ~DataRegexPcre();

            bool getCheckResult(const string & content, unsigned int contenLen, const string & rule);
};


#endif