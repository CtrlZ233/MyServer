//
// Created by ctrlz on 23-1-17.
//

#ifndef MYSERVER_MSGENCODER_H
#define MYSERVER_MSGENCODER_H

#include "ReqMessage.h"
#include "RspMessage.h"

namespace MessageAdapter {
    class MsgEncoder {
        public:
            static std::string EncodeDisConnectionReq(unsigned int pid);

            static std::string EncodeConnectionRsp(unsigned int pid);
    };
}




#endif //MYSERVER_MSGENCODER_H
