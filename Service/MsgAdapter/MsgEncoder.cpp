//
// Created by ctrlz on 23-1-17.
//

#include "MsgEncoder.h"
#include "MsgDefine.h"

namespace MessageAdapter {
    std::string MsgEncoder::EncodeDisConnectionReq(unsigned int pid) {
        ReqMessage msg{MsgType::DISCONNECTION, pid};
        return std::string{reinterpret_cast<const char *>(&msg)};
    }

    std::string MsgEncoder::EncodeConnectionRsp(unsigned int pid) {
        ConnectRspMessage msg{};
        msg.msgType = MsgType::CONNECTION;
        msg.statusCode = OK;
        msg.pid = 0;
        msg.allocPid = pid;
        return std::string{reinterpret_cast<const char *>(&msg)};
    }

    void MsgEncoder::EncodeRsp(RspMessage *msg, unsigned int pid, ResponseCode code, MsgType type) {
        msg->msgType = type;
        msg->statusCode = code;
        msg->pid = pid;
    }

    std::string MsgEncoder::EncodeRegisterRsp(unsigned int pid, ResponseCode code) {
        RegisterRspMessage msg{};
        EncodeRsp(reinterpret_cast<RspMessage *>(&msg), pid, code, MsgType::REGISTER_REQ);
        return std::string{reinterpret_cast<const char *>(&msg)};
    }

}