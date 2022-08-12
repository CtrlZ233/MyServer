#include "MsgDispatcher.h"
#include "ReqMessage.h"
#include "PidAllocator.h"

namespace MessageHandler {
    using MessageAdapter::ReqMessage;
    MsgDispatcher &MsgDispatcher::Instance() {
        static MsgDispatcher instance;
        return instance;
    }

    bool MsgDispatcher::RegisterHandler(MsgType type, MsgHandler *handler) {
        printf("this is regi\n");
        if (handlers.find(type) != handlers.end()) {
            return false;
        }
        handlers[type] = handler;
        return true;
    }

    bool MsgDispatcher::RegistSocket(unsigned int pid, std::shared_ptr<Socket> psock) {
        std::unique_lock<std::mutex> lock(pidLock);
        if (pid2sock.find(pid) != pid2sock.end()) {
            return false;
        }
        pid2sock[pid] = psock;
        return true;
    }

    bool MsgDispatcher::DeRegistSocket(unsigned int pid) {
        {
            std::unique_lock<std::mutex> lock(pidLock);
            auto iter = pid2sock.find(pid);
            if (iter == pid2sock.end()) {
                return false;
            }
            pid2sock.erase(iter);
        }
        Utils::PidDealloc(pid);
        return true;
    }

    void MsgDispatcher::GenerateMessgae(std::string &msg) {
        std::unique_lock<std::mutex> lock(RWLock);
        while (msgPool.size() == MAX_MESSAGE_NUM) {
            w_condition.wait(lock);
        }
        msgPool.push_back(msg);
        r_condition.notify_one();
    }

    void MsgDispatcher::HandleMessage() {
        while (true) {
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
            
            if (msg.length() == 0){
                printf("empty message!\n");
                continue;;
            }
            ReqMessage *iMsg = reinterpret_cast<ReqMessage *>(const_cast<char *>(msg.c_str()));
            MsgType type = static_cast<MsgType>(iMsg->msgType);
            unsigned int pid = iMsg->pid;
            auto sockIter = pid2sock.end();
            auto handlerIter = handlers.find(type);
            std::shared_ptr<Socket> psock = nullptr;
            {
                std::unique_lock<std::mutex> lock(pidLock);
                auto sockIter = pid2sock.find(pid);
                // printf("handles size: %u, sockets size: %u\n", handlers.size(), pid2sock.size());
                if (handlerIter == handlers.end() || sockIter == pid2sock.end()) {
                    printf("find handler[type: %u] or socket[pid: %u] failed!\n", type, pid);
                    continue;
                }
                psock = sockIter->second;
            }
            
            if (psock == nullptr) {
                continue;
            }

            handlerIter->second->HandleMessage(iMsg, psock);
        }
    }

    MsgDispatcher::~MsgDispatcher() {
        for (auto elem: handlers) {
            delete elem.second;
        }
        handlers.clear();
    }
    
        
    
}