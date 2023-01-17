#include <netinet/in.h>
#include <thread>
#include <iostream>
#include "ISock.h"
#include "ThreadPool.h"
#include "LOG.h"
#include "LOGDefines.h"
#include "Timer.h"
#include "MsgDispatcher.h"
#include "PidAllocator.h"
#include "RspMessage.h"
#include "Connection.h"
#include "EpollService.h"

using namespace NetIO;
using namespace Service;
// Server打开8000监听端口->遇到连接请求，分配新的socket与客户端通信->继续监听
const int BUFSIZE = 512;
const char* SERVER_ADDR  = "127.0.0.1";
const int SERVER_PORT = 8080;
const int BACKLOG = 10;

Timer::Timer timer;

ThreadUtils::ThreadPool pool(10);

using namespace MessageAdapter;
void MsgBuilder(ConnectRspMessage &msg, unsigned int pid) {
    msg.msgType = CONNECTION;
    msg.statusCode = OK;
    msg.pid = 0;
    msg.allocPid = pid;
}

void Serve(std::shared_ptr<Socket> psock) { 
    unsigned int pid = Utils::PidAlloc();
    ConnectRspMessage msg;
    MsgBuilder(msg, pid);
    auto connection = std::make_shared<Connection>(psock);
    MessageHandler::MsgDispatcher::Instance().RegisterConnection(pid, connection);
    Service::EpollService::Instance().AddConnectionListener(connection);

    psock->Send(reinterpret_cast<const char *> (&msg), sizeof(msg));
    while (psock->IsConnected()) {
        std::string recvMsg = psock->Recv();
        std::cout << "recv message from client: " << recvMsg << std::endl;
        if (recvMsg.empty()) {
            continue;
        }
        MessageHandler::MsgDispatcher::Instance().GenerateMessage(recvMsg);
    }
    MessageHandler::MsgDispatcher::Instance().DeRegisterConnection(pid);
}

void LogBackEnd() {
    GETLOG.WriteFile();
}

void HandleMessage() {
    MessageHandler::MsgDispatcher::Instance().HandleMessage();
}


int main() {
    
    sockaddr_in m_addr;
    Socket serverSocket;

    SockAddr serverAddr(AF_INET, SERVER_ADDR, SERVER_PORT);
    serverSocket.Bind(serverAddr);

    int backlog = 10;
    
    int msgHandlerNum = 3;

    for (int i = 0; i < msgHandlerNum; ++i) {
        pool.AddTask(HandleMessage);
    }
    // 启用新的线程用于定时器计数
    std::thread th(&Timer::Timer::Start, &timer, 10000);


    serverSocket.Listen(3);
    int accept_num = 100;
    pool.init();
    pool.AddTask(LogBackEnd);
    std::cout << "success" << std::endl;
    while(accept_num--) {
        auto psock = serverSocket.Accept();
        pool.AddTask(Serve, psock);
    }
    // todo: 需要等待所有任务执行完 
    GETLOG.ShutDown();
    th.join();
}