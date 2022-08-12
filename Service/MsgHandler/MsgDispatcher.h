#ifndef MSG_DISPATCHER_H_
#define MSG_DISPATCHER_H_

#include <map>
#include <mutex>
#include <condition_variable>
#include "PidAllocator.h"
#include "ISock.h"
#include "MsgDefine.h"
#include "MsgHanlder.h"

namespace MessageHandler {
    using namespace Utils;
    using namespace ISock;
    using MessageAdapter::MsgType;

    class MsgDispatcher {
    public:
        static MsgDispatcher& Instance();

        void HandleMessage();

        void GenerateMessgae(std::string &msg);

        bool RegisterHandler(MsgType type, MsgHandler *);

        bool RegistSocket(unsigned int pid, std::shared_ptr<Socket> psock);

        bool DeRegistSocket(unsigned int pid);

    private:
        MsgDispatcher() {}

        MsgDispatcher(const MsgDispatcher &other) = delete;

        MsgDispatcher operator = (const MsgDispatcher &other) = delete;

        ~MsgDispatcher();

        std::map<unsigned int, std::shared_ptr<Socket>> pid2sock;
        std::map<MsgType, MsgHandler *> handlers;

        const static unsigned int MAX_MESSAGE_NUM = 1000;

        std::vector<std::string> msgPool;
        std::mutex RWLock;
        std::mutex pidLock;
        std::condition_variable r_condition;
        std::condition_variable w_condition;
    };
}

#endif