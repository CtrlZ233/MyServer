#ifndef REGISTER_MSG_HANDLER_H_
#define REGISTER_MSG_HANDLER_H_

#include "MsgHanlder.h"

namespace MessageHandler {
    class RegisterMsgHandler : public MsgHandler {
    public:
        virtual void HandleMessage(ReqMessage *msg, std::shared_ptr<NetIO::Connection> connection);
    };
}


#endif