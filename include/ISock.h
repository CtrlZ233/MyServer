#ifndef ISOCK_H_
#define ISOCK_H_

#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <unistd.h>
#include <memory>

namespace ISock{


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

    bool send(const char *buf, int size);
    bool send(std::string & s);
    int recv(char *buf, int max_len);
    std::string recv();
    bool bind(const SockAddr& addr);
    bool listen(int backlog);
    bool connect(SockAddr& addr);
    std::shared_ptr<Socket> accept();


    virtual ~ Socket() {
        close(socketFd_);
    }
    

private:
    int socketFd_;
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
        addr_.sin_port = port;
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