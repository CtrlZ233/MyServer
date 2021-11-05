#ifndef LOG_H_
#define LOG_H_
#include <fstream>
#include <string>
#include <mutex>
#include <condition_variable>
#include "SafeVector.h"

// todo:需要重载 << 运算符以实现输入流模式
namespace Utils{

class Log {

private:
    struct LogBuffer {
        LogBuffer() {
            buffer_.reserve(maxSize);  
        }

        size_t size() { 
            return buffer_.size();
        }
        
        void Append(const std::string & s) {
            buffer_.push_back(s);
        }


        void Swap(LogBuffer* buffer) {
            buffer_.swap(buffer->buffer_);
        }

        bool empty() {
            return 0 == buffer_.size();
        }

        std::string getString(size_t i) {
            return buffer_[i];
        }

        void clear() {
            buffer_.clear();
        }

        SafeContainer::SafeVector<std::string> buffer_;
        
    };

public:
    explicit Log(std::string logDir = "./log/", int maxWaitSeconds = 3);
    void WriteFile();
    void Append(const std::string & s, const std::string & fileName, const std::string & line, const std::string functionName);
    void ShutDown();
    virtual ~Log();

private:

    
    void WriteFile(std::shared_ptr<LogBuffer> pBuffer);

private:
    static const int maxSize;
    std::string logFilePath_;
    const int maxWaitSeconds_;
    std::vector<LogBuffer *> bufferVec_;
    std::shared_ptr<LogBuffer> currentBuffer_;
    std::shared_ptr<LogBuffer> nextBuffer_;
    std::ofstream fd_;    // LOG文件的文件描述符
    std::mutex currentBufferMutex_;   // 当前push的buffer的mutex，用于生产者之间同步
    std::mutex nextBufferMutex_;    // next buffer的mutex，用于生产者和消费者同步
    std::condition_variable conditionLock_;
    std::mutex ConditionMutex_;     // 给条件变量的工具锁
    std::mutex FileMutex_ ;          // 给写文件使用
    bool isShutDown_;
};


}


#endif