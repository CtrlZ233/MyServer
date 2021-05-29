#include <netinet/in.h>
#include <arpa/inet.h>
#include<unistd.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <thread>
#include <signal.h>
#include "ISock.h"
#include "LOG.h"
#include "Defines.h"
using namespace ISock;
const int BUFSIZE = 512;
const char* SERVER_ADDR  = "127.0.0.1";
const int SERVER_PORT = 8000;

void LogBackEnd() {
    GETLOG.WriteFile();
}

void handler(int sig) {
    GETLOG.ShutDown();
    exit(sig);
}

int main() {
    signal(SIGINT, handler); 
    std::string sendMsg;
    std::thread th(LogBackEnd);
    SockAddr serverAddr(AF_INET, SERVER_ADDR, SERVER_PORT);
    Socket clientSock;
    clientSock.connect(serverAddr);
    printf("send msg to server: \n");
    std::cin >> sendMsg;
    clientSock.send(sendMsg);
    while (1) {
        std::string recvMsg = clientSock.recv();
        std::cout << "recv message from server: " << recvMsg << std::endl;
        LOG("recv message from server: " + recvMsg);
    }
    th.join();

}