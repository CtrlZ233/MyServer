#include "RegisterMsgHandler.h"
#include "ReqMessage.h"
#include "MsgDefine.h"
#include "MsgDispatcher.h"

namespace MessageHandler {
    using namespace MessageAdapter;

    void RegisterMsgHandler::HandleMessage(ReqMessage *msg, std::shared_ptr<Service::Connection> connection) {
        auto *registerMsg = reinterpret_cast<RegisterReqMessage *>(msg);
        if (registerMsg->msgType != REGISTER_REQ) {
            printf("wrong messageType:[%u]\n", registerMsg->msgType);
            return;
        }
        printf("username: %s\n", registerMsg->username);
        printf("passwd: %s\n", registerMsg->passwd);
    }

    static bool registerRet = MsgDispatcher::Instance().RegisterHandler(MsgType::REGISTER_REQ, new RegisterMsgHandler());
}