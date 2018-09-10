#include "DataRegex.h"

DataRegexPcre::DataRegexPcre() {

}

DataRegexPcre::~DataRegexPcre() {

}

bool DataRegexPcre::getCheckResult(const string & content, unsigned int contenLen, const string & rule) {
      pcre * regex = NULL;
      char *errMsg = 0;
      int errCode = 0, rc = 0;
      int  ovector[OVECCOUNT] = {0};

      regex = pcre_compile(rule.c_str(), 0, &errMsg,  &errCode, NULL);
      if (!regex) {
            LOGE("pcre compile failed! %d:%s", errCode, errMsg);
            return false;
      }

      rc = pcre_exec(regex, NULL, content.c_str(), contenLen, 0, 0, ovector, OVECCOUNT);
      free(regex);
      regex = NULL;

      return rc < 0 ? false : true;
}
