#include "EpollService.h"
#include <thread>

namespace NetIO {
    EpollService::EpollService(unsigned int maxFdSize, std::function<void(std::string)> func)
                                : handleMessageFunc(func), isShutdown(false) {
        epollFd = epoll_create(maxFdSize);
        th = std::thread([=]() {
            epoll_event events[maxFdSize];
            while (!this->isShutdown.load()) {
                int nfds = epoll_wait(epollFd, events, maxFdSize, 500);
                for (int i = 0; i < nfds; ++i) {
                    if (!(events[i].events & EPOLLIN)) {
                        break;
                    }

                    std::shared_ptr<Socket> socket;
                    {
                        std::lock_guard<std::mutex> lock(this->RWLock);
                        auto socketIter = this->sockets.find(events[i].data.fd);
                        if (socketIter == this->sockets.end()) {
                            printf("invalid socket fd: %d", events[i].data.fd);
                            continue;
                        }
                        socket = socketIter->second;
                    }
                    
                    std::string msg = socket->Recv();
                    this->handleMessageFunc(msg);
                }
            }
        });
    }

    void EpollService::AddSokcetListener(std::shared_ptr<Socket> sock) {
        {
            std::lock_guard<std::mutex> lock(this->RWLock);
            sockets[sock->socketFd_] = sock;
        }
        epoll_event event;
        event.data.fd = sock->socketFd_;
        event.events = EPOLLIN | EPOLLET;
        epoll_ctl(epollFd, EPOLL_CTL_ADD, sock->socketFd_, &event);
        

    }

    void EpollService::DeleteSocketLister(std::shared_ptr<Socket> sock) {

    }

    EpollService::~EpollService() {
        this->isShutdown.store(true);
        th.join();
    }
    
}