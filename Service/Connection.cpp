//
// Created by ctrlz on 23-1-16.
//

#include "Connection.h"
#include "MsgDispatcher.h"
#include "MsgEncoder.h"
#include "PidAllocator.h"

namespace Service {
    Connection::Connection(std::shared_ptr<Socket> sock, unsigned int pid) : ITimerListener(BEAT_INTERVAL), pid(pid) {
        this->sock = std::move(sock);
        this->Start();
    }

    void Connection::HandleTimeOut() {
        // 向 dispatch 发送关闭连接的消息
        printf("connection timeout!\n");
        MessageHandler::MsgDispatcher::Instance().GenerateMessage(MessageAdapter::MsgEncoder::EncodeDisConnectionReq(pid));
    }

    void Connection::Send(const char *buf, int size) {
        sock->Send(buf, size);
    }

    std::string Connection::Recv() {
        return sock->Recv();
    }

    Connection::~Connection() noexcept {
        printf("close socket\n");
        close(sock->socketFd_);
        Utils::PidAllocator::Instance().dealloc(pid);
    }
}