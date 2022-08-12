#ifndef I_MESSAGE_H_
#define I_MESSAGE_H_

#include <bits/types.h>

namespace MessageAdapter {

#pragma pack(1)
    struct ReqMessage {
        __uint8_t msgType;
        __uint32_t pid;
    };
#pragma pack()


const static int USERNAME_MAX_LEN = 32;
const static int PASSWORD_MAX_LEN = 16;

#pragma pack(1)
    struct RegisterReqMessage : public ReqMessage {
        char username[USERNAME_MAX_LEN];
        char passwd[PASSWORD_MAX_LEN];
    };
#pragma pack()

}




#endif