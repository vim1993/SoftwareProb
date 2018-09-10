#ifndef __DATA_PACKAGE_H__
#define __DATA_PACKAGE_H__

/*
 *by yuantaiyong
 */

#include <string>
#include <vector>

#include "UtilsCommon.h"
#include "http-hdr/http-hdr.h"

using namespace std;

struct parse_manager_s {
      unsigned int mUsed;
      struct flow_key mFlowKey;
      SoftwareProbeDataPaser mDataParse;
};

class NetPackage {

      private:
            unsigned int mDataParseUsedNum;

            vector<SoftwareProbeFilter *> mFilterList;
            struct parse_manager_s mParseArrylist[MAX_NET_DATA_PASER];

            NetPackage();
            ~NetPackage();
            static NetPackage netpackage;

      public:
            static NetPackage * getInstance(void) {
                  return &netpackage;
            };

            SoftwareProbeFilter * createFilter(string _filterID); //创建过滤器,通过mFilterList来管理
            void  setDataParseResolver(struct flow_key & _flowkey);//reset网络包解析器
            parse_manager_s * getDataParseResolver(struct flow_key & _flowkey); //获取网络包解析器实例

            //上报抓到的包
            static int cap_callback(const struct pkthdr *hdr, const unsigned char *pkt);

            //顺序上报报文
            static int content_callback(struct flow_key *key, const struct pkthdr *hdr, const unsigned char *pkt, unsigned char * content_start,
                                          int len, enum direction dir);

            //上报流情况，5秒一�?
            static int stat_callback(struct flow_key *key, struct flow_stat *stat);

            //建立TCP连接后传内容时上�?
            //返回值：0->不监测此连接�?->监测此连接的此方向，2->监测此连接的双向，其�?>�?处理。监测含义为顺序上报报文
            static int event_callback(struct flow_key *key, struct flow_stat *stat, const unsigned char *start,
                                    int len, enum event_type type);
};

#endif