#include "RegisterMsgHandler.h"
#include "ReqMessage.h"
#include "MsgDefine.h"
#include "MsgDispatcher.h"

namespace MessageHandler {
    using namespace MessageAdapter;

    void RegisterMsgHandler::HandleMessage(ReqMessage *msg, std::shared_ptr<Connection> connection) {
        RegisterReqMessage *registerMsg = reinterpret_cast<RegisterReqMessage *>(msg);
        if (registerMsg->msgType != REGISTER_REQ) {
            printf("wrong messageType:[%u]\n", registerMsg->msgType);
            return;
        }
        printf("username: %s\n", registerMsg->username);
        printf("passwd: %s\n", registerMsg->passwd);
    }

    static bool registerRet = MsgDispatcher::Instance().RegisterHandler(REGISTER_REQ, new RegisterMsgHandler());
}