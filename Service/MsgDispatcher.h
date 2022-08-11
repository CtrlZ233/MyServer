#ifndef MSG_DISPATCHER_H_
#define MSG_DISPATCHER_H_

#include <map>
#include <mutex>
#include <condition_variable>
#include "PidAllocator.h"
#include "ISock.h"
#include "MsgDefine.h"
#include "MsgHanlder.h"

namespace Service {
    using namespace Utils;
    using namespace ISock;
    using MessageAdapter::MsgType;
    using MessageHandler::MsgHandler;

    class MsgDispatcher {
    public:
        static MsgDispatcher& Instance();

        void HandleMessage();

        void GenerateMessgae(std::string msg);

        static bool RegisterHandler(MsgType type, MsgHandler *);
        
    private:
        MsgDispatcher() {}

        MsgDispatcher(const MsgDispatcher &other) = delete;

        MsgDispatcher operator = (const MsgDispatcher &other) = delete;

        ~MsgDispatcher() {}

        std::map<unsigned int, Socket *> pid2sock;
        static std::map<MsgType, MsgHandler *> handlers;

        const static unsigned int MAX_MESSAGE_NUM = 1000;

        std::vector<std::string> msgPool;
        std::mutex RWLock;
        std::condition_variable r_condition;
        std::condition_variable w_condition;
    };
}

#endif