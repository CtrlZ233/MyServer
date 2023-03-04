#include "MsgDispatcher.h"

#include <utility>
#include "ReqMessage.h"

namespace MessageHandler {
    using MessageAdapter::ReqMessage;
    MsgDispatcher &MsgDispatcher::Instance() {
        static MsgDispatcher instance;
        return instance;
    }

    bool MsgDispatcher::RegisterHandler(MsgType type, MsgHandler *handler) {
        printf("this is regi, type: %d\n", type);
        if (handlers.find(type) != handlers.end()) {
            return false;
        }
        handlers[type] = handler;
        return true;
    }

    bool MsgDispatcher::RegisterConnection(unsigned int pid, std::shared_ptr<Connection> connection) {
        std::unique_lock<std::mutex> lock(pidLock);
        printf("reg connection pid: %d\n", pid);
        if (pid2connection.find(pid) != pid2connection.end()) {
            return false;
        }
        pid2connection[pid] = std::move(connection);
        return true;
    }

    bool MsgDispatcher::DeRegisterConnection(unsigned int pid) {
        {
            std::unique_lock<std::mutex> lock(pidLock);
            auto iter = pid2connection.find(pid);
            if (iter == pid2connection.end()) {
                return false;
            }
            pid2connection.erase(iter);
        }
        return true;
    }

    void MsgDispatcher::GenerateMessage(const std::string &msg) {
        std::unique_lock<std::mutex> lock(RWLock);
        // bug: 会阻塞 EpollServer的监听线程
        while (msgPool.size() == MAX_MESSAGE_NUM) {
            w_condition.wait(lock);
        }
        msgPool.push_back(msg);
        r_condition.notify_one();
    }

    [[noreturn]] void MsgDispatcher::HandleMessage() {
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
            auto *iMsg = reinterpret_cast<ReqMessage *>(const_cast<char *>(msg.c_str()));
            auto type = static_cast<MsgType>(iMsg->msgType);
            unsigned int pid = iMsg->pid;
            auto handlerIter = handlers.find(type);
            std::shared_ptr<Connection> connection = nullptr;
            {
                std::unique_lock<std::mutex> lock(pidLock);
                auto connectionIter = pid2connection.find(pid);
                // printf("handles size: %u, sockets size: %u\n", handlers.size(), pid2sock.size());
                if (handlerIter == handlers.end() || connectionIter == pid2connection.end()) {
                    printf("find handler[type: %u] or socket[pid: %u] failed!\n", type, pid);
                    continue;
                }
                connection = connectionIter->second;
            }
            
            if (connection == nullptr) {
                continue;
            }


            handlerIter->second->HandleMessage(iMsg, connection);
            printf("[dispatch]connection use count: %ld\n", connection.use_count());
        }
    }

    MsgDispatcher::~MsgDispatcher() {
        for (auto elem: handlers) {
            delete elem.second;
        }
        handlers.clear();
    }
    
        
    
}