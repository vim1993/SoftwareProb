#ifndef __UTILS_COMMON_H__
#define __UTILS_COMMON_H__

#include <android/log.h>
#include <string>
#include <pthread.h>

#include "minidpi/minidpi.h"
#include "http-hdr/http-hdr.h"
#include "pcre/pcre.h"

using namespace std;

#define MAX_NET_DATA_PASER 32

#define MSGQUE_DATA_MAX (64 * 1024)

#define  TAG    "DSMINFO8888"

#define ___LOG_PRINT_BIGDATANEEDLECRAWLER__

#ifdef ___LOG_PRINT_BIGDATANEEDLECRAWLER__

	#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG,__VA_ARGS__)
	#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)

	#define DEBUG_TRACK LOGD("[%s][%d] !\n", __func__, __LINE__)
	#define DEBUG_CHECK_FUNC() LOGD("call [%s][%d] !\n", __func__, __LINE__)
	#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)
	#define LOGT(...)  __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)
	#define LOGX(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)

#else

	#define LOGI(...)
	#define LOGD(...)
	#define DEBUG_TRACK

	#define DEBUG_CHECK_FUNC()
	#define LOGE(...) //__android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)
	#define LOGT(...) //__android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)
	#define LOGX(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)
#endif



class http_content_buf_t {
	unsigned char buf[8 * 1024];
	int dataLen;
	int chunkLen;
public:
	http_content_buf_t() : dataLen(0), chunkLen(-1) {}
	int pushData(const void *data, int len) {

		if(len < 0)
		{
			LOGD("pushData len error:%d",len);
			return 0;
		}
		if (len > bufSize() - dataLen) {
			len = bufSize() - dataLen;
		}
		if (len == 0) {
			return 0;
		}
		memcpy(buf + dataLen, data, len);
		dataLen += len;
		return len;
	}
	// return used bytes
	int pushChunkData(const void *data, int len) {
		if (chunkLen == -4) {
			reset();
			return 0;
		}

		if (chunkLen == 0) {
			return 0;
		}

		if (chunkLen > 0) {
			if (len > chunkLen - dataLen) {
				len = chunkLen - dataLen;
			}
			if (len == 0) {
				return 0;
			}
			return pushData(data, len);
		}

		const unsigned char *dataBytes = (const unsigned char *)data;
		int i = 0;

		if (chunkLen == -2 || chunkLen == -3) {
			for (; i < len; i++) {
				buf[i] = dataBytes[i];
				if (i >= 1 && buf[i] == '\n' && buf[i - 1] == '\r') {
					i++;
					if (i == 2) {
						if (chunkLen == -3) {
							chunkLen = -4;
						} else {
							reset();
						}
					}
					return i;
				}
			}
			reset();
			return 0;
		}

		for (; i < len; i++) {
			buf[dataLen + i] = dataBytes[i];
			if (i >= 1 && buf[dataLen + i] == '\n' && buf[dataLen + i - 1] == '\r') {
					chunkLen = strtol((char*)&buf, 0, 16);
					dataLen = 0;
				i++;
				if (chunkLen == 0) {
					return i;
					}
					return pushChunkData(dataBytes + i, len - i) + i;
				}
			}
		dataLen += i;
		return i;
	}
	int chunkSize() {
		return chunkLen;
	}
	int dataSize() {
		return dataLen;
	}
	const int bufSize() const {
		return sizeof(buf);
	}
	void clear() {
		dataLen = 0;
		memset(buf, 0, sizeof(buf));
	}

	void dropChunkData() {
		if (chunkLen == 0) {
			// drop tail
			chunkLen = -3;
			dataLen = 0;
		} else if (chunkLen == dataLen) {
			// drop \r\n
			chunkLen = -2;
			dataLen = 0;
		} else if (chunkLen < 0) {
			reset();
		} else {
			chunkLen -= dataLen;
			dataLen = 0;
		}
	}

