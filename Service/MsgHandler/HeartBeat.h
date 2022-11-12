#ifndef HEART_BEAT_H_
#define HEART_BEAT_H_

#include "Timer.h"
#include "ISock.h"

namespace MessageHandler {
    using namespace Timer;
    using namespace NetIO;
    class Connection {
        public:
            Connection();

            virtual void HandleTimeOut();

            void Send();

            void KeepAlive();

        private:
            unsigned int pid;
            std::shared_ptr<Socket> sock;
            WeakTimerNodePtr sendHeartBeat;
            WeakTimerNodePtr timeOutHandler;

            // 每秒发送一次心跳
            const static unsigned HEARTBEAT_INTERVAL = 100;
    };
    
}

#endif