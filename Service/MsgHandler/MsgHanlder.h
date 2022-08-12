#ifndef MSG_HANDLER_H_
#define MSG_HANDLER_H_

#include <memory>
#include "ReqMessage.h"
#include "ISock.h"

namespace MessageHandler {
    using namespace MessageAdapter;
    using ISock::Socket;
    class MsgHandler {

    public:
        virtual void HandleMessage(ReqMessage *msg, std::shared_ptr<Socket> psock) = 0;
    };
}


#endif