	void reset() {
		chunkLen = -1;
		dataLen = 0;
	}

	const unsigned char *data() const {
		return buf;
	}
};

typedef struct needle_package_data_s {
	int  State;

	long  receivedRequestBodyBytes;
	long  receivedReponseBodyBytes;

	time_t flowtime;

	char filterid[1024];

	struct flow_key flowKey;
	struct flow_stat flowStat[32];
	unsigned int flowStatWPos;

	char requestHead[10 * 1024];
	http_content_buf_t requestPkg;

	char responseHead[10 * 1024];
	http_content_buf_t responsePkg;

	needle_package_data_s() {
		receivedRequestBodyBytes = 0;
		receivedReponseBodyBytes = 0;
		flowStatWPos = 0;
	}

	void reset(const struct flow_key &flowKey) {
		this->flowKey = flowKey;
		flowtime = time(0);
		receivedRequestBodyBytes = 0;
		receivedReponseBodyBytes = 0;
		requestPkg.reset();
		responsePkg.reset();
		flowStatWPos = 0;
	}

	bool add_flow_stat(const struct flow_stat &s) {
		flowStat[flowStatWPos] = s;
		LOGD("add_flow_stat %X:%X-%X:%X %d/%d", flowKey.addr1, flowKey.port1, flowKey.addr2, flowKey.port2, flowStatWPos, sizeof(flowStat) / sizeof(flowStat[0]));
		++flowStatWPos;
		if (flowStatWPos >= sizeof(flowStat) / sizeof(flowStat[0])) {
			return true;
		}
		return false;
	}

} needle_package_data_t;

typedef struct {

	bool isExclude;
	string name;
	enum {
		CMP_INVALID,
		CMP_EQUALS,	// string compare
		CMP_EQ,		// number compare
		CMP_LT,
		CMP_GT,
		CMP_LT_EQUALS,
		CMP_GT_EQUALS,
		CMP_NOT_EQUALS,
		CMP_REGEXP,
	} op;
	string value;
	long numValue;
	string ruleValue;

} Needle_Rule_t;

class mutex_locker_t {
	pthread_mutex_t *_mutex;
public:
	mutex_locker_t(pthread_mutex_t *mutex) : _mutex(mutex) {
		pthread_mutex_lock(_mutex);
	}
	~mutex_locker_t() {
		pthread_mutex_unlock(_mutex);
	}
};

inline bool operator < (const flow_key &k1, const flow_key &k2) {
	return memcmp(&k1, &k2, sizeof(flow_key)) < 0;
}

inline bool operator == (const flow_key &k1, const flow_key &k2) {
	return memcmp(&k1, &k2, sizeof(flow_key)) == 0;
}

inline bool operator > (const flow_key &k1, const flow_key &k2) {
	return memcmp(&k1, &k2, sizeof(flow_key)) > 0;
}

class needle_rule {
	private:
		bool mValue;
		unsigned int  mKey;
		string mStrKey;
		Needle_Rule_t mRule;

	public:
		void setRule(string ruleName, const char *ruleKey, string ruleValue, bool isex);
		Needle_Rule_t *getRule(void);

		void setu32Data(unsigned int u32Key, bool u8Value);
		void setStrData(string strKey, bool u8Value);
		unsigned int getKey(void);
		bool getValue(void);
		string getStrKey();

		~needle_rule(void);
		needle_rule(void);
};

class stack_checker {
	private:
		void * data[10];
	public:
		stack_checker() {
			for (size_t i = 0; i < 10; i++) {
				data[i] = i + this;
			}
		}
		~stack_checker() {
			for (size_t i = 0; i < 10; i++) {
				if (data[i] != i + this) {
					LOGE("CHECK STACK FAILED!!!!");
				}
			}
		}
};
#endif //BIGDATANEEDLECRAWLER_V1_X_NEEDLECOMMON_H
