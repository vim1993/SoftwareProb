#include "UtilsDataMsgQue.h"

bool CommonMsgManager::addCommonMsgHandle(unsigned int msgID, void * msgHandle) {
    if(msgHandle == NULL) {
        return false;
    }

    if(msgManagerMap.size() != 0 && msgManagerMap.find(msgID) != msgManagerMap.end()) {
        return true;
    }

    msgManagerMap.insert(pair<int, void *>(msgID, msgHandle));
}

bool CommonMsgManager::delCommonMsgHandle(unsigned int msgID) {
    if(msgManagerMap.size() == 0) {
        return false;
    }

    map<unsigned int , void *>::iterator it = msgManagerMap.find(msgID);
    if(it == msgManagerMap.end()) {
        return false;
    }

    msgManagerMap.erase(it);

    return true;
}

unsigned int CommonMsgManager::getMsgMapSize(void) {
    return msgManagerMap.size();
}

void * CommonMsgManager::getCommonMsgHandle(unsigned int msgID) {
    if(msgManagerMap.size() == 0) {
        return NULL;
    }

    static map<unsigned int , void *>::iterator it;

    it = msgManagerMap.find(msgID);

    return (void *) it->second;
}