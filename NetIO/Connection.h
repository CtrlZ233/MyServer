//
// Created by ctrlz on 23-1-16.
//

#ifndef MYSERVER_CONNECTION_H
#define MYSERVER_CONNECTION_H

#include "ITimerListener.h"
#include "ISock.h"
namespace NetIO {
    class Connection : Timer::ITimerListener {
        public:

            Connection(std::shared_ptr<Socket> sock);

            virtual void HandleTimeOut();

            std::shared_ptr<Socket> GetSocket() { return sock; }

            void Send(std::string &s);

            std::string Recv();



        private:
            std::shared_ptr<Socket> sock;
            static const int BEAT_INTERVAL = 100;
    };
}




#endif //MYSERVER_CONNECTION_H
