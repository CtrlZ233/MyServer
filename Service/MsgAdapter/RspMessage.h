#ifndef RSP_MESSAGE_H_
#define RSP_MESSAGE_H_

#include <bits/types.h>
namespace MessageAdapter {

#pragma pack(1)
    struct RspMessage {
        __uint8_t statusCode;
        __uint8_t msgType;
        __uint32_t pid;
    };

    struct ConnectRspMessage : public RspMessage {
        __uint32_t allocPid;
    };

    struct RegisterRspMessage : public  RspMessage {
    };
#pragma pack()


}


#endif