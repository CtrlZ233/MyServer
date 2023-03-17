#include "RegisterMsgHandler.h"
#include "ReqMessage.h"
#include "MsgDefine.h"
#include "MsgDispatcher.h"

#include "DBOperator.h"
#include "UserInfoTable.h"
#include "MsgEncoder.h"
namespace MessageHandler {
    using namespace MessageAdapter;
    using DBAdapter::TableOperator;
    using DBAdapter::UserInfoTableRecord;
    using DBAdapter::UserInfoKey;


    void RegisterMsgHandler::HandleMessage(ReqMessage *msg, std::shared_ptr<Service::Connection> connection) {
        auto *registerMsg = reinterpret_cast<RegisterReqMessage *>(msg);
        if (registerMsg->msgType != REGISTER_REQ) {
            printf("wrong messageType:[%u]\n", registerMsg->msgType);
            return;
        }
        printf("username: %s\n", registerMsg->username);
        printf("passwd: %s\n", registerMsg->passwd);
        std::string name = std::string(registerMsg->username);
        std::string passwd = std::string(registerMsg->passwd);
        ResponseCode code;
        if (TableOperator<UserInfoTableRecord>::QueryRecord(UserInfoKey(std::string(registerMsg->username)))) {
            printf("user exist!\n");
            code = REQ_FAILED;
        } else {
            auto record = std::make_shared<UserInfoTableRecord>(name, passwd);
            if (!TableOperator<UserInfoTableRecord>::AddRecord(record)) {
                printf("register failed!\n");
                code = REQ_FAILED;
            } else {
                printf("register success!\n");
                code = OK;
            }
        }
        auto rsp_msg = MsgEncoder::EncodeRegisterRsp(registerMsg->pid, code);
        connection->Send(rsp_msg);
    }

    static bool registerRet = MsgDispatcher::Instance().RegisterHandler(MsgType::REGISTER_REQ, new RegisterMsgHandler());
}