#ifndef __DATA_FILTER_H_V2_0__
#define __DATA_FILTER_H_V2_0__

/*
 *by liuyuyang
 */

#include <string>
#include <vector>

#include "UtilsCommon.h"
#include "http-hdr/http-hdr.h"

using namespace std;

class SoftwareProbeFilter {

      private:
            IRegex * mRegex;

            string id;
            vector<needle_rule *> ips;
            vector<needle_rule *> ipMasks_start;
            vector<needle_rule *> ipMasks_end;
            vector<needle_rule *> ports;

            vector<needle_rule *> mRequstRule;
            vector<needle_rule *> mResponseRule;
            vector<needle_rule *> mOtherRule;

            bool statistics;

            int  _check_Ip(struct flow_key *key, http_head *head);
            int  _check_Port(struct flow_key *key, http_head *head);
            int  _check_Method(http_head *head, const char *Meth, bool isex);
            bool _check_content(string src, Needle_Rule_t *rule);
            bool _check_httpReshead(http_head *head, Needle_Rule_t *rule, const char *Buf);
            bool _check_httpReqhead(http_head *head, Needle_Rule_t *rule, const char *Buf);
            bool _check_rule(Needle_Rule_t *rule, http_head *head, bool isrequst);

      public:
            //get ttach opt
            const string &getId() const;
            void setStatistics(bool statistics);

            //ttach opt
            void addIp(int u32Key, bool u8Value);
            void addIpMask(int ipMaskStart, int ipMaskEnd, bool u8Value);
            void addPort(int u32Key, bool u8Value);
            void setRule(string ruleName, string compare, string ruleValue, bool isex);
            bool getStaticstics(void);

            //filter opt
            bool checkRequstBodyIsVaild(const unsigned char *pBody, int len);
            bool checkResponseBodyIsVaild(const unsigned char * pBody, int len);
            bool checkRequstHeadIsVaild(http_head *head);
            bool checkResponseIsVaild(http_head *head);
            bool checkBasePorpertyIsVaild(struct flow_key *key, http_head *head);
};

#endif