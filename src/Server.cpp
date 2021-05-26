#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include<unistd.h>
#include <thread>
#include <iostream>
#include <vector>
#include <csignal>
#include "ISock.h"
#include "ThreadPool.h"
#include "LOG.h"
#include "Defines.h"

using namespace ISock;
// Server打开8000监听端口->遇到连接请求，分配新的socket与客户端通信->继续监听
const int BUFSIZE = 512;
const char* SERVER_ADDR  = "127.0.0.1";
const int SERVER_PORT = 8000;
const int BACKLOG = 10;


void Serve(std::shared_ptr<Socket> psock) { 
    Socket* sock = psock.get();
    std::string s = sock->recv();
    std::cout << "recv msg from client: " << s << std::endl;
    // log << "recv msg from client: " << s;
    for (int i = 0; i < 100000; ++i) {
        LOG("recv msg from client: " + s);
    }
    
    sock->send(s);
}

void LogBackEnd() {
    GETLOG.WriteFile();
}

int main() {
    ThreadUtils::ThreadPool pool(3);
    sockaddr_in m_addr;
    Socket serverSocket;

    SockAddr serverAddr(AF_INET, SERVER_ADDR, SERVER_PORT);
    serverSocket.bind(serverAddr);

    int backlog = 10;

    serverSocket.listen(3);
    int accpt_num = 3;
    pool.init();
    pool.AddTask(LogBackEnd);
    while(accpt_num--) {
        auto psock = serverSocket.accept();
        pool.AddTask(Serve, psock);
    }
    // todo: 需要等待所有任务执行完 
    GETLOG.ShutDown();
}