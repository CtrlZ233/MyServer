//
// Created by ctrlz on 23-1-16.
//

#ifndef MYSERVER_CONNECTION_H
#define MYSERVER_CONNECTION_H

#include "ITimerListener.h"
#include "ISock.h"
namespace Service {
    using namespace NetIO;
    class Connection : Timer::ITimerListener {
        public:

            Connection(std::shared_ptr<Socket> sock, unsigned int pid);

            virtual void HandleTimeOut();

            std::shared_ptr<Socket> GetSocket() { return sock; }

            void Send(std::string &s);

            void Send(const char *buf, int size);

            std::string Recv();

            virtual ~Connection();

        private:
            std::shared_ptr<Socket> sock;
            unsigned int pid;
            static const int BEAT_INTERVAL = 1000;
    };
}




#endif //MYSERVER_CONNECTION_H
