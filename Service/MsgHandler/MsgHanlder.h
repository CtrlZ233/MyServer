#ifndef MSG_HANDLER_H_
#define MSG_HANDLER_H_

#include "IMessage.h"
#include "ISock.h"
namespace MessageHandler {
    using namespace MessageAdapter;
    using ISock::Socket;
    class MsgHandler {

    public:
        virtual void HandleMessage(IMessage *msg, Socket *psock) = 0;
    };
}


#endif