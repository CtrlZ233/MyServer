#ifndef MSG_DISPATCHER_H_
#define MSG_DISPATCHER_H_

#include <map>
#include <mutex>
#include <condition_variable>
#include "PidAllocator.h"
#include "Connection.h"
#include "MsgDefine.h"
#include "MsgHanlder.h"

namespace MessageHandler {
    using namespace Utils;
    using namespace NetIO;
    using Service::Connection;
    using MessageAdapter::MsgType;

    class MsgDispatcher {
    public:
        static MsgDispatcher& Instance();

        [[noreturn]] void HandleMessage();

        void GenerateMessage(const std::string &msg);

        bool RegisterHandler(MsgType type, MsgHandler *);

        bool RegisterConnection(unsigned int pid, std::shared_ptr<Connection> connection);

        bool DeRegisterConnection(unsigned int pid);

        MsgDispatcher(const MsgDispatcher &other) = delete;

        MsgDispatcher operator = (const MsgDispatcher &other) = delete;

    private:
        MsgDispatcher() = default;

        ~MsgDispatcher();

        std::map<unsigned int, std::shared_ptr<Connection>> pid2connection;
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