#include "MsgDispatcher.h"
#include "IMessage.h"

namespace Service {
    using MessageAdapter::IMessage;
    MsgDispatcher &MsgDispatcher::Instance() {
        static MsgDispatcher instance;
        return instance;
    }

    bool MsgDispatcher::RegisterHandler(MsgType type, MsgHandler *handler) {
        if (handlers.find(type) != handlers.end()) {
            return false;
        }
        handlers[type] = handler;
        return true;
    }

    void MsgDispatcher::GenerateMessgae(std::string msg) {
        std::unique_lock<std::mutex> lock(RWLock);
        while (msgPool.size() == MAX_MESSAGE_NUM) {
            w_condition.wait(lock);
        }
        msgPool.push_back(msg);
        r_condition.notify_one();
    }

    void MsgDispatcher::HandleMessage() {
        std::string msg;
        {
            std::unique_lock<std::mutex> lock(RWLock);
            while (msgPool.empty()) {
                r_condition.wait(lock);
            }
            msg = msgPool.back();
            msgPool.pop_back();
            w_condition.notify_one();
        }
        
        if (msg.length() == 0) return;
        IMessage *iMsg = reinterpret_cast<IMessage *>(const_cast<char *>(msg.c_str()));
        MsgType type = static_cast<MsgType>(iMsg->msgType);
        unsigned int pid = iMsg->pid;

        auto handlerIter = handlers.find(type);
        auto sockIter = pid2sock.find(pid);

        if (handlerIter == handlers.end() || sockIter == pid2sock.end()) {
            printf("find handler[type: %u] or socket[pid: %u] failed!", type, pid);
            return;;
        }
        
        handlerIter->second->HandleMessage(iMsg, sockIter->second);
    }
    
}