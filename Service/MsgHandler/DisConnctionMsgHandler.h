//
// Created by ctrlz on 23-1-18.
//

#ifndef MYSERVER_DISCONNCTIONMSGHANDLER_H
#define MYSERVER_DISCONNCTIONMSGHANDLER_H

#include "MsgHanlder.h"

namespace MessageHandler {
    class DisConnctionMsgHandler : public MsgHandler {
        public:
            virtual void HandleMessage(ReqMessage *msg, std::shared_ptr<Service::Connection> connection);
    };
}




#endif //MYSERVER_DISCONNCTIONMSGHANDLER_H
