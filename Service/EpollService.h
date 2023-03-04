#ifndef EPOLL_SERVICE_H_
#define EPOLL_SERVICE_H_

#include <sys/epoll.h>
#include <functional>
#include <thread>
#include <atomic>
#include <map>
#include "Connection.h"

namespace Service {
    class EpollService {
        public:
            static EpollService &Instance();

            void AddConnectionListener(const std::shared_ptr<Connection>&);

            void DeleteConnectionLister(const std::shared_ptr<Connection>&);

            EpollService(const EpollService &other) = delete;

            EpollService operator = (const EpollService *other) = delete;

        private:
            EpollService(unsigned int fdSize, std::function<void(std::string &)> handleMessageFunc);

            ~EpollService();
        private:

            const static int MAX_FD_SIZE = 1000;
            int epollFd;
            std::function<void(std::string &)> handleMessageFunc;
            std::atomic<bool> isShutdown;
            std::thread th;
            std::map<int, std::shared_ptr<Connection>> connections;
            std::mutex RWLock;
    };
}

#endif
