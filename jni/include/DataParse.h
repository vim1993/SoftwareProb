#ifndef __DATA_PARSE_H__
#define __DATA_PARSE_H__

#include <vector>
#include <string>

#include <time.h>

#include "DataFilter.h"
#include "UtilsCommon.h"
#include "http-hdr/http-hdr.h"

using namespace std;

class SoftwareProbeDataPaser {
      private:
            http_head *httpHead;
            http_head *httpHead_response;

            vector<SoftwareProbeFilter *> filters_base;
            vector<SoftwareProbeFilter *> filters[FILTER_MAX_CNT];
            int filter_ues[FILTER_MAX_CNT];

            int _is_chunked;
            long _responseLength;
            int _parse_status;
            int _parse_statue_response;
            int _wait_num;
            bool _is_reset;
            //int _cancelled;
            //bool _not_match;
            time_t last_time;
            bool _is_rtsp;

            int send_report;
            int reques_cnt;
            int response_cnt;
            bool _is_match[10000];
            int  _is_match_filter_id[10000];

            needle_package_data_t MsgData;

            int find_filter_id();
            int impl_parse_responce(struct flow_key *key, const struct pkthdr *hdr, const unsigned char *pkt, unsigned char* content_start, enum direction dir = DIR_ONE);
            int impl_parse_request(struct flow_key *key, const struct pkthdr *hdr, const unsigned char *pkt, unsigned char* content_start, enum direction dir = DIR_ONE);
            int impl_parse_content(struct flow_key *key, const struct pkthdr *hdr, const unsigned char *pkt, unsigned char* content_start,int len, enum direction dir = DIR_ONE);
            unsigned int get_http_pkt_content_len(unsigned int pktlen, const unsigned char *pkt, unsigned char *content_start);
            int HttpHead2Str(http_head *head, char *pHeadContent, int len);
            bool hasAnyFilterMatchedRequest(http_head *head,int index);
            bool hasAnyFilterMatchedResponse(http_head *head,int index);
            bool hasAnyFilterMatchedRequestBody(const unsigned char *data, int len,int index);
            bool hasAnyFilterMatchedResponseBody(const unsigned char *data, int len,int index);
            bool captureStatistics(int index);

            long HttpContentLen(http_head *head);
            bool HttpResponse_Encoding(http_head *head);

      public:
            inline bool is_rest(void) const {
                  return _is_reset == true;
            };
            void reset(void);
            void set_needlepackage_info(const vector<SoftwareProbeFilter *> &filters, const struct flow_key &flow_key, int type);
            void update_last_flowtime();
            unsigned int get_last_flowtime(void);

            string getFilterID(void);
            int addPackage(struct flow_key *key, const struct pkthdr *hdr, const unsigned char *pkt, unsigned char * content_start,int len, enum direction dir = DIR_ONE);
            int addStat(struct flow_stat *stat);
            char *getRequestPackage(void);
            char *getResponsePackage(void);
            bool waitingRequest();
            void report(int u32ReportSta, int type = 9,int index = 9999);

            SoftwareProbeDataPaser();
            ~SoftwareProbeDataPaser();
};

#endif