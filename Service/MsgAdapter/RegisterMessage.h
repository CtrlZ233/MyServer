#ifndef REGISTER_MESSAGE_H_
#define REGISTER_MESSAGE_H_

#include "IMessage.h"

namespace MessageAdapter {
const static int USERNAME_MAX_LEN = 32;
const static int PASSWORD_MAX_LEN = 16;

#pragma pack(1)
    struct RegisterMessage : public IMessage {
        char username[USERNAME_MAX_LEN];
        char passwd[PASSWORD_MAX_LEN];
    };
}

#pragma pack()



#endif