//
// Created by ctrlz on 23-1-17.
//

#ifndef MYSERVER_MSGENCODER_H
#define MYSERVER_MSGENCODER_H

#include "ReqMessage.h"
#include "RspMessage.h"
#include "MsgDefine.h"

namespace MessageAdapter {
    class MsgEncoder {
        public:
            static std::string EncodeDisConnectionReq(unsigned int pid);

            static std::string EncodeConnectionRsp(unsigned int pid);

            static void EncodeRegisterRsp(RegisterRspMessage &msg, unsigned int pid, ResponseCode code);

        private:
            static void EncodeRsp(RspMessage &msg, unsigned int pid, ResponseCode code, MsgType type);
    };
}




#endif //MYSERVER_MSGENCODER_H
