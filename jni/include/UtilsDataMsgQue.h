#ifndef __UTILS_DATA_MSG_QUE_H__
#define __UTILS_DATA_MSG_QUE_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <semaphore.h>

#include <map>

#include "UtilsLoopBuffer.h"
#include "UtilsMemoryPool.h"

using namespace std;

typedef sem_t               Needle_Sme_t;
typedef unsigned int        Needle_Partition_t;

Needle_Sme_t *msg_sem = NULL;
inline Needle_Sme_t * Needle_CreateSemaphoreFifo(Needle_Partition_t * Partition_p, const int InitialValue)
{
    Needle_Sme_t * Semaphore_p;

    if (Partition_p != NULL)
    {

    }

    Semaphore_p = (Needle_Sme_t *)sdk_mem_malloc(sizeof(Needle_Sme_t));
    if (Semaphore_p != NULL)
    {
        sem_init(Semaphore_p, 0, InitialValue);
    }
    return Semaphore_p;
}

inline unsigned int Needle_DeleteSemaphore(Needle_Partition_t * Partition_p, Needle_Sme_t * Semaphore_p)
{
    if (Partition_p != NULL)
    {

    }

    if (Semaphore_p != NULL)
    {
        sem_destroy(Semaphore_p);
        sdk_mem_free((char*)Semaphore_p);
        Semaphore_p = NULL;
    } else
    {
        return 0;
    }
    return 1;
}

inline unsigned int Needle_SignalSemaphore(Needle_Sme_t * Semaphore_p)
{
    if (Semaphore_p != NULL)
    {
        sem_post(Semaphore_p);
        return 1;
    }
    return 0;
}

inline unsigned int Needle_WaitSemaphore(Needle_Sme_t * Semaphore_p)
{
    if (Semaphore_p != NULL)
    {
        return (sem_wait(Semaphore_p) == 0) ? 1 : 0;
    }
    return 0;
}

inline unsigned int Needle_GetSemaphoreValue(Needle_Sme_t * Semaphore_p, int *sval)
{
    if (Semaphore_p != NULL)
    {
        sem_getvalue(Semaphore_p, sval);
        return 1;
    }
    return 0;
}


inline size_t getpagesize(void)
{
    return 4096;
}

template <class _T>
class NeedleCommonMsg {
	private:
		loopbuffer_t buffer_t;
		Needle_Sme_t * msgSem;

	public:
		NeedleCommonMsg(const unsigned int msgLen):buffer_t(msgLen) {
			msgSem = Needle_CreateSemaphoreFifo(NULL,0);
                  LOGE("addMsg::create MsgBuffer:%d",msgLen);
		};

		~NeedleCommonMsg() {

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
				Needle_SignalSemaphore(msgSem);
				return true;
		};

		_T *receiveCommonMessageMsg(void) {
			static _T get_msg;
            LOGE("addMsg RECV start");
			Needle_WaitSemaphore(msgSem);
			size_t data_len = buffer_t.pop_front(&get_msg, sizeof(get_msg));
			if (data_len == sizeof(get_msg)) {
				return &get_msg;
			} else {
				return NULL;
			}
		};
};

class NeedleCommonMsgManager {

	private:
		NeedleCommonMsgManager() {

		};

		map<unsigned int , void * > msgManagerMap;

	public:
		static NeedleCommonMsgManager * getInstance(void) {
			static NeedleCommonMsgManager msgManger;
			return &msgManger;
		};

		bool addCommonMsgHandle(unsigned int msgID, void * msgHandle);
		bool delCommonMsgHandle(unsigned int msgID);

		unsigned int getMsgMapSize();
		void * getCommonMsgHandle(unsigned int msgID);
};

#endif