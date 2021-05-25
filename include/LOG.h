#ifndef LOG_H_
#define LOG_H_
#include <fstream>
#include <string>
#include <mutex>
#include <condition_variable>
#include "SafeVector.h"
namespace Utils{

// 线程安全的单例模式 
// 参考Linux多线程服务端编程一书的单例实现，也可以在普通模式下加锁
template <typename T>
class Singleton {
public:
    static T& GetInstance() {
        pthread_once(&ponce_, &Singleton::init);  // init函数在整个程序运行期间只执行一次
        return *value_;
    }

    ~Singleton() {
        delete value_;
    }

private:
    static void init() {
        value_ = new T();
    }

private:
    static pthread_once_t ponce_;
    static T* value_;

};

template <typename T>
pthread_once_t Singleton<T>::ponce_ = PTHREAD_ONCE_INIT;

template <typename T>
T* Singleton<T>::value_ = nullptr;


class LOG {

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

        SafeContainer::SafeVector<std::string> buffer_;
        
    };

public:
    explicit LOG(std::string filename, int maxWaitSeconds = 3);
    LOG & operator << (const std::string& s);
    void ShutDown();
    virtual ~LOG();

private:
    void Append(const std::string & s);
    void WriteFile();
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