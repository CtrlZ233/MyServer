#include <netinet/in.h>
#include <arpa/inet.h>
#include<unistd.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include "ISock.h"
using namespace ISock;
const int BUFSIZE = 512;
const char* SERVER_ADDR  = "127.0.0.1";
const int SERVER_PORT = 8000;
int main() {
    
    std::string sendMsg;

    SockAddr serverAddr(AF_INET, SERVER_ADDR, SERVER_PORT);
    Socket clientSock;
    
    clientSock.connect(serverAddr);
    printf("send msg to server: \n");
    std::cin >> sendMsg;
    clientSock.send(sendMsg);

    std::string recvMsg = clientSock.recv();
    std::cout << "recv message from server: " << recvMsg << std::endl;

}