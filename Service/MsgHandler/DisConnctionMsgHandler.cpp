//
// Created by ctrlz on 23-1-18.
//

#include "DisConnctionMsgHandler.h"
#include "MsgDispatcher.h"
#include "EpollService.h"

namespace MessageHandler {
    void DisConnctionMsgHandler::HandleMessage(ReqMessage *msg, std::shared_ptr<Service::Connection> connection) {
        printf("disconnection req, connection count num: %ld\n", connection.use_count());
        unsigned int pid = msg->pid;
        Service::EpollService::Instance().DeleteConnectionLister(connection);
        MsgDispatcher::Instance().DeRegisterConnection(pid);
    }

    static bool registerRet = MsgDispatcher::Instance().RegisterHandler(MsgType::DISCONNECTION, new DisConnctionMsgHandler());
}