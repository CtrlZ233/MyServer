//
// Created by ctrlz on 23-1-16.
//

#include "Connection.h"
#include "EpollService.h"

namespace NetIO {
    Connection::Connection(std::shared_ptr<Socket> sock) : ITimerListener(BEAT_INTERVAL) {
        this->sock = std::move(sock);
        this->Start();
    }

    void Connection::HandleTimeOut() {

    }

    void Connection::Send(std::string &s) {
        sock->Send(s);
    }

    std::string Connection::Recv() {
        return sock->Recv();
    }
}