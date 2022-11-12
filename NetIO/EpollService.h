#ifndef EPOLL_SERVICE_H_
#define EPOLL_SERVICE_H_

#include "ISock.h"

#include <sys/epoll.h>
#include <functional>
#include <thread>
#include <atomic>
#include <map>

namespace NetIO {
    class EpollService {
        public:
            EpollService(unsigned int fdSize, std::function<void(std::string)> handleMessageFunc);

            ~EpollService();

            void AddSokcetListener(std::shared_ptr<Socket>);

            void DeleteSocketLister(std::shared_ptr<Socket>);

        private:
            static void HandleEvent();

        private:
            int epollFd;
            std::function<void(std::string)> handleMessageFunc;
            std::atomic<bool> isShutdown;
            std::thread th;
            std::map<int, std::shared_ptr<Socket>> sockets;
            std::mutex RWLock;
    };
}

#endif
