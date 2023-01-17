//
// Created by ctrlz on 23-1-17.
//

#ifndef MYSERVER_MSGENCODER_H
#define MYSERVER_MSGENCODER_H

#include "ReqMessage.h"
#include "RspMessage.h"

namespace MsgAdapter {
    class MsgEncoder {
        static std::string EncodeDisConnectionReq();

        static std::string EncodeConnectionRsp(unsigned int pid);
    };
}




#endif //MYSERVER_MSGENCODER_H
