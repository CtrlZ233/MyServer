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
#include "LOGDefines.h"
#include "Timer.h"

using namespace NetIO;
// Server打开8000监听端口->遇到连接请求，分配新的socket与客户端通信->继续监听
const int BUFSIZE = 512;
const char* SERVER_ADDR  = "127.0.0.1";
const int SERVER_PORT = 8080;
const int BACKLOG = 10;

Timer::Timer timer;

void Send(std::shared_ptr<Socket> psock, std::string s) {
    std::cout << "sending" << std::endl;
    if (!psock->send(s)) {
        std::cout << "send failed." << std::endl;
    }
} 

void Serve(std::shared_ptr<Socket> psock) { 
    Socket* sock = psock.get();
    {
        std::string recvMsg = sock->recv();
        std::cout << "recv message from client: " << recvMsg << std::endl;
    }

    std::function<void()> func = std::bind(Send, psock, "testssss");
    // 每秒发送一次信息给客户端，持续五十次。
    auto pnode = timer.AddTimer(func, 100, 50);
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

    // 启用新的线程用于定时器计数
    std::thread th(&Timer::Timer::Start, &timer, 10000);

    serverSocket.listen(3);
    int accpt_num = 100;
    pool.init();
    pool.AddTask(LogBackEnd);
    std::cout << "success" << std::endl;
    while(accpt_num--) {
        auto psock = serverSocket.accept();
        pool.AddTask(Serve, psock);
    }
    // todo: 需要等待所有任务执行完 
    GETLOG.ShutDown();
    th.join();
}