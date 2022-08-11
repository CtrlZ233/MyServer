#include "RegisterMsgHandler.h"
#include "RegisterMessage.h"
#include "MsgDefine.h"

namespace MessageHandler {
    using namespace MessageAdapter;
    void RegisterMsgHandler::HandleMessage(IMessage *msg, Socket *psock) {
        RegisterMessage *registerMsg = reinterpret_cast<RegisterMessage *>(msg);
        if (registerMsg->msgType != REGISTER_REQ) {
            printf("wrong messageType:[%u]\n", registerMsg->msgType);
            return;
        }
        printf("username: %s\n", registerMsg->username);
        printf("passwd: %s", registerMsg->passwd);
    }
}