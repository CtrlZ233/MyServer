#ifndef I_MESSAGE_H_
#define I_MESSAGE_H_

#include <bits/types.h>

namespace MessageAdapter {

#pragma pack(1)
    struct IMessage {
        __uint8_t msgType;
        __uint32_t pid;
    };
}

#pragma pack()

#endif