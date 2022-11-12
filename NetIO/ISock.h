#ifndef ISOCK_H_
#define ISOCK_H_

#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <unistd.h>
#include <memory>
#include <mutex>

namespace NetIO {

    class Socket;
    class SockAddr;

    enum SocketState {
        UNINITIAL,
        CLOSED,
        CONNECTED,
        LISTENING
    };

    class Socket{
    public:
        Socket();

        Socket(Socket & s) = delete;

        bool Send(const char *buf, int size);

        bool Send(std::string & s);

        int Recv(char *buf, int max_len);

        std::string Recv();

        bool Bind(const SockAddr& addr);

        bool Listen(int backlog);

        bool Connect(SockAddr& addr);
        
        std::shared_ptr<Socket> Accept();

        bool IsConnected() {
            return state_ == CONNECTED;
        }

        virtual ~Socket() {
            printf("bye bye~\n");
            close(socketFd_);
        }

    public:
        int socketFd_;
        
    private:
        std::shared_ptr<SockAddr> remoteAddr_;
        SocketState state_;
        static const int maxBufSize;

        Socket(int socketFd, SocketState state, const SockAddr& addr);
    };

    class SockAddr{
    public:
        SockAddr(int type, std::string addr, uint16_t port);
        SockAddr();
        SockAddr(sockaddr_in addr);
        void SetType(int type) {
            addr_.sin_family = type;
        }

        void SetAddr(std::string & addr) {
            addr_.sin_addr.s_addr = inet_addr(addr.c_str());
        }

        void SetPort(uint16_t port) {
            addr_.sin_port = htons(port);
        }


        int GetType() const { return addr_.sin_family; }

        std::string GetAddr() const { return std::string(inet_ntoa(addr_.sin_addr)); }

        uint16_t GetPort() const { return addr_.sin_port; }

        sockaddr_in* GetAddrIn() { return &addr_; }

    private:
        sockaddr_in addr_;
    };
}

#endif