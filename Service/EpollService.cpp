#include "EpollService.h"
#include "MsgDispatcher.h"
#include <thread>
#include <utility>

namespace Service {
    EpollService &EpollService::Instance() {
        using MessageHandler::MsgDispatcher;
        static EpollService instance(MAX_FD_SIZE,
                                     std::bind(&MsgDispatcher::GenerateMessage, &MsgDispatcher::Instance(), std::placeholders::_1));
        return instance;
    }

    EpollService::EpollService(unsigned int maxFdSize, std::function<void(std::string &)> func)
                                : handleMessageFunc(std::move(func)), isShutdown(false) {
        epollFd = epoll_create(maxFdSize);
        th = std::thread([=]() {
            epoll_event events[maxFdSize];
            while (!this->isShutdown.load()) {
                int nfds = epoll_wait(epollFd, events, maxFdSize, 500);
                for (int i = 0; i < nfds; ++i) {
                    if (!(events[i].events & EPOLLIN)) {
                        break;
                    }

                    std::shared_ptr<Connection> connection;
                    {
                        std::lock_guard<std::mutex> lock(this->RWLock);
                        auto connectionIter = this->connections.find(events[i].data.fd);
                        if (connectionIter == this->connections.end()) {
                            printf("invalid socket fd: %d", events[i].data.fd);
                            continue;
                        }
                        connection = connectionIter->second;
                    }
                    
                    std::string msg = connection->Recv();
                    this->handleMessageFunc(msg);
                }
            }
        });
    }

    void EpollService::AddConnectionListener(std::shared_ptr<Connection> connection) {
        {
            std::lock_guard<std::mutex> lock(this->RWLock);
            connections[connection->GetSocket()->socketFd_] = connection;
        }
        epoll_event event{};
        event.data.fd = connection->GetSocket()->socketFd_;
        event.events = EPOLLIN | EPOLLET;
        epoll_ctl(epollFd, EPOLL_CTL_ADD, connection->GetSocket()->socketFd_, &event);
        

    }

    void EpollService::DeleteConnectionLister(std::shared_ptr<Connection> connection) {
        epoll_event event{};
        event.data.fd = connection->GetSocket()->socketFd_;
        epoll_ctl(epollFd, EPOLL_CTL_DEL, connection->GetSocket()->socketFd_, &event);
    }

    EpollService::~EpollService() {
        this->isShutdown.store(true);
        th.join();
    }

}