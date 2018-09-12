#ifndef __UTILS_DATA_MSG_QUE_H__
#define __UTILS_DATA_MSG_QUE_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <map>

#include "UtilsLoopBuffer.h"
#include "UtilsMemoryPool.h"
#include "UtilsCommon.h"

using namespace std;

template <class _T>
class CommonMsg {
	private:
		loopbuffer_t buffer_t;

	public:
		CommonMsg(const unsigned int msgLen):buffer_t(msgLen) {
            LOGE("addMsg::create MsgBuffer:%d",msgLen);
		};

		~CommonMsg() {

		};

		int addCommonMsg(void *pMsg, unsigned int u32MsgLen) {
			clock_t  start_time = clock();
			clock_t  time_1;

			if (buffer_t.push_back(pMsg, u32MsgLen) == false) {
				LOGE("addMsg failed");
				return false;
			}
			time_1 = clock() - start_time;

			if(time_1 > 100) {
				LOGE("addMsg time:%d",time_1);
			}

			return true;
		};

		_T *receiveCommonMessageMsg(void) {
			static _T get_msg;

			size_t data_len = buffer_t.pop_front(&get_msg, sizeof(get_msg));
			if (data_len == sizeof(get_msg)) {
				return &get_msg;
			} else {
				return NULL;
			}
		};
};

class CommonMsgManager {

	private:
		CommonMsgManager() {

		};

		map<unsigned int , void * > msgManagerMap;

	public:
		static CommonMsgManager * getInstance(void) {
			static CommonMsgManager msgManger;
			return &msgManger;
		};

		bool addCommonMsgHandle(unsigned int msgID, void * msgHandle);
		bool delCommonMsgHandle(unsigned int msgID);

		unsigned int getMsgMapSize();
		void * getCommonMsgHandle(unsigned int msgID);
};

#endif