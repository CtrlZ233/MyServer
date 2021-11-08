#ifndef UTILS_H_
#define UTILS_H_
#include <memory>
#include "ISock.h"
namespace Utils {

class ConnectionNode {
public:
    ConnectionNode(std::shared_ptr<ISock::Socket>, std::shared_ptr<ISock::Socket>);
    // 服务器端发送给客户端
    bool send(std::string);
    std::string recv();


private:
    // 接收到后更新时间戳，并调整连接队列的优先级
    void update();

private:
    std::weak_ptr<ISock::Socket> s_socket_;
    std::weak_ptr<ISock::Socket> c_socket_;
    int taskID_;
    int timePlant_;

};

class ConnectionManager {

public:

private: 
    
    
};

}


#endif