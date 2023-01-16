#ifndef MSG_HANDLER_H_
#define MSG_HANDLER_H_

#include <memory>
#include "ReqMessage.h"
#include "ISock.h"
#include "Connection.h"

namespace MessageHandler {
    using namespace MessageAdapter;
    using NetIO::Socket;
    class MsgHandler {

    public:
        virtual void HandleMessage(ReqMessage *msg, std::shared_ptr<NetIO::Connection> connection) = 0;
    };
}


#endif