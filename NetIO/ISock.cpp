#include "ISock.h"
#include <string.h>
namespace NetIO {

    const int Socket::maxBufSize = 512;

    SockAddr::SockAddr(int type, std::string addr, uint16_t port) {
        memset(&addr_, 0, sizeof(addr_));
        SetType(type);
        SetAddr(addr);
        SetPort(port);
    }

    SockAddr::SockAddr() {
        memset(&addr_, 0, sizeof(addr_));
    }

    SockAddr::SockAddr(sockaddr_in addr) {
        addr_ = addr;
    }

    Socket::Socket() {
        state_ = UNINITIAL;
        if((socketFd_ = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
            printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);
            return;
        }
        state_ = CLOSED;
        remoteAddr_.reset();
    }

    Socket::Socket(int socketFd, SocketState state, const SockAddr& addr) : socketFd_(socketFd), state_(state) {
        remoteAddr_.reset(new SockAddr(addr));
    }

    bool Socket::Send(const char *buf, int size) {
        if (state_ != CONNECTED) {
            printf("Socket State expected is connected.\n ");
            return false;
        }
        if (::send(socketFd_, buf, size, MSG_NOSIGNAL) <= 0) {
            printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
            return false;
        }
        return true;
    }
    
    bool Socket::Send(std::string & s) {
        return Send(s.c_str(), s.length());
    }

    int Socket::Recv(char *buf, int max_len) {
        if (state_ == CONNECTED) {
            int n = ::recv(socketFd_, buf, max_len, 0);
            if (n <= 0) {
                printf("recv socket error: %s(errno: %d)\n", strerror(errno), errno);
                state_ = CLOSED;
                close(socketFd_);
            }
            return n;
        }
        printf("Socket State expected is connected.\n");
        return 0;
    }

    std::string Socket::Recv() {
        char recvBuf[maxBufSize];
        int n = Recv(recvBuf, maxBufSize);
        printf("recv len: %d\n", n);
        return std::move(std::string(recvBuf, n));
    }

    bool Socket::Bind(const SockAddr & addr) {
        if (state_ != CLOSED) {
            printf("Socket State expected is initialed and closed.\n ");
            return false;
        }
        if (::bind(socketFd_, (sockaddr* ) &addr, sizeof(addr)) == -1) {
            printf("bind socket error: %s(errno: %d)\n", strerror(errno), errno);
            return false;
        }
        return true;
    }

    bool Socket::Listen(int backlog) {
        if (state_ != CLOSED) {
            printf("Socket State expected is initialed and closed.\n ");
            return false;
        }

        if (::listen(socketFd_, backlog) < 0) {
            printf("bind socket error: %s(errno: %d)\n", strerror(errno), errno);
            return false;
        }
        state_ = LISTENING;
        return true; 
    }

    bool Socket::Connect(SockAddr & addr) {
        if (state_ != CLOSED) {
            printf("Socket State expected is initialed and closed.\n ");
            return false;
        }
        if (::connect(socketFd_, (sockaddr*) addr.GetAddrIn(), sizeof(sockaddr_in)) < 0) {
            printf("connect error: %s(errno: %d)\n",strerror(errno),errno);
            return false;
        }
        remoteAddr_.reset(new SockAddr(addr));
        state_ = CONNECTED;
        return true;
    }


    std::shared_ptr<Socket> Socket::Accept() {
        if (state_ != LISTENING) {
            printf("Socket State expected is listenning.\n ");
            return nullptr;
        }
        
        int client_socketfd;
        sockaddr_in remoteAddr;
        socklen_t len = 0;
        if((client_socketfd = ::accept(socketFd_, (sockaddr *)&remoteAddr, &len)) < 0) {
            printf("accept socket error: %s(errno: %d)",strerror(errno),errno);
            return nullptr;
        }
        std::shared_ptr<Socket> rsock(new Socket(client_socketfd, CONNECTED, remoteAddr));
        return rsock;
    }

}